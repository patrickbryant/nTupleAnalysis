// -*- C++ -*-

#if !defined(dimuon_H)
#define dimuon_H
#include <iostream>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/muonData.h"
#include "nTupleAnalysis/baseClasses/interface/truthData.h"
#include "nTupleAnalysis/baseClasses/interface/truthParticle.h"

namespace nTupleAnalysis {
  const float mJpsi =  3.096916;



  //dimuon object
  class dimuon {

  public:
    TLorentzVector p1;
    TLorentzVector p2;

    std::shared_ptr<muon> lead;
    std::shared_ptr<muon> subl;

    TLorentzVector p;
    float dR;
    float dPhi;
    float st;
    float pt;
    float eta;
    float phi;
    float m;
    float e;
    Int_t charge;

    //dimuon();
    dimuon(std::shared_ptr<muon>&, std::shared_ptr<muon>&); 
    ~dimuon(); 

    //void dump();
  };

  typedef std::shared_ptr<dimuon> dimuonPtr;

}
#endif // dimuon_H

