#include "state.h"

struct Windscribe_state* create_default_windscribe_state(){
	struct Windscribe_state* p = malloc(sizeof(struct Windscribe_state));

	p->started = 0;
	p->connected = 0;
	strcpy(p->username, "N/A");
	strcpy(p->IP, "N/A");
	strcpy(p->firewall, "N/A");

	return p;
}

int windscribe_is_started(){
	char* output = read_windscribe_status();
	int length = 0;
	char** splitted = split_str(output, "\n", &length);

	int started = !(length == 2 && strcmp(splitted[0], "Windscribe is not running"));

	s_free(output);
	s_free_2D_array((void**)splitted, length);
	return started;
}