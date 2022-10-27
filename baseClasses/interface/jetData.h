// -*- C++ -*-

#if !defined(jetData_H)
#define jetData_H
#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"
#include "nTupleAnalysis/baseClasses/interface/trackData.h"
#include "nTupleAnalysis/baseClasses/interface/btaggingData.h"

#include "CondTools/BTau/interface/BTagCalibrationReader.h"


namespace nTupleAnalysis {

  //forward declaration for use in jet constructor from tree
  class jetData;


  //jet object
  class jet {


  public:

    UInt_t tree_idx;

    UChar_t cleanmask;

    float pt;
    float eta;
    float phi;
    float m;
    float e;
    TLorentzVector p;

    float bRegCorr;
    float pt_wo_bRegCorr;

    float deepB = 0;
    float CSVv2 = 0;
    float deepFlavB = 0;
    float bTagScore = -1;
    Int_t puId;
    Int_t jetId;

    float Ip2N     = -99;
    float Ip2P     = -99;
    float Ip3N     = -99;
    float Ip3P     = -99;
    float ProbaN   = -99;
    float Proba    = -99;
    float BprobN   = -99;
    float Bprob    = -99;
    float Svx      = -99;
    float SvxHP    = -99;
    float CombIVF  = -99;
    float CombIVF_N= -99;
    float SoftMuN  = -99;
    float SoftElN  = -99;
    float cMVAv2   = -99;
    float cMVAv2N  = -99;



    int ntracks        ;
    int nseltracks     ;
    float SoftMu       ;
    float SoftEl       ;
    int nSM            ;
    int nSE            ;
    int looseID        ;
    int tightID        ;
    float DeepCSV      = 0;
    float DeepCSV_reCalc = -2;
    float DeepCSVb     = 0;
    float DeepCSVc     = 0;
    float DeepCSVl     = 0;
    float DeepCSVbb    = 0;

    // truth Info
    int flavour        ;
    int flavourCleaned ;
    int partonFlavour  ;
    int hadronFlavour  ;
    int nbHadrons      ;
    int ncHadrons      ;


    //
    //  Tracks in Jet
    //
    float nFirstTrack;
    float nLastTrack;
    std::vector<trackPtr> tracks;

    //
    // SVs in Jet
    //
    int DeepJet_nsv = -1;
    std::vector<svPtr> svs;

    //
    // trkTag in Jet
    //
    int DeepJet_nCpfcand = -1;
    std::vector<trkTagVarPtr> trkTagVars;

    //
    // tag vars in Jet
    //
    tagVarPtr tagVars;


    //
    //  Matched Jets
    //
    float match_dR = -99;
    std::weak_ptr<jet>  matchedJet;

    //
    // GenJet
    //
    TLorentzVector genJet_p;

    float SF = 1.0; //btagging scale-factor

    Bool_t isTag = false;
    Bool_t isSel = false;
    
    float match_dR_bjet = -99;

    jet();
    jet(UInt_t, jetData*, std::string tagger = ""); 
    jet(TLorentzVector&, float tag = -1); 
    void bRegression();
    void undo_bRegression();
    void dump();
    ~jet(); 

    void RotateZ(float dPhi);
    void scaleFourVector(float scale);
    //void dump();

  private:
    bool  appliedBRegression = false;

  public:
    // Accessor
    bool AppliedBRegression() const {return appliedBRegression;}


  };

  typedef std::shared_ptr<jet> jetPtr;


  //class for tree access
  class jetData {

  public:

    std::string m_name ="";
    bool m_isMC = false;
    std::string m_prefix ="";
    bool debug = false;
    std::string m_jetDetailLevel;
    static const unsigned int MAXJETS = 10000;

    bool doPFNano = true;
    bool doBTA    = false;

    UInt_t nJets = 0;

    UChar_t cleanmask[MAXJETS];

    float pt [MAXJETS];
    float eta[MAXJETS];
    float phi[MAXJETS];
    float m  [MAXJETS];

    float bRegCorr[MAXJETS];

    float deepB[MAXJETS];
    float CSVv2[MAXJETS];
    float deepFlavB[MAXJETS] = {0};
    float deepFlavourB[MAXJETS];
    float deepFlavourBB[MAXJETS];
    float deepFlavourLEPB[MAXJETS];
    float *bTagScore;
    Int_t puId[MAXJETS];
    Int_t jetId[MAXJETS];


