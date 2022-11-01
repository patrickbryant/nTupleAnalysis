// -*- C++ -*-

#if !defined(elecData_H)
#define elecData_H
#include <TChain.h>
#include <TH2D.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"

namespace nTupleAnalysis {
  //forward declaration for use in elec constructor from tree
  class elecData;
  //elec object
  class elec {

  public:
    float pt;
    float eta;
    float phi;
    float m;
    TLorentzVector p;

    Float_t dr03EcalRecHitSumEt          ;
    Float_t dr03HcalDepth1TowerSumEt	 ;
    Float_t dr03TkSumPt			 ;
    Float_t eInvMinusPInv		 ;
    Float_t hoe				 ;
    Float_t miniPFRelIso_all		 ;
    Float_t miniPFRelIso_chg		 ;
    Float_t pfRelIso03_all		 ;
    Float_t pfRelIso03_chg		 ;
    Float_t r9				 ;
    Float_t scEtOverPt			 ;
    Float_t sieie			 ;
					 ;
    Int_t cutBased			 ;
    Int_t pdgId				 ;
					 ;
    Bool_t convVeto			 ;
    UChar_t genPartFlav                  ;


    Float_t     deltaEtaSC    ;
    Float_t     dxy           ;
    Float_t     dxyErr        ;
    Float_t     dz            ;
    Float_t     dzErr         ;
    Float_t     energyErr     ;
    Float_t     ip3d          ;
    Float_t     jetPtRelv2    ;
    Float_t     jetRelIso     ;
    Float_t     mvaHZZIso     ;
    Float_t     mvaIso        ;
    Float_t     mvaNoIso      ;
    Float_t     sip3d         ;
    Float_t     mvaTTH        ;
    Bool_t      mvaIso_WP80   ;
    Bool_t      mvaIso_WP90   ;
    Bool_t      mvaIso_WPL    ;
    Bool_t      mvaNoIso_WP80 ;
    Bool_t      mvaNoIso_WP90 ;
    Bool_t      mvaNoIso_WPL  ;
    Int_t       jetIdx        ;
    Int_t       tightCharge   ;
    Int_t       charge        ;
    UChar_t     lostHits      ;

    float SF = 1.0;

    elec(UInt_t, elecData*); 
    ~elec(); 

    //void dump();
  };

  typedef std::shared_ptr<elec> elecPtr;

  //class for tree access
  class elecData {

  public:
    std::string m_name;
    static const unsigned int MAXELECS = 10000;
    bool m_isMC;


    UInt_t nElecs = 0;

    float pt [MAXELECS];
    float eta[MAXELECS];
    float phi[MAXELECS];
    float m  [MAXELECS] = {0};

    Float_t dr03EcalRecHitSumEt[MAXELECS];                                     //         | Float_t Non-PF Ecal isolation within a delta R cone of 0.3 with electron pt > 35 GeV//
    Float_t dr03HcalDepth1TowerSumEt[MAXELECS];    //         | Float_t Non-PF Hcal isolation within a delta R cone of 0.3 with electron pt > 35 GeV//
    Float_t dr03TkSumPt[MAXELECS];  //         | Float_t Non-PF track isolation within a delta R cone of 0.3 with electron pt > 35 GeV//
    Float_t eInvMinusPInv[MAXELECS];  // Float_t 1/E_SC - 1/p_trk                  //
    Float_t hoe[MAXELECS]; // Float_t H over E                                    //
    Float_t miniPFRelIso_all[MAXELECS];   //         | Float_t mini PF relative isolation, total (with scaled rho//EA PU corrections)//
    Float_t miniPFRelIso_chg[MAXELECS];   //         | Float_t mini PF relative isolation, charged component            //
    Float_t pfRelIso03_all[MAXELECS]; ///         | Float_t PF relative isolation dR=0.3, total (with rho//EA PU corrections)//
    Float_t pfRelIso03_chg[MAXELECS];    //         | Float_t PF relative isolation dR=0.3, charged component          //
    Float_t r9[MAXELECS];   //         | Float_t R9 of the supercluster, calculated with full 5x5 region  //
    Float_t scEtOverPt[MAXELECS]; // : Float_t (supercluster transverse energy)/pt-1//
    Float_t sieie[MAXELECS];  //         | Float_t sigma_IetaIeta of the supercluster, calculated with full 5x5 region//

    Int_t cutBased[MAXELECS]; // Int_t cut-based ID Fall17 V2 (0:fail, 1: veto, 2:loose, 3:medium, 4:tight)                                //

    Int_t pdgId[MAXELECS];   //         | Int_t PDG code assigned by the event reconstruction (not by MC truth)//

    Bool_t convVeto[MAXELECS]; // Bool_t pass conversion veto                    //
    UChar_t genPartFlav[MAXELECS]; //         | UChar_t Flavour of genParticle for MC matching to status==1 electrons or photons://
    //         |  1 = prompt electron (including gamma//->mu mu), 15 = electron from prompt tau, 22 = prompt photon (likely conversion), 5 = electron from b, 4 = electron from c, 3 = electron from light or unknown, 0 = unmatched//


    Float_t     deltaEtaSC    [MAXELECS];
    Float_t     dxy           [MAXELECS];
    Float_t     dxyErr        [MAXELECS];
    Float_t     dz            [MAXELECS];
    Float_t     dzErr         [MAXELECS];
    Float_t     energyErr     [MAXELECS];
    Float_t     ip3d          [MAXELECS];
    Float_t     jetPtRelv2    [MAXELECS];
    Float_t     jetRelIso     [MAXELECS];
    Float_t     mvaHZZIso     [MAXELECS];
    Float_t     mvaIso        [MAXELECS];
    Float_t     mvaNoIso      [MAXELECS];
    Float_t     sip3d         [MAXELECS];
    Float_t     mvaTTH        [MAXELECS];
    Bool_t      mvaIso_WP80   [MAXELECS];
    Bool_t      mvaIso_WP90   [MAXELECS];
    Bool_t      mvaIso_WPL    [MAXELECS];
    Bool_t      mvaNoIso_WP80 [MAXELECS];
    Bool_t      mvaNoIso_WP90 [MAXELECS];
    Bool_t      mvaNoIso_WPL  [MAXELECS];
    Int_t       jetIdx        [MAXELECS];
    Int_t       tightCharge   [MAXELECS];
    Int_t       charge        [MAXELECS];
    UChar_t     lostHits      [MAXELECS];

    elecData(std::string name, TTree* tree, bool readIn = true, bool isMC = false, std::string SFName = ""); 
    std::vector<std::shared_ptr<elec>> getElecs(float ptMin = -1e6, float etaMax = 1e6, bool mvaCut = false);

    void writeElecs(std::vector< std::shared_ptr<elec> > outputElecs) ;
    void connectBranches(bool readIn, TTree* tree);


    ~elecData(); 

    TH2D*  m_SFHistTight = nullptr;
    TH2D*  m_SFHistReco = nullptr;

  private:

    TFile* m_SFFileTight = nullptr;
    TFile* m_SFFileReco = nullptr;


    //void dump();
  };

}
#endif // elecData_H

