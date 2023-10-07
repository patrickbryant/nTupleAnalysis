// -*- C++ -*-
#if !defined(dijetHists_H)
#define dijetHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/dijet.h"
#include "nTupleAnalysis/baseClasses/interface/fourVectorHists.h"
#include "nTupleAnalysis/baseClasses/interface/jetHists.h"

//using namespace nTupleAnalysis;

namespace nTupleAnalysis {

  class dijetHists {
  public:
    TFileDirectory dir;
    
    fourVectorHists* v;
    TH1F* dR;
    TH1F* dPhi;
    TH1F* nDiJets;
    TH2F* leadPt_vs_sublPt;

    jetHists* lead;
    jetHists* subl;


    dijetHists(std::string, fwlite::TFileService&, std::string title = "");
    void Fill(std::shared_ptr<dijet>&, float);
    ~dijetHists(); 

  };

}
#endif // dijetHists_H
