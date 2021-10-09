// -*- C++ -*-
#if !defined(elecHists_H)
#define elecHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/elecData.h"
#include "nTupleAnalysis/baseClasses/interface/fourVectorHists.h"

namespace nTupleAnalysis {

  class elecHists {
  public:
    TFileDirectory dir;
    
    fourVectorHists* v;

    TH1F* dr03EcalRecHitSumEt        ;
    TH1F* dr03HcalDepth1TowerSumEt   ;
    TH1F* dr03TkSumPt                ;
    TH1F* eCorr                      ;
    TH1F* eInvMinusPInv              ;
    TH1F* hoe                        ;
    TH1F* miniPFRelIso_all           ;
    TH1F* miniPFRelIso_chg           ;
    TH1F* mvaFall17V1Iso             ;
    TH1F* mvaFall17V1noIso           ;
    TH1F* mvaFall17V2Iso             ;
    TH1F* mvaFall17V2noIso           ;
    TH1F* pfRelIso03_all             ;
    TH1F* pfRelIso03_chg             ;
    TH1F* r9                         ;
    TH1F* scEtOverPt                 ;
    TH1F* sieie                      ;
    TH1F* cutBased                   ;
    TH1F* cutBased_Fall17_V1         ;
    TH1F* pdgId                      ;
    TH1F* convVeto                   ;
    TH1F* mvaFall17V2Iso_WP80        ;
    TH1F* mvaFall17V2Iso_WP90        ;
    TH1F* mvaFall17V2Iso_WPL         ;
    TH1F* genPartFlav                ;

    TH1F* nElecs;
    TH1F* SF;

    elecHists(std::string, fwlite::TFileService&, std::string title = "");
    void Fill(const elecPtr&, float);
    ~elecHists(); 

  };

}
#endif // elecHists_H
