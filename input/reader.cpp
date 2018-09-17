#include "reader.hpp"

using std::string;
using std::stringstream;

string read_output_from_command(string command){
    stringstream ss = stringstream();

    redi::ipstream is(command);

    string line = "";
    bool passed_first = false; // at least second

    while (std::getline(is, line)) {
        if (!passed_first)
            passed_first = true;
        else
            ss << "\n";

        ss << line;
    }

    return ss.str();
}

string read_windscribe_status(){
    return read_output_from_command("windscribe status");
}

string read_account_details(){
    return read_output_from_command("windscribe account");
}

string read_locations(){
    return read_output_from_command("windscribe locations");
}

string read_firewall(){
    return read_output_from_command("windscribe firewall");
}
