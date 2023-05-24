// -*- C++ -*-

#if !defined(btaggingData_H)
#define btaggingData_H
#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"


namespace nTupleAnalysis {


  //forward declaration for use in secondaryVertex constructor from tree
  class btaggingData;


  //secondaryVertex object from the btagging inputs
  class secondaryVertex {

  public:
    float e;
    TLorentzVector p;

    float x                 ;
    float y                 ;
    float z                 ;
    float ex                ;    
    float ey                ;
    float ez                ;
    float chi2              ;
    float ndf               ;
    float flight            ;
    float flightErr         ;
    float flightSig         ;
    float deltaR_jet        ;
    float deltaR_sum_jet    ;
    float deltaR_sum_dir    ;
    float vtx_pt            ;
    float flight2D          ;
    float flight2DErr       ;
    float flight2DSig       ;
    float totCharge         ;
    float vtxDistJetAxis    ;
    float nTrk              ;
    float mass              ;
    float vtx_eta           ;
    float vtx_phi           ;
    float EnergyRatio       ;
    float dir_x             ;
    float dir_y             ;
    float dir_z             ;

    float DeepJet_sv_normchi2         ;
    float DeepJet_sv_costhetasvpv     ;

    std::weak_ptr<secondaryVertex>  matchedSV;

    secondaryVertex();
    secondaryVertex(UInt_t, btaggingData*); 
    secondaryVertex(UInt_t iJet, UInt_t iSV, btaggingData* data);

    ~secondaryVertex(); 

    //void dump();
  };

  typedef std::shared_ptr<secondaryVertex> secondaryVertexPtr;


  class trkTagVar {

  public:

    float pt;
    float trackEta	   ;
    float trackPhi	   ;
    float m;
    float e;
    TLorentzVector p;

    float trackMomentum	   ;

    float trackPtRel	   ;
    float trackPPar	   ;
    float trackEtaRel	   ;
    float trackDeltaR	   ;
    float trackPtRatio	   ;
    float trackPParRatio   ;	
    float trackSip2dVal	   ;
    float trackSip2dSig	   ;
    float trackSip3dVal	   ;
    float trackSip3dSig	   ;
    float trackDecayLenVal ;
    float trackDecayLenSig ;
    float trackJetDistVal  ;
    float trackJetDistSig  ;
    float trackChi2	   ;
    float trackNTotalHits  ;
    float trackNPixelHits  ;
    bool  hasTrackMatch = false;
    int   matchIsFromV0 = -99;

    float DeepJet_Cpfcan_puppiw   ;             
    float DeepJet_Cpfcan_drminsv  ;		     
    float DeepJet_Cpfcan_VTX_ass  ;		     
    float DeepJet_Cpfcan_quality  ;             



    std::weak_ptr<trkTagVar>  matchedTrkTagVar;

    trkTagVar();
    trkTagVar(UInt_t, btaggingData*); 
    trkTagVar(UInt_t iJet, UInt_t iTrk, btaggingData* data);

    ~trkTagVar(); 

    //void dump();
  };

  typedef std::shared_ptr<trkTagVar> trkTagVarPtr;

  class tagVar {

  public:


    int   jetNTracks            ;
    int   jetNSecondaryVertices ;

    int   chargedMultiplicity         ;
    float chargedHadronEnergyFraction ;
    int   chargedHadronMultiplicity   ;
    float chargedEmEnergyFraction     ;
    int   neutralMultiplicity         ;
    float neutralHadronEnergyFraction ;
    int   neutralHadronMultiplicity   ;
    float neutralEmEnergyFraction     ;
    float photonEnergyFraction        ;   
    int   photonMultiplicity          ;   
    float muonEnergyFraction          ;   
    int   muonMultiplicity            ;   
    float electronEnergyFraction      ;   
    int   electronMultiplicity        ;   
    int   numberOfDaughters           ;   

    float trackJetPt                 ;   
    float jetNTracksCSV              ;
    float jetNTracksEtaRel           ;
    float trackSumJetEtRatio         ;   
    float trackSumJetDeltaR          ;   
    float trackSip2dValAboveCharm    ;   
    float trackSip2dSigAboveCharm    ;   
    float trackSip3dValAboveCharm    ;   
    float trackSip3dSigAboveCharm    ;   
    float vertexCategory             ;   
    float jetNSecondaryVerticesCSV   ;
    float vertexMass                 ;
    float vertexNTracks              ;
    float vertexEnergyRatio          ;   
    float vertexJetDeltaR            ;   
    float flightDistance2dVal        ;
    float flightDistance2dSig        ;
    float flightDistance3dVal        ;
    float flightDistance3dSig        ;
    std::vector<float> TagVarCSV_trackEtaRel;


    tagVar();
    tagVar(UInt_t, btaggingData*); 

    ~tagVar(); 

