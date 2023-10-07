// -*- C++ -*-
#if !defined(truthParticleHists_H)
#define truthParticleHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/truthParticle.h"
#include "nTupleAnalysis/baseClasses/interface/fourVectorHists.h"

namespace nTupleAnalysis {

  class truthParticleHists {
  public:
    TFileDirectory dir;
    
    fourVectorHists* v;
    TH1F* pdgId;
    TH1F* partonFlavour ;
    TH1F* hadronFlavour ;

    truthParticleHists(std::string name, fwlite::TFileService& fs, std::string title = "");
    truthParticleHists(std::string name, TFileDirectory& dir, std::string title = "");
    void makeHists(std::string name, TFileDirectory& dir, std::string title = "");
    void Fill(const particlePtr& truthP, float weight);
    ~truthParticleHists(); 

  };

}
#endif // truthParticleHists_H
