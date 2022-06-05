#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "demogData.h"
#include "psData.h"
#include "parse.h"
// #include "dataAQ.h"
#include "visitorCombineCounty.h"
#include "visitorCombineState.h"
// #include "visitor.h"
// #include "stats.h"
#include "statTool.h"
// #include "visitorCombine.h"


// lab06 pt2 (visitor design redesign) - sangita kunapuli, shivani sista

using namespace std;

int main() {

    std::vector<shared_ptr<regionData>> pileOfData;

    //read in the police data
    read_csv(pileOfData, "police_shootings_cleaned.csv", POLICE);
   
    //read in the demographic data
    read_csv(pileOfData, "county_demographics.csv", DEMOG); 

 //create a visitor to combine the state data
    visitorCombineState theStates;
    statTool::createStateData(pileOfData, theStates);
    //theStates.printAllCombo(&demogData::getBelowPovertyCount, &psCombo::getNumberOfCases);

    //create a visitor to combine the county data
    visitorCombineCounty theCounties;
    statTool::createCountyData(pileOfData, theCounties);
    //theCounties.printAllCombo(&demogData::getBelowPovertyCount, &psCombo::getNumberOfCases);


// DEMOG DATA COMPARES -----------------------------------------------
// computeStatsDemogRegionData
    //Under 18 + Below Poverty (state)
    cout << "---- State data Pop under 18 and Below Pov: ----" << endl;
    statTool::computeStatsDemogRegionData(&theStates, &demogData::getpopUnder18, &demogData::getBelowPoverty,
        &demogData::getpopUnder18Count, &demogData::getBelowPovertyCount);

    //Under 18 + Below Poverty (county)
    cout << "---- County data Pop under 18 and Below Pov: ----" << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &demogData::getpopUnder18, &demogData::getBelowPoverty,
        &demogData::getpopUnder18Count, &demogData::getBelowPovertyCount);


    //Below Poverty + HS and Up (state)
    cout << "---- State data Below Pov and HS and up: ----" << endl;
    statTool::computeStatsDemogRegionData(&theStates, &demogData::getBelowPoverty, &demogData::getHSup,
        &demogData::getBelowPovertyCount, &demogData::getHSupCount);


    //Below Poverty + HS and Up (county)
    cout << "---- County data Below Pov and HS and up: ----" << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &demogData::getBelowPoverty, &demogData::getHSup,
        &demogData::getBelowPovertyCount, &demogData::getHSupCount);



// POLICE SHOOTING COMPARES -----------------------------------------------
//computeStatsPSData
// statTool::computeStatsPSData(visitorCombine*  theRegions, 
//                                 int (psCombo::*f1)()const, int (psCombo::*f2)() const)


    // mental health + whiteNH victims -- corr coeff (county)
    cout << "---- Comparing Mental Health & White Victims Correlation: ----" << endl;
    statTool::computeStatsPSData(&theCounties, &psCombo::getNumMentalI, &psCombo::getWhiteNH);

    // mental health + AfAms victims -- corr coeff (county)
    cout << "---- Comparing Mental Health & African American Victims Correlation: ----" << endl;
    statTool::computeStatsPSData(&theCounties, &psCombo::getNumMentalI, &psCombo::getBlack);


// MIX DATA -----------------------------------------------------------------
//computeStatsMixRegionData
//   static void computeStatsMixRegionData(visitorCombine*  theRegions, 
//         int (demogCombo::*f1)() const, int (psCombo::*f2)() const);

    // total county population (demographic data) to total number of incidents (police shooting data):
    cout << "---- Mix Data comparing total county population (Demog) and total number of incidents (PS) ----" << endl;
    statTool::computeStatsMixRegionData(&theCounties, &demogData::getPop, &psCombo::getNumberOfCases);

    // total county population under 18  (demographic data) to total number of incident for people 18 and younger (police shooting data):
    cout << "---- Mix Data comparing total population under 18 (Demog) and total number of incidents under 18 (PS) ----" << endl;
    statTool::computeStatsMixRegionData(&theCounties, &demogData::getpopUnder5Count, &psCombo::getCasesUnder18);


// PROPORTIONS ---------------------------------------------------------------
// computeStatsRaceProportion
    
