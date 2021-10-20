// -*- C++ -*-
#if !defined(btaggingDeltaHists_H)
#define btaggingDeltaHists_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/btaggingData.h"
#include "nTupleAnalysis/baseClasses/interface/jetData.h"

namespace nTupleAnalysis {

  class btaggingDeltaHists {
  public:
    
    //SV Hists
    TH1F*   dsv_NTracks                    ;
    TH1F*   dsv_Mass                       ;
    TH1F*   dsv_JetDeltaR                  ;
    TH1F*   dsv_FitProb                    ;
    TH1F*   dsv_EnergyRatio                ;
    TH1F*   dsv_R          ;
    TH1F*   dsv_Z          ;
    TH1F*   dsv_Chi2       ;
    TH1F*   dsv_Chi2_l       ;
    TH1F*   dsv_NDF        ;
    TH1F*   dsv_Flight     ;
    TH1F*   dsv_FlightSig  ;
    TH1F*   dsv_Flight2D   ;
    TH1F*   dsv_FlightSig2D;
    TH1F*   dsv_Pt         ;
    TH1F*   dsv_Eta        ;
    TH1F*   dsv_Phi        ;
    TH1F*   dsv_DistJetAxis;
    TH1F*   dsv_nSVs;
    TH1F*   dsv_boostOverSqrtJetPt;
    TH1F*   dsv_massVertexEnergyFraction;
    TH1F*   dsv_totCharge;

    //TrkTagVar Hists
    TH1F* dtrkTag_ip3d_l ;
    TH1F* dtrkTag_ip3d   ;
    TH1F* dtrkTag_ip3d_sig_l;
    TH1F* dtrkTag_ip3d_sig  ;
    TH1F* dtrkTag_ip3d_err_l;
    TH1F* dtrkTag_ip3d_err  ;

    TH1F* dtrkTag_ip2d_l ;
    TH1F* dtrkTag_ip2d   ;
    TH1F* dtrkTag_ip2d_sig_l;
    TH1F* dtrkTag_ip2d_sig;
    TH1F* dtrkTag_ip2d_err_l;
    TH1F* dtrkTag_ip2d_err;
    
    TH1F* dtrkTag_trackDecayLenVal_l ;
    TH1F* dtrkTag_trackDecayLenVal;
    TH1F* dtrkTag_trackJetDistVal ;    
    TH1F* dtrkTag_trackJetDistSig ;    
    TH1F* dtrkTag_trackPt_logx           ;
    TH1F* dtrkTag_trackMomentum   ;
    TH1F* dtrkTag_trackPt   ;
    TH1F* dtrkTag_trackEta           ;       
    TH1F* dtrkTag_trackPhi           ;       
    TH1F* dtrkTag_trackPtRel      ; 
    TH1F* dtrkTag_trackDeltaR        ;       
    TH1F* dtrkTag_trackDeltaR_l        ;       
    TH1F* dtrkTag_trackPtRatio       ;       
    TH1F* dtrkTag_trackPPar          ;       
    TH1F* dtrkTag_trackEtaRel        ;       
    TH1F* dtrkTag_trackPParRatio     ;       
    TH1F* dtrkTag_trackChi2          ;       
    TH1F* dtrkTag_trackNTotalHits    ;       
    TH1F* dtrkTag_trackNPixelHits    ;       
    //TH1F* dtrkTag_nTracks;
    TH1F* dtrkTag_isFromV0  ;

    TH1F*   dtag_jetNTracks                      ;
    TH1F*   dtag_jetNSecondaryVertices              ;
    TH1F*   dtag_chargedMultiplicity             ;
    TH1F*   dtag_chargedHadronEnergyFraction     ;
    TH1F*   dtag_chargedHadronMultiplicity       ;
    TH1F*   dtag_chargedEmEnergyFraction         ;
    TH1F*   dtag_neutralMultiplicity             ;
    TH1F*   dtag_neutralHadronEnergyFraction     ;
    TH1F*   dtag_neutralHadronMultiplicity       ;
    TH1F*   dtag_neutralEmEnergyFraction         ;
    TH1F*   dtag_photonMultiplicity              ;
    TH1F*   dtag_photonEnergyFraction            ;
    TH1F*   dtag_muonMultiplicity                ;
    TH1F*   dtag_muonEnergyFraction              ;
    TH1F*   dtag_elecMultiplicity                ;
    TH1F*   dtag_elecEnergyFraction              ;
    TH1F*   dtag_totalMultiplicity               ;

    btaggingDeltaHists(std::string,       TFileDirectory&, std::string title = "");
    btaggingDeltaHists(std::string, fwlite::TFileService&, std::string title = "");

    void makeHists(std::string, TFileDirectory&, std::string title);
    void FillSVHists(const svPtr& sv1, const jetPtr& jet1, 
		     const svPtr& sv2, const jetPtr& jet2, 
		     float weight);

    void FillTrkTagVarHists(const trkTagVarPtr& trkTag1, 
			    const trkTagVarPtr& trkTag2, 
			    float weight);

    void FillTagVarHists(const tagVarPtr& tag1, 
			 const tagVarPtr& tag2, 
			 float weight );

    ~btaggingDeltaHists(); 

  };

}
#endif // btaggingDeltaHists_H
