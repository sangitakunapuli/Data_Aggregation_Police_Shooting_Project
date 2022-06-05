#include "demogCombo.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>

/* print state data - as aggregate of all the county data */
std::ostream& operator<<(std::ostream &out, const demogCombo&SD) {
    out << std::fixed << std::setprecision(2);
    //out << "Combo Demographic Info: key: " << SD.getKey() << endl; 
    out << "Combo Info: " << SD.printState();
    out << "\nNumber of Counties: " << SD.getNumRegions() << " County Demographics Info: " << SD.getRegionName() << ", " << SD.getState();
    out << "\nPopulation info: \n(over 65): " << SD.getpopOver65() << "\%";
    out <<  " and total: " << SD.getpopOver65Count();
    out << "\n(under 18): " << SD.getpopUnder18() << "\%";
    out <<  " and total: " << SD.getpopUnder18Count();
    out << "\n(under 5): " << SD.getpopUnder5() << "\%";
    out <<  " and total: " << SD.getpopUnder5Count();
    out << "\nEducation info: " << endl;
    out << "(Bachelor or more): " << SD.getBAup() << "\%";
    out << " and total: " << SD.getBAupCount();
    out << "\n(high school or more): " << SD.getHSup() << "\%";
    out << " and total: " << SD.getHSupCount();
    out << "\npersons below poverty: " << SD.getBelowPoverty() << "\%";
    out << " and total: " << SD.getBelowPovertyCount();
    out << "\nTotal population: " << SD.getPop();
    out << "\n" << SD.getRaces();
    return out;
}
