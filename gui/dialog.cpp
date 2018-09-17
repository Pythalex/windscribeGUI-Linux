#include <QtWidgets>

#include "dialog.hpp"

Dialog::Dialog()
{

    // get server locations
    debug("Read locations");
    locations = parse_locations(read_locations());

    // Init gui
    debug("Creating GUI");

    createMenu();
    createGridGroupBox();
    createHorizontalGroupBox();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(horizontalGroupBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Windscribe"));

    debug("Cache updated asked.");

    // Init cache
    forceCacheUpdate = true;
    forceflags = CACHE_STATUS | CACHE_FIREWALL | CACHE_ACCOUNT;
    state = new State();

    debug("Creating updater thread");

    // Create updater thread
    updaterThread = std::thread(thread_updater_routine, this);

    debug("Wait for cache init");

    // wait for cache init
    while(forceCacheUpdate) std::this_thread::sleep_for(std::chrono::milliseconds(100));

    debug("Initializing gui update timer");

    // Create timer used for gui update
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateEverything()));

    debug("Update every widgets.");

    updateEverything();

    // disconnect button is greyed out if the user is already disconnected
    // no need to update it everytime (it is updated when the buttons are clicked)
    if (!state->connected)
        buttonDisconnect->setEnabled(false);

    debug("Set timer for GUI update.");

}

Dialog::~Dialog(){
    stop_thread = true;
    updaterThread.join();
}

void Dialog::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&Menu"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
}

void Dialog::createHorizontalGroupBox()
{
    horizontalGroupBox = new QGroupBox();
    QHBoxLayout *layout = new QHBoxLayout;

    horizontalGroupBox->setLayout(layout);
}

void Dialog::createGridGroupBox()
{
    gridGroupBox = new QGroupBox();
    QGridLayout *layout = new QGridLayout;

    locationsList = new QComboBox();
    for (uint i = 0; i < locations.size(); i++){
        Location l = locations[i];
        std::wstring str = L"\u1F1E9";
        locationsList->addItem(QString::fromStdString(l.country + " - " + l.label + (l.pro ? " *PRO*" : "")));
    }

    connectionLabel = new QLabel("N/A");
    IPLabel = new QLabel("External IP : N/A");

    buttonConnect = new QPushButton("Connect");
    connect(buttonConnect, SIGNAL(clicked(bool)), this, SLOT(buttonConnectClicked()));

    buttonDisconnect = new QPushButton("Disconnect");
    connect(buttonDisconnect, SIGNAL(clicked(bool)), this, SLOT(buttonDisconnectClicked()));

    movie = new QMovie("resources/loading.gif");

    if (!movie->isValid()){
        debug("Loading gif wasn't loaded.");
    }

    loadingGif = new QLabel(this);
    loadingGif->setMovie(movie);
    // hidden by default
    loadingGif->setVisible(false);
    movie->start();

    layout->addWidget(locationsList, 0, 0);
    layout->addWidget(connectionLabel, 0, 1);
    layout->addWidget(loadingGif, 0, 2);
    layout->addWidget(IPLabel, 1, 0);
    layout->addWidget(buttonConnect, 1, 1);
    layout->addWidget(buttonDisconnect, 1, 2);
    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 20);

    gridGroupBox->setLayout(layout);
}

void Dialog::updateEverything(bool useCache){

    // update all cache if asked or necessary
    if (!useCache) {
        forceCacheUpdate = true;
        forceflags = CACHE_STATUS | CACHE_FIREWALL | CACHE_ACCOUNT;
    }

    updateConnectionLabel(true);
    updateIP(true);

    timer->start(period);
}

void Dialog::updateConnectionLabel(bool useCache){

    if (!useCache) {
        forceCacheUpdate = true;
        forceflags = CACHE_STATUS;
    }

    connectionLabel->setText(QString::fromStdString(state->connected ? ": Connected" : ": Disconnected"));
}

void Dialog::updateIP(bool useCache){

    if (!useCache) {
        forceCacheUpdate = true;
        forceflags = CACHE_STATUS;
    }

    IPLabel->setText(QString::fromStdString("External IP : " + state->IP));
}

void Dialog::updateLastUpdateValue(){
    time_t current = time(nullptr);
    lastUpdate += difftime(current, lastUpdateTimet);
    lastUpdateTimet = current;
}

