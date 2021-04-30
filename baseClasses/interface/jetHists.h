// -*- C++ -*-
#if !defined(jetHists_H)
#define jetHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/jetData.h"
#include "nTupleAnalysis/baseClasses/interface/fourVectorHists.h"
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

    TH1F*   SoftMu     ;
    TH1F*   nSoftMu        ;
    TH1F*   pt_wo_bRegCorr;
    TH1F*   bRegCorr;

    TH1F*   SoftEl     ;
    TH1F*   nSoftEl        ;

    TH1F* flavour       ;
    TH1F* flavourCleaned;
    TH1F* partonFlavour ;
    TH1F* hadronFlavour ;
    TH1F* nbHadrons     ;
    TH1F* ncHadrons     ;
    TH1F* SF     ;

    TH1F* matched_dPt      = NULL;
    TH1F* matched_dEta     ;
    TH1F* matched_dPhi     ;
    TH1F* matched_dR       ;
    TH1F* matched_dcsv     ;
    TH1F* matched_dDeepcsv ;

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
