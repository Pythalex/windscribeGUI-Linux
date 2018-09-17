#include "location.hpp"

using std::ostream;

Location::Location()
{

}

ostream& operator<<(ostream& os, const Location &l){
    os << "Country     Short-Name     City-Name     Label     pro\n"
       << l.country << "     " << l.short_name << "     "
       << l.city << "     " << l.label << "     "
       << (l.pro ? "*" : " ");
    return os;
}
