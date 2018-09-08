#include "parser.h"

struct Windscribe_state* parse_state(){

    // declarations
    char* status = NULL;
    char* account = NULL;
    char* firewall = NULL;

    // Create the new state and get status output
    struct Windscribe_state* state = create_default_windscribe_state();
    status = read_windscribe_status();
    check_mem(status);

    // Parse windscribe start
    state->started = parse_started(status);
    // Parse windscribe server connection
    state->connected = parse_connected(status);

    // Parse user's visible IP
    memcpy(state->IP, parse_IP(status),
        MAX_IPV4_LENGTH);

    // Parse username
    account = read_account_details();
    check_mem(account);
    memcpy(state->username, parse_account_username(account),
        MAX_LENGTH_ACCOUNT_NAME);

    // Parse firewall mode
    firewall = read_firewall();
    check_mem(firewall);
    memcpy(state->firewall, parse_firewall(firewall),
        MAX_FIREWALL_MODE_LENGTH);

    // clean and return new state
    s_free(status);
    s_free(account);
    s_free(firewall);
    return state;

    error:
    s_free(status);
    s_free(account);
    s_free(firewall);
    return NULL;
}

int parse_started(char* status){

    int length = 0;
    char** splitted = split_str(status, ",\n", &length);
    check_mem(splitted);

    int output = strcmp(splitted[0], "Windscribe is not running") != 0;

    s_free_2D_array((void**)splitted, length);
    return output;

    error:
    return -1;
}

int parse_connected(char* status){

    int length = 0;
    char** splitted = split_str(status, ",\n", &length);
    check_mem(splitted);

    int output = 0;
    if (length > 6)
        output = strcmp(splitted[6], "DISCONNECTED") != 0;

    s_free_2D_array((void**)splitted, length);
    return output;

    error:
    return -1;
}

char* parse_IP(char* status){

    // declarations
    char** splitted = NULL; // status splitted array
    int splitted_length = 0;
    char** splitted_line = NULL; // IP line splitted array
    int splitted_line_length = 0;

    // split status
    splitted = split_str(status, ",\n", &splitted_length);
    check_mem(splitted);

    // get ip line and split it
    char* line = splitted[5];
    splitted_line = split_str(line, ":", &splitted_line_length);
    check_mem(splitted_line);

    // trim IP
    char* output = remove_whitespaces(splitted_line[1]);

    // clean and return output
    s_free_2D_array((void**)splitted, splitted_length);
    s_free_2D_array((void**)splitted_line, splitted_line_length);
    return output;

    error:
    s_free_2D_array((void**)splitted, splitted_length);
    s_free_2D_array((void**)splitted_line, splitted_line_length);
    return "N/A";
}

char* parse_account_username(char* account_output){
    
    // declarations
    char** splitted = NULL;
    int length = 0;
    char* username_line;
    char** username_splitted = NULL;
    int username_split_length = 0;

    char* output = NULL;

    // split the input
    splitted = split_str(account_output, "\n", &length);
    check_mem(splitted);

    // split the username line
    username_line = splitted[1];
    username_splitted = split_str(username_line, ":", &username_split_length);
    check_mem(username_splitted);

    // Check that the line is not corrupted
    if (strcmp(username_splitted[0], "Username") == 0)
        output = remove_whitespaces(username_splitted[1]);
    // Else clean and return error
    else
        goto error;

    // clean and return output
    s_free_2D_array((void**)splitted, length);
    s_free_2D_array((void**)username_splitted, username_split_length);
    return output;

    error:
    s_free_2D_array((void**)splitted, length);
    s_free_2D_array((void**)username_splitted, username_split_length);
    return "N/A";
}

struct Windscribe_location* parse_locations(char** splitted_output, 
    int input_size, int* output_size)
{
    // The commentary line doesn't count
    *output_size = input_size - 1;

    // create the struct array to store locations
    struct Windscribe_location* locations = \
        malloc(sizeof(struct Windscribe_location) * (*output_size));

    // For each location, create a struct location
    // start at 1 to ignore commentary line
    for (int i = 1; i < input_size; i++){
        struct Windscribe_location* new_location = create_default_location();
        locations[i - 1] = *new_location;
        free(new_location);

        // Split the location line
        int location_split_length = 0;
        char** splitted_location = split_str_substring(splitted_output[i], "  ",
            &location_split_length);
        
        // If the line was effectively a location line, it must be
        // of length 4 or 5 (5 if it's a pro location), else it's
        // a corrupted string and no changes will be made
        if (location_split_length >= 4){
            strcpy(locations[i - 1].location, 
                remove_whitespaces(splitted_location[0]));
            strcpy(locations[i - 1].short_name, 
                remove_whitespaces(splitted_location[1]));
            strcpy(locations[i - 1].city_name, 
                remove_whitespaces(splitted_location[2]));
            strcpy(locations[i - 1].label, 
                remove_whitespaces(splitted_location[3]));

            // The pro column will only be kept if there is the pro '*'
            // so if the length is of 5, it means there was a character,
            // as the non-pro character is a space
            if (location_split_length == 5)
                if (*remove_whitespaces(splitted_location[4]) == '*')
                    locations[i - 1].pro = 1;
        }
    }

    return locations;

}

char* parse_firewall(char* firewall_output){
    
    // declarations
    char** splitted = NULL;
    int length = 0;
    char** splitted_line = NULL;
    int splitted_line_length = 0;
    char* output = NULL;

    // split the firewall output
    splitted = split_str(firewall_output, "\n", &length);
    check_mem(splitted);

    // split the mode line
    splitted_line = split_str(splitted[1], ":", &splitted_line_length); 
    check_mem(splitted_line);

    // check if mode line is not corrupted
    if (splitted_line_length == 2)
        output = remove_whitespaces(splitted_line[1]);
    // else clean and return error
    else
        goto error;

    // clean and return output
    s_free_2D_array((void**)splitted, length);
    s_free_2D_array((void**)splitted_line, splitted_line_length);
    return output;

    error:
    s_free_2D_array((void**)splitted, length);
    s_free_2D_array((void**)splitted_line, splitted_line_length);
    return "N/A";
}