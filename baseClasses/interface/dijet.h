// -*- C++ -*-

#if !defined(dijet_H)
#define dijet_H
#include <iostream>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/jetData.h"
#include "nTupleAnalysis/baseClasses/interface/truthData.h"
#include "nTupleAnalysis/baseClasses/interface/truthParticle.h"

namespace nTupleAnalysis {
  const float mW =  80.4;
  const float mZ =  91.0;
  const float mH = 125.0;

  //dijet object
  class dijet {

  public:
    TLorentzVector p1;
    TLorentzVector p2;

    std::shared_ptr<jet> lead;
    std::shared_ptr<jet> subl;

    TLorentzVector p;
    float dR;
    float st;
    float pt;
    float eta;
    float phi;
    float m;
    float e;

    TLorentzVector pW;
    TLorentzVector pZ;
    TLorentzVector pH;

    float xW;
    float xZ;
    float xH;

    std::shared_ptr<particle> truthMatch = NULL;

    //dijet();
    dijet(std::shared_ptr<jet>&, std::shared_ptr<jet>&, bool undo_bJES=false, nTupleAnalysis::truthData* truth = NULL); 
    ~dijet(); 

    //void dump();
  };

}
#endif // dijet_H

