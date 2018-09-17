/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
class QComboBox;
class QProgressBar;
QT_END_NAMESPACE

#include <ctime>
#include <thread>
#include <chrono>

#include "../dbg.hpp"
#include "../location.hpp"
#include "../state.hpp"
#include "../pstream.h"
#include "../string_manip.hpp"
#include "../input/reader.hpp"
#include "../input/parser.hpp"
#include "../output/shellwriter.hpp"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog();
    ~Dialog();

private slots:
    /**
     * @brief Updates the ": connected" label
     * Called when the user turn on/off the connection.
     *
     * @param useCache whether to use the cache for update
     */
    void updateConnectionLabel(bool useCache = true);

    /**
     * @brief Updates the IP Label
     * Called when the external IP is suceptible to change.
     *
     * @param useCache whether to use the cache for update
     */
    void updateIP(bool useCache = true);

    /**
     * @brief Updates cache if necessary
     */
    void updateLastUpdateValue();

    /**
     * @brief Updates the state cache
     *
     * To choose the values to update, caller must send a
     * bitwise OR of the flags CACHE_STATUS, CACHE_FIREWALL, CACHE_ACCOUNT
     */
    void updateCache(uint flags);

    /**
     * @brief Calls every update methods.
     * @param useCache whether to use the cache for update
     */
    void updateEverything(bool useCache = true);

    /**
     * @brief Function called when clicking the button of connection switch
     * Is called when buttonConnect is clicked on.
     */
    void buttonConnectClicked();

    /**
     * @brief Function called when clicking the button of disconnection switch
     * Is called when buttonDisconnect is clicked on.
     */
    void buttonDisconnectClicked();

private:

    /**
     * @brief Creates the menubar
     */
    void createMenu();

    /**
     * @brief Creates the horizonlisttal box for firewall informations
     */
    void createHorizontalGroupBox();

    /**
     * @brief Creates the grid box which will contains server and connections informations
     */
    void createGridGroupBox();

    /**
     * @brief Indicates if the cache is too old
     * @return true if the cache must be updated
     */
    bool cacheTooOld();

    /**
     * @brief Reset the periodic update timer
     *
     * Set lastUpdate to 0 and lastUpdateTimert to current time
     */
    void resetTimer();

    void displayLoadingCircle();

    void hideLoadingCircle();

    static void thread_updater_routine(Dialog *instance);

    enum { NumGridRows = 3, NumButtons = 4 };

    QMenuBar *menuBar;
    QGroupBox *horizontalGroupBox;
    QGroupBox *gridGroupBox;

    QMovie *movie;
    QLabel *loadingGif;

    // Connection area
    QComboBox *locationsList;
    std::vector<Location> locations;
    bool talkingToWindscribe = false; // true when the programs is reading or writing to windscribe

    QLabel *connectionLabel;
    QLabel *IPLabel;
    QPushButton *buttonConnect;
    QPushButton *buttonDisconnect;

    QMenu *fileMenu;
    QAction *exitAction;

    // Cache for updates
    std::thread updaterThread;
    bool stop_thread = false; // used for stopping thread loop
    bool updating = false;

    bool forceCacheUpdate = false; // Is set to true when a function want the updater thread to update cache right now
    uint forceflags = 0; // CACHE flags used when forcing an update

    QTimer *timer; // use to recall updateEverything()
    int period = 400; // update periode (ms)

    time_t lastUpdateTimet; // used for difftime
    int lastUpdate = 0; // time since last update (s)
    int maxCacheAge = 3; // Updates will take Cache value if < 3s (unless they are told to update it)
    State *state;

    // Flags used for cache update
    uint CACHE_STATUS = 1;
    uint CACHE_FIREWALL = 2;
    uint CACHE_ACCOUNT = 4;
};

#endif // DIALOG_HPP
