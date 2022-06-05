#ifndef REGION_H
#define REGION_H

#include <string>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Visitor;

/* very general data type for any kind of regional data*/
class regionData {
  public:
    regionData(const string inN, const string inS, const int pop) : regionName(inN), population(pop) {
      stateS.insert(inS);
    }
 
    regionData(const string inN, const string inS) : 
    regionName(inN), population(0) {
      stateS.insert(inS);
    }

    string getRegionName() const { return regionName; }
    string getState() const { if (stateS.size() == 1) return *(stateS.begin()); else return "many";  }
    void addState(string inS) { stateS.insert(inS);}
    string printState() const { 
      string s;
      for (std::set<string>::iterator it=stateS.begin(); it != stateS.end(); it++) 
        s += *it + ", ";
      s+= "total states: " + std::to_string(stateS.size());
      return s;
    }
    void setName(string inN) {regionName = inN;}
    int getPop() const { return population; }
    void setPop(int inPop) { population = inPop; }

    //Lab06 anything that is region data must accept a visitor (aka must be visitable)
    virtual void accept(class Visitor &v) = 0;

    virtual void toString(ostream& os) const = 0;

  protected:
  	string regionName; //city or county or place name
    //region data could be more than one state
    std::set<string> stateS; //all regions should have identifying state in US
  	int population; //region population
  	
};
#endif
