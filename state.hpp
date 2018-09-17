#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>
#include <cstring>

class State{

public:
    State();

    bool started;
    bool connected;
    std::string username;
    std::string IP;
    std::string firewall;

};

#endif