    //void dump();
  };

  typedef std::shared_ptr<tagVar> tagVarPtr;




  //class for tree access
  class btaggingData {

  public:

    int   nSV;
    bool  haveSVs = false;
    static const unsigned int MAXSVS = 10000;
    float sv_x                 [MAXSVS];
    float sv_y                 [MAXSVS];
    float sv_z                 [MAXSVS];
    float sv_ex                [MAXSVS];
    float sv_ey                [MAXSVS];
    float sv_ez                [MAXSVS];
    float sv_chi2              [MAXSVS];
    float sv_ndf               [MAXSVS];
    float sv_flight            [MAXSVS];
    float sv_flightErr         [MAXSVS];
    float sv_deltaR_jet        [MAXSVS];
    float sv_deltaR_sum_jet    [MAXSVS];
    float sv_deltaR_sum_dir    [MAXSVS];
    float sv_vtx_pt            [MAXSVS];
    float sv_flight2D          [MAXSVS];
    float sv_flight2DErr       [MAXSVS];
    float sv_totCharge         [MAXSVS];
    float sv_vtxDistJetAxis    [MAXSVS];
    int   sv_nTrk              [MAXSVS];
    float sv_mass              [MAXSVS];
    float sv_vtx_eta           [MAXSVS];
    float sv_vtx_phi           [MAXSVS];
    float sv_EnergyRatio       [MAXSVS];
    float sv_dir_x             [MAXSVS];
    float sv_dir_y             [MAXSVS];
    float sv_dir_z             [MAXSVS];

    bool  haveTrkTagVars = false;
    bool  doPFNano       = true;
    
    static const unsigned int MAXNTRK = 100000;
    float trackMomentum	    [MAXNTRK];
    float trackEta	    [MAXNTRK];
    float trackPhi	    [MAXNTRK];
    float trackPtRel	    [MAXNTRK];
    float trackPPar	    [MAXNTRK];
    float trackEtaRel	    [MAXNTRK];
    float trackDeltaR	    [MAXNTRK];
    float trackPtRatio	    [MAXNTRK];
    float trackPParRatio    [MAXNTRK];	
    float trackSip2dVal	    [MAXNTRK];
    float trackSip2dSig	    [MAXNTRK];
    float trackSip3dVal	    [MAXNTRK];
    float trackSip3dSig	    [MAXNTRK];
    float trackDecayLenVal  [MAXNTRK];
    float trackDecayLenSig  [MAXNTRK];
    float trackJetDistVal   [MAXNTRK];
    float trackJetDistSig   [MAXNTRK];
    float trackChi2	    [MAXNTRK];
    float trackNTotalHits   [MAXNTRK];
    float trackNPixelHits   [MAXNTRK];

    bool  haveTagVars = false;
    static const unsigned int MAXNJETS = 10000;
    int   jetNTracks                  [MAXNJETS];
    int   jetNSecondaryVertices       [MAXNJETS];
    int   chargedMultiplicity         [MAXNJETS];
    float chargedHadronEnergyFraction [MAXNJETS];
    int   chargedHadronMultiplicity   [MAXNJETS];
    float chargedEmEnergyFraction     [MAXNJETS];
    int   neutralMultiplicity         [MAXNJETS];
    float neutralHadronEnergyFraction [MAXNJETS];
    int   neutralHadronMultiplicity   [MAXNJETS];
    float neutralEmEnergyFraction     [MAXNJETS];
    float photonEnergyFraction        [MAXNJETS];   
    int   photonMultiplicity          [MAXNJETS];   
    float muonEnergyFraction          [MAXNJETS];   
    int   muonMultiplicity            [MAXNJETS];   
    float electronEnergyFraction      [MAXNJETS];   
    int   electronMultiplicity        [MAXNJETS];   
    int   numberOfDaughters           [MAXNJETS];   

    float trackJetPt                  [MAXNJETS];   
    float jetNTracksCSV               [MAXNJETS];   
    float jetNTracksEtaRel            [MAXNJETS];
    float trackSumJetEtRatio          [MAXNJETS];   
    float trackSumJetDeltaR           [MAXNJETS];   
    float trackSip2dValAboveCharm     [MAXNJETS];   
    float trackSip2dSigAboveCharm     [MAXNJETS];   
    float trackSip3dValAboveCharm     [MAXNJETS];   
    float trackSip3dSigAboveCharm     [MAXNJETS];   
    float vertexCategory              [MAXNJETS];   
    float jetNSecondaryVerticesCSV    [MAXNJETS];
    float vertexMass                  [MAXNJETS];
    float vertexNTracks               [MAXNJETS];
    float vertexEnergyRatio           [MAXNJETS];   
    float vertexJetDeltaR             [MAXNJETS];   
    float flightDistance2dVal         [MAXNJETS];
    float flightDistance2dSig         [MAXNJETS];
    float flightDistance3dVal         [MAXNJETS];
    float flightDistance3dSig         [MAXNJETS];
    //int nTrkEtaRelTagVarCSV           [MAXNJETS];
    int Jet_nFirstTrkEtaRelTagVarCSV  [MAXNJETS];
    int Jet_nLastTrkEtaRelTagVarCSV   [MAXNJETS];  
    float TagVarCSV_trackEtaRel       [4*MAXNJETS]; 


