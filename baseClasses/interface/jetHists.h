// -*- C++ -*-
#if !defined(jetHists_H)
#define jetHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/jetData.h"
#include "nTupleAnalysis/baseClasses/interface/fourVectorHists.h"
#include "nTupleAnalysis/baseClasses/interface/jetDeltaHists.h"
#include "nTupleAnalysis/baseClasses/interface/trackHists.h"
#include "nTupleAnalysis/baseClasses/interface/btaggingHists.h"

namespace nTupleAnalysis {

  class jetHists {
  public:
    bool debug;
    TFileDirectory dir;
    
    fourVectorHists* v;
    TH1F* cleanmask;
    TH1F* puId;
    TH1F* jetId;
    TH1F* deepB;
    TH1F* CSVv2;
    TH1F* deepFlavB;
    TH1F* nJets;
    TH1F* nTrksExpected;

    TH1F*   ntracks    ;
    TH1F*   nseltracks ;
    TH1F*   CSVv2_l    ;
    TH1F*   deepCSV_l    ;
    TH1F*   deepCSVb_l    ;
    TH1F*   deepCSVbb_l    ;

    TH1F*   nSoftMu        ;
    TH1F*   pt_wo_bRegCorr;
    TH1F*   bRegCorr;

    TH1F*   nSoftEl        ;

    TH1F* flavour       ;
    TH1F* flavourCleaned;
    TH1F* partonFlavour ;
    TH1F* hadronFlavour ;
    TH1F* nbHadrons     ;
    TH1F* ncHadrons     ;
    TH1F* SF     ;

    jetDeltaHists* hMatchedJet = NULL;

    TH1F* Ip2N     = NULL;
    TH1F* Ip2P     = NULL;
    TH1F* Ip3N     = NULL;
    TH1F* Ip3P     = NULL;
    TH1F* Ip2N_l     = NULL;
    TH1F* Ip2P_l     = NULL;
    TH1F* Ip3N_l     = NULL;
    TH1F* Ip3P_l     = NULL;
    TH1F* ProbaN   = NULL;
    TH1F* Proba    = NULL;
    TH1F* BprobN   = NULL;
    TH1F* Bprob    = NULL;
    TH1F* Svx      = NULL;
    TH1F* SvxHP    = NULL;
    TH1F* CombIVF  = NULL;
    TH1F* CombIVF_N= NULL;
    TH1F* SoftMuN  = NULL;
    TH1F* SoftMu   = NULL;
    TH1F* SoftElN  = NULL;
    TH1F* SoftEl   = NULL;
    TH1F* cMVAv2   = NULL;
    TH1F* cMVAv2N  = NULL;


    TH1F* matched_dRAll    = NULL ;
    TH1F* matched_dRBjet   = NULL ;

    TH1F*   deepCSV_reCalc = NULL;
    TH1F*   delta_deepCSV    ;

    trackHists* tracks = NULL;
    trackHists* tracks_noV0 = NULL;

    btaggingHists* btags = NULL;
    btaggingHists* btags_noV0 = NULL;
    
    TH1F* Delta_nTracks_tracks_btag = NULL;
    TH1F* Delta_nTracks_tracks_btag_noV0 = NULL;
    TH1F* Delta_nTracks_tracks_btag_l = NULL;
    TH1F* Delta_nTracks_tracks_btag_noV0_l = NULL;

    std::string name;
    std::string title;

    jetHists(std::string, fwlite::TFileService&, std::string _title = "", std::string jetDetailLevel = "", bool _debug = false);
    void Fill(const std::shared_ptr<jet>&, float);
    ~jetHists(); 

  };

}
#endif // jetHists_H
