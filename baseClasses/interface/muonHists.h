// -*- C++ -*-
#if !defined(muonHists_H)
#define muonHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/muonData.h"
#include "nTupleAnalysis/baseClasses/interface/fourVectorHists.h"

namespace nTupleAnalysis {

  class muonHists {
  public:
    TFileDirectory dir;
    
    fourVectorHists* v;
    TH1F* quality;
    //TH1F* isolation;
    //TH1F* isolation_cor;
    //TH1F* isolation_cor_s;
    TH1F* dR;
    TH1F* nMuons;
    TH1F* SF;

    TH1F* ip3d            ;
    TH1F* ip3d_l            ;
    TH1F* sip3d  	      ;
    TH1F* sip3d_l  	      ;
    TH1F* pfRelIso03_all  ;
    TH1F* pfRelIso03_chg  ;
    TH1F* ptErr           ;
    TH1F* tkRelIso        ;
    TH1F* pdgId           ;
    TH1F* looseId         ;
    TH1F* mediumPromptId  ;
    TH1F* mvaId           ;
    TH1F* pfIsoId         ;
    TH1F* tkIsoId         ;
    TH1F* genPartFlav     ;

    TH1F* dxybs            ;
    TH1F* dz               ;
    TH1F* dzErr            ;
    TH1F* miniPFRelIso_all ;
    TH1F* miniPFRelIso_chg ;
    TH1F* mvaTTH           ;
    TH1F* nStations        ;
    TH1F* nTrackerLayers   ;
    TH1F* highPurity       ;
    TH1F* cleanmask        ;


    muonHists(std::string, fwlite::TFileService&, std::string title = "");
    void Fill(const muonPtr&, float);
    ~muonHists(); 

  };

}
#endif // muonHists_H
