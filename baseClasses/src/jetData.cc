#include <sstream>      // std::stringstream, std::stringbuf

#include "TChain.h"

#include "nTupleAnalysis/baseClasses/interface/jetData.h"
#include "DataFormats/BTauReco/interface/ParticleMasses.h"
#include "CondFormats/BTauObjects/interface/BTagEntry.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"

using namespace nTupleAnalysis;
using std::cout;  using std::endl;


//jet object
jet::jet(){}
jet::jet(UInt_t i, jetData* data, std::string tagger){

  tree_idx = i;

  cleanmask = data->cleanmask[i];

  pt  = data->pt [i];
  eta = data->eta[i];
  phi = data->phi[i];
  m   = data->m  [i];
  p = TLorentzVector();
  p.SetPtEtaPhiM(pt, eta, phi, m);
  e = p.E();

  bRegCorr = data->bRegCorr[i];
  appliedBRegression = false;
  pt_wo_bRegCorr = data->pt[i];

  deepB     = data->deepB[i];
  CSVv2     = data->CSVv2[i];
  deepFlavB = data->deepFlavB[i];
  float deepFlavB_alt = data->deepFlavourB[i] + data->deepFlavourBB[i] + data->deepFlavourLEPB[i];
  if(deepFlavB == 0)
    deepFlavB = deepFlavB_alt;

  bTagScore = deepFlavB;
  if(tagger == "CSVv2") bTagScore = CSVv2;
  if(tagger == "deepB") bTagScore = deepB;
  //if(tagger == "deepFlavB" || tagger == "deepjet") bTagScore = deepFlavB;

  // Normalizize the underflow
  if(CSVv2 < 0) 
    CSVv2 = -0.1; 
  
  puId = data->puId[i];
  jetId = data->jetId[i];


  ntracks        = data->ntracks        [i];
  nseltracks     = data->nseltracks     [i];

  //CombIVF_N      = data->CombIVF_N      [i];
  SoftMu         = data->SoftMu         [i];
  if(SoftMu < 0) 
    SoftMu = -0.1; 

  SoftEl         = data->SoftEl         [i];
  if(SoftEl < 0) 
    SoftEl = -0.1; 


  nSM            = data->nSM            [i];
  nSE            = data->nSE            [i];
  looseID        = data->looseID        [i];
  tightID        = data->tightID        [i];
  DeepCSVb       = data->DeepCSVb       [i];
  DeepCSVc       = data->DeepCSVc       [i];
  DeepCSVl       = data->DeepCSVl       [i];
  DeepCSVbb      = data->DeepCSVbb      [i];

  DeepCSV = DeepCSVb+DeepCSVbb;
  if(DeepCSV < 0)
    DeepCSV = -0.1;

  if(DeepCSVb < 0)
    DeepCSVb = -0.1;

  if(DeepCSVbb < 0)
    DeepCSVbb = -0.1;


  flavour        = data->flavour        [i];
  flavourCleaned = data->flavourCleaned [i];
  partonFlavour  = data->partonFlavour  [i];
  hadronFlavour  = data->hadronFlavour  [i];
  nbHadrons      = data->nbHadrons      [i];
  ncHadrons      = data->ncHadrons      [i];

  isTag          = data->isTag      [i];
  isSel          = data->isSel      [i];

  if(data->trkData){
    nFirstTrack = data->nFirstTrack[i];
    nLastTrack = data->nLastTrack[i];

    std::vector<trackPtr> tracksTmp = data->trkData->getTracks(nFirstTrack,nLastTrack);
    for(const trackPtr& track: tracksTmp){
      track->dR = track->p.DeltaR(p);
      track->ptRel = track->p.Vect().Perp(p.Vect().Unit());
      track->pPar  = track->p.Vect().Dot(p.Vect().Unit());
      if(track->dR < 0.3)
	tracks.push_back(track);
    }
  }

  //
  //  Set the isV0 bits
  //
  unsigned int nTracks = tracks.size();
  for(unsigned int iTrk1 = 0; iTrk1 < nTracks; ++iTrk1){
    for(unsigned int iTrk2 = iTrk1; iTrk2 < nTracks; ++iTrk2){
      if(iTrk1 == iTrk2 ) continue;

      if (tracks[iTrk1]->charge * tracks[iTrk2]->charge > 0)
	continue;


      float invariantMass = (tracks[iTrk1]->p + tracks[iTrk2]->p).M();
      if (std::abs(invariantMass - reco::ParticleMasses::k0) < 0.03){
	tracks[iTrk1]->isfromV0 = true;
	tracks[iTrk2]->isfromV0 = true;
      }

    }
  }

  if(data->debug){
    std::cout << "i is " << i << std::endl;;

    std::cout << "nFirst is ";
    for(unsigned int iT =0; iT < 100; ++iT){
      std::cout << data->nFirstSV[iT] << " ";
    }
    std::cout << std::endl;

    std::cout << "nLast is ";
    for(unsigned int iT =0; iT < 100; ++iT){
      std::cout << data->nLastSV[iT] << " ";
    }
    std::cout << std::endl;
  }

  if(data->btagData){
    if(data->btagData->haveSVs){
      if(data->debug)  std::cout << data->m_name << " Getting SVs " << data->nFirstSV[i] << " " << data->nLastSV[i] << std::endl;
      svs = data->btagData->getSecondaryVertices(data->nFirstSV[i],data->nLastSV[i], data->debug);
    }
    
    if(data->btagData->haveTrkTagVars){
      trkTagVars = data->btagData->getTrkTagVars(data->nFirstTrkTagVar[i],data->nLastTrkTagVar[i]);
    }
    
    if(data->btagData->haveTagVars){
      tagVars = data->btagData->getTagVars(i);
    }
  }

  //
  // Hack to fix trkTagVas phi which is not filled in cmssw
  //
  for(const trkTagVarPtr& trkTagVar: trkTagVars){
    //std::cout << "Matching " << trkTagVar->trackEta << " " << trkTagVar->pt << std::endl;
    //bool foundMatch = false;

    for(const trackPtr& track: tracks){
      //std::cout << "\t " << track->eta << " " << track->pt << std::endl;
      if(fabs(track->IP2D - trkTagVar->trackSip2dVal) < 1e-6 && fabs(track->IP - trkTagVar->trackSip3dVal) < 1e-6){
  	trkTagVar->trackPhi = track->phi;
  	trkTagVar->p.SetPtEtaPhiM(trkTagVar->pt, trkTagVar->trackEta, trkTagVar->trackPhi, trkTagVar->m);
  	trkTagVar->e = p.E();
	//foundMatch = true;
  	break;
      }
    }

    //if(!foundMatch){
    //  cout << "Did not find trkTag --> track match for track  eta: " << trkTagVar->trackEta << " pt "  << trkTagVar->pt 
    //	   << "  trackSip2dVal: " << trkTagVar->trackSip2dVal
    //	   << "  trackSip3dVal: " << trkTagVar->trackSip3dVal
    //	   << "  trackMomentum: " << trkTagVar->trackMomentum
    //	   << " dR " << trkTagVar->trackDeltaR << endl;
    //  cout << "We have tracks " << endl;
    //
    //  for(const trackPtr& track: tracks){
    //	cout << "\t eta : " <<  track->eta << " phi:  " << track->phi << " pt : " << track->pt << "  IP2D: " << track->IP2D << " IP: " << track->IP << endl;
    //  }
    //}

  }


  for(const trkTagVarPtr& trkTagVar: trkTagVars){
    //std::cout << "Matching " << trkTagVar->trackEta << " " << trkTagVar->pt << std::endl;
    for(const trackPtr& track: tracks){
      
      if(track->p.DeltaR(trkTagVar->p) < 0.01){
	trkTagVar->hasTrackMatch = true;
	trkTagVar->matchIsFromV0 = track->isfromV0;
	track->hasTrkTagVarMatch = true;
      }
    }
  }

  if(data->m_loadGenJets){
    genJet_p = TLorentzVector();    
    genJet_p.SetPtEtaPhiM(data->GenJet_pt[i],
			  data->GenJet_eta[i],
			  data->GenJet_phi[i],
			  data->GenJet_m[i]);
    
    if(data->isB[i] || data->isBB[i] || data->isGBB[i] ){
      flavour        = 5;
    }else if(data->isC[i] || data->isCC[i] || data->isGCC[i] ){
      flavour        = 4;
    }else{
      flavour        = 0;
    }
    
  }

  if(data->m_isMC && data->m_btagCalibrationTool){
    SF = data->getSF(eta, pt, DeepCSV, hadronFlavour);
  }else{
    SF = 1.0;
  }

}


