
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
  isolation_corrected = data->isolation_corrected[i];
  isolation_trackerOnly = data->isolation_trkIsoOnly[i];
 
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
  connectBranchArr(readIn, tree, muonName+"_iso",            isolation_corrected, NMuonName, "F" );
  connectBranchArr(readIn, tree, muonName+"_isoTrackerOnly", isolation_trkIsoOnly,NMuonName, "F" );

  // Add

  //   12 :Muon_pfRelIso03_all :                                              //
  //         | Float_t PF relative isolation dR=0.3, total (deltaBeta corrections)//
  //   13 :Muon_pfRelIso03_chg :                                              //
  //         | Float_t PF relative isolation dR=0.3, charged component          //
  //   17 :Muon_ptErr : Float_t ptError of the muon track                     //
  //   21 :Muon_tkRelIso :                                                    //
  //         | Float_t Tracker-based relative isolation dR=0.3 for highPt, trkIso/tunePpt//
  //   29 :Muon_pdgId :                                                       //
  //         | Int_t PDG code assigned by the event reconstruction (not by MC truth)//
  //   39 :Muon_looseId : Bool_t muon is loose muon                           //
									      
  //   41 :Muon_mediumPromptId : Bool_t cut-based ID, medium prompt WP        //
  //   44 :Muon_mvaId :                                                       //
  //   46 :Muon_pfIsoId :                                                     //
  //         | UChar_t PFIso ID from miniAOD selector (1=PFIsoVeryLoose, 2=PFIsoLoose, 3=PFIsoMedium, 4=PFIsoTight, 5=PFIsoVeryTight, 6=PFIsoVeryVeryTight)//
  //   51 :Muon_tkIsoId : UChar_t TkIso ID (1=TkIsoLoose, 2=TkIsoTight)       //
  //   54 :Muon_genPartFlav :                                                 //
  //         | UChar_t Flavour of genParticle for MC matching to status==1 muons://
  //         |  1 = prompt muon (including gamma//->mu mu), 15 = muon from prompt tau, 5 = muon from b, 4 = muon from c, 3 = muon from light or unknown, 0 = unmatched//


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
    this->isolation_corrected[i] =    thisMuon->isolation_corrected   ;
    this->isolation_trkIsoOnly[i] =    thisMuon->isolation_trackerOnly  ;

  }

  return ;
}



std::vector<std::shared_ptr<muon>> muonData::getMuons(float ptMin, float etaMax, int tag, bool isolation){

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
    if(isolation && pfRelIso04_all[i] > 0.20) continue; //working points here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2

    if(      pt[i] < ptMin) continue;
    if(fabs(eta[i])>etaMax) continue;

    outputMuons.push_back(std::make_shared<muon>(muon(i, this)));
  }

  return outputMuons;
}

muonData::~muonData(){
  std::cout << "muonData::destroyed " << std::endl;
}
