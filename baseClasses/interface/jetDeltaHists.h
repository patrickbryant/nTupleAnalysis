// -*- C++ -*-
#if !defined(jetDeltaHists_H)
#define jetDeltaHists_H

#include <iostream>
#include <TH1F.h>
#include <TLorentzVector.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/jetData.h"

namespace nTupleAnalysis {

  class jetDeltaHists {
  public:
    
    TH1F* dPt      = NULL;
    TH1F* dEta     = NULL;
    TH1F* dPhi     = NULL;
    TH1F* dR       = NULL;

    TH1F* ddeepFlavB = NULL;
    TH1F* dcsv     = NULL;
    TH1F* dDeepcsv = NULL;
    TH1F* dntracks    = NULL;
    TH1F* dnseltracks = NULL;
    TH1F* dIp2N     = NULL;
    TH1F* dIp2P     = NULL;
    TH1F* dIp3N     = NULL;
    TH1F* dIp3P     = NULL;
    TH1F* dIp2N_l     = NULL;
    TH1F* dIp2P_l     = NULL;
    TH1F* dIp3N_l     = NULL;
    TH1F* dIp3P_l     = NULL;
    TH1F* dProbaN   = NULL;
    TH1F* dProba    = NULL;
    TH1F* dBprobN   = NULL;
    TH1F* dBprob    = NULL;
    TH1F* dSvx      = NULL;
    TH1F* dSvxHP    = NULL;
    TH1F* dCombIVF  = NULL;
    TH1F* dCombIVF_N= NULL;
    TH1F* dSoftMuN  = NULL;
    TH1F* dSoftMu   = NULL;
    TH1F* dSoftElN  = NULL;
    TH1F* dSoftEl   = NULL;
    TH1F* dcMVAv2   = NULL;
    TH1F* dcMVAv2N  = NULL;

    jetDeltaHists(std::string,       TFileDirectory&, std::string title = "");
    jetDeltaHists(std::string, fwlite::TFileService&, std::string title = "");

    void makeHists(std::string, TFileDirectory&, std::string title);
    void Fill(const std::shared_ptr<nTupleAnalysis::jet> &jet, const std::shared_ptr<nTupleAnalysis::jet> &matchedJet, float weight);

    ~jetDeltaHists(); 

  };

}
#endif // jetDeltaHists_H
