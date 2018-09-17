#include "shellwriter.hpp"

using std::string;
using std::vector;

void write_in_shell(string command){
    FILE *fp = nullptr;

    debug("Write \"%s\" to shell.", command.c_str());
    fp = popen(command.c_str(), "w");

    if (fp) {
        debug("Operation successful.");
        pclose(fp);
    } else {
        debug("Operation failed.");
    }
}

void write_in_shell(vector<string> commands){
    FILE *fp = nullptr;

    if (commands.size() > 0) {
        debug("Write \"%s\" to shell.", commands[0].c_str());
        fp = popen(commands[0].c_str(), "w");
    }

    if (fp) {
        for (uint i = 1; i < commands.size(); i++){
            debug("Write \"%s\" to shell.", commands[i].c_str());
            fputs(commands[i].c_str(), fp);
        }

        debug("Operation successful.");
        pclose(fp);
    } else {
        debug("Operation failed.");
    }
}

void write_in_shell_commands(vector<string> commands){
    for (uint i = 0; i < commands.size(); i++){
        write_in_shell(commands[i]);
    }
}

void connect_to_nearest_server(){
    write_in_shell("windscribe connect");
}

void connect_to_server(Location &l){
    // Add " around the label because some labels contain whitespace(s)
    write_in_shell("windscribe connect \"" + l.label + "\"");
}

void disconnect_from_server(){
    write_in_shell("windscribe disconnect");
}

void change_firewall_mode(string mode){
    debug("Changing firewall mode for : %s", mode.c_str());
    write_in_shell("windscribe firewall " + mode);
}
