// -*- C++ -*-

#if !defined(muonData_H)
#define muonData_H
#include <TChain.h>
#include <TH2D.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"

namespace nTupleAnalysis {
  //forward declaration for use in muon constructor from tree
  class muonData;
  //muon object
  class muon {

  public:
    float pt;
    float eta;
    float phi;
    float m;
    float ip3d;
    float sip3d;
    float dxy;
    float dxyErr;
    TLorentzVector p;

    bool    softId;
    UChar_t highPtId;

    bool mediumId;
    bool tightId;

    int quality;

    Float_t pfRelIso03_all ;
    Float_t pfRelIso03_chg ;
    Float_t ptErr          ;
    Float_t tkRelIso       ;
    Int_t   pdgId          ;
    Bool_t  looseId        ;
    Bool_t  mediumPromptId ;
    UChar_t mvaId          ;
    UChar_t pfIsoId        ;
    UChar_t tkIsoId        ;
    UChar_t genPartFlav    ;

    int jetIdx;
    float isolation;
    //float isolation_corrected;
    //float isolation_trackerOnly;
    float dR = 1e6;

    Float_t  dxybs              ;
    Float_t  dz                 ;
    Float_t  dzErr              ;
    Float_t  miniPFRelIso_all   ;
    Float_t  miniPFRelIso_chg   ;
    Float_t  pfRelIso04_all     ;
    Float_t  mvaTTH             ;
    Int_t    nStations          ;
    Int_t    nTrackerLayers     ;
    Bool_t   highPurity         ;
    UChar_t  cleanmask          ;

    float SF = 1.0;

    muon(UInt_t, muonData*); 
    ~muon(); 

    //void dump();
  };

  typedef std::shared_ptr<muon> muonPtr;

  //class for tree access
  class muonData {

  public:
    std::string m_name;
    static const unsigned int MAXMUONS = 10000;
    bool m_isMC;
    
    UInt_t nMuons = 0;

    Float_t  dxybs              [MAXMUONS];
    Float_t  dz                 [MAXMUONS];
    Float_t  dzErr              [MAXMUONS];
    Float_t  miniPFRelIso_all   [MAXMUONS];
    Float_t  miniPFRelIso_chg   [MAXMUONS];
    Float_t  pfRelIso04_all     [MAXMUONS];
    Float_t  mvaTTH             [MAXMUONS];
    Int_t    nStations          [MAXMUONS];
    Int_t    nTrackerLayers     [MAXMUONS];
    Bool_t   highPurity         [MAXMUONS];
    UChar_t  cleanmask          [MAXMUONS];

    float pt [MAXMUONS];
    float eta[MAXMUONS];
    float phi[MAXMUONS];
    float m  [MAXMUONS];
    float ip3d [MAXMUONS];     //    6 :Muon_ip3d : Float_t 3D impact parameter wrt first PV, in cm        //
    float sip3d [MAXMUONS];      //    19 :Muon_sip3d : Float_t 3D impact parameter significance wrt first PV //
    float dxy [MAXMUONS];          // 0 :Muon_dxy  : Float_t dxy (with sign) wrt first PV, in cm            //
    float dxyErr [MAXMUONS];      //    1 :Muon_dxyErr : Float_t dxy uncertainty, in cm                      //

    Bool_t  softId[MAXMUONS];     //   48 :Muon_softId : Bool_t soft cut-based ID                             //
    UChar_t highPtId[MAXMUONS];   //   32 :Muon_highPtId :  | UChar_t high-pT cut-based ID (1 = tracker high pT, 2 = global high pT, which includes tracker high pT)//                     //

    Bool_t mediumId[MAXMUONS];
    Bool_t tightId[MAXMUONS];

    int jetIdx[MAXMUONS];
    //float isolation_corrected[MAXMUONS];
    //float isolation_trkIsoOnly[MAXMUONS];


    Float_t pfRelIso03_all [MAXMUONS]; //         | Float_t PF relative isolation dR=0.3, total (deltaBeta corrections)//
    Float_t pfRelIso03_chg [MAXMUONS]; //         | Float_t PF relative isolation dR=0.3, charged component          //
    Float_t ptErr          [MAXMUONS]; // Float_t ptError of the muon track                     //
    Float_t tkRelIso       [MAXMUONS]; //         | Float_t Tracker-based relative isolation dR=0.3 for highPt, trkIso/tunePpt//
    Int_t   pdgId          [MAXMUONS]; //         | Int_t PDG code assigned by the event reconstruction (not by MC truth)//
    Bool_t  looseId        [MAXMUONS]; // Bool_t muon is loose muon                           //
    Bool_t  mediumPromptId [MAXMUONS]; // Bool_t cut-based ID, medium prompt WP        //
    UChar_t mvaId          [MAXMUONS]; //         | UChar_t Mva ID from miniAOD selector (1=MvaLoose, 2=MvaMedium, 3=MvaTight, 4=MvaVTight, 5=MvaVVTight)*
    UChar_t pfIsoId        [MAXMUONS]; //         | UChar_t PFIso ID from miniAOD selector (1=PFIsoVeryLoose, 2=PFIsoLoose, 3=PFIsoMedium, 4=PFIsoTight, 5=PFIsoVeryTight, 6=PFIsoVeryVeryTight)//
    UChar_t tkIsoId        [MAXMUONS]; // UChar_t TkIso ID (1=TkIsoLoose, 2=TkIsoTight)       //
    UChar_t genPartFlav    [MAXMUONS]; //         | UChar_t Flavour of genParticle for MC matching to status==1 muons://
                                       //         |  1 = prompt muon (including gamma//->mu mu), 15 = muon from prompt tau, 5 = muon from b, 4 = muon from c, 3 = muon from light or unknown, 0 = unmatched//
    

    
    muonData(std::string, TTree*, bool readIn = true, bool isMC = false, std::string SFName=""); 
    std::vector<std::shared_ptr<muon>> getMuons(float ptMin = -1e6, float etaMax = 1e6, int tag = -1, bool isolation = false, float sip3dMax = -1);
    ~muonData(); 

    void writeMuons(std::vector< std::shared_ptr<muon> > outputMuons) ;
    void connectBranches(bool readIn, TTree* tree);

    TH2D*  m_SFHistTight = nullptr;
    TH2D*  m_SFHistIso = nullptr;

  private:

    TFile* m_SFFileID = nullptr;
    TFile* m_SFFileIso = nullptr;


    //void dump();
  };

}
#endif // muonData_H

