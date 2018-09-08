#include "location.h"

struct Windscribe_location* create_location(char* location, char* short_name,
    char* city_name, char* label, int pro)
{
    struct Windscribe_location* loc = malloc(sizeof(struct Windscribe_location));

    strcpy(loc->location, location);
    strcpy(loc->short_name, short_name);
    strcpy(loc->city_name, city_name);
    strcpy(loc->label, label);
    loc->pro = pro;

    return loc;
}

struct Windscribe_location* create_default_location(){
    return create_location("N/A", "N/A", "N/A", "N/A", 0);
}

char* Windscribe_location_tostr(struct Windscribe_location* p){
    if (p){

        // calculate string size
        char* output = malloc(49 + strlen(p->location) +\
            strlen(p->short_name) + strlen(p->city_name) +\
            strlen(p->label) + 1);

        // create formatted string
        sprintf(output, "Location: %s\nShort Name: %s\nCity Name: %s\n"\
            "Label: %s\nPro: %c",
            p->location, p->short_name, p->city_name, p->label, 
            (p->pro ? '*' : ' '));

        // return string
        return output;
    } else {
        return "";
    }
}

void print_location(struct Windscribe_location* p){
    printf("%s", Windscribe_location_tostr(p));
}