#ifndef POLICE_H
#define POLICE_H

#include <string>
#include <iostream>
#include <utility>
#include <memory>
#include "raceDemogData.h"
#include "regionData.h"

using namespace std;

/*
  class to represent police shooting data
  from CORGIS
*/
class psData : public regionData, public std::enable_shared_from_this<psData> {
  public:
    //add appropriate function paramaters to constructor once you add data
    psData(string inState, string theName, int theAge, string theGender, string theRace, string theCity, bool theCondition, string theFlee) : regionData{theCity, inState},
      name(theName), age(theAge), gender(theGender), race(theRace), signs_of_mental_illness(theCondition), flee(theFlee) {}

    //string getState() const { return state; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const { return gender; }
    string getRace() const { return race; }
    bool getMentalIll() const { return signs_of_mental_illness; }
    string getFlee() const { return flee; }

    //getters for aggregating the individual case stats (1 represents the condition is true for a given case, 0 is false)
    int isFemale() const { if(gender == "F") { return 1; } else { return 0; }}
    int isMale() const { if(gender == "M") { return 1; } else { return 0; }}
    int isMentalIll() const { if(signs_of_mental_illness) { return 1; } else { return 0; }}
    int isFlee() const { if(flee == "Not fleeing" || flee == "") { return 0; } else if (flee == "Car" || flee == "Foot" || flee == "Other") { return 1; }}
    int isOver65() const { if (age >= 65) { return 1; } else { return 0; }}
    int isUnder18() const { if (age <= 18) { return 1; } else { return 0; }}

   friend std::ostream& operator<<(std::ostream &out, const psData &PD);

   void toString(ostream& os) const {
      os << *this;
   }

  void accept(class Visitor &v) override;

private:
    const string name;
    const int age;
    const string gender;
    const string race;
    const bool signs_of_mental_illness;
    const string flee;
};

#endif
