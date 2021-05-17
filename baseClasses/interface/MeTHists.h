// -*- C++ -*-
#if !defined(MeTHists_H)
#define MeTHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/MeTData.h"

namespace nTupleAnalysis {

  class MeTHists {
  public:
    TFileDirectory dir;
    
    TH1F* pt_s;
    TH1F* pt_m;
    TH1F* pt_l;

    TH1F* phi;

    TH1F* sumEt_s;
    TH1F* sumEt_m;
    TH1F* sumEt_l;

    MeTHists(std::string name, fwlite::TFileService& fs, std::string title = "");
    void Fill(const MetData&, float);
    ~MeTHists(); 

  };

}
#endif // MeTHists_H
