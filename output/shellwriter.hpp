#ifndef SHELLWRITER_HPP
#define SHELLWRITER_HPP

#include <vector>
#include <iostream>
#include <cstring>

#include <stdlib.h>
#include <unistd.h>

#include "../dbg.hpp"
#include "../location.hpp"

/**
 * Writes the given command in shell
 *
 * Parameters
 * ----------
 *
 * command
 *      String, the command to write
 *
 * Example
 * -------
 *
 *      write_in_shell("mkdir test");
 */
void write_in_shell(std::string command);

/**
 * Writes all the given command in shell.
 * Additional commands will be given to stdin.
 *
 * Parameters
 * ----------
 *
 * commands
 *      The commands to write in shell
 *
 */
void write_in_shell(std::vector<std::string> commands);

/**
 * Writes all the given command in shell.
 * Each command is sent to the terminal independently, and
 * will not be sent to stdin.
 *
 * Parameters
 * ----------
 *
 * commands
 *      The commands to write in shell
 *
 */
void write_in_shell_commands(std::vector<std::string> commands);

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
//void connect_to_server(struct Windscribe_location* locp);

/**
 * Connects to the nearest windscribe server location.
 *
 * Parameters
 * ----------
 *
 * None
 *
 */
void connect_to_nearest_server();

/**
 * Connects to the given server location.
 *
 * Parameters
 * ----------
 *
 * l
 *      Windscribe location
 *
 * Example
 * -------
 *
 *      string output = read_firewall();
 *      vector<Location> locs = parse_locations(output);
 *      connect_to_server(locs[0]);
 */
void connect_to_server(Location &l);

/**
 * Disconnects from current connected server.
 *
 * Parameters
 * ----------
 *
 * None
 *
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
void change_firewall_mode(std::string mode);


#endif