    //
    //  From DeepJetTableProducer
    //
    static const unsigned n_cpf_ = 25;
    float DeepJet_Cpfcan_puppiw                  [n_cpf_][MAXNJETS];
    float DeepJet_Cpfcan_drminsv		 [n_cpf_][MAXNJETS];
    float DeepJet_Cpfcan_chi2			 [n_cpf_][MAXNJETS];
    float DeepJet_Cpfcan_BtagPf_trackDeltaR	 [n_cpf_][MAXNJETS];
    float DeepJet_Cpfcan_BtagPf_trackEtaRel	 [n_cpf_][MAXNJETS];
    float DeepJet_Cpfcan_BtagPf_trackJetDistVal	 [n_cpf_][MAXNJETS];
    float DeepJet_Cpfcan_BtagPf_trackPPar	 [n_cpf_][MAXNJETS];
    float DeepJet_Cpfcan_BtagPf_trackPParRatio	 [n_cpf_][MAXNJETS];
    float DeepJet_Cpfcan_BtagPf_trackPtRel	 [n_cpf_][MAXNJETS];
    float DeepJet_Cpfcan_BtagPf_trackSip2dSig	 [n_cpf_][MAXNJETS];
    float DeepJet_Cpfcan_BtagPf_trackSip3dSig	 [n_cpf_][MAXNJETS];
    float DeepJet_Cpfcan_BtagPf_trackSip2dVal	 [n_cpf_][MAXNJETS];
    float DeepJet_Cpfcan_BtagPf_trackSip3dVal	 [n_cpf_][MAXNJETS];
    float DeepJet_Cpfcan_VTX_ass		 [n_cpf_][MAXNJETS];
    float DeepJet_Cpfcan_quality                 [n_cpf_][MAXNJETS];
    //float DeepJet_Cpfcan_ptrel			 [n_cpf_][MAXNJETS];

    static const unsigned n_sv_ = 4; // 5
    float DeepJet_sv_mass             [n_sv_][MAXNJETS];
    float DeepJet_sv_pt               [n_sv_][MAXNJETS];
    float DeepJet_sv_ntracks          [n_sv_][MAXNJETS];
    float DeepJet_sv_chi2             [n_sv_][MAXNJETS];
    float DeepJet_sv_normchi2         [n_sv_][MAXNJETS];
    float DeepJet_sv_dxy              [n_sv_][MAXNJETS];
    float DeepJet_sv_dxysig           [n_sv_][MAXNJETS];
    float DeepJet_sv_d3d              [n_sv_][MAXNJETS];
    float DeepJet_sv_d3dsig           [n_sv_][MAXNJETS];
    float DeepJet_sv_costhetasvpv     [n_sv_][MAXNJETS];
    float DeepJet_sv_deltaR           [n_sv_][MAXNJETS];
    float DeepJet_sv_enratio          [n_sv_][MAXNJETS];

//    Jet_DeepJet_Npfcan_puppiw_0 = 1, 
//      Jet_DeepJet_Npfcan_deltaR_0 = -0.568359, 
//      Jet_DeepJet_Npfcan_drminsv_0 = -0.345215, 
//      Jet_DeepJet_Npfcan_HadFrac_0 = 0, 
//      Jet_DeepJet_Npfcan_ptrel_0 = -0.945801, 
//      Jet_DeepJet_Npfcan_isGamma_0 = 1, 





    btaggingData(); 

    void initSecondaryVerticies(std::string name, TTree* tree, bool doPFNano_=true);
    std::vector<secondaryVertexPtr> getSecondaryVerticesPFNano(unsigned int jetIndex, unsigned int nSVs, bool debug);
    std::vector<secondaryVertexPtr> getSecondaryVertices(int nFirstSV, int nLastSV, bool debug);

    void initTrkTagVar(std::string name, TTree* tree, bool doPFNano_=true);
    std::vector<trkTagVarPtr> getTrkTagVarsPFNano(unsigned int jetIndex, unsigned int nTrkTagVars);
    std::vector<trkTagVarPtr> getTrkTagVars(int nFirstTrkTagVar, int nLastTrkTagVar);

    void initTagVar(std::string name, TTree* tree);
    tagVarPtr getTagVars(int jetIdx);

    ~btaggingData(); 

    //void dump();
  };



}
#endif // btaggingData_H

