#include "TChain.h"
#include "TFile.h"

#include "nTupleAnalysis/baseClasses/interface/elecData.h"

using namespace nTupleAnalysis;

//elec object
elec::elec(UInt_t i, elecData* data){

  pt  = data->pt [i];
  eta = data->eta[i];
  phi = data->phi[i];
  m   = data->m  [i];
  if(m < 0.10) m = 0.0005;
    
  p = TLorentzVector();
  p.SetPtEtaPhiM(pt, eta, phi, m);


  dr03EcalRecHitSumEt          = data->dr03EcalRecHitSumEt          [i];
  dr03HcalDepth1TowerSumEt     = data->dr03HcalDepth1TowerSumEt     [i];
  dr03TkSumPt                  = data->dr03TkSumPt                  [i];
  eInvMinusPInv                = data->eInvMinusPInv                [i];
  hoe                          = data->hoe                          [i];
  miniPFRelIso_all             = data->miniPFRelIso_all             [i];
  miniPFRelIso_chg             = data->miniPFRelIso_chg             [i];
  pfRelIso03_all               = data->pfRelIso03_all               [i];
  pfRelIso03_chg               = data->pfRelIso03_chg               [i];
  r9                           = data->r9                           [i];
  scEtOverPt                   = data->scEtOverPt                   [i];
  sieie                        = data->sieie                        [i];
  cutBased                     = data->cutBased                     [i];
  pdgId                        = data->pdgId                        [i];
  convVeto                     = data->convVeto                     [i];
  genPartFlav                  = data->genPartFlav                  [i];

  deltaEtaSC               = data->deltaEtaSC    [i];
  dxy           	   = data->dxy           [i];
  dxyErr        	   = data->dxyErr        [i];
  dz            	   = data->dz            [i];
  dzErr         	   = data->dzErr         [i];
  energyErr     	   = data->energyErr     [i];
  ip3d          	   = data->ip3d          [i];
  jetPtRelv2    	   = data->jetPtRelv2    [i];
  jetRelIso     	   = data->jetRelIso     [i];
  mvaHZZIso     	   = data->mvaHZZIso     [i];
  mvaIso        	   = data->mvaIso        [i];
  mvaNoIso      	   = data->mvaNoIso      [i];
  sip3d         	   = data->sip3d         [i];
  mvaTTH        	   = data->mvaTTH        [i];
  mvaIso_WP80   	   = data->mvaIso_WP80   [i];
  mvaIso_WP90   	   = data->mvaIso_WP90   [i];
  mvaIso_WPL    	   = data->mvaIso_WPL    [i];
  mvaNoIso_WP80 	   = data->mvaNoIso_WP80 [i];
  mvaNoIso_WP90 	   = data->mvaNoIso_WP90 [i];
  mvaNoIso_WPL  	   = data->mvaNoIso_WPL  [i];
  jetIdx        	   = data->jetIdx        [i];
  tightCharge   	   = data->tightCharge   [i];
  charge        	   = data->charge        [i];
  lostHits      	   = data->lostHits      [i];



  
}

elec::~elec(){}


//access tree
elecData::elecData(std::string name, TTree* tree, bool readIn, bool isMC, std::string SFName){

  m_name = name;
  m_isMC = isMC;

  connectBranches(readIn, tree);

  //
  // Load the electron SFs
  //
  if(m_isMC){

    if(SFName != "2017" && SFName != "2018"){
      std::cout << "elecData::Warning no scale factors for " << m_name << std::endl;
    }else{

      std::string tightSFName = "nTupleAnalysis/baseClasses/data/ElecSF2017/egammaEffi.txt_EGM2D_runBCDEF_passingTight94X.root";
      std::string recoSFName  = "nTupleAnalysis/baseClasses/data/ElecSF2017/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root";
      if(SFName == "2018"){
	tightSFName = "nTupleAnalysis/baseClasses/data/ElecSF2018/2018_ElectronTight.root";
	//recoSFName  = "nTupleAnalysis/baseClasses/data/ElecSF2018/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root";
	recoSFName  = "nTupleAnalysis/baseClasses/data/ElecSF2018/egammaEffi.txt_EGM2D_updatedAll.root";
      }

      std::cout << "elecData::Loading SF from files: \n\t" << tightSFName << "\n and \n\t" << recoSFName  << "\n For elecs " << m_name << std::endl;

      m_SFFileTight = new TFile(tightSFName.c_str(),"READ");
      m_SFHistTight = (TH2D*)m_SFFileTight->Get("EGamma_SF2D");
      
      m_SFFileReco = new TFile(recoSFName.c_str(),"READ");
      m_SFHistReco = (TH2D*)m_SFFileReco->Get("EGamma_SF2D");
    }
    
  }// isMC
  
  
}

