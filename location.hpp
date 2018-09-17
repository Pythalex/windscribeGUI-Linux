#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>

class Location
{
public:
    Location();

    std::string country;
    std::string short_name;
    std::string city;
    std::string label;
    bool pro;

    friend std::ostream& operator<<(std::ostream& os,
                                    const Location& l);
};

std::ostream& operator<<(std::ostream& os, const Location &l);

#endif // LOCATION_HPP
