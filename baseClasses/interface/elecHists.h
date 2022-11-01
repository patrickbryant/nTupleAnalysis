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
    TH1F* eInvMinusPInv              ;
    TH1F* hoe                        ;
    TH1F* miniPFRelIso_all           ;
    TH1F* miniPFRelIso_chg           ;
    TH1F* pfRelIso03_all             ;
    TH1F* pfRelIso03_chg             ;
    TH1F* r9                         ;
    TH1F* scEtOverPt                 ;
    TH1F* sieie                      ;
    TH1F* cutBased                   ;
    TH1F* pdgId                      ;
    TH1F* convVeto                   ;
    TH1F* genPartFlav                ;

    TH1F* deltaEtaSC    ;
    TH1F* dxy           ;
    TH1F* dxyErr        ;
    TH1F* dz            ;
    TH1F* dzErr         ;
    TH1F* energyErr     ;
    TH1F* ip3d          ;
    TH1F* jetPtRelv2    ;
    TH1F* jetRelIso     ;
    TH1F* mvaHZZIso     ;
    TH1F* mvaIso        ;
    TH1F* mvaNoIso      ;
    TH1F* sip3d         ;
    TH1F* mvaTTH        ;
    TH1F* mvaIso_WP80   ;
    TH1F* mvaIso_WP90   ;
    TH1F* mvaIso_WPL    ;
    TH1F* mvaNoIso_WP80 ;
    TH1F* mvaNoIso_WP90 ;
    TH1F* mvaNoIso_WPL  ;
    TH1F* jetIdx        ;
    TH1F* tightCharge   ;
    TH1F* charge        ;
    TH1F* lostHits      ;


    TH1F* nElecs;
    TH1F* SF;

    elecHists(std::string, fwlite::TFileService&, std::string title = "");
    void Fill(const elecPtr&, float);
    ~elecHists(); 

  };

}
#endif // elecHists_H