jet::jet(TLorentzVector& vec, float tag){

  p = TLorentzVector(vec);
  pt  = p.Pt();
  eta = p.Eta();
  phi = p.Phi();
  m   = p.M();
  e   = p.E();

  bRegCorr = 1.0;
  appliedBRegression = false;
  pt_wo_bRegCorr  = pt;

  deepB = tag;
  CSVv2 = tag;
  deepFlavB = tag;
  bTagScore = tag;
}

void jet::bRegression(){
  if(appliedBRegression)
    cout << "jetData::ERROR double applying bRegression " << endl;

  scaleFourVector(bRegCorr);
  appliedBRegression = true;
}


void jet::undo_bRegression(){
  assert(appliedBRegression);
  scaleFourVector(1./bRegCorr);
  
  // Sanity Check
  assert(fabs(pt - pt_wo_bRegCorr) < 0.001);
  
  // Avoid subtle floating point errors
  pt = pt_wo_bRegCorr;
  appliedBRegression = false;
  //cout << "pt is " << pt << " pt_wo_bRegCorr " << pt_wo_bRegCorr << endl;

}


void jet::scaleFourVector(float scale){
  p  *= scale;
  pt  = p.Pt();
  eta = p.Eta();
  phi = p.Phi();
  m   = p.M();
  e   = p.E();
}