// static void computeStatsRaceProportion(visitorCombine*  theRegions, 
//                                 int (raceDemogData::*f1)()const, int (raceDemogData::*f2)() const);

    // mean of the proportion of the population at the COUNTY level that is White versus the proportion of the reported police shooting when the victim is White (non Hispanic):
    cout << "---- COUNTY proportion (whiteNH vs. whiteNH ps) ----" << endl;
    statTool::computeStatsRaceProportion(&theCounties, &raceDemogData::getWhiteNHCount, &raceDemogData::getWhiteNHCount);



    // mean of the proportion of the population at the COUNTY level that is African American/Black versus the proportion of the reported police shooting when the victim is African American/Black:
    cout << "---- COUNTY proportion (Black vs. Black ps) ----" << endl;
    statTool::computeStatsRaceProportion(&theCounties, &raceDemogData::getBlackCount, &raceDemogData::getBlackCount);


    // mean of the proportion of the population at the STATE level that is White versus the proportion of the reported police shooting when the victim is White (non Hispanic):
    cout << "---- STATE proportion (whiteNH vs. whiteNH ps) ----" << endl;
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getWhiteNHCount, &raceDemogData::getWhiteNHCount);


    // mean of the proportion of the population at the STATE level that is African American/Black versus the proportion of the reported police shooting when the victim is African American/Black:
    cout << "---- STATE proportion (Black vs. Black ps) ----" << endl;
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getBlackCount, &raceDemogData::getBlackCount);


    // mean of the proportion of the population at the STATE level that is Latinx/Hispanic versus the proportion of the reported police shooting when the victim is Latinx/Hispanic 
    cout << "---- STATE proportion (Latinx vs. Latinx ps) ----" << endl;
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getLatinxCount, &raceDemogData::getLatinxCount);


    // mean of the proportion of the population at the STATE level that is First Nation/Native American versus the proportion of the reported police shooting when the victim is First Nation/Native American :
    cout << "---- STATE proportion (Native American vs. Native American ps) ----" << endl;
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getFirstNationCount, &raceDemogData::getFirstNationCount);
    

    // mean of the proportion of the population at the STATE level that is Asian American versus the proportion of the reported police shooting when the victim is Asian American
    cout << "---- STATE proportion (Asian American vs. Asian American ps) ----" << endl;
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getAsianCount, &raceDemogData::getAsianCount);
    
    
//---------------------------------------------------------------

     //debug print out
    
    // for (const auto &obj : theDemogData) {
    //     //std::cout << *(std::static_pointer_cast<demogData>(obj)) << std::endl;
    //     //std::cout << *obj << std::endl;
    // }
    
    // std::vector<shared_ptr<demogData>> data;
    // for (const auto &obj : theDemogData) {
    //     data.push_back(std::static_pointer_cast<demogData>(obj));
    // }
    
//     theAnswers.createComboDemogData((std::vector<shared_ptr<demogData> >&)theDemogData);
//     theAnswers.createComboPoliceData((std::vector<shared_ptr<psData> >&)thePoliceData);
//     theAnswers.comboReport(92);

    // OLD PRINT OUTS & DEBUGGING -----------------------------------------------------------
    // theAnswers.createComboDemogData(data);
 
    // theAnswers.createComboPoliceDataKey((std::vector<shared_ptr<psData> >&) thePoliceData);
    // theAnswers.createComboDemogDataKey((std::vector<shared_ptr<demogData> >&) theDemogData);

    //cout << *(theAnswers.getComboPoliceData("KeyNativeAmericanVictim")) << endl;
    //cout << *(theAnswers.getComboDemogData("KeyBelowPovAboveThirtyPer")) << endl;

    //theAnswers.createStatePoliceData(thePoliceData);
    //cout << theAnswers << endl;

    //theAnswers.reportTopTenStatesPS();
    //theAnswers.reportTopTenStatesBP();

    /*
    cout << "*** the state that needs the most pre-schools**" << endl;
    string needPK = theAnswers.youngestPop();
    cout << *(theAnswers.getStateData(needPK)) << endl;
    cout << "*** the state that needs the most high schools**" << endl;
    string needHS = theAnswers.teenPop();
    cout << *(theAnswers.getStateData(needHS)) << endl;
    cout << "*** the state that needs the most vaccines**" << endl;
    string needV = theAnswers.wisePop();
    cout << *(theAnswers.getStateData(needV)) << endl;

    cout << "*** the state that needs the most help with education**" << endl;
    string noHS = theAnswers.underServeHS();
    cout << *(theAnswers.getStateData(noHS)) << endl;
    cout << "*** the state with most college grads**" << endl;
    string grads = theAnswers.collegeGrads();
    cout << *(theAnswers.getStateData(grads)) << endl;

    cout << "*** the state with most population below the poverty line**" << endl;
    string belowPov = theAnswers.belowPoverty();
    cout << *(theAnswers.getStateData(belowPov)) << endl;
    */
    return 0;
}

