#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>

#include "../dbg.h"

#include "reader.h"
#include "../state.h"
#include "../string_manip.h"
#include "../location.h"
#include "../free.h"

/**
 * Parses the splitted output of windscribe status shell command and creates
 * a Windscribe_state structure from it.
 * 
 * Parameters
 * ----------
 * 
 * None
 * 
 * Return value
 * --------------
 * 
 * Returns the newly created Windscribe_state struct pointer
 * 
 * Example
 * -------
 * 
 *      struct Windscribe_state* p = parse_state();
 *      printf("username: %s\n", p->username);
 * 
 * output:
 * username: YourName
 * 
 */
struct Windscribe_state* parse_state();

/**
 * Parses the output of windscribe status shell command to check
 * whether the service is running.
 * 
 * Parameters
 * ----------
 * 
 * status
 * 
 *      C string of the output of the command "windscribe status"
 * 
 * Return value
 * --------------
 * 
 * Returns whether windscribe is started.
 * 
 * Example
 * -------
 * 
 *      char* output = read_windscribe_status();
 *      int started = parse_started(output);
 * 
 */
int parse_started(char* status);

/**
 * Parses the output of windscribe status shell command to check
 * whether the service is connected.
 * 
 * Parameters
 * ----------
 * 
 * status
 * 
 *      C string of the output of the command "windscribe status"
 * 
 * Return value
 * --------------
 * 
 * Returns whether windscribe is connected to a server.
 * 
 * Example
 * -------
 * 
 *      char* output = read_windscribe_status();
 *      int connected = parse_connected(output);
 * 
 */
int parse_connected(char* status);

/**
 * Parses the output of windscribe status shell command to get
 * the user's visible IP.
 * 
 * Parameters
 * ----------
 * 
 * status
 * 
 *      C string of the output of the command "windscribe status"
 * 
 * Return value
 * --------------
 * 
 * Returns the user's visible IP.
 * 
 * Example
 * -------
 * 
 *      char* output = read_windscribe_status();
 *      char* IP = parse_IP(output);
 * 
 */
char* parse_IP(char* status);

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
 *      char* output = read_account_details();
 *      char* username = parse_account_username(output);
 * 
 */
char* parse_account_username(char* account_output);

struct Windscribe_location* parse_locations(char** splitted_output, 
    int input_size, int* output_size);

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
 *      char* output = read_firewall();
 *      char* mode = parse_firewall(output);
 * 
 */
char* parse_firewall(char* firewall_output);

#endif