void jet::RotateZ(float dPhi){
  p.RotateZ(dPhi);
  phi = p.Phi();
}


void jet::dump(){
  std::cout << "jet::dump()" << std::endl;
  std::cout << "    tree_idx: " << tree_idx << std::endl;
  std::cout << "    (pt, eta, phi, m, e) = (" << pt << ", " << eta << ", " << phi << ", " << m << ", " << e << ")" << std::endl;
  std::cout << "    |p| = " << p.P() << std::endl;
  std::cout << "    appliedBRegression = " << appliedBRegression << ", bRegCorr = "<< bRegCorr << std::endl;
}


jet::~jet(){
}

//
//access tree
//
jetData::jetData(std::string name, TTree* tree, bool readIn, bool isMC, std::string jetDetailLevel, std::string prefix, std::string SFName, std::string btagVariations, std::string JECSyst, std::string tagger){

  m_name = name;
  m_prefix = prefix;
  m_isMC = isMC;
  m_jetDetailLevel = jetDetailLevel;

  connectBranches(readIn, tree, JECSyst);
  bTagScore = deepFlavB; // default btagger
  if(tagger != ""){
    if(tagger == "CSVv2") bTagScore = CSVv2;
    if(tagger == "deepB") bTagScore = deepB;
    //if(tagger == "deepFlavB" || tagger == "deepjet") bTagScore = deepFlavB;
  }


  // Split btagVariations at spaces into vector of variation names
  std::stringstream ss(btagVariations);
  std::istream_iterator<std::string> begin(ss);
  std::istream_iterator<std::string> end;
  m_btagVariations = std::vector<std::string>(begin,end);

  //
  // Load the BTagging SFs
  //
  if(readIn && m_isMC && SFName != ""){

    if(SFName != "2017" && SFName != "deepcsv2018" && SFName != "deepjet2018" && SFName != "deepjet2017" && SFName != "deepjet2016"){
      std::cout << "jetData::Warning no scale factors for " << m_name << " and SFName " << SFName << std::endl;
    }else{

      std::string systTag = "_noSyst";
      if(m_btagVariations.size()>1){
	systTag = "";
	std::cout << "Loading b-tag systematic variations. Will take several miniutes and use a few hundred MB of RAM." << std::endl;	
      }else{
	std::cout << "Not loading b-tag systematic variations" << std::endl;
      }
      
      std::string sfFileName =  "nTupleAnalysis/baseClasses/data/BTagSF2017/DeepCSV_94XSF_V4_B_F"+systTag+".csv";
      if(SFName == "deepcsv2018")
	sfFileName = "nTupleAnalysis/baseClasses/data/BTagSF2018/DeepCSV_102XSF_V1"+systTag+".csv";
      if(SFName == "deepjet2018")
	sfFileName = "nTupleAnalysis/baseClasses/data/BTagSF2018/DeepJet_106XUL18SF"+systTag+".csv";
      //sfFileName = "nTupleAnalysis/baseClasses/data/BTagSF2018/DeepJet_102XSF_V1"+systTag+".csv";
      if(SFName == "deepjet2017")
	sfFileName = "nTupleAnalysis/baseClasses/data/BTagSF2017/DeepJet_106XUL17SF_V2"+systTag+".csv";
      //sfFileName = "nTupleAnalysis/baseClasses/data/BTagSF2017/DeepFlavour_94XSF_V3_B_F"+systTag+".csv";
      if(SFName == "deepjet2016")
	sfFileName = "nTupleAnalysis/baseClasses/data/BTagSF2016/DeepJet_2016LegacySF_V1"+systTag+".csv";
      
      std::cout << "jetData::Loading SF from " << sfFileName << " For jets " << m_name << std::endl;
      BTagCalibration calib = BTagCalibration("", sfFileName);//tagger name only needed for creating csv files


      for(auto &variation: m_btagVariations){
	std::cout<<"Load btag systematic variation: "<<variation<<std::endl;

	m_btagCalibrationTools[variation] = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, // 0 is for loose op, 1: medium, 2: tight, 3: discr. reshaping
								      variation // systematic type
								      );

	std::cout << "jetData::Load BTagEntry::FLAV_B" << std::endl;
	m_btagCalibrationTools[variation]->load(calib, 
						BTagEntry::FLAV_B,   // 0 is for b flavour, 1: FLAV_C, 2: FLAV_UDSG
						"iterativefit"      // measurement type
						);
	
	std::cout << "jetData::Load BTagEntry::FLAV_C" << std::endl;
	m_btagCalibrationTools[variation]->load(calib, 
					       BTagEntry::FLAV_C,   // 0 is for b flavour, 1: FLAV_C, 2: FLAV_UDSG
					       "iterativefit"      // measurement type
					       );

	std::cout << "jetData::Load BTagEntry::FLAV_UDSG" << std::endl;
	m_btagCalibrationTools[variation]->load(calib, 
						BTagEntry::FLAV_UDSG,   // 0 is for b flavour, 1: FLAV_C, 2: FLAV_UDSG
						"iterativefit"      // measurement type
						);
      }

    }

  }

}





