
#include "TChain.h"
#include "TFile.h"

#include "nTupleAnalysis/baseClasses/interface/muonData.h"

using namespace nTupleAnalysis;

//muon object
muon::muon(UInt_t i, muonData* data){


  pt  = data->pt [i];
  eta = data->eta[i];
  phi = data->phi[i];
  m   = data->m  [i];
  ip3d   = data->ip3d[i];
  sip3d  = data->sip3d[i];
  dxy    = data->dxy[i];
  dxyErr = data->dxyErr[i];

  if(m < 0.10) m = 0.1057;
    
  p = TLorentzVector();
  p.SetPtEtaPhiM(pt, eta, phi, m);

  softId   = data->softId[i];
  highPtId = data->highPtId[i];
  
  mediumId = data->mediumId[i];
  tightId  = data->tightId[i];

  quality  = mediumId + tightId;

  jetIdx    = data->jetIdx[i];
  isolation = data->pfRelIso04_all[i];
  //isolation_corrected = data->isolation_corrected[i];
  //isolation_trackerOnly = data->isolation_trkIsoOnly[i];

  pfRelIso03_all     = data->pfRelIso03_all  [i];
  pfRelIso03_chg     = data->pfRelIso03_chg  [i];
  ptErr              = data->ptErr           [i];
  tkRelIso           = data->tkRelIso        [i];
  pdgId              = data->pdgId           [i];
  looseId            = data->looseId         [i];
  mediumPromptId     = data->mediumPromptId  [i];
  mvaId              = data->mvaId           [i];
  pfIsoId            = data->pfIsoId         [i];
  tkIsoId            = data->tkIsoId         [i];
  genPartFlav        = data->genPartFlav     [i];



  dxybs              = data->dxybs              [i];
  dz                 = data->dz                 [i];
  dzErr              = data->dzErr              [i];
  miniPFRelIso_all   = data->miniPFRelIso_all   [i];
  miniPFRelIso_chg   = data->miniPFRelIso_chg   [i];
  mvaTTH             = data->mvaTTH             [i];
  nStations          = data->nStations          [i];
  nTrackerLayers     = data->nTrackerLayers     [i];
  highPurity         = data->highPurity         [i];
  cleanmask          = data->cleanmask          [i];


 
  //
  // Load the SFs
  //
  if(data->m_isMC && data->m_SFHistTight && data->m_SFHistIso){
    if(pt < 120. ){
      SF *= data->m_SFHistIso  ->GetBinContent(data->m_SFHistIso  ->FindBin(pt, fabs(eta)));
      SF *= data->m_SFHistTight->GetBinContent(data->m_SFHistTight->FindBin(pt, fabs(eta)));
    }
  }
  

}

muon::~muon(){}


//access tree
muonData::muonData(std::string name, TTree* tree, bool readIn, bool isMC, std::string SFName){
  
  m_name = name;
  m_isMC = isMC;

  connectBranches(readIn, tree);

  //
  // Load the muon SFs
  //
  if(readIn && m_isMC){

    if(SFName != "2017" && SFName != "2018"){
      std::cout << "muonData::Warning no scale factors for " << m_name << std::endl;
    }else{

      std::string IDSFName = "";
      std::string IsoSFName = "";
      
      if(SFName == "2017"){
	
	IDSFName = "nTupleAnalysis/baseClasses/data/MuonSF2017/RunBCDEF_SF_ID.root";
	IsoSFName = "nTupleAnalysis/baseClasses/data/MuonSF2017/RunBCDEF_SF_ISO.root";

	m_SFFileID = new TFile(IDSFName.c_str(),"READ");
	m_SFHistTight = (TH2D*)m_SFFileID->Get("NUM_TightID_DEN_genTracks_pt_abseta");
      
	m_SFFileIso = new TFile(IsoSFName.c_str(),"READ");
	m_SFHistIso = (TH2D*)m_SFFileIso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");

      }else{
	IDSFName = "nTupleAnalysis/baseClasses/data/MuonSF2018/RunABCD_SF_ID.root";
	IsoSFName = "nTupleAnalysis/baseClasses/data/MuonSF2018/RunABCD_SF_ISO.root";

	m_SFFileID = new TFile(IDSFName.c_str(),"READ");
	m_SFHistTight = (TH2D*)m_SFFileID->Get("NUM_TightID_DEN_TrackerMuons_pt_abseta");
      
	m_SFFileIso = new TFile(IsoSFName.c_str(),"READ");
	m_SFHistIso = (TH2D*)m_SFFileIso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");

      }

      std::cout << "muonData::Loading SF from files: \n\t" << IDSFName << "\n and \n\t" << IsoSFName  << "\n For muons " << m_name << std::endl;

    }
    
  }// isMC

}

