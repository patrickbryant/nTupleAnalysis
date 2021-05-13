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

    int jetIdx;
    float isolation;
    float isolation_corrected;
    float isolation_trackerOnly;
    float dR = 1e6;

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
    
    UInt_t nMuons;

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
    float pfRelIso04_all[MAXMUONS];
    float isolation_corrected[MAXMUONS];
    float isolation_trkIsoOnly[MAXMUONS];
    
    muonData(std::string, TTree*, bool readIn = true, bool isMC = false, std::string SFName=""); 
    std::vector<std::shared_ptr<muon>> getMuons(float ptMin = -1e6, float etaMax = 1e6, int tag = -1, bool isolation = false);
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

