#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include "parse.h"
#include <string>
#include <memory>
#include <fstream>
#include <cassert>

class visitorCombineCounty : public visitorCombine {
public:
    visitorCombineCounty() {
    }

    //store demographic data by county name
	void visit(shared_ptr<demogData> obj) {
        //fill in
        std::string countyKey = obj->getRegionName();
        //strip county from the name and concatenate the state to make a unique key
        std::string county = "County";
        size_t found = countyKey.find(county);
        if (found != std::string::npos) {
            countyKey.erase(found-1, county.length()+1);
        }
        countyKey.append(obj->getState()); //add the state to end of county name -- county var now represents a key


        if (allComboDemogData.count(countyKey) == 0) {     // map::count() returns 1 if key is present and 0 if not present
        // create new demogCombo obj
        auto myCounty = make_shared<demogCombo>(obj->getState(), "comboCounty", obj->getpopOver65Count(), obj->getpopUnder18Count(),
            obj->getpopUnder5Count(), obj->getBAupCount(), obj->getHSupCount(),
            obj->getBelowPovertyCount(), obj->getPop(), 1, obj->getRaces(), "county");

        allComboDemogData[countyKey] = myCounty; // create key-value pair in hashmap
        } else {
        // county exists in hashmap, aggregate counts
        allComboDemogData[countyKey]->aggregateArea(obj);
        }
    }
    
    //aggregate police shooting data by county
    void visit(shared_ptr<psData> obj) {
        std::string city = obj->getRegionName();
        std::string county = "County";
        size_t found = city.find(county);
        if (found != std::string::npos) {
            city.erase(found-1, county.length()+1);
        }
        city.append(obj->getState()); //add the state to end of county name -- county var now represents a key

        if (allComboPoliceData.count(city) == 0) {     // map::count() returns 1 if key is present and 0 if not present
            // create new demogState obj
            auto myRegion = make_shared<psCombo>(city, obj->getState(), obj->isMentalIll(), obj->isFlee(),
                obj->isOver65(), obj->isUnder18(), obj->isMale(), obj->isFemale(), 1);

            myRegion->addNewRace(obj->getRace());
            allComboPoliceData[city] = myRegion; // create key-value pair in hashmap
        
        } else {
        // state exists in hashmap, aggregate counts
            allComboPoliceData[city]->aggregateCases(obj);
            allComboPoliceData[city]->addNewRace(obj->getRace());
        }
    }
    
    void visit(shared_ptr<psCombo> obj) {
        //placeholder
    }

    private:
        //only inherited data at this point
};

#endif