void muonData::connectBranches(bool readIn, TTree* tree){

  std::string muonName =  m_name;
  std::string NMuonName = "n"+m_name;

  connectBranch(readIn, tree, NMuonName, nMuons, "i" );

  connectBranchArr(readIn, tree, muonName+"_pt"     , pt     ,NMuonName, "F");  
  connectBranchArr(readIn, tree, muonName+"_eta"    , eta    ,NMuonName, "F");  
  connectBranchArr(readIn, tree, muonName+"_phi"    , phi    ,NMuonName, "F");  
  connectBranchArr(readIn, tree, muonName+"_mass"   , m      ,NMuonName, "F");
  connectBranchArr(readIn, tree, muonName+"_ip3d"   , ip3d   ,NMuonName, "F");
  connectBranchArr(readIn, tree, muonName+"_sip3d"  , sip3d  ,NMuonName, "F");
  connectBranchArr(readIn, tree, muonName+"_dxy"    , dxy    ,NMuonName, "F");
  connectBranchArr(readIn, tree, muonName+"_dxyErr" , dxyErr ,NMuonName, "F");

  int softIDRes = connectBranchArr(readIn, tree, muonName+"_softId"  , softId, NMuonName, "O" );
  if(softIDRes == -1){
    std::cout << "\tUsing " << muonName+"_isSoftMuon"         << " for softId " << std::endl;
    connectBranchArr(readIn, tree, muonName+"_isSoftMuon"  , softId, NMuonName, "O" );
  }
  connectBranchArr(readIn, tree, muonName+"_highPtId", highPtId, NMuonName, "B" );
  //load othr vars here
  int medIDRes = connectBranchArr(readIn, tree, muonName+"_mediumId", mediumId, NMuonName, "O" );
  if(medIDRes == -1){
    std::cout << "\tUsing " << muonName+"_isMediumMuon" << " for mediumId " << std::endl;
    connectBranchArr(readIn, tree, muonName+"_isMediumMuon", mediumId, NMuonName, "O" );
  }

  int tightIDRes = connectBranchArr(readIn, tree, muonName+"_tightId" , tightId , NMuonName, "O");
  if(tightIDRes == -1){
    std::cout << "\tUsing " << muonName+"_isTightMuon"   << " for tightId " << std::endl;
    connectBranchArr(readIn, tree, muonName+"_isTightMuon" , tightId, NMuonName, "O" );
  }

  connectBranchArr(readIn, tree, muonName+"_jetIdx",         jetIdx,              NMuonName, "i" );
  connectBranchArr(readIn, tree, muonName+"_pfRelIso04_all", pfRelIso04_all,      NMuonName, "F" );
  //connectBranchArr(readIn, tree, muonName+"_iso",            isolation_corrected, NMuonName, "F" );
  //connectBranchArr(readIn, tree, muonName+"_isoTrackerOnly", isolation_trkIsoOnly,NMuonName, "F" );


  connectBranchArr(readIn, tree, muonName+"_pfRelIso03_all"  , pfRelIso03_all  , NMuonName, "F");
  connectBranchArr(readIn, tree, muonName+"_pfRelIso03_chg"  , pfRelIso03_chg  , NMuonName, "F");
  connectBranchArr(readIn, tree, muonName+"_ptErr"           , ptErr           , NMuonName, "F");
  connectBranchArr(readIn, tree, muonName+"_tkRelIso"        , tkRelIso        , NMuonName, "F");
  connectBranchArr(readIn, tree, muonName+"_pdgId"           , pdgId           , NMuonName, "i");
  connectBranchArr(readIn, tree, muonName+"_looseId"         , looseId         , NMuonName, "O");
  connectBranchArr(readIn, tree, muonName+"_mediumPromptId"  , mediumPromptId  , NMuonName, "O");
  connectBranchArr(readIn, tree, muonName+"_mvaId"           , mvaId           , NMuonName, "b");
  connectBranchArr(readIn, tree, muonName+"_pfIsoId"         , pfIsoId         , NMuonName, "b");
  connectBranchArr(readIn, tree, muonName+"_tkIsoId"         , tkIsoId         , NMuonName, "b");
  connectBranchArr(readIn, tree, muonName+"_genPartFlav"     , genPartFlav     , NMuonName, "b");



  connectBranchArr(readIn, tree, muonName+"_dxybs"               , dxybs              ,  NMuonName, "F");
  connectBranchArr(readIn, tree, muonName+"_dz"                  , dz                 ,  NMuonName, "F");
  connectBranchArr(readIn, tree, muonName+"_dzErr"               , dzErr              ,  NMuonName, "F");
  connectBranchArr(readIn, tree, muonName+"_miniPFRelIso_all"    , miniPFRelIso_all   ,  NMuonName, "F");
  connectBranchArr(readIn, tree, muonName+"_miniPFRelIso_chg"    , miniPFRelIso_chg   ,  NMuonName, "F");
  connectBranchArr(readIn, tree, muonName+"_mvaTTH"              , mvaTTH             ,  NMuonName, "F");
  connectBranchArr(readIn, tree, muonName+"_nStations"           , nStations          ,  NMuonName, "i");
  connectBranchArr(readIn, tree, muonName+"_nTrackerLayers"      , nTrackerLayers     ,  NMuonName, "i");
  connectBranchArr(readIn, tree, muonName+"_highPurity"          , highPurity         ,  NMuonName, "b");
  connectBranchArr(readIn, tree, muonName+"_cleanmask"           , cleanmask          ,  NMuonName, "b");






}    


