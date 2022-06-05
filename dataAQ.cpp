/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include "psData.h"
#include "regionData.h"
#include "visitorReport.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

class Visitor;

dataAQ::dataAQ() {}

string makeKeyExample(shared_ptr<demogData> theData) {

  string theKey = "Key";

  if (theData->getPovPer() < 10) {
    theKey += "BelowPovLessTenPer";
  } else if (theData->getPovPer() < 20) {
    theKey += "BelowPovLessTwentyPer";
  } else if (theData->getPovPer() < 30) {
    theKey += "BelowPovLessThirtyPer";
  } else {
    theKey += "BelowPovAboveThirtyPer";
  }

  return theKey;
}


// string makeKeyExample(shared_ptr<psData> theData) {

//   string theKey = "Key";
  
//   if (theData->getFleeing() == "Foot") {
//     theKey += "FleeingOnFoot";
//   } else if (theData->getFleeing() == "Car") {
//     theKey += "FleeingByCar";

//   } else if (theData->getFleeing() == "Other") {
//     theKey += "FleeingOtherMeans";
//   } else {
//     theKey += "NotFleeing";
//   }

//   return theKey;
// }

string makeKeyExample(shared_ptr<psData> theData) {

  string theKey = "Key";
  if (theData->getRace() == "W") {
    theKey += "WhiteVictim";
  } else if (theData->getRace() == "A") {
    theKey += "AsianVictim";
  } else if (theData->getRace() == "H") {
    theKey += "HispanicVictim";
  } else if (theData->getRace() == "N") {
    theKey += "NativeAmericanVictim";
  } else if (theData->getRace() == "B") {
    theKey += "AfricanAmericanVictim";
  } else if (theData->getRace() == "O") {
    theKey += "OtherRaceVictim";
  } else {
    theKey += "RaceUnspecifiedVictim";
  }
  return theKey;
}

void dataAQ::comboReport(double thresh) {
    
    std::vector<shared_ptr<regionData>> pileData;

    for (auto entry : allComboDemogData) {
      if ((entry.second)->getHSupPer() > thresh) {
        pileData.push_back(entry.second);
        pileData.push_back(allComboPoliceData[entry.first]);
        //cout << "pushed to hashmap" << endl;
      }
    }

    visitorReport report;
    for (const auto &obj : pileData) {
        //cout << "iterating through pileData" << endl;
        obj->accept(report);
    }
}


//swtich to a function parameter
void dataAQ::createComboDemogDataKey(std::vector<shared_ptr<demogData> >& theData) {

  for (auto county : theData) {
    std::string keyName = makeKeyExample(county);
    if (allComboDemogData.count(keyName) == 0) {
        auto myCounty = make_shared<demogCombo>(county->getState(), "comboData", county->getpopOver65(), county->getpopUnder18(),
          county->getpopUnder5(), county->getBAup(), county->getHSup(),
          county->getIncUnderPov(), county->getPop(), 1, county->getRaces(), keyName);
        allComboDemogData[keyName] = myCounty; // create key-value pair in hashmap
    }
    else {
        // key exists in hashmap, aggregate counties
        allComboDemogData[keyName]->aggregateArea(county);
    }
  }
}


void dataAQ::createComboPoliceDataKey(std::vector<shared_ptr<psData> >& theData) {

  for (auto pCase : theData) {
    std::string keyName = makeKeyExample(pCase);
    if (allComboPoliceData.count(keyName) == 0) {
        auto myCase = make_shared<psCombo>(pCase->getState(), keyName, pCase->isMentalIll(), pCase->isFlee(),
          pCase->isOver65(), pCase->isUnder18(), pCase->isMale(), pCase->isFemale(), 1);
        myCase->addNewRace(pCase->getRace());
        allComboPoliceData[keyName] = myCase; // create key-value pair in hashmap
    }
    else {
        // key exists in hashmap, aggregate cases
        allComboPoliceData[keyName]->aggregateCases(pCase);
        allComboPoliceData[keyName]->addNewRace(pCase->getRace());
    }
  }
}

/******************************************/
/* state examples*/ 
void dataAQ::createComboDemogData(std::vector<shared_ptr<demogData> >&  theData) {
  for (auto dataStat : theData) {
    std::string currRegion = dataStat->getState();

    if (allComboDemogData.count(currRegion) == 0) {     // map::count() returns 1 if key is present and 0 if not present
      // create new demogState obj
      auto myState = make_shared<demogCombo>(currRegion, "comboData", dataStat->getpopOver65(), dataStat->getpopUnder18(),
          dataStat->getpopUnder5(), dataStat->getBAup(), dataStat->getHSup(),
          dataStat->getIncUnderPov(), dataStat->getPop(), 1, dataStat->getRaces(), "state");

      allComboDemogData[currRegion] = myState; // create key-value pair in hashmap
    } else {
      // state exists in hashmap, aggregate counts
      allComboDemogData[currRegion]->aggregateArea(dataStat);
    }
  }
}

