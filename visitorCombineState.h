#ifndef VCOMBOS_H
#define VCOMBOS_H


#include "visitorCombine.h"
#include <memory>

class visitorCombineState : public visitorCombine {
public:
    visitorCombineState() {}

	void visit(shared_ptr<demogData> obj) {
        std::string state = obj->getState();

        if (allComboDemogData.count(state) == 0) {     // map::count() returns 1 if key is present and 0 if not present
        // create new demogCombo obj
        auto myState = make_shared<demogCombo>(state, "comboState", obj->getpopOver65Count(), obj->getpopUnder18Count(),
            obj->getpopUnder5Count(), obj->getBAupCount(), obj->getHSupCount(),
            obj->getBelowPovertyCount(), obj->getPop(), 1, obj->getRaces(), "state");

        allComboDemogData[state] = myState; // create key-value pair in hashmap
        } else {
        // state exists in hashmap, aggregate counts
        allComboDemogData[state]->aggregateArea(obj);
        }
    }
    
    void visit(shared_ptr<psData> obj) {
        std::string currState = obj->getState();
        if (allComboPoliceData.count(currState) == 0) {     // map::count() returns 1 if key is present and 0 if not present
        // create new demogState obj
        auto myState = make_shared<psCombo>(currState, obj->getState(), obj->isMentalIll(), obj->isFlee(),
            obj->isOver65(), obj->isUnder18(), obj->isMale(), obj->isFemale(), 1);

        myState->addNewRace(obj->getRace());
        allComboPoliceData[currState] = myState; // create key-value pair in hashmap
        
        } else {
        // state exists in hashmap, aggregate counts
        allComboPoliceData[currState]->aggregateCases(obj);
        allComboPoliceData[currState]->addNewRace(obj->getRace());
        }
    }

    void visit(shared_ptr<psCombo> obj) {
        //placeholder
    }
    private:
       //inherited
};

#endif
