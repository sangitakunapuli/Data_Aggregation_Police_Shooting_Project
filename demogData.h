#ifndef DEMOG_H
#define DEMOG_H

#include <string>
#include<iostream>
#include <cmath>
#include <memory>
#include "raceDemogData.h"
#include "regionData.h"

using namespace std;

/*
  class to represent county demographic data
  from CORGIS
*/
class demogData : public regionData, public std::enable_shared_from_this<demogData> {
  public:
    demogData(string inN, string inS, int in65, int in18, int in5, int totPop14) : regionData{inN, inS, totPop14},
      popOver65(in65), popUnder18(in18), popUnder5(in5), incUnderPov(0), undergradDeg(0), highSchoolGrad(0) {}

    demogData(string inN, string inS, int in65, int in18, int in5, int ugrad, int hs, int pov, int totPop14, raceDemogData racial) : 
      regionData{inN, inS, totPop14}, popOver65(in65), popUnder18(in18), popUnder5(in5), 
      undergradDeg(ugrad), highSchoolGrad(hs), incUnderPov(pov), raceData(racial) {}
    
    int getBAupCount() const { return undergradDeg; }
    int getHSupCount() const { return highSchoolGrad; }
    int getpopOver65Count() const { return popOver65; }
    int getpopUnder18Count() const { return popUnder18; }
    int getpopUnder5Count() const { return popUnder5; }
    int getBelowPovertyCount() const { return incUnderPov; }
    raceDemogData getRaces() const { return raceData; }

    raceDemogData getCommunityRaceMix() const { /*return variable name for racial demographics of this demographic data*/ return raceData; }
    //int getPop() const { return totalPopulation2014; }
    //string getState() const { return state; } 
    //string getName() const { return name; }

    //getter methods for count
    // int getpopOver65Count() const { return (round((popOver65/100) * population)); }
    // int getpopUnder18Count() const { return (round((popUnder18/100) * population)); }
    // int getpopUnder5Count() const { return (round((popUnder5/100) * population)); }
    // int getBAupCount() const { return (round((undergradDeg/100) * population)); }
    // int getHSupCount() const { return (round((highSchoolGrad/100) * population)); }
    // int getPovCount() const { return (round((incUnderPov/100) * population)); } 


  //calculate percentages (getters)
    double getpopOver65() const { return ((double(popOver65)/population) * 100.0); }
    double getpopUnder18() const { return ((double(popUnder18)/population) * 100.0); }
    double getpopUnder5() const { return ((double(popUnder5)/population) * 100.0); }
    double getBAup() const { return ((double(undergradDeg)/population) * 100.0); }
    double getHSup() const { return ((double(highSchoolGrad)/population) * 100.0); }
    double getBelowPoverty() const { return ((double(incUnderPov)/population) * 100.0); }

   friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

  void toString(ostream& os) const {
    os << *this;
  }

  void accept(class Visitor &v) override;

  protected:
    int popOver65;
    int popUnder18;
    int popUnder5;
    int undergradDeg;
    int highSchoolGrad;
    int incUnderPov;
    raceDemogData raceData;

};
#endif