#include "dataAQ.h"
#include "parse.h"
#include <string>   // std::string
#include <iostream> // std::cout
#include <sstream>  
#include <iomanip>
#include "tddFuncs.h"
using namespace std;

int main() {


cout << "Testing First part Report" << endl;

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
    string expectReport ="print summary demog Data:\nRegion info: comboData, MN\nEducation info:\n(Bachelor or more): 32.81% and total: 1790458\n(high school or more): 92.09% and total: 5025407\nTotal population: 5457173\nRacial Demographics Info: \n";
    
    std::string subReport = theReport.substr(0, expectReport.length());

    ASSERT_EQUALS(expectReport, subReport);

  return 0;
}