std::vector< jetPtr > jetData::getJets(float ptMin, float ptMax, float etaMax, bool clean, float tagMin, std::string tagger, bool antiTag, int puIdMin){
  
  std::vector< jetPtr > outputJets;

  float *tag = bTagScore;
  if(tagger != ""){
    if(tagger == "CSVv2") tag = CSVv2;
    if(tagger == "deepB") tag = deepB;
    if(tagger == "deepFlavB" || tagger == "deepjet") tag = deepFlavB;
  }

  if(debug) std::cout << "We have " << nJets << " jets"<< std::endl;
  for(Int_t i = 0; i < int(nJets); ++i){

    if(i > int(MAXJETS-1)) {
      std::cout  << m_name << "::Warning too many jets! " << nJets << " jets. Skipping. "<< std::endl;
      break;
    }

    if(debug) std::cout << " jet   " << pt[i] << " " << eta[i] << " " << phi[i] << std::endl;

      
    if(clean && cleanmask[i] == 0){
      if(debug) std::cout << "... failed cleaning  " << std::endl;
      continue;
    }

    if(          pt[i]  <  ptMin ){
      if(debug) std::cout << "... failed ptMin  " << pt[i] << " < " << ptMin <<  std::endl;
      continue;
    }

    if(          pt[i]  >= ptMax ){
      if(debug) std::cout << "... failed ptMax  " << pt[i] << " >= " << ptMax <<  std::endl;
      continue;
    }

    if(    fabs(eta[i]) > etaMax ) continue;
    if(       (puId[i]  < puIdMin) && (pt[i] < 50)) continue; // Fail pilup rejection. https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupJetID
    if(antiTag^(tag[i]  < tagMin)) continue; // antiTag XOR (jet fails tagMin). This way antiTag inverts the tag criteria to select untagged jets
    outputJets.push_back(std::make_shared<jet>(jet(i, this)));
  }

  return outputJets;
}