void elecData::connectBranches(bool readIn, TTree* tree){

  std::string elecName =  m_name;
  std::string NElecName = "n"+m_name;

  connectBranch(readIn, tree, NElecName, nElecs, "i" );

  connectBranchArr(readIn, tree, elecName+"_pt"     , pt     ,NElecName, "F");  
  connectBranchArr(readIn, tree, elecName+"_eta"    , eta    ,NElecName, "F");  
  connectBranchArr(readIn, tree, elecName+"_phi"    , phi    ,NElecName, "F");  
  connectBranchArr(readIn, tree, elecName+"_mass"   , m      ,NElecName, "F");

  connectBranchArr(readIn, tree, elecName+"_dr03EcalRecHitSumEt"        ,     dr03EcalRecHitSumEt             ,NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_dr03HcalDepth1TowerSumEt"   ,     dr03HcalDepth1TowerSumEt        ,NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_dr03TkSumPt"                ,     dr03TkSumPt                     ,NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_eInvMinusPInv"              ,     eInvMinusPInv                   ,NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_hoe"                        ,     hoe                             ,NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_miniPFRelIso_all"           ,     miniPFRelIso_all                ,NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_miniPFRelIso_chg"           ,     miniPFRelIso_chg                ,NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_pfRelIso03_all"             ,     pfRelIso03_all                  ,NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_pfRelIso03_chg"             ,     pfRelIso03_chg                  ,NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_r9"                         ,     r9                              ,NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_scEtOverPt"                 ,     scEtOverPt                      ,NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_sieie"                      ,     sieie                           ,NElecName, "F");

  connectBranchArr(readIn, tree, elecName+"_cutBased"                   ,     cutBased                        ,NElecName, "i");
  connectBranchArr(readIn, tree, elecName+"_pdgId"                      ,     pdgId                           ,NElecName, "i");

  connectBranchArr(readIn, tree, elecName+"_convVeto"                    ,    convVeto                         ,NElecName, "O");

  connectBranchArr(readIn, tree, elecName+"_genPartFlav"                 ,    genPartFlav                      ,NElecName, "b");


  connectBranchArr(readIn, tree, elecName+"_deltaEtaSC"        , deltaEtaSC    , NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_dxy"               , dxy           , NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_dxyErr"            , dxyErr        , NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_dz"                , dz            , NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_dzErr"             , dzErr         , NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_energyErr"         , energyErr     , NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_ip3d"              , ip3d          , NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_jetPtRelv2"        , jetPtRelv2    , NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_jetRelIso"         , jetRelIso     , NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_mvaHZZIso"         , mvaHZZIso     , NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_mvaIso"            , mvaIso        , NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_mvaNoIso"          , mvaNoIso      , NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_sip3d"             , sip3d         , NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_mvaTTH"            , mvaTTH        , NElecName, "F");
  connectBranchArr(readIn, tree, elecName+"_mvaIso_WP80"       , mvaIso_WP80   , NElecName, "O");
  connectBranchArr(readIn, tree, elecName+"_mvaIso_WP90"       , mvaIso_WP90   , NElecName, "O");
  connectBranchArr(readIn, tree, elecName+"_mvaIso_WPL"        , mvaIso_WPL    , NElecName, "O");
  connectBranchArr(readIn, tree, elecName+"_mvaNoIso_WP80"     , mvaNoIso_WP80 , NElecName, "O");
  connectBranchArr(readIn, tree, elecName+"_mvaNoIso_WP90"     , mvaNoIso_WP90 , NElecName, "O");
  connectBranchArr(readIn, tree, elecName+"_mvaNoIso_WPL"      , mvaNoIso_WPL  , NElecName, "O");
  connectBranchArr(readIn, tree, elecName+"_jetIdx"            , jetIdx        , NElecName, "i");
  connectBranchArr(readIn, tree, elecName+"_tightCharge"       , tightCharge   , NElecName, "i");
  connectBranchArr(readIn, tree, elecName+"_charge"            , charge        , NElecName, "i");
  connectBranchArr(readIn, tree, elecName+"_lostHits"          , lostHits      , NElecName, "b");



}    


void elecData::writeElecs(std::vector< std::shared_ptr<elec> > outputElecs){
  
  int nOutputElecs = outputElecs.size();
  this->nElecs = outputElecs.size();
 
  for(Int_t i = 0; i < int(this->nElecs); ++i){
    if(i > int(MAXELECS-1)) {
      std::cout  << m_name << "::Warning too many elecs! " << nOutputElecs << " electrons. Skipping. "<< std::endl;
      break;
    }

    const elecPtr& thisElec = outputElecs.at(i);

    this->pt    [i] = thisElec->pt         ;
    this->eta   [i] = thisElec->eta        ;
    this->phi   [i] = thisElec->phi        ;
    this->m     [i] = thisElec->m          ;

    this->dr03EcalRecHitSumEt          [i]  = thisElec->dr03EcalRecHitSumEt          ;
    this->dr03HcalDepth1TowerSumEt     [i]  = thisElec->dr03HcalDepth1TowerSumEt     ;
    this->dr03TkSumPt                  [i]  = thisElec->dr03TkSumPt                  ;
    this->eInvMinusPInv                [i]  = thisElec->eInvMinusPInv                ;
    this->hoe                          [i]  = thisElec->hoe                          ;
    this->miniPFRelIso_all             [i]  = thisElec->miniPFRelIso_all             ;
    this->miniPFRelIso_chg             [i]  = thisElec->miniPFRelIso_chg             ;
    this->pfRelIso03_all               [i]  = thisElec->pfRelIso03_all               ;
    this->pfRelIso03_chg               [i]  = thisElec->pfRelIso03_chg               ;
    this->r9                           [i]  = thisElec->r9                           ;
    this->scEtOverPt                   [i]  = thisElec->scEtOverPt                   ;
    this->sieie                        [i]  = thisElec->sieie                        ;
    this->cutBased                     [i]  = thisElec->cutBased                     ;
    this->pdgId                        [i]  = thisElec->pdgId                        ;
    this->convVeto                     [i]  = thisElec->convVeto                     ;
    this->genPartFlav                  [i]  = thisElec->genPartFlav                  ;

    this->deltaEtaSC                 [i] = thisElec->deltaEtaSC    ;
    this->dxy           	     [i] = thisElec->dxy           ;
    this->dxyErr        	     [i] = thisElec->dxyErr        ;
    this->dz            	     [i] = thisElec->dz            ;
    this->dzErr         	     [i] = thisElec->dzErr         ;
    this->energyErr     	     [i] = thisElec->energyErr     ;
    this->ip3d          	     [i] = thisElec->ip3d          ;
    this->jetPtRelv2    	     [i] = thisElec->jetPtRelv2    ;
    this->jetRelIso     	     [i] = thisElec->jetRelIso     ;
    this->mvaHZZIso     	     [i] = thisElec->mvaHZZIso     ;
    this->mvaIso        	     [i] = thisElec->mvaIso        ;
    this->mvaNoIso      	     [i] = thisElec->mvaNoIso      ;
    this->sip3d         	     [i] = thisElec->sip3d         ;
    this->mvaTTH        	     [i] = thisElec->mvaTTH        ;
    this->mvaIso_WP80   	     [i] = thisElec->mvaIso_WP80   ;
    this->mvaIso_WP90   	     [i] = thisElec->mvaIso_WP90   ;
    this->mvaIso_WPL    	     [i] = thisElec->mvaIso_WPL    ;
    this->mvaNoIso_WP80 	     [i] = thisElec->mvaNoIso_WP80 ;
    this->mvaNoIso_WP90 	     [i] = thisElec->mvaNoIso_WP90 ;
    this->mvaNoIso_WPL  	     [i] = thisElec->mvaNoIso_WPL  ;
    this->jetIdx        	     [i] = thisElec->jetIdx        ;
    this->tightCharge   	     [i] = thisElec->tightCharge   ;
    this->charge        	     [i] = thisElec->charge        ;
    this->lostHits      	     [i] = thisElec->lostHits      ;

  }

  return ;
}



std::vector<std::shared_ptr<elec> > elecData::getElecs(float ptMin, float etaMax, bool mvaCut){

  std::vector<std::shared_ptr<elec>> outputElecs;
  for(Int_t i = 0; i < int(nElecs); ++i){
    if(i > int(MAXELECS-1)) {
      std::cout  << m_name << "::Warning too many elecs! " << nElecs << " elecs. Skipping. "<< std::endl;
      break;
    }

    if(      pt[i] < ptMin) continue;
    if(fabs(eta[i])>etaMax) continue;
    if(mvaCut && !mvaIso_WP80[i]) continue;
    //if(isolation && pfRelIso04_all[i] > 0.20) continue; 

    outputElecs.push_back(std::make_shared<elec>(elec(i, this)));
  }

  return outputElecs;
}

elecData::~elecData(){
  std::cout << "elecData::destroyed " << std::endl;
}
