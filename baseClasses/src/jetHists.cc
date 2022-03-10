#include "nTupleAnalysis/baseClasses/interface/jetHists.h"
#include <sstream>      // std::stringstream

using namespace nTupleAnalysis;

jetHists::jetHists(std::string _name, fwlite::TFileService& fs, std::string _title, std::string jetDetailLevel, bool _debug) {
    debug = _debug;
    name  = _name;
    title = _title;
    dir = fs.mkdir(name);
    v = new fourVectorHists(name, dir, title);

    cleanmask = dir.make<TH1F>("cleanmask", (name+"/cleanmask; "+title+" Clean Mask; Entries").c_str(), 2,-0.5,1.5);
    puId = dir.make<TH1F>("puId", (name+"/puId; "+title+" Pileup ID; Entries").c_str(), 17,-0.5,16.5);
    jetId = dir.make<TH1F>("jetId", (name+"/jetId; "+title+" Jet ID; Entries").c_str(), 17,-0.5,16.5);

    deepB     = dir.make<TH1F>("deepB",     (name+"/deepB; "    +title+" Deep B; Entries").c_str(), 120,-0.2,1.2);
    CSVv2     = dir.make<TH1F>("CSVv2",     (name+"/CSVv2; "    +title+" CSV v2; Entries").c_str(), 120,-0.2,1.2);
    deepFlavB = dir.make<TH1F>("deepFlavB", (name+"/deepFlavB; "+title+" Deep (Jet) Flavour B; Entries").c_str(), 120,-0.2,1.2);
    nJets     = dir.make<TH1F>("nJets",     (name+"/nJets;    " +title+" Number of Jets; Entries").c_str(),  10,-0.5,9.5);

    CSVv2_l     = dir.make<TH1F>("CSVv2_l",     (name+"/CSVv2_l; "   +title+" CSV v2; Entries").c_str(), 120,-0.2,1.2);
    deepCSV_l   = dir.make<TH1F>("DeepCSV_l",   (name+"/DeepCSV_l; "   +title+" DeepCSV; Entries").c_str(), 120,-0.2,1.2);
    deepCSVb_l  = dir.make<TH1F>("DeepCSVb_l",   (name+"/DeepCSVb_l; "   +title+" DeepCSVb; Entries").c_str(), 120,-0.2,1.2);
    deepCSVbb_l = dir.make<TH1F>("DeepCSVbb_l",   (name+"/DeepCSVbb_l; "   +title+" DeepCSVbb; Entries").c_str(), 120,-0.2,1.2);

    nSoftMu     = dir.make<TH1F>("nSoftMu",     (name+"/nSoftMu;    " +title+" Number of Soft Mu.; Entries").c_str(),  11,-0.5,10.5);
    nSoftEl     = dir.make<TH1F>("nSoftEl",     (name+"/nSoftEl;    " +title+" Number of Soft El; Entries").c_str(),  11,-0.5,10.5);

    pt_wo_bRegCorr = dir.make<TH1F>("pt_wo_bRegCorr", (name+"/pt_wo_bRegCorr; "+title+" p_T (No bRegCorr) [GeV]; Entries").c_str(),  100,0, 500);
    bRegCorr       = dir.make<TH1F>("bRegCorr", (name+"/bRegCorr; "+title+" bRegCorr; Entries").c_str(),  100,0,2 );
    hadronFlavour     = dir.make<TH1F>("hadronFlavour",     (name+"/hadronFlavour;    " +title+" Hadron Flavour; Entries").c_str(),  31,-5.5,25.5);

    
    if(jetDetailLevel.find("matchedJet") != std::string::npos){
      hMatchedJet = new jetDeltaHists(name+"/matchedJet", fs, title);
    }

    if(jetDetailLevel.find("matchedBJet") != std::string::npos){
      matched_dRAll        = dir.make<TH1F>("matched_dRAll",      (name+"/matched_dRAll      ;#DeltaR Nearest Jet;;Entries"   ).c_str()  ,100, 0,5.);
      matched_dRBjet       = dir.make<TH1F>("matched_dRBjet",     (name+"/matched_dRBjet     ;#DeltaR Nearest B-jet Jet;;Entries"   ).c_str()  ,100, 0,5.);
    }

    if(jetDetailLevel.find("Tracks") != std::string::npos){
      nTrksExpected  = dir.make<TH1F>("nTrksExpected",     (name+"/nTrksExpected;    " +title+" Number of Expected Tracks; Entries").c_str(),  20,-0.5,19.5);
      ntracks     = dir.make<TH1F>("nTracks",     (name+"/nTracks;    " +title+" Number of Tracks; Entries").c_str(),  20,-0.5,19.5);
      nseltracks  = dir.make<TH1F>("nSelTracks",  (name+"/nSelTracks;    " +title+" Number of Selected Tracks; Entries").c_str(),  20,-0.5,19.5);

      tracks      = new trackHists(name+"/tracks",      fs, title);
      
      if(jetDetailLevel.find("noV0")          != std::string::npos) tracks_noV0          = new trackHists(name+"/tracks_noV0", fs, title);
      if(jetDetailLevel.find("innerPixHit")   != std::string::npos) tracks_innerPixHit   = new trackHists(name+"/tracks_innerPixHit", fs, title);
      if(jetDetailLevel.find("noInnerPixHit") != std::string::npos) tracks_noInnerPixHit = new trackHists(name+"/tracks_noInnerPixHit", fs, title);
    }

    if(jetDetailLevel.find("btagInputs") != std::string::npos){
      flavour          = dir.make<TH1F>("flavour",     (name+"/flavour;    " +title+" Flavour; Entries").c_str(),  31,-5.5,25.5);
      flavourCleaned     = dir.make<TH1F>("flavourCleaned",     (name+"/flavourCleaned;    " +title+" Flavour (cleaned); Entries").c_str(),  31,-5.5,25.5);
      partonFlavour     = dir.make<TH1F>("partonFlavour",     (name+"/partonFlavour;    " +title+" Parton Flavour; Entries").c_str(),  31,-5.5,25.5);
      nbHadrons     = dir.make<TH1F>("nbHadrons",     (name+"/nbHadrons;    " +title+" Number of B Hadrons; Entries").c_str(),  5,-0.5,4.5);
      ncHadrons     = dir.make<TH1F>("ncHadrons",     (name+"/ncHadrons;    " +title+" Number of C Hadrons; Entries").c_str(),  5,-0.5,4.5);

      SF      = dir.make<TH1F>("SF",     (name+"/SF;SF;Entries").c_str(),50,-0.1,2);

      btags      = new btaggingHists(name+"/btags",      fs, title);
      if(jetDetailLevel.find("noV0") != std::string::npos) btags_noV0 = new btaggingHists(name+"/btags_noV0", fs, title);

      if(jetDetailLevel.find("Tracks") != std::string::npos){
	Delta_nTracks_tracks_btag                    = dir.make<TH1F>("Del_nTracks",     ("#Delta NTracks (trks-btag);    " +title+" Number of Tracks; Entries").c_str(),  21,-10.5,10.5);
	if(jetDetailLevel.find("noV0") != std::string::npos) Delta_nTracks_tracks_btag_noV0               = dir.make<TH1F>("Del_nTracks_noV0",("#Delta NTracks (trks-btag);    " +title+" Number of Tracks; Entries").c_str(),  21,-10.5,10.5);
	Delta_nTracks_tracks_btag_l                  = dir.make<TH1F>("Del_nTracks_l",     ("#Delta NTracks (trks-btag);    " +title+" Number of Tracks; Entries").c_str(),  101,-50.5,50.5);
	if(jetDetailLevel.find("noV0") != std::string::npos) Delta_nTracks_tracks_btag_noV0_l             = dir.make<TH1F>("Del_nTracks_noV0_l",("#Delta NTracks (trks-btag);    " +title+" Number of Tracks; Entries").c_str(),  101,-50.5,50.5);
      }

    }

    if(jetDetailLevel.find("reCalcDeepCSV") != std::string::npos){
      deepCSV_reCalc   = dir.make<TH1F>("DeepCSV_reCalc",   (name+"/DeepCSV_reCalc; "   +title+" DeepCSV; Entries").c_str(), 120,-0.2,1.2);
      delta_deepCSV    = dir.make<TH1F>("delta_DeepCSV",   (name+"/delta_DeepCSV; "   +title+" #Detla DeepCSV (nom-recalc); Entries").c_str(), 100,-1.2,1.2);
    }

    if(jetDetailLevel.find("allTaggers") != std::string::npos){
      Ip2N      = dir.make<TH1F>("Ip2N"         ,  (name+"/Ip2N;     "+title+ " Ip2N     ;Entries").c_str(), 100, -10.2, 10.2);
      Ip2P      = dir.make<TH1F>("Ip2P"         ,  (name+"/Ip2P;     "+title+ " Ip2P     ;Entries").c_str(), 100, -10.2, 10.2);
      Ip3N      = dir.make<TH1F>("Ip3N"         ,  (name+"/Ip3N;     "+title+ " Ip3N     ;Entries").c_str(), 100, -10.2, 10.2);
      Ip3P      = dir.make<TH1F>("Ip3P"         ,  (name+"/Ip3P;     "+title+ " Ip3P     ;Entries").c_str(), 100, -10.2, 10.2);

      Ip2N_l      = dir.make<TH1F>("Ip2N_l"     ,  (name+"/Ip2N_l;     "+title+ " Ip2N     ;Entries").c_str(), 100, -80.2, 40.2);
      Ip2P_l      = dir.make<TH1F>("Ip2P_l"     ,  (name+"/Ip2P_l;     "+title+ " Ip2P     ;Entries").c_str(), 100, -40.2, 80.2);
      Ip3N_l      = dir.make<TH1F>("Ip3N_l"     ,  (name+"/Ip3N_l;     "+title+ " Ip3N     ;Entries").c_str(), 100, -80.2, 40.2);
      Ip3P_l      = dir.make<TH1F>("Ip3P_l"     ,  (name+"/Ip3P_l;     "+title+ " Ip3P     ;Entries").c_str(), 100, -40.2, 80.2);

      ProbaN    = dir.make<TH1F>("ProbaN"       ,  (name+"/ProbaN;   "+title+ " ProbaN   ;Entries").c_str(), 100, -0.2, 4.2);
      Proba     = dir.make<TH1F>("Proba"        ,  (name+"/Proba;    "+title+ " Proba    ;Entries").c_str(), 100, -0.2, 4.2);
      BprobN    = dir.make<TH1F>("BprobN"       ,  (name+"/BprobN;   "+title+ " BprobN   ;Entries").c_str(), 100, -0.2, 12.2);
      Bprob     = dir.make<TH1F>("Bprob"        ,  (name+"/Bprob;    "+title+ " Bprob    ;Entries").c_str(), 100, -0.2, 12.2);
      Svx       = dir.make<TH1F>("Svx"          ,  (name+"/Svx;      "+title+ " Svx      ;Entries").c_str(), 100,  1.0, 7.2);
      SvxHP     = dir.make<TH1F>("SvxHP"        ,  (name+"/SvxHP;    "+title+ " SvxHP    ;Entries").c_str(), 100,  1.0, 7.2);
      CombIVF   = dir.make<TH1F>("CombIVF"      ,  (name+"/CombIVF;  "+title+ " CombIVF  ;Entries").c_str(), 100, -0.2, 1.2);
      CombIVF_N = dir.make<TH1F>("CombIVF_N"    ,  (name+"/CombIVF_N;"+title+ " CombIVF_N;Entries").c_str(), 100, -0.2, 1.2);
      SoftMuN   = dir.make<TH1F>("SoftMuN"      ,  (name+"/SoftMuN;  "+title+ " SoftMuN  ;Entries").c_str(), 100, -0.2, 1.2);
      SoftMu    = dir.make<TH1F>("SoftMu"       ,  (name+"/SoftMu;   "+title+ " SoftMu   ;Entries").c_str(), 100, -0.2, 1.2);
      SoftElN   = dir.make<TH1F>("SoftElN"      ,  (name+"/SoftElN;  "+title+ " SoftElN  ;Entries").c_str(), 100, -0.2, 1.2);
      SoftEl    = dir.make<TH1F>("SoftEl"       ,  (name+"/SoftEl;   "+title+ " SoftEl   ;Entries").c_str(), 100, -0.2, 1.2);
      cMVAv2    = dir.make<TH1F>("cMVAv2"       ,  (name+"/cMVAv2;   "+title+ " cMVAv2   ;Entries").c_str(), 100, -1.2, 1.2);
      cMVAv2N   = dir.make<TH1F>("cMVAv2N"      ,  (name+"/cMVAv2N;  "+title+ " cMVAv2N  ;Entries").c_str(), 100, -1.2, 1.2);
    } 

    if(jetDetailLevel.find("DeepJetBins") != std::string::npos){
      for(float ptBin : deepFlavB_ptBins){
	
	std::stringstream ss; 
	ss << ptBin;
	std::string ptStr = ss.str();

	deepFlavB_ptHists.push_back( dir.make<TH1F>(("deepFlavB_pt"+ptStr).c_str(), (name+"/deepFlavB_pt"+ptStr+"; "+title+" Deep (Jet) Flavour B ptBin "+ptStr+"; Entries").c_str(), 120,-0.2,1.2));
	Proba_ptHists    .push_back( dir.make<TH1F>(("Proba_pt"+ptStr)    .c_str(), (name+"/Proba_pt"+ptStr+";     "+title+ " Proba ptBin "+ptStr+"    ;Entries").c_str(), 100, -0.2, 4.2));
      }


      for(float etaBin : deepFlavB_etaBins){
	
	std::stringstream ss; 
	ss << etaBin;
	std::string etaStr = ss.str();

	deepFlavB_etaHists.push_back( dir.make<TH1F>(("deepFlavB_eta"+etaStr).c_str(), (name+"/deepFlavB_eta"+etaStr+"; "+title+" Deep (Jet) Flavour B etaBin "+etaStr+"; Entries").c_str(), 120,-0.2,1.2));	
	Proba_etaHists    .push_back( dir.make<TH1F>(("Proba_eta"+etaStr)    .c_str(), (name+"/Proba_eta"+etaStr+";     "+title+ " Proba etaBin "+etaStr+"    ;Entries").c_str(), 100, -0.2, 4.2));
      }


    }

}


