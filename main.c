#include <stdio.h>
#include <stdlib.h>

#include "dbg.h"

#include "input/parser.h"
#include "input/reader.h"

#include "output/shellwriter.h"

#include "state.h"
#include "string_manip.h"
#include "location.h"
#include "free.h"

int main(){

    struct Windscribe_location* p = create_location("", "", "", 
        "Tea", 0);

    disconnect_from_server();
    connect_to_server(p);
    
    return 0;
}