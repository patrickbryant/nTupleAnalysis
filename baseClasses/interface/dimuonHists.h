// -*- C++ -*-
#if !defined(dimuonHists_H)
#define dimuonHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/dimuon.h"
#include "nTupleAnalysis/baseClasses/interface/fourVectorHists.h"
#include "nTupleAnalysis/baseClasses/interface/muonHists.h"

//using namespace nTupleAnalysis;

namespace nTupleAnalysis {

  class dimuonHists {
  public:
    TFileDirectory dir;
    
    fourVectorHists* v;
    TH1F* dR;
    TH1F* dPhi;
    TH1F* nDiMuons;
    TH1F* charge;

    muonHists* lead;
    muonHists* subl;

    dimuonHists(std::string, fwlite::TFileService&, std::string title = "");
    void Fill(std::shared_ptr<dimuon>&, float);
    ~dimuonHists(); 

  };

}
#endif // dimuonHists_H
