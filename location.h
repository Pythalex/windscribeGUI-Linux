#ifndef LOCATION_H
#define LOCATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 30

/**
 * Structure of a server location for windscribe
 * 
 * location : geographical location of the server (typically country)
 * short_name: alias used by windscribe when the user chooses the server
 * city_name : self explanatory 
 * label : the label to use when the users wants to connect to the server
 * pro : whether the location is premium-only
 */
struct Windscribe_location {

    char location[MAX_STRING_SIZE];
    char short_name[MAX_STRING_SIZE];
    char city_name[MAX_STRING_SIZE];
    char label[MAX_STRING_SIZE];
    int pro;

};

struct Windscribe_location* create_default_location();

struct Windscribe_location* create_location(char* location, char* short_name,
    char* city_name, char* label, int pro);

char* Windscribe_location_tostr(struct Windscribe_location* p);

void print_location(struct Windscribe_location* p);

#endif