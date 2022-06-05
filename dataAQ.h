#ifndef DATAAQ_H
#define DATAAQ_H

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "demogCombo.h"
#include "psCombo.h"

/*
  data aggregator and query for testing
*/
class dataAQ {
  public:
    dataAQ();

    /* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
    void createComboDemogData(std::vector<shared_ptr<demogData> >& theData);
    void createComboPoliceData(std::vector<shared_ptr<psData> >& theData);

    void createComboDemogDataKey(std::vector<shared_ptr<demogData> >& theData);
    void createComboPoliceDataKey(std::vector<shared_ptr<psData> >& theData);

    //sort and report the top ten states in terms of number of police shootings 
    void reportTopTenStatesPS();
    //sort and report the top ten states with largest population below poverty 
    void reportTopTenStatesBP();

    shared_ptr<demogCombo> getComboDemogData(string regionName) { return allComboDemogData[regionName]; }
    shared_ptr<psCombo> getComboPoliceData(string regionName) { return allComboPoliceData[regionName]; }

    void comboReport(double thresh);
    
   friend std::ostream& operator<<(std::ostream &out, const dataAQ &comboData);

    //this quarter restriction
    private:
       std::map<string, shared_ptr<demogCombo> > allComboDemogData;

       std::map<string, shared_ptr<psCombo> > allComboPoliceData;

};
#endif