void jetHists::Fill(const std::shared_ptr<jet> &jet, float weight){
  if(debug) std::cout << "jetHists::Fill " << name << " " << title << std::endl;
  v->Fill(jet->p, weight);

  cleanmask->Fill(jet->cleanmask, weight);
  if(jet->pt < 50){
    puId->Fill(jet->puId, weight);
  }else{
    puId->Fill(7, weight);
  }


  jetId->Fill(jet->jetId, weight);

  deepB    ->Fill(jet->deepB, weight);
  CSVv2    ->Fill(jet->CSVv2, weight);
  CSVv2_l  ->Fill(jet->CSVv2, weight);
  deepFlavB->Fill(jet->deepFlavB, weight);


  deepCSV_l  ->Fill(jet->DeepCSV    ,weight);
  deepCSVb_l  ->Fill(jet->DeepCSVb    ,weight);
  deepCSVbb_l  ->Fill(jet->DeepCSVbb    ,weight);

  nSoftMu    ->Fill(jet->nSM        ,weight);
  nSoftEl    ->Fill(jet->nSE        ,weight);

  pt_wo_bRegCorr ->Fill(jet->pt_wo_bRegCorr, weight);
  bRegCorr ->Fill(jet->bRegCorr, weight);

  hadronFlavour    ->Fill(jet->hadronFlavour,   weight);


  unsigned int nTrks_noV0 = 0;


  //
  // track hists
  //
  if(tracks){
    ntracks    ->Fill(jet->ntracks    ,weight);
    nseltracks ->Fill(jet->nseltracks ,weight);
    nTrksExpected->Fill(jet->nLastTrack-jet->nFirstTrack,weight);
    tracks->nTracks->Fill(jet->tracks.size(), weight);
    for(const trackPtr& track: jet->tracks){ 
      if(tracks_innerPixHit || tracks_noInnerPixHit){
	if(track->isHitL1){
	  if(tracks_innerPixHit) tracks_innerPixHit->Fill(track, weight);
	}else{
	  if(tracks_noInnerPixHit) tracks_noInnerPixHit->Fill(track, weight);
	}
      }
      tracks->Fill(track, weight);
    }

    //
    // No V0s
    //
    for(const trackPtr& track: jet->tracks) {
      if(!track->isfromV0){
	++nTrks_noV0;
	if(tracks_noV0) tracks_noV0->Fill(track, weight);
      }
    }
    if(tracks_noV0) tracks_noV0->nTracks->Fill(nTrks_noV0, weight);  
  }

  //
  // btagging
  //
  if(btags){
    flavour    ->Fill(jet->flavour,   weight);
    flavourCleaned    ->Fill(jet->flavourCleaned,   weight);
    partonFlavour    ->Fill(jet->partonFlavour,   weight);
    nbHadrons        ->Fill(jet->nbHadrons,   weight);
    ncHadrons        ->Fill(jet->ncHadrons,   weight);

    SF               ->Fill(jet->SF      , weight);

    btags->sv_nSVs->Fill(jet->svs.size(), weight);
    for(const svPtr& sv: jet->svs) 
      btags->FillSVHists(sv, jet, weight);

    btags->trkTag_nTracks->Fill(jet->trkTagVars.size(), weight);
    for(const trkTagVarPtr& trkTag: jet->trkTagVars) {
      //float delta_trackDelta = trkTag->trackDeltaR - jet->p.DeltaR(trkTag->p);
      //if(fabs(delta_trackDelta) < 0.01){
      btags->FillTrkTagVarHists(trkTag, weight);
      //}else{
      //	std::cout << "DeltaR comb " << trkTag->trackDeltaR << " vs " << jet->p.DeltaR(trkTag->p) << " eta: " << trkTag->trackEta << " phi: " << trkTag->trackPhi << std::endl; // hltTrack is not in cone of offJet
      //}
    }

    if(jet->tagVars)
      btags->FillTagVarHists(jet->tagVars, jet, weight);

    //
    // No V0s
    //
    unsigned int nTrkTags_noV0 = 0;
    for(const trkTagVarPtr& trkTag: jet->trkTagVars) {
      if(!trkTag->matchIsFromV0){
	if(btags_noV0) btags_noV0->FillTrkTagVarHists(trkTag, weight);
	++nTrkTags_noV0;
      }
    }
    if(btags_noV0) btags_noV0->trkTag_nTracks->Fill(nTrkTags_noV0, weight);

    if(tracks){
      Delta_nTracks_tracks_btag         ->Fill( jet->tracks.size() - jet->trkTagVars.size()  ,weight);
      if(Delta_nTracks_tracks_btag_noV0) Delta_nTracks_tracks_btag_noV0    ->Fill( nTrks_noV0 - nTrkTags_noV0  ,weight);

      Delta_nTracks_tracks_btag_l       ->Fill( jet->tracks.size() - jet->trkTagVars.size()  ,weight);
      if(Delta_nTracks_tracks_btag_noV0_l) Delta_nTracks_tracks_btag_noV0_l  ->Fill( nTrks_noV0 - nTrkTags_noV0  ,weight);
    }

  }
  
  if(hMatchedJet){
    const std::shared_ptr<nTupleAnalysis::jet> matchedJet = jet->matchedJet.lock();
    if(matchedJet){
      hMatchedJet -> Fill(jet, matchedJet, weight);
    }
  }

  if(matched_dRAll){
    matched_dRAll       ->Fill(jet->match_dR     ,weight);
    matched_dRBjet      ->Fill(jet->match_dR_bjet,weight);
  }


  if(deepCSV_reCalc){
    deepCSV_reCalc   ->Fill(jet->DeepCSV_reCalc, weight);
    delta_deepCSV    ->Fill(jet->DeepCSV - jet->DeepCSV_reCalc, weight);
  }
  
  if(Ip2N){
    Ip2N      ->Fill(jet-> Ip2N      , weight);
    Ip2P      ->Fill(jet-> Ip2P      , weight);
    Ip2N_l    ->Fill(jet-> Ip2N      , weight);
    Ip2P_l    ->Fill(jet-> Ip2P      , weight);

    Ip3N      ->Fill(jet-> Ip3N      , weight);
    Ip3P      ->Fill(jet-> Ip3P      , weight);
    Ip3N_l    ->Fill(jet-> Ip3N      , weight);
    Ip3P_l    ->Fill(jet-> Ip3P      , weight);

    ProbaN    ->Fill(jet-> ProbaN    , weight);
    Proba     ->Fill(jet-> Proba     , weight);

    BprobN    ->Fill(jet-> BprobN    , weight);
    Bprob     ->Fill(jet-> Bprob     , weight);

    Svx       ->Fill(jet-> Svx       , weight);
    SvxHP     ->Fill(jet-> SvxHP     , weight);

    CombIVF   ->Fill(jet-> CombIVF   , weight);
    CombIVF_N ->Fill(jet-> CombIVF_N , weight);

    SoftMuN   ->Fill(jet-> SoftMuN   , weight);
    SoftMu    ->Fill(jet-> SoftMu    , weight);

    SoftElN   ->Fill(jet-> SoftElN   , weight);
    SoftEl    ->Fill(jet-> SoftEl    , weight);

    cMVAv2    ->Fill(jet-> cMVAv2    , weight);
    cMVAv2N   ->Fill(jet-> cMVAv2N   , weight);
  }

  if(deepFlavB_ptHists.size()){

    for(unsigned int iPt = 0; iPt < deepFlavB_ptBins.size(); ++iPt){
    
      if(jet->pt < deepFlavB_ptBins.at(iPt)){
	deepFlavB_ptHists.at(iPt)->Fill(jet->deepFlavB,weight);	 
	Proba_ptHists    .at(iPt)->Fill(jet->Proba,    weight);	 
	break;
      }
    }
  }


  if(deepFlavB_etaHists.size()){

    for(unsigned int iEta = 0; iEta < deepFlavB_etaBins.size(); ++iEta){
    
      if(fabs(jet->eta) < deepFlavB_etaBins.at(iEta)){
	deepFlavB_etaHists.at(iEta)->Fill(jet->deepFlavB,weight);	 
	Proba_etaHists    .at(iEta)->Fill(jet->Proba,    weight);	 
	break;
      }
    }
  }



  if(debug) std::cout << "jetHists::Fill " << name << " " << title << " done" << std::endl;
  return;
}

jetHists::~jetHists(){} 
