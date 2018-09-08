#include "reader.h"

#define MAX_LINE_SIZE 100

char* read_output_from_command(const char *command){

    FILE *fp;

    int output_limit = 1000;

    char* output = malloc(output_limit);
    char* line = malloc(MAX_LINE_SIZE);

    int cur = 0;

    fp = popen(command, "r");

    if (fp != NULL){
        while (fgets(line, MAX_LINE_SIZE, fp)){
            int len = strlen(line);

            // If output limit is reached, double it
            if (cur + len >= output_limit){
                output = realloc(output, output_limit * 2);
                output_limit *= 2;
            }

            memcpy(output + cur, line, len);
            cur += len;
        }
        pclose(fp);
    } else {
        perror("popen failed.\n");
    }

    s_free(line);

    return output;
}

char* read_windscribe_status(){
    return read_output_from_command("windscribe status");
}

char* read_account_details(){
    return read_output_from_command("windscribe account");
}

char* read_locations(){
    return read_output_from_command("windscribe locations");
}

char* read_firewall(){
    return read_output_from_command("windscribe firewall");
}