std::vector< jetPtr > jetData::getJets(std::vector< jetPtr > inputJets, float ptMin, float ptMax, float etaMax, bool clean, float tagMin, std::string tagger, bool antiTag, int puIdMin){
  if(debug) cout << "jetData::getJets " << endl;
  std::vector< jetPtr > outputJets;
  
  for(auto &jet: inputJets){
    if(debug) cout << "new jet " << endl;

    if(clean && jet->cleanmask == 0) {
      if(debug) cout << "\t fail clean " << endl;
      continue;
    }

    if(         jet->pt   <  ptMin ){
      if(debug) cout << "\t fail ptMin (" << jet->pt << " < " << ptMin << ")" << jet->pt_wo_bRegCorr << " diff: " << jet->pt - ptMin << endl;
      if(debug) jet->dump();
      continue;
    }

    if(         jet->pt   >= ptMax ) {
      if(debug) cout << "\t fail ptMax (" << jet->pt << " >= " << ptMax << ")" << endl;
      continue;
    }

    if(    fabs(jet->eta) > etaMax ) {
      if(debug) cout << "\t fail etaMax (" << fabs(jet->eta) << " > " << etaMax << ")" << endl;
      continue;
    }

    if((jet->puId < puIdMin) && (jet->pt < 50)){//(bit two = loose, bit one = medium, bit zero = tight so puIdMin = 4, 6, 7 : loose, medium, tight)
      if(debug) cout << "\t fail pileup rejection" << endl;
      continue; // Fail pilup rejection. https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupJetID
    }
    
    float tag = jet->bTagScore;
    if(tagger != ""){
      if(tagger == "CSVv2") tag = jet->CSVv2;
      if(tagger == "deepB") tag = jet->deepB;
      if(tagger == "deepFlavB" || tagger == "deepjet") tag = jet->deepFlavB;
    }

    if(antiTag^(tag < tagMin)) {
      if(debug) cout << "\t fail " << tagger << endl;
      continue;
    }

    if(debug) cout << "\t pass jet " << endl;
    outputJets.push_back(jet);
  }

  return outputJets;
}


jetData::~jetData(){ 
  std::cout << "jetData::destroyed " << std::endl;
}


float jetData::getSF(float jetEta,  float jetPt,  float jetTagScore, int jetHadronFlavour, std::string variation){ 
  if(m_btagCalibrationTools.empty()) 
    return 1;
  
  if(fabs(jetHadronFlavour) == 5)
    return m_btagCalibrationTools[variation]->eval_auto_bounds(variation, BTagEntry::FLAV_B, fabs(jetEta), jetPt, jetTagScore);
  
  if(fabs(jetHadronFlavour) == 4)
    return m_btagCalibrationTools[variation]->eval_auto_bounds(variation, BTagEntry::FLAV_C, fabs(jetEta), jetPt, jetTagScore);
  
  return m_btagCalibrationTools[variation]->eval_auto_bounds(variation, BTagEntry::FLAV_UDSG, fabs(jetEta), jetPt, jetTagScore);
}


void jetData::updateSFs(float jetEta,  float jetPt,  float jetTagScore, int jetHadronFlavour,bool debug){
  for(auto &variation: m_btagVariations){
    if(debug)
      cout << "jetPt/jetEta/jetTagScore/jetHadronFlavour/SF" 
	   << jetPt << "/" << jetEta << "/" << jetTagScore << "/" << jetHadronFlavour << "/" << getSF(jetEta, jetPt, jetTagScore, jetHadronFlavour, variation) << endl;
      
    m_btagSFs[variation] *= getSF(jetEta, jetPt, jetTagScore, jetHadronFlavour, variation);
  }
}

