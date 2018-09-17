#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>

#include "../dbg.hpp"
#include "../state.hpp"
#include "../string_manip.hpp"
#include "../location.hpp"
#include "reader.hpp"

State parse_state();

/**
 * Parses the output of windscribe status shell command to check
 * whether the service is running.
 *
 * Parameters
 * ----------
 *
 * status
 *
 *      String of the output of the command "windscribe status"
 *
 * Return value
 * --------------
 *
 * Returns whether windscribe is started.
 *
 * Example
 * -------
 *
 *      string output = read_windscribe_status();
 *      bool started = parse_started(output);
 *
 */
bool parse_started(std::string status);

/**
 * Parses the output of windscribe status shell command to check
 * whether the service is connected.
 *
 * Parameters
 * ----------
 *
 * status
 *
 *      String of the output of the command "windscribe status"
 *
 * Return value
 * --------------
 *
 * Returns whether windscribe is connected to a server.
 *
 * Example
 * -------
 *
 *      string output = read_windscribe_status();
 *      bool connected = parse_connected(output);
 *
 */
bool parse_connected(std::string status);

/**
 * Parses the output of windscribe status shell command to get
 * the user's visible IP.
 *
 * Parameters
 * ----------
 *
 * status
 *
 *      String of the output of the command "windscribe status"
 *
 * Return value
 * --------------
 *
 * Returns the user's visible IP.
 *
 * Example
 * -------
 *
 *      string output = read_windscribe_status();
 *      string IP = parse_IP(output);
 *
 */
std::string parse_IP(std::string status);

/**
 * Parses the output of windscribe account shell command to get
 * the username of the account.
 *
 * Parameters
 * ----------
 *
 * account
 *      output of the command "windscribe account"
 *
 * Return value
 * --------------
 *
 * Returns the account's username
 *
 * Example
 * -------
 *
 *      string output = read_account_details();
 *      string username = parse_account_username(output);
 *
 */
std::string parse_account_username(std::string account_output);

/**
 * Parses the output of "windscribe firewall" command to
 * get the firewall current mode.
 *
 * Parameters
 * ----------
 *
 * firewall_output
 *      The output of the command "windscribe firewall"
 *
 * Return value
 * --------------
 *
 * Returns the firewall mode
 *
 * Example
 * -------
 *
 *      string output = read_firewall();
 *      string mode = parse_firewall(output);
 *
 */
std::string parse_firewall(std::string firewall_output);

/**
 * Parses the output of "windscribe location" command to
 * construct a list of available locations.
 *
 * Parameters
 * ----------
 *
 * location_output
 *      The output of the command "windscribe location"
 *
 * Return value
 * --------------
 *
 * Returns the firewall mode
 *
 * Example
 * -------
 *
 *      string output = read_firewall();
 *      vector<Location> locs = parse_locations(output);
 *      connect_to_server(locs[0]);
 *
 */
std::vector<Location> parse_locations(std::string location_output);

#endif // PARSER_HPP
