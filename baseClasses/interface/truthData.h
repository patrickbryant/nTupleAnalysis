// -*- C++ -*-

#if !defined(truthData_H)
#define truthData_H

#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"
#include "nTupleAnalysis/baseClasses/interface/truthParticle.h"

// for jet pseudoTag calculations
#include <TRandom3.h>
#include <boost/math/special_functions/binomial.hpp> 

namespace nTupleAnalysis {

  class truthData {

  public:
    // Member variables
    TChain* tree;
    bool isMC;
    std::string year;
    bool debug;

    truthParticle* truthParticles;
    std::vector<particlePtr> Zbbs;//all Z bosons which decayed to bb
    std::vector<particlePtr> Hbbs;//all H bosons which decayed to bb
    std::vector<particlePtr> HWWs;//all H bosons which decayed to WW
    std::vector<particlePtr> Bbbs;//all massive bosons which decayed to bb
    std::vector<particlePtr> Zqqs;//all Z bosons which decayed to qq
    std::vector<particlePtr> Wqqs;//all W bosons which decayed to qq
    std::vector<particlePtr> Wlnus;//all W bosons which decayed to l nu
    std::vector<particlePtr> Vqqs;//all V bosons which decayed to qq

    float m4b;
    float mbbWW;

    // Constructors and member functions
    truthData(TChain*, bool, std::string truthName = "GenPart"); 
    void reset();
    void update();
    void dump();
    ~truthData(); 

  };

}
#endif // truthData_H
