#ifndef COMBODEMOG_H
#define COMBODEMOG_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "raceDemogData.h"

/*
  class to represent combined demographic data 
*/
class demogCombo : public demogData {
  public:
  demogCombo(std::string stateName, std::string region, int in65, int in18, int in5, int undergrad, 
    int highSchool, int incomeUnderPov, int totPop14, int numAreas, raceDemogData races, std::string aggregator) : 
      demogData{region, stateName, in65, in18, in5, undergrad, highSchool, incomeUnderPov, totPop14, races},
      numRegions(numAreas), key(aggregator) {}

  friend std::ostream& operator<<(std::ostream &out, const demogCombo &SD);

    //setters for aggregation
    void addBAup(int ba) { undergradDeg += ba; }
    void addHSup(int hs) { highSchoolGrad += hs; }
    void addpopOver65(int over65) { popOver65 += over65; }
    void addpopUnder18(int under18) { popUnder18 += under18; }
    void addpopUnder5(int under5) { popUnder5 += under5; }
    void addIncUnderPov(int inPov) { incUnderPov += inPov; }
    void addPop(int pop) { population += pop; }
    void addNumRegions(int num) { numRegions += num; }

    int getNumRegions() const { return numRegions; }

    //getter for the key
    std::string getKey() const { return key; }
    
    //aggregating helper fn
    void aggregateArea(shared_ptr<demogData> d) {
      numRegions += 1;
      popOver65 += d->getpopOver65Count();
      popUnder18 += d->getpopUnder18Count();
      popUnder5 += d->getpopUnder5Count();
      incUnderPov += d->getBelowPovertyCount();
      undergradDeg += d->getBAupCount();
      highSchoolGrad += d->getHSupCount();
      population += d->getPop();
      raceData += d->getRaces();
      addState(d->getState());
    }

    void toString(ostream& os) const {
      os << *this;
    }

private:
    int numRegions; // number of regions within the area being aggregated
    std::string key; // what we are aggregating by
};
#endif