#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include "raceDemogData.h"
#include "psData.h"
#include "regionData.h"
#include <memory>
#include <cassert>

using namespace std;

class psCombo : public regionData, public std::enable_shared_from_this<psCombo>  {
public:
    //write psCombo constructor
    psCombo(string inS, string agg, int ill, int flee, int o65, int u18, int male, int female, int caseCount) : regionData{agg, inS},
      numIll(ill), fleeing(flee), over65(o65), under18(u18), numMale(male), numFemale(female), numCases(caseCount) {}

    psCombo(string inS, string agg, int ill, int flee, int o65, int u18, int male, int female, int caseCount, raceDemogData race) : regionData{agg, inS},
      numIll(ill), fleeing(flee), over65(o65), under18(u18), numMale(male), numFemale(female), raceStats(race), numCases(caseCount) {}
    //getters
    int getNumMentalI() const { return numIll; }
    int getFleeingCount() const { return fleeing; }
    int getCasesOver65() const { return over65; }
    int getCasesUnder18() const { return under18; }
    raceDemogData getRacialData() const { return raceStats; }
    int getnumMales() const { return numMale; }
    int getnumFemales() const { return numFemale; }
    int getNumberOfCases() const { return numCases; }

    //setters for aggregation
    void addMentallyIll() { numIll++; }
    void addFleeing() { fleeing++; }
    void addOver65() { over65++; }
    void addUnder18() { under18++; }
    void addRaceData(raceDemogData r) { raceStats += r; }
    void addMale() { numMale++; }
    void addFemale() {numFemale++; }
    void addCase() { numCases++; }


    void addNewRace(std::string raceStr) {
      if (raceStr == "W") { 
        raceStats.addWhiteCount(1);
        raceStats.addCommunityCount(1); //double count the White population in total Community Count
        raceStats.addWhiteNHCount(1);
        raceStats.addCommunityCount(1);
      } else if (raceStr == "B") {
        raceStats.addBlackCount(1);
        raceStats.addCommunityCount(1);
      } else if (raceStr == "A") {
        raceStats.addAsianCount(1);
        raceStats.addCommunityCount(1);
      } else if (raceStr == "N") {
        raceStats.addFirstNationCount(1);
        raceStats.addCommunityCount(1);
      } else if (raceStr == "H") {
        raceStats.addLatinxCount(1);
        raceStats.addCommunityCount(1);
      } else if (raceStr == "O") {
        raceStats.addOtherCount(1);
        raceStats.addCommunityCount(1);
      } else {
        //raceStats.addOtherCount(1);
        //raceStats.addCommunityCount(1);
      }
    }

    //percentage getters
    double get65Per() const { return ((double(over65)/numCases) * 100); }
    double get18Per() const { return ((double(under18)/numCases) * 100); }
    double getMIPer() const { return ((double(numIll)/numCases) * 100); }
    double getFleePer() const { return ((double(fleeing)/numCases) * 100); }

    //race getters
    int getWhiteNH() const { return (raceStats.getWhiteNHCount()); }
    int getBlack() const { return (raceStats.getBlackCount()); }
    
    void aggregateCases(shared_ptr<psData> c) {
      numCases += 1;
      over65 += c->isOver65();
      under18 += c->isUnder18();
      numMale += c->isMale();
      numFemale += c->isFemale();
      numIll += c->isMentalIll();
      if (c->isFlee()) {
        fleeing++;
      }
      addState(c->getState());
    }

    friend std::ostream& operator<<(std::ostream &out, const psCombo& PD);

    void toString(ostream& os) const {
      os << *this;
    }

    void accept(class Visitor &v) override;

protected:
    int numIll;
    int fleeing;
    int over65;
    int under18;
    int numMale;
    int numFemale;
    int numCases;
    raceDemogData raceStats;
};

#endif