void Dialog::updateCache(uint flags){

    debug("Updating cache ...");

    bool status = (flags & 1) == 1;
    bool firewall = (flags & 2) == 2;
    bool account = (flags & 4) == 4;

    State s = *state;

    if (status) {
        std::string status_str = read_windscribe_status();

        if (status_str == "Service communication error" || status_str == ""){
            debug("Cache update ended abnormally (returned %s).", status_str.c_str());
            return;
        }

        s.started = parse_started(status_str);
        s.connected = parse_connected(status_str);
        s.IP = parse_IP(status_str);
    }
    if (firewall) {

        std::string firewall_str = read_firewall();

        if (firewall_str == "Service communication error" || firewall_str == ""){
            debug("Cache update ended abnormally (returned %s).", firewall_str.c_str());
            return;
        }

        s.firewall = parse_firewall(firewall_str);
    }
    if (account) {

        std::string account_str = read_account_details();

        if (account_str == "Service communication error" || account_str == ""){
            debug("Cache update ended abnormally (returned %s).", account_str.c_str());
            return;
        }

        s.username = parse_account_username(account_str);
    }

    *state = s;

    resetTimer();
}

bool Dialog::cacheTooOld(){
    return lastUpdate > maxCacheAge;
}void displayLoadingCircle();

void hideLoadingCircle();

void Dialog::resetTimer(){
    lastUpdate = 0;
    time(&lastUpdateTimet); // reset time_t
}

void Dialog::thread_updater_routine(Dialog *instance){

    debug("Updater : Starting updater thread.");

    while (!instance->stop_thread) {

        debug("Updater : Waiting...");

        // First update
        instance->updateLastUpdateValue();
        /*
         * While the cache is recent enough, and nobody needs an urgent update, wait.
         * If you need to stop the thread, exit.
         * If the program is currently talking to windscribe, keep waiting.
         */
        while ( ( (!instance->cacheTooOld() && !instance->forceCacheUpdate ) || instance->talkingToWindscribe)
               && !instance->stop_thread)
        {
            instance->updateLastUpdateValue();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        void displayLoadingCircle();

        void hideLoadingCircle();
        debug("Updater : thread exited waiting loop.");

        // If you need to stop, don't update
        if (instance->stop_thread)
            break;

        instance->updating = true;
        // Update the desired cache if forced or all cache if time out
        if (instance->cacheTooOld())
            instance->updateCache(instance->CACHE_STATUS | instance->CACHE_FIREWALL | instance->CACHE_ACCOUNT);
        else
            instance->updateCache(instance->forceflags);
        instance->updating = false;

        // Reset force flags
        instance->forceCacheUpdate = false;
        instance->forceflags = 0;

    }

    debug("Updater : Thread exiting.");
}

void Dialog::buttonConnectClicked(){

    // protection check
    if (!state->started){
        /* TODO: Display a pop up void displayLoadingCircle();

    void hideLoadingCircle();window or whathever to inform the user that
           windscribe must be started */
        debug("Windscribe is not started.");
        return;
    }

    // warn user of pending operations
    displayLoadingCircle();

    // Stop the updater thread
    talkingToWindscribe = true;

    // Grey the button to prevent user to traumatize the program
    // by pressing the turn on/off multiple times (Murphy's law)
    buttonConnect->setEnabled(false);
    buttonConnect->repaint();

    // Get the index of current chosen location in GUI location comboBox
    size_t index = static_cast<size_t>(locationsList->currentIndex());
    Location l = locations[index];

    debug("Connecting to server location : %s ...", l.label.c_str());
    connect_to_server(l);
    debug("Connected to server.");

    // Update the cache with status information (needed for Connection label and ext. IP)
    updateCache(CACHE_STATUS);

    // Reactive the switch button
    buttonConnect->setEnabled(true);
    // If the disconnect button was disabled (already disconnected), enable it
    if (!buttonDisconnect->isEnabled())
        buttonDisconnect->setEnabled(true);

    // Remove the pending operation animation
    hideLoadingCircle();

    // Authorize the updater thread to continue
    talkingToWindscribe = false;
}

void Dialog::buttonDisconnectClicked(){

    // protection check
    if (!state->started){
        /* TODO: Display a pop up window or whathever to inform the user that
           windscribe must be started */
        debug("Windscribe is not started.");
        return;
    }

    // warn user of pending operations
    displayLoadingCircle();

    // Stop the updater thread
    talkingToWindscribe = true;

    // Grey the button to prevent the user to traumatize the program
    // by pressing the turn on/off multiple times (Murphy's law)
    buttonDisconnect->setEnabled(false);
    buttonDisconnect->repaint();

    debug("Disconnecting from server.");
    disconnect_from_server();
    debug("Disonnected to server.");

    // Update the cache with status information (needed for Connection label and ext. IP)
    updateCache(CACHE_STATUS);

    // Remove the pending operation animation
    hideLoadingCircle();

    // Authorize the updater thread to continue
    talkingToWindscribe = false;
}

void Dialog::displayLoadingCircle(){
    loadingGif->setVisible(true);
    loadingGif->movie()->start();
}

void Dialog::hideLoadingCircle(){
    loadingGif->setVisible(false);
}
