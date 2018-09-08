#include "string_manip.h"

char** split_str(const char* str, const char* delim, int* length_ptr){

    // Create the splitted array with initial size of 1
    char** splitted = malloc(sizeof(char*));
    int size = 1;
    // Check allocated memory, if the ptr is NULL, print "Out of memory" 
    // and go to error label
    check_mem(splitted);

    // Create a copy of given str
    char* str_copy = malloc(strlen(str) + 1);
    check_mem(str_copy);
    strcpy(str_copy, str);
    str_copy[strlen(str)] = '\0';

    // Get the first token
    char* token;
    int length = 0;
    token = strtok(str_copy, delim);
    
    // If a first token is found, repeat
    while (token != NULL){

        // After the first token is stored, allocate memory to add a 
        // token each time
        if (length == size){
            splitted = realloc(splitted, sizeof(char*) * (size + 1));
            size++;
        }

        // Allocate memory to store the token and store it
        splitted[length] = malloc(strlen(token) + 1);
        memcpy(splitted[length], token, strlen(token));
        // NULL terminate the token string
        splitted[length][strlen(token)] = '\0';

        length++;
        token = strtok(NULL, delim);
    }

    // FREE
    if (str_copy)
        free(str_copy);

    // output
    *length_ptr = length;
    return splitted;

    error:
    if (splitted){
        for (int i = 0; i < size; i++)
            if (splitted[i])
                free(splitted[i]);
        free(splitted);
    }
    if (str_copy != NULL)
        free(str_copy);
    return NULL;
}

char** split_str_substring(const char* str, const char* delim_substr, 
    int* length_ptr)
{

    // Create the splitted array with initial size of 1
    char** splitted = malloc(sizeof(char*));
    int size = 1;
    int length = 0;

    // Create a copy of given str
    char* str_copy = malloc(strlen(str) + 1);
    // keep reference for future free
    char* start_str_copy = str_copy;
    // check allocated memory and copy str
    check_mem(str_copy);
    strcpy(str_copy, str);
    str_copy[strlen(str)] = '\0';

    // Find substr
    char* position = str_copy;
    do {
        // Get address of matching
        position = strstr(str_copy, delim_substr);

        debug("position : %p", position);

        /**
         * If position is NULL, it means strstr reached the end
         * of str_copy, in which case it means the only token is
         * the whole string, so position is set to the last character
         * in order to copy it entirely
         */
        if (position == NULL)
            position = str_copy + strlen(str_copy);

        // After the first token is stored, allocate memory to add a 
        // token each time
        if (length == size){
            splitted = realloc(splitted, sizeof(char*) * (size + 1));
            size++;
        }

        int token_size = position - str_copy;

        // If the token is a least one character long, store it
        // else just go for next token
        if (token_size > 0) {
            // Allocate memory to store the token and store it
            splitted[length] = malloc(token_size + 1);
            memcpy(splitted[length], str_copy, token_size);
            // NULL terminate the token string
            splitted[length][token_size] = '\0';

            length++;
        }

            str_copy = position + strlen(delim_substr);
            position = str_copy;

    } while (*position != '\0');

    if(start_str_copy)
        free(start_str_copy);

    *length_ptr = length;
    return splitted;

    error:
    if (start_str_copy)
        free(start_str_copy);
    if (splitted) {
        for (int i = 0; i < length; i++){
            if (splitted[length])
                free(splitted[length]);
        }
        free(splitted);
    }

    return NULL;
}

char* remove_whitespaces(const char* string){
    int start = 0;
    int end = strlen(string) - 1;

    while(string[start] == ' ') start++;
    while(string[end] == ' ') end--;
    end++;

    if (start == end) return "";
    else {
        char* output = malloc(end - start + 1);
        for (int i = 0; i < end - start + 1; i++)
            output[i] = string[start + i];
        for (int i = end - start + 1; i < end + 1; i++)
            output[i] = '\0';

        return output;
    }
}