    float Ip2N     [MAXJETS];
    float Ip2P     [MAXJETS];
    float Ip3N     [MAXJETS];
    float Ip3P     [MAXJETS];
    float ProbaN   [MAXJETS];
    float Proba    [MAXJETS];
    float BprobN   [MAXJETS];
    float Bprob    [MAXJETS];
    float Svx      [MAXJETS];
    float SvxHP    [MAXJETS];
    float CombIVF  [MAXJETS];
    float CombIVF_N[MAXJETS];
    float SoftMuN  [MAXJETS];
    float SoftElN  [MAXJETS];
    float cMVAv2   [MAXJETS];
    float cMVAv2N  [MAXJETS];


    int ntracks        [MAXJETS];
    int nseltracks     [MAXJETS];
    float SoftMu       [MAXJETS];
    float SoftEl       [MAXJETS];
    int nSM            [MAXJETS];
    int nSE            [MAXJETS];
    int looseID        [MAXJETS];
    int tightID        [MAXJETS];
    float DeepCSVb     [MAXJETS] = {0};;
    float DeepCSVc     [MAXJETS] = {0};;
    float DeepCSVl     [MAXJETS] = {0};;
    float DeepCSVbb    [MAXJETS] = {0};

    //
    bool m_loadGenJets =  false; 
    int   GenJet_hasMatch [MAXJETS];
    float GenJet_pt       [MAXJETS];
    float GenJet_eta      [MAXJETS];
    float GenJet_phi      [MAXJETS];
    float GenJet_m        [MAXJETS];
    int   isB             [MAXJETS];
    int   isGBB           [MAXJETS];
    int   isBB            [MAXJETS];
    int   isC             [MAXJETS];
    int   isGCC           [MAXJETS];
    int   isCC            [MAXJETS];
    int   isTau           [MAXJETS];
    int   isG             [MAXJETS];
    int   isUD            [MAXJETS];
    int   isS             [MAXJETS];
    int   isUndefined     [MAXJETS];


    // truth Info
    int flavour        [MAXJETS];
    int flavourCleaned [MAXJETS];
    int partonFlavour  [MAXJETS];
    int hadronFlavour  [MAXJETS];
    int nbHadrons      [MAXJETS];
    int ncHadrons      [MAXJETS];

    Bool_t isTag[MAXJETS];
    Bool_t isSel[MAXJETS];

    int nFirstTrack[MAXJETS];
    int nLastTrack[MAXJETS];
    trackData* trkData = NULL;

    int DeepJet_nsv[MAXJETS];
    int nFirstSV[MAXJETS] = {0};
    int nLastSV[MAXJETS] = {0};

    int DeepJet_nCpfcand[MAXJETS];
    int nFirstTrkTagVar [MAXJETS];
    int nLastTrkTagVar  [MAXJETS];

    btaggingData* btagData = nullptr;


    jetData(std::string, TTree*, bool readIn = true, bool isMC = false, std::string jetDetailLevel = "Tracks.btagInputs", std::string prefix = "", std::string SFName = "", std::string btagVariations = "central",
	    std::string JECSyst = "", std::string tagger = ""); 

    std::vector< jetPtr > getJets(float ptMin = -1e6, float ptMax = 1e6, float etaMax = 1e6, bool clean = false, float tagMin = -1e6, std::string tagger = "CSVv2", bool antiTag = false, int puIdMin = 0);
    std::vector< jetPtr > getJets(std::vector< jetPtr > inputJets, 
				  float ptMin = -1e6, float ptMax = 1e6, float etaMax = 1e6, bool clean = false, float tagMin = -1e6, std::string tagger = "CSVv2", bool antiTag = false, int puIdMin = 0);
    ~jetData(); 

    BTagCalibrationReader* m_btagCalibrationTool = NULL;
    std::vector<std::string> m_btagVariations;
    std::map<std::string, BTagCalibrationReader*> m_btagCalibrationTools;
    std::map<std::string,float> m_btagSFs;
    float getSF(float jetEta,  float jetPt,  float jetTagScore, int jetHadronFlavour, std::string variation = "central");
    void updateSFs(float jetEta,  float jetPt,  float jetTagScore, int jetHadronFlavour, bool debug = false );
    void updateSFs(const jetPtr& jet, bool debug = false );
    void updateSFs(std::vector< jetPtr > jets, bool debug = false );
    void resetSFs();

    void writeJets(std::vector< jetPtr > outputJets) ;
    void connectBranches(bool readIn, TTree* tree, std::string JECSyst = "");
    //void dump();
  };



}
#endif // jetData_H

