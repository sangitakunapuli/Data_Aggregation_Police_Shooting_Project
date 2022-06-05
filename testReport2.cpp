#include "dataAQ.h"
#include "parse.h"
#include <string>   // std::string
#include <iostream> // std::cout
#include <sstream>  
#include <iomanip>
#include "tddFuncs.h"
using namespace std;

int main() {


cout << "Testing Report" << endl;

	  dataAQ theAnswers;
    cout << std::setprecision(2) << std::fixed;
    //read in the hospital data
    std::vector<shared_ptr<regionData> > theDemogData = read_csv(
            "county_demographics.csv", DEMOG);
   
    //read in the demographic data
    std::vector<shared_ptr<regionData> > thePoliceData = read_csv(
            "police_shootings_cleaned.csv", POLICE);

    //create the state demographic data
    theAnswers.createComboDemogData((std::vector<shared_ptr<demogData> >&) theDemogData);
    theAnswers.createComboPoliceData((std::vector<shared_ptr<psData> >&) thePoliceData);

    std::stringstream buffer;
    // Redirect std::cout to buffer
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    //the report code
    theAnswers.comboReport(92);
    // Use the string value of buffer to compare against expected output
    std::string theReport = buffer.str();

    // Restore original buffer before exiting
    std::cout.rdbuf(prevcoutbuf);

    // report
    string expectReport ="WY\nEducation info:\n(Bachelor or more): 24.85% and total: 145165\n(high school or more): 92.37% and total: 539588\nTotal population: 584153\nRacial Demographics Info: ";

    std::size_t found = theReport.find("WY");
    std::string subReport = theReport.substr(found, expectReport.length());
    cout << "difference in characters: " << subReport.compare(expectReport);
    ASSERT_EQUALS(expectReport, subReport);

  return 0;
}
