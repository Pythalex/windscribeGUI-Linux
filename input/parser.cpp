#include "parser.hpp"

using std::string;
using std::vector;

void parse_state(State *s){

    string status = read_windscribe_status();

    if (status == "Service communication error"){
        debug("Windscribe returned Service communication error.");
        return ;
    }

    string firewall = read_firewall();
    string account = read_account_details();

    if (!s)
        s = new State();

    s->started = parse_started(status);
    s->connected = parse_connected(status);
    s->IP = parse_IP(status);
    s->firewall = parse_firewall(firewall);
    s->username = parse_account_username(account);
}

bool parse_started(string status){

    vector<string> split = explode(status, "\n");

    return (split.size() > 0 && split[0] !=\
            "Windscribe is not running");
}

bool parse_connected(string status){

    vector<string> split = explode(status, "\n");

    return (split.size() > 2 && split[2] != "DISCONNECTED");
}


string parse_IP(string status){

    vector<string> split = explode(status, "\n");

    vector<string> IP_line_split = explode(split[1], ":");

    if (IP_line_split.size() > 1)
        return trim_whitespaces(IP_line_split[1]);
    else
        return "N/A";
}

string parse_account_username(string account_output){

    vector<string> split = explode(account_output, "\n");

    vector<string> user_line_split = explode(split[1], ":");

    if (user_line_split.size() > 1)
        return trim_whitespaces(user_line_split[1]);
    else
        return "N/A";

}

string parse_firewall(string firewall_output){
    vector<string> split = explode(firewall_output, "\n");

    vector<string> mode_line_split = explode(split[1], ":");

    if (mode_line_split.size() > 1)
        return trim_whitespaces(mode_line_split[1]);
    else
        return "N/A";

}

vector<Location> parse_locations(string location_output){
    vector<Location> locations = vector<Location>();

    vector<string> split = explode(location_output, "\n");

    // skip commentary line
    for (uint i = 1; i < split.size(); i++){
        vector<string> line_split = explode_substring(split[i], "  ");

        Location l = Location();
        l.country = trim_whitespaces(line_split[0]);
        l.short_name = trim_whitespaces(line_split[1]);
        l.city = trim_whitespaces(line_split[2]);
        l.label = trim_whitespaces(line_split[3]);
        l.pro = (trim_whitespaces(line_split[4]) == "*" ?\
                    true : false);
        locations.push_back(l);
    }

    return locations;
}
