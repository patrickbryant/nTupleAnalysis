
#include "nTupleAnalysis/baseClasses/interface/trackHists.h"

using namespace nTupleAnalysis;

trackHists::trackHists(std::string name, fwlite::TFileService& fs, std::string title) {
  TFileDirectory dir = fs.mkdir(name);
  this->makeHists(name, dir, title);
}

trackHists::trackHists(std::string name, TFileDirectory& dir, std::string title) {
  this->makeHists(name, dir, title);
}


void trackHists::makeHists(std::string name, TFileDirectory& dir, std::string title) {
  v = new fourVectorHists(name, dir, title);

  ip3d_l = dir.make<TH1F>("ip3d_l","ip3d;IP3D [cm]",100,-0.2,0.2);
  ip3d   = dir.make<TH1F>("ip3d",  "ip3d;IP3D [cm]",100,-0.05,0.05);
  
  ip3d_sig_l = dir.make<TH1F>("ip3d_sig_l","ip3d sig;IP3D significance",100,-100,100);
  ip3d_sig   = dir.make<TH1F>("ip3d_sig",  "ip3d sig;IP3D significance",100,-10,10);
  
  ip3d_err_l = dir.make<TH1F>("ip3d_err_l","ip3d err;IP3D uncertianty [cm]",100,-0.01,0.1);
  ip3d_err   = dir.make<TH1F>("ip3d_err",  "ip3d err;IP3D uncertianty [cm]",100,-0.001,0.01);
  
  ip2d_l = dir.make<TH1F>("ip2d_l","ip2d;IP2D [cm]",100,-0.2,0.2);
  ip2d   = dir.make<TH1F>("ip2d",  "ip2d;IP2D [cm]",100,-0.05,0.05);

            
  Double_t nBinsPt[11] = {0,2,4,6,8,10,15,20,30,40,60};
  ip2d_vs_pt   = dir.make<TH2F>("ip2d_vs_pt",  "ip2d_vs_pt;P_T [GeV]; IP2D [cm]",10,nBinsPt,100,-0.03,0.03);

  Double_t nBinsEta[11] = {0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5};
  ip2d_vs_eta   = dir.make<TH2F>("ip2d_vs_eta",  "ip2d_vs_eta;|#eta|; IP2D [cm]",10,nBinsEta,100,-0.03,0.03);


  ip2d_sig_l = dir.make<TH1F>("ip2d_sig_l","ip2d sig;IP2D significance",100,-100,100);
  ip2d_sig   = dir.make<TH1F>("ip2d_sig",  "ip2d sig;IP2D significance",100,-10,10);
        
  ip2d_err_l = dir.make<TH1F>("ip2d_err_l","ip2d err;IP2D uncertianty [cm]",100,-0.01,0.1);
  ip2d_err   = dir.make<TH1F>("ip2d_err",  "ip2d err;IP2D uncertianty [cm]",100,-0.001,0.01);
    
  trackDecayLenVal_l         = dir.make<TH1F>("DecayLenVal_l"  ,    "trackDecayLenVal;trackDecayLenVal [cm];Entries", 100, -0.1,  6);
  trackDecayLenVal           = dir.make<TH1F>("DecayLenVal"    ,    "trackDecayLenVal;trackDecayLenVal [cm];Entries", 100, -0.1,  0.5);
  trackJetDistVal            = dir.make<TH1F>("JetDistVal"     ,    "trackJetDistVal;trackJetDistVal [cm];Entries",  100, -0.1,0.01);      
  trackPtRel                 = dir.make<TH1F>("PtRel"          ,    "trackPtRel;track p_{T} Rel [GeV];Entries", 100, -0.1, 7);          
  trackMomentum              = dir.make<TH1F>("Momentum"       ,    "trackMomentum;track momentum [GeV];Entries", 60, 0, 60);       
  trackPt                    = dir.make<TH1F>("trackPt"             ,    "trackPt;track pt [GeV];Entries", 100, 0, 20);       
  trackPt_l                  = dir.make<TH1F>("trackPt_l"           ,    "trackPt;track pt [GeV];Entries", 100, 0, 200);       

  Double_t binsPt[28] = {0.9, 1.116, 1.3838, 1.716, 2.1278, 2.6385, 3.2717, 4.0569, 5.0306, 6.2379, 7.735, 9.5914, 11.8933, 14.7477, 18.2872, 22.6761, 28.1183, 34.8667, 43.2347, 53.6111, 66.4777, 82.4324, 102.2162, 126.748, 157.1676, 194.8878, 241.6609, 299.6595};
  trackPt_logx               = dir.make<TH1F>("Pt_logx", "trackPt;track p_{T} [GeV];Entries", 27, binsPt);
  
  trackEta                   = dir.make<TH1F>("Eta"            ,    "trackEta;track #eta;Entries", 100, -2.6, 2.6);            
  trackPhi                   = dir.make<TH1F>("Phi"            ,    "trackPhi;track #phi;Entries", 100, -3.2, 3.2);            
  trackPPar                  = dir.make<TH1F>("PPar"           ,    "trackPPar;track PPar [GeV];Entries",60, 0, 60);           
  trackDeltaR                = dir.make<TH1F>("DeltaR"         ,    "trackDeltaR;track #DeltaR;Entries", 160, -0.05, 0.35);         
  trackDeltaR_l              = dir.make<TH1F>("DeltaR_l"         ,    "trackDeltaR;track #DeltaR;Entries", 160, -0.05, 0.6);         
  trackEtaRel                = dir.make<TH1F>("EtaRel"         ,    "trackEtaRel;track Eta Rel;Entries", 100, 0, 7);         
  trackPtRatio               = dir.make<TH1F>("PtRatio"        ,    "trackPtRatio;track p_{T} Ratio;Entries", 100, -0.01, 0.3); 
  trackPParRatio             = dir.make<TH1F>("PParRatio"      ,    "trackPParRatio;track P Par Ratio;Entries", 100, 0.95, 1.02);  
  
  trackChi2                  = dir.make<TH1F>("Chi2"            ,    "trackChi2;track Chi2;Entries", 100, -0.1, 6);            
  trackNTotalHits            = dir.make<TH1F>("NTotalHits"      ,    "trackNTotalHits;trackNTotalHits;Entries", 30, -0.5, 29.5);
  trackNPixelHits            = dir.make<TH1F>("NPixelHits"      ,    "trackNPixelHits;trackNPixelHits;Entries", 10, -0.5,  9.5);  
  trackNStripHits            = dir.make<TH1F>("NStripHits"      ,    "trackNStripHits;trackNStripHits;Entries", 30, -0.5, 39.5);  
  trackHasInnerPixHit        = dir.make<TH1F>("HasInnerPixHit"  ,    "trackHasInnerPixHit;trackHasInnerPixHit;Entries", 2, -0.5,  1.5);  

  trackHasInnerPixHit_vs_eta        = dir.make<TProfile>("HasInnerPixHit_vs_eta"  ,    "trackHasInnerPixHit_vs_eta;Eta;HasInnerPixHit", 50, -2.6, 2.6, 0.0,  1.0);  
  trackHasInnerPixHit_vs_pt         = dir.make<TProfile>("HasInnerPixHit_vs_pt"  ,    "trackHasInnerPixHit_vs_pt;pT;HasInnerPixHit", 50, 0, 20., 0.0,  1.0);  
  trackHasInnerPixHit_vs_phi         = dir.make<TProfile>("HasInnerPixHit_vs_phi"  ,    "trackHasInnerPixHit_vs_phi;Phi;HasInnerPixHit", 100, -3.2, 3.2, 0.0,  1.0);  
  trackHasInnerPixHit_vs_phi_f         = dir.make<TProfile>("HasInnerPixHit_vs_phi_f"  ,    "trackHasInnerPixHit_vs_phi_f;Phi;HasInnerPixHit", 300, -3.2, 3.2, 0.0,  1.0);  
  trackHasInnerPixHit_vs_dR         = dir.make<TProfile>("HasInnerPixHit_vs_dR"  ,    "trackHasInnerPixHit_vs_dR;dR;HasInnerPixHit", 50, 0, 0.5, 0.0,  1.0);  

  for(unsigned int iAlgo = 0; iAlgo < nAlgos; ++iAlgo){
    std::string sAlgo = std::to_string(iAlgo);
    trackEta_forAlgo.push_back(dir.make<TH1F>(("Eta_forAlgo"+sAlgo).c_str(),    ("Eta;track #eta (algo = "+sAlgo+");Entries").c_str(), 100, -2.6, 2.6));              
    trackPhi_forAlgo.push_back(dir.make<TH1F>(("Phi_forAlgo"+sAlgo).c_str(),    ("Phi;track #phi (algo = "+sAlgo+");Entries").c_str(), 100, -3.2, 3.2));              
    trackPt_forAlgo .push_back(dir.make<TH1F>(("Pt_forAlgo"+sAlgo ).c_str(),    ("Pt;track P_{T} (algo = "+sAlgo+");Entries").c_str(), 100, 0, 50));              
  }
  
  nMatches = dir.make<TH1F>("nMatches", "track_nMatches;# of matched tracks;Entries", 6, -0.5, 5.5);
  
  track_matched_dip2d     = dir.make<TH1F>("matched_dip2d"    ,    "track_matched_dip2d;IP2D-IP2D^{matched} [cm];Entries",100,-0.05,0.05);
  track_matched_phi_vs_dip2d = dir.make<TH2F>("matched_phi_vs_dip2d", "track_matched_phi_vs_dip2d;#phi;IP2D-IP2D^{matched} [cm]", 64,-3.2,3.2, 40,-0.02,0.02);
  track_matched_eta_vs_dip2d = dir.make<TH2F>("matched_eta_vs_dip2d", "track_matched_eta_vs_dip2d;#eta;IP2D-IP2D^{matched} [cm]", 52,-2.6,2.6, 40,-0.02,0.02);
  track_matched_dPtRel    = dir.make<TH1F>("matched_dPtRel"   ,    "track_matched_dPtRel;p_{T}^{Rel}-p_{T}^{Rel, matched} [GeV];Entries", 100, -5, 5);
  track_matched_dMomentum = dir.make<TH1F>("matched_dMomentum",    "track_matched_dMomentum;p-p^{matched} [GeV];Entries", 500, -10, 10);
  track_matched_dEta      = dir.make<TH1F>("matched_dEta"     ,    "track_matched_dEta;#eta-#eta^{matched};Entries", 500, -0.1, 0.1);            
  track_matched_dEta_s    = dir.make<TH1F>("matched_dEta_s"   ,    "track_matched_dEta;#eta-#eta^{matched};Entries", 500, -0.01, 0.01);            
  track_matched_dPhi      = dir.make<TH1F>("matched_dPhi"     ,    "track_matched_dPhi;#phi-#phi^{matched};Entries", 500,     0, 0.1);            
  track_matched_dR        = dir.make<TH1F>("matched_dR"       ,    "track_matched_dR;#DeltaR(track, matched track);;Entries", 500, -0.05, 1.2);
  track_matched_dR_s      = dir.make<TH1F>("matched_dR_s"     ,    "track_matched_dR;#DeltaR(track, matched track);;Entries", 340, -0.005, 0.08);
  
  track_matched_dEta_vs_dMomentum = dir.make<TH2F>("matched_dEta_vs_dMomentum", "dEta_vs_dMomentum;#eta-#eta^{matched};p-p^{matched} [GeV]",100,-0.01,0.01,100,-5,5);
  track_matched_dEta_vs_dPhi = dir.make<TH2F>("matched_dEta_vs_dPhi", "dEta_vs_dPhi;#eta-#eta^{matched};|#phi-#phi^{matched}|",120,-0.012,0.012,60,0,0.012);

  track_secondClosest_dEta      = dir.make<TH1F>("secondClosest_dEta",         "track_matched_dEta2;#eta-#eta^{second closest};Entries", 500, -0.1, 0.1);
  track_secondClosest_dEta_s    = dir.make<TH1F>("secondClosest_dEta_s",       "track_matched_dEta2;#eta-#eta^{second closest};Entries", 500, -0.01, 0.01);
  track_secondClosest_dMomentum = dir.make<TH1F>("secondClosest_dMomentum",    "track_secondClosest_dMomentum;p-p^{second closest} [GeV];Entries", 500, -10, 10);
  track_secondClosest_dR        = dir.make<TH1F>("secondClosest_dR"       ,    "track_secondClosest_dR;#DeltaR(matched track, secondClosest track);;Entries", 500, -0.05, 1.2);
  track_secondClosest_dR_s      = dir.make<TH1F>("secondClosest_dR_s"     ,    "track_secondClosest_dR;#DeltaR(matched track, secondClosest track);;Entries", 340, -0.005, 0.08);
  track_secondClosest_dEta_vs_dMomentum = dir.make<TH2F>("secondClosest_dEta_vs_dMomentum", "dEta_vs_dMomentum;#eta-#eta^{secondClosest};p-p^{secondClosest} [GeV]",100,-0.01,0.01,100,-5,5);
  track_dEta12 = dir.make<TH1F>("dEta12", "track_dEta12;#eta^{matched}-#eta^{second closest};Entries", 500, -0.1, 0.1);

  nTracks         = dir.make<TH1F>("nTracks",     ("nTracks;    " +title+" Number of Tracks; Entries").c_str(),  20,-0.5,19.5);
  trackCharge     = dir.make<TH1F>("charge",     ("charge;    " +title+" Charge; Entries").c_str(),  3,-1.5,1.5);
  trackIsFromSV   = dir.make<TH1F>("IsFromSV"  ,  "IsFromSV;Is from SV;Entries", 2, -0.5,  1.5);  
  trackIsFromV0   = dir.make<TH1F>("IsFromV0"  ,  "IsFromV0;Is from V0;Entries", 2, -0.5,  1.5);  
  trackAlgo       = dir.make<TH1F>("algo"  ,  "Algo;Track Algo", 40, -0.5,  39.5);  
  trackOrigAlgo   = dir.make<TH1F>("origAlgo"  ,  "origAlgo;Track Original Algo", 40, -0.5,  39.5);  
  PV              = dir.make<TH1F>("PV"  ,  "PV;PV", 10, -0.5,  9.5);  
  PVweight        = dir.make<TH1F>("PVweight"  ,  "PVweight;PVweight", 40, -0.1,  1.1);  
  SV              = dir.make<TH1F>("SV"  ,  "SV;SV", 10, -0.5,  9.5);  
  SVweight        = dir.make<TH1F>("SVweight"  ,  "SVweight;SVweight", 40, -0.1,  1.1);  

  //
  // Eta/Phi Maps
  //
  nTrackMap       = dir.make<TH2F>("nTrackMap"     , (name+"/nTrackMap; "+title+" Eta; Phi; nTracks").c_str(),  50,-3, 3, 50, -3.3, 3.3);
  pixHitMap       = dir.make<TH2F>("pixHitMap"     , (name+"/pixHitMap; "+title+" Eta; Phi; PixelHits").c_str(),  50,-3, 3, 50, -3.3, 3.3);
  stripHitMap     = dir.make<TH2F>("stripHitMap"   , (name+"/stripHitMap; "+title+" Eta; Phi; Strips").c_str(),  50,-3, 3, 50, -3.3, 3.3);
  totHitMap       = dir.make<TH2F>("totHitMap"     , (name+"/totHitMap; "+title+" Eta; Phi; TotalHitMap").c_str(),  50,-3, 3, 50, -3.3, 3.3);
  innerPixHitMap  = dir.make<TH2F>("innerPixHitMap", (name+"/innerPixHitMap; "+title+" Eta; Phi; hasInnerPix").c_str(),  50,-3, 3, 50, -3.3, 3.3);
  noInnerPixHitMap  = dir.make<TH2F>("noInnerPixHitMap", (name+"/noInnerPixHitMap; "+title+" Eta; Phi; hasInnerPix").c_str(),  100,-3, 3, 100, -3.3, 3.3);


} 

