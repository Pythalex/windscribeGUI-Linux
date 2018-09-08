#ifndef SHELLWRITER_H
#define SHELLWRITER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../dbg.h"
#include "../free.h"
#include "../location.h"

/**
 * Writes the given command in shell
 * 
 * Parameters
 * ----------
 * 
 * command
 *      C string, the command to write
 * 
 * Example
 * -------
 * 
 *      write_in_shell("mkdir test");
 */
void write_in_shell(const char* command);

/**
 * Writes all the given command in shell.
 * Command should be of the given form
 * 
 *      {"windscribe login", "username", "password"}
 * 
 * Parameters
 * ----------
 * 
 * commands
 *      The commands to write in shell
 * length
 *      The number of commands
 * 
 * Example
 * -------
 * 
 *      char** commands = malloc(3);
 *      commands[0] = malloc(20);
 *      strcpy(commands[0], "windscribe login");
 *      commands[1] = malloc(10);
 *      strcpy(commands[1], "myname");
 *      commands[2] = malloc(10);
 *      strcpy(commands[2], "mypassword");
 * 
 *      write_in_shell_commands(commands, 3);
 */
void write_in_shell_commands(char** commands, int length);


/**
 * Connects to the given server location.
 * 
 * Parameters
 * ----------
 * 
 * locp
 *      windscribe location pointer
 * 
 * Example
 * -------
 * 
 *      struct Windscribe_location* p = create_default_location();
 *      strcpy(p->label, "Tea");
 * 
 *      connect_to_server(p);
 */
void connect_to_server(struct Windscribe_location* locp);

/**
 * Connects to the nearest server location.
 * 
 * Parameters
 * ----------
 * 
 * None
 * 
 * Example
 * -------
 * 
 *      connect_to_whatever_server(); // that's it
 */
void connect_to_whatever_server();

/**
 * Disconnects from current connected server.
 * 
 * Parameters
 * ----------
 * 
 * None
 * 
 * Example
 * -------
 * 
 *      disconnect_from_server(); // that's it
 */
void disconnect_from_server();

/**
 * Changes the windscribe firewall mode.
 * 
 * Parameters
 * ----------
 * 
 * mode
 *      The new mode to change to. Can be :
 *          - auto (on when connected, off when disconnected)
 *          - on 
 *          - off
 * 
 * Example
 * -------
 * 
 *      change_firewall_mode("on"); // turn it on
 *      change_firewall_mode("off"); // turn it off
 *      change_firewall_mode("auto"); // automatic changes
 */
void change_firewall_mode(char* mode);

#endif