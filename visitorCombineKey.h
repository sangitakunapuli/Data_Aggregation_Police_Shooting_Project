#ifndef VCOMBOK_H
#define VCOMBOK_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include <memory>


class visitorCombineKey : public visitorCombine {
public:
    visitorCombineKey(string (*df)(shared_ptr<demogData>), string (*psf)(shared_ptr<psData>)) {
      demogFunc = df;
      psFunc =psf; 
   }

	void visit(shared_ptr<demogData> obj) {
        //wait to fill in
    }
    
    void visit(shared_ptr<psData> obj) {
        //wait to fill in
    }

    private:
      //the function pointers to the key functions
      string (*demogFunc)(shared_ptr<demogData>);
      string (*psFunc)(shared_ptr<psData>);
};

#endif