void jetData::updateSFs(const jetPtr& jet, bool debug){
  for(auto &variation: m_btagVariations){
    if(debug)
      cout << "jetPt/jetEta/jetTagScore/jetHadronFlavour/SF" 
	   << jet->pt << "/" << jet->eta << "/" << jet->bTagScore << "/" << jet->hadronFlavour << "/" << getSF(jet->eta, jet->pt, jet->bTagScore, jet->hadronFlavour, variation) << endl;
      
    m_btagSFs[variation] *= getSF(jet->eta, jet->pt, jet->bTagScore, jet->hadronFlavour, variation);
  }
}

void jetData::updateSFs(std::vector< jetPtr > jets, bool debug){
  for(auto &jet: jets) updateSFs(jet, debug);
}


void jetData::resetSFs(){
  for(auto &variation: m_btagVariations){
    m_btagSFs[variation] = 1;
  }  
}


void jetData::writeJets(std::vector< jetPtr > outputJets){
  
  int nOutputJets = outputJets.size();
  this->nJets = outputJets.size();

  for(Int_t i = 0; i < int(this->nJets); ++i){
    if(i > int(MAXJETS-1)) {
      std::cout  << m_name << "::Warning too many jets! " << nOutputJets << " jets. Skipping. "<< std::endl;
      break;
    }

    const jetPtr& thisJet = outputJets.at(i);
    this->cleanmask[i] = thisJet->cleanmask;

    this->pt [i] = thisJet->pt  ;
    this->eta[i] = thisJet->eta ;
    this->phi[i] = thisJet->phi ;
    this->m  [i] = thisJet->m   ;


    this->bRegCorr[i] =  thisJet-> bRegCorr;

    this->deepB[i]	      = thisJet->deepB   ; 
    this->CSVv2[i]	      = thisJet->CSVv2   ; 
    this->deepFlavB[i]        = thisJet->deepFlavB; 
  
    this->puId[i] = thisJet->puId;
    this->jetId[i] = thisJet->jetId;
    
    
    this->ntracks        [i] = thisJet->ntracks        ;
    this->nseltracks     [i] = thisJet->nseltracks     ; 
    
      //CombIVF_N      = this->CombIVF_N      [i];
    this->SoftMu         [i] =     thisJet->SoftMu          ;
    this->SoftEl         [i] =     thisJet->SoftEl          ;
    
    this->nSM            [i] =      thisJet->nSM            ;
    this->nSE            [i] =      thisJet->nSE            ;
    this->looseID        [i] =      thisJet->looseID        ;
    this->tightID        [i] =      thisJet->tightID        ;
    this->DeepCSVb       [i] =      thisJet->DeepCSVb       ;
    this->DeepCSVc       [i] =      thisJet->DeepCSVc       ;
    this->DeepCSVl       [i] =      thisJet->DeepCSVl       ;
    this->DeepCSVbb      [i] =      thisJet->DeepCSVbb      ;
    
    this->flavour        [i] =     thisJet->flavour        ;
    this->flavourCleaned [i] =     thisJet->flavourCleaned ;
    this->partonFlavour  [i] =     thisJet->partonFlavour  ;
    this->hadronFlavour  [i] =     thisJet->hadronFlavour  ;
    this->nbHadrons      [i] =     thisJet->nbHadrons      ;
    this->ncHadrons      [i] =     thisJet->ncHadrons      ;

    this->isTag      [i] =   thisJet->isTag          ;
    this->isSel      [i] =   thisJet->isSel          ;

  }

  return ;
}


