// -*- C++ -*-
#if !defined(btaggingHists_H)
#define btaggingHists_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/btaggingData.h"
#include "nTupleAnalysis/baseClasses/interface/jetData.h"


namespace nTupleAnalysis {

  class btaggingHists {
  public:
    
    //SV Hists
    TH1F*   sv_NTracks                    ;
    TH1F*   sv_Mass                       ;
    TH1F*   sv_JetDeltaR                  ;
    TH1F*   sv_FitProb                    ;
    TH1F*   sv_EnergyRatio                ;
    TH1F*   sv_R          ;
    TH1F*   sv_Z          ;
    TH1F*   sv_Chi2       ;
    TH1F*   sv_NDF        ;
    TH1F*   sv_Flight     ;
    TH1F*   sv_FlightSig  ;
    TH1F*   sv_Flight2D   ;
    TH1F*   sv_FlightSig2D;
    TH1F*   sv_Pt         ;
    TH1F*   sv_Eta        ;
    TH1F*   sv_Phi        ;
    TH1F*   sv_DistJetAxis;
    TH1F*   sv_nSVs;
    TH1F*   sv_boostOverSqrtJetPt;
    TH1F*   sv_massVertexEnergyFraction;
    TH1F*   sv_totCharge;

    //TrkTagVar Hists
    TH1F* trkTag_ip3d_l ;
    TH1F* trkTag_ip3d   ;
    TH1F* trkTag_ip3d_sig_l;
    TH1F* trkTag_ip3d_sig  ;
    TH1F* trkTag_ip3d_err_l;
    TH1F* trkTag_ip3d_err  ;

    TH1F* trkTag_ip2d_l ;
    TH1F* trkTag_ip2d   ;
    TH1F* trkTag_ip2d_sig_l;
    TH1F* trkTag_ip2d_sig;
    TH1F* trkTag_ip2d_err_l;
    TH1F* trkTag_ip2d_err;
    
    TH1F* trkTag_trackDecayLenVal_vl ;
    TH1F* trkTag_trackDecayLenVal_l ;
    TH1F* trkTag_trackDecayLenVal;
    TH1F* trkTag_trackJetDistVal ;    
    TH1F* trkTag_trackJetDistVal_l ;    
    TH1F* trkTag_trackJetDistVal_vl ;    
    TH1F* trkTag_trackJetDistSig ;    
    TH1F* trkTag_trackPt_logx           ;
    TH1F* trkTag_trackMomentum   ;
    TH1F* trkTag_trackPt   ;
    TH1F* trkTag_trackPt_l   ;
    TH1F* trkTag_trackEta           ;       
    TH1F* trkTag_trackEta_l           ;       
    TH1F* trkTag_trackPhi           ;       
    TH1F* trkTag_trackPtRel      ; 
    TH1F* trkTag_trackDeltaR        ;       
    TH1F* trkTag_trackDeltaR_l        ;       
    TH1F* trkTag_trackPtRatio       ;       
    TH1F* trkTag_trackPPar          ;       
    TH1F* trkTag_trackEtaRel        ;       
    TH1F* trkTag_trackPParRatio     ;       
    TH1F* trkTag_trackChi2          ;       
    TH1F* trkTag_trackNTotalHits    ;       
    TH1F* trkTag_trackNPixelHits    ;       
    TH1F* trkTag_nTracks;
    TH1F* trkTag_isFromV0  ;

    TH1F*   tag_jetNTracks                      ;
    TH1F*   tag_jetNSecondaryVertices              ;
    TH1F*   tag_chargedMultiplicity             ;
    TH1F*   tag_chargedHadronEnergyFraction     ;
    TH1F*   tag_chargedHadronMultiplicity       ;
    TH1F*   tag_chargedEmEnergyFraction         ;
    TH1F*   tag_neutralMultiplicity             ;
    TH1F*   tag_neutralHadronEnergyFraction     ;
    TH1F*   tag_neutralHadronMultiplicity       ;
    TH1F*   tag_neutralEmEnergyFraction         ;
    TH1F*   tag_photonMultiplicity              ;
    TH1F*   tag_photonEnergyFraction            ;
    TH1F*   tag_muonMultiplicity                ;
    TH1F*   tag_muonEnergyFraction              ;
    TH1F*   tag_elecMultiplicity                ;
    TH1F*   tag_elecEnergyFraction              ;
    TH1F*   tag_totalMultiplicity               ;

    TH1F* tag_trackSumJetEtRatio       ;
    TH1F* tag_trackSumJetDeltaR        ;
    TH1F* tag_vertexCategory           ;
    TH1F* tag_trackSip2dValAboveCharm  ;
    TH1F* tag_trackSip2dSigAboveCharm  ;
    TH1F* tag_trackSip3dValAboveCharm  ;
    TH1F* tag_trackSip3dSigAboveCharm  ;
    TH1F* tag_jetNTracksEtaRel         ;
    TH1F* tag_vertexMass               ;
    TH1F* tag_vertexNTracks            ;
    TH1F* tag_vertexJetDeltaR          ;
    TH1F* tag_vertexEnergyRatio        ;
    TH1F* tag_flightDistance2dSig      ;
    TH1F* tag_flightDistance2dVal      ;
    TH1F* tag_flightDistance3dSig      ;
    TH1F* tag_flightDistance3dVal      ;
    TH1F* tag_trackEtaRel              ;


    btaggingHists(std::string,       TFileDirectory&, std::string title = "");
    btaggingHists(std::string, fwlite::TFileService&, std::string title = "");

    void makeHists(std::string, TFileDirectory&, std::string title);
    void FillSVHists(const secondaryVertexPtr& sv, const jetPtr& jet, float weight);

    void FillTrkTagVarHists(const trkTagVarPtr&, float);

    void FillTagVarHists(const tagVarPtr& tag, const jetPtr& jet, float weight );

    ~btaggingHists(); 

  };

}
#endif // btaggingHists_H