void muonData::writeMuons(std::vector< std::shared_ptr<muon> > outputMuons){
  
  int nOutputMuons = outputMuons.size();
  this->nMuons = outputMuons.size();
 
  for(Int_t i = 0; i < int(this->nMuons); ++i){
    if(i > int(MAXMUONS-1)) {
      std::cout  << m_name << "::Warning too many muons! " << nOutputMuons << " muons. Skipping. "<< std::endl;
      break;
    }

    const muonPtr& thisMuon = outputMuons.at(i);

    this->pt    [i] = thisMuon->pt         ;
    this->eta   [i] = thisMuon->eta        ;
    this->phi   [i] = thisMuon->phi        ;
    this->m     [i] = thisMuon->m          ;
    this->ip3d  [i] = thisMuon->ip3d       ;
    this->sip3d [i] = thisMuon->sip3d	   ;
    this->dxy   [i] = thisMuon->dxy	   ;
    this->dxyErr[i] = thisMuon->dxyErr     ;

    this->softId[i] = 	       thisMuon->softId     ;
    this->highPtId[i] =        thisMuon->highPtId ; 
    this->mediumId[i] =        thisMuon->mediumId ; 
    this->tightId[i] =         thisMuon->tightId  ; 
    this->jetIdx[i] = 	       thisMuon->jetIdx     ;
    this->pfRelIso04_all[i] =  thisMuon->isolation; 
    //this->isolation_corrected[i] =    thisMuon->isolation_corrected   ;
    //this->isolation_trkIsoOnly[i] =    thisMuon->isolation_trackerOnly  ;

    this->pfRelIso03_all  [i] = thisMuon->pfRelIso03_all     ;
    this->pfRelIso03_chg  [i] = thisMuon->pfRelIso03_chg     ;
    this->ptErr           [i] = thisMuon->ptErr              ;
    this->tkRelIso        [i] = thisMuon->tkRelIso           ;
    this->pdgId           [i] = thisMuon->pdgId              ;
    this->looseId         [i] = thisMuon->looseId            ;
    this->mediumPromptId  [i] = thisMuon->mediumPromptId     ;
    this->mvaId           [i] = thisMuon->mvaId              ;
    this->pfIsoId         [i] = thisMuon->pfIsoId            ;
    this->tkIsoId         [i] = thisMuon->tkIsoId            ;
    this->genPartFlav     [i] = thisMuon->genPartFlav        ;

    this->dxybs             [i] = thisMuon-> dxybs              ;
    this->dz                [i] = thisMuon-> dz                 ;
    this->dzErr             [i] = thisMuon-> dzErr              ;
    this->miniPFRelIso_all  [i] = thisMuon-> miniPFRelIso_all   ;
    this->miniPFRelIso_chg  [i] = thisMuon-> miniPFRelIso_chg   ;
    this->mvaTTH            [i] = thisMuon-> mvaTTH             ;
    this->nStations         [i] = thisMuon-> nStations          ;
    this->nTrackerLayers    [i] = thisMuon-> nTrackerLayers     ;
    this->highPurity        [i] = thisMuon-> highPurity         ;
    this->cleanmask         [i] = thisMuon-> cleanmask          ;
  }

  return ;
}



std::vector<std::shared_ptr<muon>> muonData::getMuons(float ptMin, float etaMax, int tag, bool isolation, float sip3dMax){

  std::vector<std::shared_ptr<muon>> outputMuons;

  for(Int_t i = 0; i < int(nMuons); ++i){
    if(i > int(MAXMUONS-1)) {
      std::cout  << m_name << "::Warning too many muons! " << nMuons << " muons. Skipping. "<< std::endl;
      break;
    }

    if(tag == 0 && softId[i]   == 0) continue;
    if(tag == 1 && highPtId[i] == 0) continue;
    if(tag == 2 && mediumId[i] == 0) continue;
    if(tag == 3 && tightId[i]  == 0) continue;
    if(tag == 4 && int(mvaId[i]) < 3) continue;
    if(isolation && pfRelIso04_all[i] > 0.20) continue; //working points here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2

    if(      pt[i] < ptMin) continue;
    if(fabs(eta[i])>etaMax) continue;

    if( (sip3dMax > 0) && (sip3d[i] > sip3dMax) ) continue;

    outputMuons.push_back(std::make_shared<muon>(muon(i, this)));
  }

  return outputMuons;
}

muonData::~muonData(){
  std::cout << "muonData::destroyed " << std::endl;
}