void trackHists::Fill(const std::shared_ptr<track> &track, float weight){

  v->Fill(track->p, weight);

  ip3d  ->Fill(track->IP,weight);
  ip3d_l->Fill(track->IP,weight);
        
  ip3d_sig  ->Fill(track->IPsig,weight);
  ip3d_sig_l->Fill(track->IPsig,weight);
  
  ip3d_err  ->Fill(track->IPerr,weight);
  ip3d_err_l->Fill(track->IPerr,weight);
  
  ip2d  ->Fill(track->IP2D,weight);
  ip2d_l->Fill(track->IP2D,weight);
  
  ip2d_sig  ->Fill(track->IP2Dsig,weight);
  ip2d_sig_l->Fill(track->IP2Dsig,weight);
  
  ip2d_err  ->Fill(track->IP2Derr,weight);
  ip2d_err_l->Fill(track->IP2Derr,weight);

  float pt = track->p.Pt();
  float eta = track->p.Eta();
  float phi  = track->p.Phi();

  ip2d_vs_pt->Fill(     pt, track->IP2D,weight);
  ip2d_vs_eta->Fill(fabs(eta)    , track->IP2D,weight);
        

  trackDecayLenVal_l   ->Fill(track->length,weight);
  trackDecayLenVal     ->Fill(track->length,weight);
  trackJetDistVal      ->Fill(track->dist ,weight);
  trackPtRel           ->Fill(track->ptRel      ,weight);

  trackMomentum        ->Fill(track->p.P()   ,weight); 
  trackPt              ->Fill(pt   ,weight); 
  trackPt_l            ->Fill(pt   ,weight); 
  trackPt_logx         ->Fill(pt         ,weight); 
  trackEta             ->Fill(eta        ,weight);
  trackPhi             ->Fill(phi        ,weight);
  trackPPar            ->Fill(track->pPar       ,weight);
  trackDeltaR          ->Fill(track->dR         ,weight);
  trackDeltaR_l          ->Fill(track->dR         ,weight);
  //trackEtaRel          ->Fill(track->etaRel     ,weight);
  trackPtRatio         ->Fill(track->ptRel/ track->p.P()    ,weight);
  trackPParRatio       ->Fill(track->pPar / track->p.P()  ,weight);

  trackChi2                  ->Fill(track->chi2      ,weight);
  trackNTotalHits            ->Fill(track->nHitAll,weight); 
  trackNPixelHits            ->Fill(track->nHitPixel,weight);
  trackNStripHits            ->Fill(track->nHitStrip,weight);
  trackHasInnerPixHit        ->Fill(track->isHitL1,weight);
  trackHasInnerPixHit_vs_eta ->Fill(eta, track->isHitL1,weight);
  trackHasInnerPixHit_vs_phi ->Fill(phi, track->isHitL1,weight);
  trackHasInnerPixHit_vs_phi_f ->Fill(phi, track->isHitL1,weight);
  trackHasInnerPixHit_vs_pt  ->Fill(pt,  track->isHitL1,weight);
  trackHasInnerPixHit_vs_dR  ->Fill(track->dR, track->isHitL1,weight);

  trackCharge          ->Fill(track->charge        ,weight);
  trackIsFromSV        ->Fill(track->isfromSV,weight);
  trackIsFromV0        ->Fill(track->isfromV0,weight);
  trackAlgo            ->Fill(track->algo,weight);
  trackOrigAlgo        ->Fill(track->originalAlgo,weight);
  PV                   ->Fill(track->PV,weight);
  PVweight             ->Fill(track->PVweight,weight);
  SV                   ->Fill(track->SV,weight);
  SVweight             ->Fill(track->SVweight,weight);



  //
  // Eta/Phi Maps
  //
  nTrackMap       ->Fill(eta, phi,  1.0);
  pixHitMap       ->Fill(eta, phi,  track->nHitPixel);
  stripHitMap     ->Fill(eta, phi,  track->nHitStrip);
  totHitMap       ->Fill(eta, phi,  track->nHitAll);
  innerPixHitMap  ->Fill(eta, phi,  track->isHitL1);
  noInnerPixHitMap->Fill(eta, phi,  !track->isHitL1);




  const nTupleAnalysis::trackPtr trackMatchedTrack = track->matchedTrack.lock();
  if(trackMatchedTrack){
    track_matched_dip2d       ->Fill(            track->IP2D  - trackMatchedTrack->IP2D,weight);
    track_matched_phi_vs_dip2d->Fill(track->phi, track->IP2D  - trackMatchedTrack->IP2D,weight);
    track_matched_eta_vs_dip2d->Fill(track->eta, track->IP2D  - trackMatchedTrack->IP2D,weight);
    //track_matched_dPtRel   ->Fill(track.ptRel    - track.matchedTrack->ptRel);
    
    float dPt = track->pt - trackMatchedTrack->pt; 
    track_matched_dMomentum->Fill(dPt);
    float dEta = track->eta      - trackMatchedTrack->eta;
    track_matched_dEta     ->Fill(dEta, weight);
    track_matched_dEta_s   ->Fill(dEta, weight);
    float dPhi = track->p.DeltaPhi(trackMatchedTrack->p);
    track_matched_dPhi     ->Fill(dPhi,weight);

    //float matched_dEta = (track.eta-track.matchedTrack->eta);
    float dR   = track->p.DeltaR(trackMatchedTrack->p);
    track_matched_dR       ->Fill(dR, weight);
    track_matched_dR_s     ->Fill(dR, weight);
    
    track_matched_dEta_vs_dMomentum->Fill(dEta, dPt,weight);
    track_matched_dEta_vs_dPhi     ->Fill(dEta, dPhi,weight);
  }

  const nTupleAnalysis::trackPtr trackSecondClosest = track->secondClosest.lock();
  if(trackSecondClosest){
    track_secondClosest_dEta     ->Fill(track->eta      - trackSecondClosest->eta,weight);
    track_secondClosest_dEta_s   ->Fill(track->eta      - trackSecondClosest->eta,weight);
    track_secondClosest_dMomentum->Fill(track->pt - trackSecondClosest->pt,weight); 

    float secondClosest_dEta = track->eta-trackSecondClosest->eta;
    //float secondClosest_dPhi = track->p.DeltaPhi(trackSecondClosest->p);
    float secondClosest_dR   = track->p.DeltaR(trackSecondClosest->p);
    track_secondClosest_dR       ->Fill(secondClosest_dR,weight);
    track_secondClosest_dR_s     ->Fill(secondClosest_dR,weight);
    track_secondClosest_dEta_vs_dMomentum->Fill(secondClosest_dEta, track->pt - trackSecondClosest->pt,weight);
    track_dEta12->Fill(trackMatchedTrack->eta - trackSecondClosest->eta,weight);
 }


  for(unsigned int iAlgo = 0; iAlgo < nAlgos; ++iAlgo){
    if(track->algo == int(iAlgo)){
      trackEta_forAlgo.at(iAlgo)->Fill(eta, weight);
      trackPhi_forAlgo.at(iAlgo)->Fill(phi, weight);
      trackPt_forAlgo .at(iAlgo)->Fill(pt, weight);
    }
  }


  return;
}

void 
trackHists::FillMatchStats (const std::shared_ptr<track> &track, float weight){
  nMatches->Fill(track->nMatches, weight);
  return;
}


trackHists::~trackHists(){
} 