void jetData::connectBranches(bool readIn, TTree* tree, std::string JECSyst){
  if(debug) std::cout << "jetData::connectBranches(bool readIn, TTree* tree)" << std::endl;

  std::string jetName =  m_prefix+m_name;
  std::string NjetName = m_prefix+"n"+m_name;

  if(JECSyst!="") std::cout << "jetData::connectBranches() Using JEC Systematic " << JECSyst << std::endl;

  connectBranch(readIn, tree, NjetName, nJets, "i");

  connectBranchArr(readIn, tree, jetName+"_pt"  +JECSyst, pt,  NjetName,  "F");
  connectBranchArr(readIn, tree, jetName+"_eta",          eta, NjetName,  "F");
  connectBranchArr(readIn, tree, jetName+"_phi",          phi, NjetName,  "F");
  connectBranchArr(readIn, tree, jetName+"_mass"+JECSyst, m,   NjetName,  "F");  

  connectBranchArr(readIn, tree, jetName+"_cleanmask", cleanmask,   NjetName,  "b");  

  connectBranchArr(readIn, tree, jetName+"_bRegCorr", bRegCorr,   NjetName,  "F");  
  connectBranchArr(readIn, tree, jetName+"_btagDeepB", deepB,   NjetName,  "F");  
  

  int CSVRes = connectBranchArr(readIn, tree, jetName+"_btagCSVV2", CSVv2,   NjetName,  "F");  
  if(readIn && CSVRes == -1){
    std::cout << "\tUsing " << (m_prefix+m_name+"_CombIVF"        ) << " for CSVv2 " << std::endl;
    connectBranchArr(readIn, tree, jetName+"_CombIVF", CSVv2,   NjetName,  "F");  
  }

  int DeepFlavBRes = connectBranchArr(readIn, tree, jetName+"_btagDeepFlavB", deepFlavB,   NjetName,  "F");  
  if(readIn && DeepFlavBRes == -1){
    std::cout << "\tUsing " << (m_prefix+m_name+"_DeepFlavourB  + "+m_prefix+m_name+"_DeepFlavourBB  + " + m_prefix+m_name+"_DeepFlavourLEPB"       ) << " for " << m_prefix + m_name+ "_btagDeepFlavB " << std::endl;
    connectBranchArr(readIn, tree, jetName+"_DeepFlavourB",    deepFlavourB,    NjetName,  "F");  
    connectBranchArr(readIn, tree, jetName+"_DeepFlavourBB",   deepFlavourBB,   NjetName,  "F");  
    connectBranchArr(readIn, tree, jetName+"_DeepFlavourLEPB", deepFlavourLEPB, NjetName,  "F");  
  }
  

  connectBranchArr(readIn, tree, jetName+"_puId",   puId,   NjetName,  "I");  
  connectBranchArr(readIn, tree, jetName+"_jetId", jetId,   NjetName,  "I");  

  if(m_isMC){
    connectBranchArr(readIn, tree, jetName+"_flavour", flavour,   NjetName,  "I");  
    connectBranchArr(readIn, tree, jetName+"_flavourCleaned", flavourCleaned,   NjetName,  "I");  
    connectBranchArr(readIn, tree, jetName+"_partonFlavour", partonFlavour,   NjetName,  "I");  
    connectBranchArr(readIn, tree, jetName+"_hadronFlavour", hadronFlavour,   NjetName,  "I");  
    connectBranchArr(readIn, tree, jetName+"_nbHadrons", nbHadrons,   NjetName,  "I");  
    connectBranchArr(readIn, tree, jetName+"_ncHadrons", ncHadrons,   NjetName,  "I");  
  }

  connectBranchArr(readIn, tree, jetName+"_looseID", looseID,   NjetName,  "I");  
  connectBranchArr(readIn, tree, jetName+"_tightID", tightID,   NjetName,  "I");  

  connectBranchArr(readIn, tree, jetName+"_DeepCSVb", DeepCSVb,   NjetName,  "F");  
  connectBranchArr(readIn, tree, jetName+"_DeepCSVc", DeepCSVc,   NjetName,  "F");  
  connectBranchArr(readIn, tree, jetName+"_DeepCSVl", DeepCSVl,   NjetName,  "F");  
  connectBranchArr(readIn, tree, jetName+"_DeepCSVbb", DeepCSVbb,   NjetName,  "F");  

  connectBranchArr(readIn, tree, jetName+"_isTag", isTag,   NjetName,  "O");  
  connectBranchArr(readIn, tree, jetName+"_isSel", isSel,   NjetName,  "O");  

  //
  //  Following only supported for reading In
  //
  if(readIn){

    //
    //  only load the track if the variables are availible
    //
    if(m_jetDetailLevel.find("Tracks") != std::string::npos){
      std::cout << "jetData::" << m_name << " loading Tracks" << std::endl;
      inputBranch(tree, (m_prefix+m_name+"_ntracks"        ).c_str(),         ntracks        );
      inputBranch(tree, (m_prefix+m_name+"_nseltracks"     ).c_str(),         nseltracks     );
      int nFirstTrackCode = inputBranch(tree, (m_prefix+m_name+"_nFirstTrack").c_str(),  nFirstTrack);
      int nLastTrackCode  = inputBranch(tree, (m_prefix+m_name+"_nLastTrack" ).c_str(),  nLastTrack );
      if(nFirstTrackCode != -1 && nLastTrackCode != -1){
	trkData = new trackData(m_prefix, tree);
      }
    }

    //
    //  Load the btagging data
    //
    if(m_jetDetailLevel.find("btagInputs") != std::string::npos){
      std::cout << "jetData::" << m_name << " loading btagInputs" << std::endl;
      btagData = new btaggingData();
      btagData->initTagVar(m_prefix, tree);  

      inputBranch(tree, (m_prefix+m_name+"_SoftMu"         ).c_str(),         SoftMu         ); 
      inputBranch(tree, (m_prefix+m_name+"_SoftEl"         ).c_str(),         SoftEl         ); 
      inputBranch(tree, (m_prefix+m_name+"_nSM"            ).c_str(),         nSM            ); 
      inputBranch(tree, (m_prefix+m_name+"_nSE"            ).c_str(),         nSE            ); 
  
      int nFirstSVCode = inputBranch(tree, (m_prefix+m_name+"_nFirstSV").c_str(),  nFirstSV);
      int nLastSVCode  = inputBranch(tree, (m_prefix+m_name+"_nLastSV" ).c_str(),  nLastSV );
      if(nFirstSVCode != -1 && nLastSVCode != -1){
	btagData->initSecondaryVerticies(m_prefix, tree);
      }

      int nFirstTrkTagVarCode = inputBranch(tree, (m_prefix+m_name+"_nFirstTrkTagVar").c_str(),  nFirstTrkTagVar);
      int nLastTrkTagVarCode  = inputBranch(tree, (m_prefix+m_name+"_nLastTrkTagVar" ).c_str(),  nLastTrkTagVar );
      if(nFirstTrkTagVarCode != -1 && nLastTrkTagVarCode != -1){
	btagData->initTrkTagVar(m_prefix, tree);
      }
    }

    if(m_jetDetailLevel.find("GenJet") != std::string::npos){
      m_loadGenJets = true;
      connectBranchArr(readIn, tree, jetName+"_GenJetHasMatch"  , GenJet_hasMatch,  NjetName,  "I");
      connectBranchArr(readIn, tree, jetName+"_GenJet_pt"  , GenJet_pt,  NjetName,  "F");
      connectBranchArr(readIn, tree, jetName+"_GenJet_eta",  GenJet_eta, NjetName,  "F");
      connectBranchArr(readIn, tree, jetName+"_GenJet_phi",  GenJet_phi, NjetName,  "F");
      connectBranchArr(readIn, tree, jetName+"_GenJet_mass", GenJet_m,   NjetName,  "F");  

      connectBranchArr(readIn, tree, jetName+"_Jet_isB"         , isB        , NjetName, "I");
      connectBranchArr(readIn, tree, jetName+"_Jet_isGBB"	, isGBB      , NjetName, "I");
      connectBranchArr(readIn, tree, jetName+"_Jet_isBB" 	, isBB       , NjetName, "I");
      connectBranchArr(readIn, tree, jetName+"_Jet_isC" 	, isC        , NjetName, "I");
      connectBranchArr(readIn, tree, jetName+"_Jet_isGCC"	, isGCC      , NjetName, "I");
      connectBranchArr(readIn, tree, jetName+"_Jet_isCC" 	, isCC       , NjetName, "I");
      connectBranchArr(readIn, tree, jetName+"_Jet_isTau"	, isTau      , NjetName, "I");
      connectBranchArr(readIn, tree, jetName+"_Jet_isG" 	, isG        , NjetName, "I");
      connectBranchArr(readIn, tree, jetName+"_Jet_isUD"	, isUD       , NjetName, "I");
      connectBranchArr(readIn, tree, jetName+"_Jet_isS" 	, isS        , NjetName, "I");
      connectBranchArr(readIn, tree, jetName+"_Jet_isUndefined" , isUndefined, NjetName, "I"); 
									       
    }

  }


  return ;
}
