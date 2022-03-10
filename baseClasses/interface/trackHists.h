// -*- C++ -*-
#if !defined(trackHists_H)
#define trackHists_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include <TProfile.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/trackData.h"
#include "nTupleAnalysis/baseClasses/interface/fourVectorHists.h"

namespace nTupleAnalysis {

  class trackHists {
  public:
    
    fourVectorHists* v;
        
    TH1F* ip3d_l ;
    TH1F* ip3d   ;
    
    TH1F* ip3d_sig_l;
    TH1F* ip3d_sig  ;
    
    TH1F* ip3d_err_l;
    TH1F* ip3d_err  ;
    
    TH1F* ip2d_l ;
    TH1F* ip2d   ;
    
    
    TH2F* ip2d_vs_pt;

    TH2F* ip2d_vs_eta;


    TH1F* ip2d_sig_l;
    TH1F* ip2d_sig;
        
    TH1F* ip2d_err_l;
    TH1F* ip2d_err;
    
    TH1F* trackDecayLenVal_l ;
    TH1F* trackDecayLenVal;
    TH1F* trackJetDistVal ;    
    TH1F* trackPtRel      ; 
    TH1F* trackMomentum   ;
    TH1F* trackPt   ;
    TH1F* trackPt_l   ;
    
    TH1F* trackPt_logx           ;

    TH1F* trackEta           ;       
    TH1F* trackPhi           ;       
    TH1F* trackPPar          ;       
    TH1F* trackDeltaR        ;       
    TH1F* trackDeltaR_l        ;       
    TH1F* trackEtaRel        ;       
    TH1F* trackPtRatio       ;       
    TH1F* trackPParRatio     ;       
    
    TH1F* trackChi2          ;       
    TH1F* trackNTotalHits    ;       
    TH1F* trackNPixelHits    ;       
    TH1F* trackNStripHits    ;       
    TH1F* trackHasInnerPixHit;       

    TProfile* trackHasInnerPixHit_vs_eta;
    TProfile* trackHasInnerPixHit_vs_phi;
    TProfile* trackHasInnerPixHit_vs_phi_f;
    TProfile* trackHasInnerPixHit_vs_pt;
    TProfile* trackHasInnerPixHit_vs_dR;

    TH1F* nMatches;

    TH1F* track_matched_dip2d;
    TH2F* track_matched_phi_vs_dip2d;
    TH2F* track_matched_eta_vs_dip2d;
    TH1F* track_matched_dPtRel   ; 
    TH1F* track_matched_dMomentum; 
    TH1F* track_matched_dEta     ;  
    TH1F* track_matched_dEta_s   ;    
    TH1F* track_matched_dPhi     ;   
    TH1F* track_matched_dR       ; 
    TH1F* track_matched_dR_s     ; 

    TH2F* track_matched_dEta_vs_dMomentum;
    TH2F* track_matched_dEta_vs_dPhi;

    TH1F* track_secondClosest_dEta              ;
    TH1F* track_secondClosest_dEta_s    	;
    TH1F* track_secondClosest_dMomentum 	;
    TH1F* track_secondClosest_dR        	;
    TH1F* track_secondClosest_dR_s      	;
    TH2F* track_secondClosest_dEta_vs_dMomentum	;
    TH1F* track_dEta12                          ;

    TH1F* nTracks;
    TH1F* trackCharge    ;
    TH1F* trackIsFromSV  ;
    TH1F* trackIsFromV0  ;
    TH1F* trackAlgo      ;
    TH1F* trackOrigAlgo  ;

    TH1F* PV  ;
    TH1F* PVweight  ;
    TH1F* SV  ;
    TH1F* SVweight  ;

    //
    // Eta/Phi Maps
    //
    TH2F* nTrackMap;
    TH2F* pixHitMap;
    TH2F* stripHitMap;
    TH2F* totHitMap;
    TH2F* innerPixHitMap;
    TH2F* noInnerPixHitMap;


    //
    // For Algo study
    //
    const unsigned int nAlgos = 30;
    std::vector<TH1F*> trackEta_forAlgo;
    std::vector<TH1F*> trackPhi_forAlgo;
    std::vector<TH1F*> trackPt_forAlgo;

    

    trackHists(std::string,       TFileDirectory&, std::string title = "");
    trackHists(std::string, fwlite::TFileService&, std::string title = "");

    void makeHists(std::string, TFileDirectory&, std::string title);
    void Fill(const trackPtr&, float);
    void FillMatchStats(const trackPtr&, float);

    ~trackHists(); 

  };

}
#endif // trackHists_H