void dataAQ::createComboPoliceData(std::vector<shared_ptr<psData> >& theData) {
for (auto dataStat : theData) {
    std::string currRegion = dataStat->getState();

    if (allComboPoliceData.count(currRegion) == 0) {     // map::count() returns 1 if key is present and 0 if not present
      // create new demogState obj
      auto myRegion = make_shared<psCombo>(currRegion, dataStat->getState(), dataStat->isMentalIll(), dataStat->isFlee(),
        dataStat->isOver65(), dataStat->isUnder18(), dataStat->isMale(), dataStat->isFemale(), 1);

      myRegion->addNewRace(dataStat->getRace());

      allComboPoliceData[currRegion] = myRegion; // create key-value pair in hashmap
    } else {
      // state exists in hashmap, aggregate counts
      allComboPoliceData[currRegion]->aggregateCases(dataStat);
      allComboPoliceData[currRegion]->addNewRace(dataStat->getRace());
    }
  }
}

// compare predicate functions, used in reportTopTenState functions
bool compareShootings(shared_ptr<psCombo> x, shared_ptr<psCombo> y)
{
  return (x->getNumberOfCases() > y->getNumberOfCases());
}

bool comparePoverty(shared_ptr<demogCombo> x, shared_ptr<demogCombo> y)
{
  return (x->getPovPer() > y->getPovPer());
}


//sort and report the top ten states in terms of number of police shootings 
void dataAQ::reportTopTenStatesPS() { 
  //push back hashmap values into a vector
  std::vector<shared_ptr<psCombo>> p_shoot;
  for (auto entry : allComboPoliceData) {
    p_shoot.push_back(entry.second);
  }

  //sort using std::sort
  std::sort(p_shoot.begin(), p_shoot.end(), compareShootings);

  //printing top 10
  for (int i = 0; i < 10; i++) {
      std::cout << p_shoot[i]->getState() << endl;
      std::cout << "Total population: " << allComboDemogData[p_shoot[i]->getState()]->getPop(); //seg faulting
      std::cout << std::setprecision(2) << std::fixed;
      std::cout << "\nPolice shooting incidents: " << p_shoot[i]->getNumberOfCases();
      std::cout << "\nPercent below poverty: " << allComboDemogData[p_shoot[i]->getState()]->getPovPer() << endl;
    }

  //printing details for top 3
  std::cout << "**Full listings for top 3 Police Shooting data & the associated below poverty data for top 3:" << endl;
  for (int i = 0; i < 3; i++) {
    std::cout << *p_shoot[i] << endl; //psState object
    std::cout << "**Below Poverty Data:" << *(allComboDemogData[p_shoot[i]->getState()]) << endl;
  }
}

//sort and report the top ten states with largest population below poverty 
void dataAQ::reportTopTenStatesBP(){ 
  //push back hashmap values into a vector
  std::vector<shared_ptr<demogCombo>> poverty;
  for (auto entry : allComboDemogData) {
    poverty.push_back(entry.second);
  }

  //sort using std::sort
  std::sort(poverty.begin(), poverty.end(), comparePoverty);

  //giving top ten based on below poverty
  for (int i = 0; i < 10; i++) {
      std::cout << poverty[i]->getRegionName() << endl;
      std::cout << "Total population: " << allComboDemogData[poverty[i]->getRegionName()]->getPop();
      std::cout << std::setprecision(2) << std::fixed;
      std::cout << "\nPercent below poverty: " << allComboDemogData[poverty[i]->getRegionName()]->getPovPer();
      std::cout << "\nPolice shooting incidents: " << allComboPoliceData[poverty[i]->getRegionName()]->getNumberOfCases() << endl;
  }
  //printing details for top 3
  std::cout << "**Full listings for top 3 Below Poverty data & the associated police shooting data for top 3:" << endl;
  for (int i = 0; i < 3; i++) {
    std::cout << "State info: " << poverty[i]->getRegionName();
    std::cout << *poverty[i] << endl; //demogState obj
    std::cout << "**Police shooting incidents:" << *(allComboPoliceData[poverty[i]->getRegionName()]) << endl;
  }
}


/* print all combo data */
std::ostream& operator<<(std::ostream &out, const dataAQ &theAnswers) {
  out << "Combo Demographic Info: ";
  for (auto const& entry : theAnswers.allComboDemogData) {
      out << "key: " << entry.first << endl;
      out << *(entry.second) << "\n";

  }

  for (auto const& entry : theAnswers.allComboPoliceData) {
      out << "key: " << entry.first << endl;
      out << *(entry.second) << "\n";

  }

  return out;
}