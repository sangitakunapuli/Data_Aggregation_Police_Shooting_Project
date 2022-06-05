#ifndef VISITREP_H
#define VISITREP_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "visitor.h"

class visitorReport : public Visitor {
public:
    visitorReport() : numVisited(0) {}

	void visit(shared_ptr<demogData> e) {
        //fill in
    }
    
    void visit(shared_ptr<psData> e) {
        //fill in
    }

    void visit(shared_ptr<psCombo> e) {
        //fill in
    }

//   virtual void visit(const demogData *d) {
//     std::cout << "print summary demog Data:";
//     std::cout << std::setprecision(2) << std::fixed;
//     std::cout << "\nRegion info: " << d->getRegionName() << ", " << d->getState();
//     std::cout << "\nEducation info:" << endl;
//     std::cout << "(Bachelor or more): " << d->getBAupPer() << "\%";
//     std::cout << " and total: " << d->getBAup();
//     std::cout << "\n(high school or more): " << d->getHSupPer() << "\%";
//     std::cout << " and total: " << d->getHSup();
//     std::cout << "\nTotal population: " << d->getPop();
//     std::cout << "\n" << d->getRaces();
//   }

//   virtual void visit(const psCombo *p) {
//     //std::cout << "\nprint aggregate police shooting data";
//     std::cout << "\nState Info: " << p->printState();
//     std::cout << "\nNumber of incidents: " << p->getNumberOfCases();
//     std::cout << std::setprecision(2) << std::fixed;
//     std::cout << "\nRacial demographics of state incidents: " << p->getRacialData() << endl;
//   }

//   virtual void visit(const psData *p) {
//     std::cout << "psData output" << endl;
//   }

    private:
    	int numVisited;
};

#endif