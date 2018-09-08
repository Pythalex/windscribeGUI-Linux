#include "shellwriter.h"

void write_in_shell(const char* command){

    FILE *fp = NULL;

    debug("Write \"%s\" to shell.", command);
    fp = popen(command, "w");

    if (fp) {
        debug("Operation successful.");
        pclose(fp);
    } else {
        debug("Operation failed.");
    }
}

void write_in_shell_commands(char** commands, int length){
    FILE *fp = NULL;

    if (length > 0) {
        debug("Writing \"%s\" to shell.", commands[0]);
        fp = popen(commands[0], "w");
    }

    if (fp) {
        debug("File successfully opened.");

        for (int i = 1; i < length; i++){
            debug("%s", "Writing \"%s\" to shell.");
            fputs(commands[i], fp);
        }

        pclose(fp);
    } else {
        debug("Operation failed.");
    }
}

void connect_to_server(struct Windscribe_location* locp){
    char* label = locp->label;

    int size = strlen("windscribe connect ") + strlen(label);
    char* output = malloc(size + 1);
    check_mem(output);
    strcpy(output, "windscribe connect ");
    strcpy(output + strlen("windscribe connect "), label);
    output[size] = '\0';

    write_in_shell(output);

    s_free(output);

    return;
    error:
    return;
}

void connect_to_whatever_server(){
    write_in_shell("windscribe connect");
}

void disconnect_from_server(){
    write_in_shell("windscribe disconnect");
}

void change_firewall_mode(char* mode){
    char* output = malloc(strlen("windscribe firewall     ") + 1);
    check_mem(output);

    sprintf(output, "windscribe firewall %s", mode);
    output[strlen("windscribe firewall     ")] = '\0';

    if (!strcmp(mode, "auto") || !strcmp(mode, "on") || !strcmp(mode, "off"))
        write_in_shell(output);
    s_free(output);

    return;
    error:
    return;
}