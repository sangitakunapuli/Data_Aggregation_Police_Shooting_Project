#include <sstream>
#include "psData.h"
#include "visitor.h"

/* print police data */
std::ostream& operator<<(std::ostream &out, const psData &PD) {
    out << "Police Shooting Info: " << PD.getRegionName();
    out << "\nPerson name: " << PD.getName();
    out << "\nAge: " << PD.getAge();
    out << "\nGender: " << PD.getGender();
    out << "\nRace:" << PD.getRace();
    out << "\nMental Illness:" << PD.getMentalIll();
    out << "\nFleeing:" << PD.getFlee();
    return out;
}

void psData::accept(class Visitor &v) {
    v.visit(shared_from_this());
}
