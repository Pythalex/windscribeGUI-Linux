#ifndef STATE_H
#define STATE_H

#include <stdio.h>
#include <stdlib.h>

#include "dbg.h"
#include "input/reader.h"
#include "string_manip.h"
#include "free.h"

#define MAX_LENGTH_ACCOUNT_NAME 50
#define MAX_IPV4_LENGTH 15
#define MAX_FIREWALL_MODE_LENGTH 10

struct Windscribe_state {
	int started;
	int connected;
	char username[MAX_LENGTH_ACCOUNT_NAME];
	char IP[MAX_IPV4_LENGTH];
	char firewall[MAX_FIREWALL_MODE_LENGTH];
};

/**
 * Creates a new windscribe state structure with default values.
 * 
 * Parameters
 * ----------
 * 
 * None
 * 
 * Return value
 * --------------
 * 
 * Pointer to a Windscribe_state with default values.
 * 
 * Example
 * -------
 * 
 *      struct Windscribe_state* p = create_default_windscribe_state();
 * 		printf("%s\n", p->username);
 * 
 * output:
 * N/A
 * 
 */
struct Windscribe_state* create_default_windscribe_state();

/**
 * Indicates whether windscribe is started.
 * 
 * Parameters
 * ----------
 * 
 * None
 * 
 * Return value
 * --------------
 * 
 * 1 if windscribe is started, else 0
 * 
 * Example
 * -------
 * 
 *      int started = windscribe_is_started();
 * 
 */
int windscribe_is_started();

#endif
