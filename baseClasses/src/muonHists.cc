#include "nTupleAnalysis/baseClasses/interface/muonHists.h"

using namespace nTupleAnalysis;

muonHists::muonHists(std::string name, fwlite::TFileService& fs, std::string title) {
  TFileDirectory dir = fs.mkdir(name);
  this->makeHists(name, dir, title);
}


muonHists::muonHists(std::string name, TFileDirectory& dir, std::string title) {
  this->makeHists(name, dir, title);
}


void muonHists::makeHists(std::string name, TFileDirectory& dir, std::string title) {

    v = new fourVectorHists(name, dir);
    v->pt_s->SetBins(100, 0, 20);
    v->pt_m->SetBins(100, 0, 40);
    v->pt_l->SetBins(100, 0, 100);



    quality   = dir.make<TH1F>("quality",   (name+"/quality;   "+title+" Quality;   Entries").c_str(), 3,-0.5,2.5);
    //isolation = dir.make<TH1F>("isolation", (name+"/isolation; "+title+" Isolation; Entries").c_str(), 50,0,1);
    //isolation_cor = dir.make<TH1F>("iso_cor", (name+"/iso_cor; "+title+" Isolation; Entries").c_str(), 50,0,1);
    //isolation_cor_s = dir.make<TH1F>("iso_cor_s", (name+"/iso_cor_s; "+title+" Isolation; Entries").c_str(), 50,0,0.1);
    dR_match        = dir.make<TH1F>("dR_match",        (name+"/dR_match;        "+title+" Min #DeltaR(muon,jet); Entries").c_str(), 50, 0, 5);
    dR_match_s        = dir.make<TH1F>("dR_match_s",        (name+"/dR_match_s;        "+title+" Min #DeltaR(muon,jet); Entries").c_str(), 50, 0, 1);
    dR_noMatch        = dir.make<TH1F>("dR_noMatch",        (name+"/dR_noMatch;        "+title+" Min #DeltaR(muon,jet); Entries").c_str(), 50, 0, 5);
    nMuons    = dir.make<TH1F>("nMuons",    (name+"/nMuons;    "+title+" Number of Muons; Entries").c_str(),  6,-0.5,5.5);
    SF      = dir.make<TH1F>("SF",     (name+"/SF;SF;Entries").c_str(),50,-0.1,2);



    ip3d              = dir.make<TH1F>("ip3d",            (name+"/ip3d             ; "+title+" ip3d           ; Entries").c_str(), 50,0,2);
    ip3d_l            = dir.make<TH1F>("ip3d_l",          (name+"/ip3d_l           ; "+title+" ip3d           ; Entries").c_str(), 50,0,20);
    sip3d             = dir.make<TH1F>("sip3d",           (name+"/sip3d            ; "+title+" sip3d          ; Entries").c_str(), 50,-0.1,10);
    sip3d_l           = dir.make<TH1F>("sip3d_l",         (name+"/sip3d            ; "+title+" sip3d          ; Entries").c_str(), 50,-0.1,100);
    pfRelIso04_all    = dir.make<TH1F>("pfRelIso04_all",  (name+"/pfRelIso04_all   ; "+title+" pfRelIso04_all ; Entries").c_str(), 50,0,2);
    pfRelIso03_all    = dir.make<TH1F>("pfRelIso03_all",  (name+"/pfRelIso03_all   ; "+title+" pfRelIso03_all ; Entries").c_str(), 50,0,2);
    pfRelIso03_chg    = dir.make<TH1F>("pfRelIso03_chg",  (name+"/pfRelIso03_chg   ; "+title+" pfRelIso03_chg ; Entries").c_str(), 50,0,2);
    tkRelIso          = dir.make<TH1F>("tkRelIso",        (name+"/tkRelIso         ; "+title+" tkRelIso       ; Entries").c_str(), 50,0,2);
    pdgId             = dir.make<TH1F>("pdgId",           (name+"/pdgId            ; "+title+" pdgId          ; Entries").c_str(), 31,-15.5,15.5);
    looseId           = dir.make<TH1F>("looseId",         (name+"/looseId          ; "+title+" looseId        ; Entries").c_str(), 2,-0.5,1.5);
    softId            = dir.make<TH1F>("softId",          (name+"/softId           ; "+title+" softId         ; Entries").c_str(), 2,-0.5,1.5);
    mediumPromptId    = dir.make<TH1F>("mediumPromptId",  (name+"/mediumPromptId   ; "+title+" mediumPromptId ; Entries").c_str(), 2,-0.5,1.5);
    mvaId             = dir.make<TH1F>("mvaId",           (name+"/mvaId            ; "+title+" mvaId          ; Entries").c_str(), 10,-0.5,9.5);
    pfIsoId           = dir.make<TH1F>("pfIsoId",         (name+"/pfIsoId          ; "+title+" pfIsoId        ; Entries").c_str(), 10,-0.5,9.5);
    tkIsoId           = dir.make<TH1F>("tkIsoId",         (name+"/tkIsoId          ; "+title+" tkIsoId        ; Entries").c_str(), 10,-0.5,9.5);
    genPartFlav       = dir.make<TH1F>("genPartFlav",     (name+"/genPartFlav      ; "+title+" genPartFlav    ; Entries").c_str(), 25, -0.5, 24.5);


    dxybs              = dir.make<TH1F>("dxybs"                , (name+"/dxybs              ; "+title+" dxybs              ; Entries").c_str(), 50,0,2);
    dz                 = dir.make<TH1F>("dz"                   , (name+"/dz                 ; "+title+" dz                 ; Entries").c_str(), 50,-20,20);
    dzErr              = dir.make<TH1F>("dzErr"                , (name+"/dzErr              ; "+title+" dzErr              ; Entries").c_str(), 50,0,2);
    miniPFRelIso_all   = dir.make<TH1F>("miniPFRelIso_all"     , (name+"/miniPFRelIso_all   ; "+title+" miniPFRelIso_all   ; Entries").c_str(), 50,0,2);
    miniPFRelIso_chg   = dir.make<TH1F>("miniPFRelIso_chg"     , (name+"/miniPFRelIso_chg   ; "+title+" miniPFRelIso_chg   ; Entries").c_str(), 50,0,2);
    mvaTTH             = dir.make<TH1F>("mvaTTH"               , (name+"/mvaTTH             ; "+title+" mvaTTH             ; Entries").c_str(), 50,-1,1);
    nStations          = dir.make<TH1F>("nStations"            , (name+"/nStations          ; "+title+" nStations          ; Entries").c_str(), 15,-0.5,14.5);
    nTrackerLayers     = dir.make<TH1F>("nTrackerLayers"       , (name+"/nTrackerLayers     ; "+title+" nTrackerLayers     ; Entries").c_str(), 20,-0.5,19.5);
    highPurity         = dir.make<TH1F>("highPurity"           , (name+"/highPurity         ; "+title+" highPurity         ; Entries").c_str(), 2,-0.5,1.5);
    cleanmask          = dir.make<TH1F>("cleanmask"            , (name+"/cleanmask          ; "+title+" cleanmask          ; Entries").c_str(), 10,-0.5,9.5);



    mvaLowPtId       = dir.make<TH1F>("mvaLowPtId"       , (name+"/mvaLowPtId     ; "+title+" mvaLowPtId     ; Entries").c_str(), 50, -2, 20);
    inTimeMuon       = dir.make<TH1F>("inTimeMuon"       , (name+"/inTimeMuon     ; "+title+" inTimeMuon     ; Entries").c_str(), 2, -0.5, 1.5);
    triggerIdLoose   = dir.make<TH1F>("triggerIdLoose"   , (name+"/triggerIdLoose ; "+title+" triggerIdLoose ; Entries").c_str(), 2, -0.5, 1.5);
    jetPtRelv2       = dir.make<TH1F>("jetPtRelv2"       , (name+"/jetPtRelv2     ; "+title+" jetPtRelv2     ; Entries").c_str(), 50, 0, 20);
    fsrPhotonIdx     = dir.make<TH1F>("fsrPhotonIdx"     , (name+"/fsrPhotonIdx   ; "+title+" fsrPhotonIdx   ; Entries").c_str(), 15, -0.5, 14.5);
    isPFcand         = dir.make<TH1F>("isPFcand"         , (name+"/isPFcand       ; "+title+" isPFcand       ; Entries").c_str(), 2, -0.5, 1.5);
    softMva          = dir.make<TH1F>("softMva"          , (name+"/softMva        ; "+title+" softMva        ; Entries").c_str(), 50, -1.1, 1.1);
    isTracker        = dir.make<TH1F>("isTracker"        , (name+"/isTracker      ; "+title+" isTracker      ; Entries").c_str(), 2, -0.5, 1.5);
    mvaLowPt         = dir.make<TH1F>("mvaLowPt"         , (name+"/mvaLowPt       ; "+title+" mvaLowPt       ; Entries").c_str(), 50, -1.1, 1.1);
    puppiIsoId       = dir.make<TH1F>("puppiIsoId"       , (name+"/puppiIsoId     ; "+title+" puppiIsoId     ; Entries").c_str(), 10, -0.5, 9.5);
    segmentComp      = dir.make<TH1F>("segmentComp"      , (name+"/segmentComp    ; "+title+" segmentComp    ; Entries").c_str(), 50, 0, 1.5);
    jetNDauCharged   = dir.make<TH1F>("jetNDauCharged"   , (name+"/jetNDauCharged ; "+title+" jetNDauCharged ; Entries").c_str(), 20, -0.5, 19.5);
    multiIsoId       = dir.make<TH1F>("multiIsoId"       , (name+"/multiIsoId     ; "+title+" multiIsoId     ; Entries").c_str(), 10, -0.5, 9.5);
    isGlobal         = dir.make<TH1F>("isGlobal"         , (name+"/isGlobal       ; "+title+" isGlobal       ; Entries").c_str(), 2, -0.5, 1.5);
    isStandalone     = dir.make<TH1F>("isStandalone"     , (name+"/isStandalone   ; "+title+" isStandalone   ; Entries").c_str(), 2, -0.5, 1.5);
    tunepRelPt       = dir.make<TH1F>("tunepRelPt"       , (name+"/tunepRelPt     ; "+title+" tunepRelPt     ; Entries").c_str(), 50, -1, 2);
    miniIsoId        = dir.make<TH1F>("miniIsoId"        , (name+"/miniIsoId      ; "+title+" miniIsoId      ; Entries").c_str(), 10, -0.5, 9.5);
    charge           = dir.make<TH1F>("charge"           , (name+"/charge         ; "+title+" charge         ; Entries").c_str(), 3, -1.5, 1.5);
    softMvaId        = dir.make<TH1F>("softMvaId"        , (name+"/softMvaId      ; "+title+" softMvaId      ; Entries").c_str(), 2, -0.5, 1.5);
    tightCharge      = dir.make<TH1F>("tightCharge"      , (name+"/tightCharge    ; "+title+" tightCharge    ; Entries").c_str(), 3, -1.5, 1.5);
    jetRelIso        = dir.make<TH1F>("jetRelIso"        , (name+"/jetRelIso      ; "+title+" jetRelIso      ; Entries").c_str(), 50, -1, 20);
    jetIdx           = dir.make<TH1F>("jetIdx"           , (name+"/jetIdx         ; "+title+" jetIdx         ; Entries").c_str(), 20, -1.5, 18.5);



} 



void muonHists::Fill(const muonPtr &muon, float weight){

  v->Fill(muon->p, weight);

  quality  ->Fill(muon->quality,   weight);
  //isolation->Fill(muon->isolation, weight);
  //isolation_cor->Fill(muon->isolation_corrected, weight);
  //isolation_cor_s->Fill(muon->isolation_corrected, weight);
  const nTupleAnalysis::jetPtr matchedJet = muon->matchedJet.lock();
  if(matchedJet){
    dR_match_s       ->Fill(muon->p.DeltaR(matchedJet->p),        weight);
    dR_match       ->Fill(muon->p.DeltaR(matchedJet->p),        weight);
  }else{
    dR_noMatch       ->Fill(muon->dR,        weight);
  }
    

  SF               ->Fill(muon->SF      , weight);

  ip3d                  -> Fill(muon->ip3d            ,weight);
  ip3d_l                -> Fill(muon->ip3d            ,weight);
  sip3d                 -> Fill(muon->sip3d           ,weight);
  sip3d_l               -> Fill(muon->sip3d           ,weight);
  pfRelIso04_all        -> Fill(muon->pfRelIso04_all  ,weight);
  pfRelIso03_all        -> Fill(muon->pfRelIso03_all  ,weight);
  pfRelIso03_chg        -> Fill(muon->pfRelIso03_chg  ,weight);
  tkRelIso              -> Fill(muon->tkRelIso        ,weight);
  pdgId                 -> Fill(muon->pdgId           ,weight);
  looseId               -> Fill(muon->looseId         ,weight);
  softId                -> Fill(muon->softId         ,weight);
  mediumPromptId        -> Fill(muon->mediumPromptId  ,weight);
  mvaId                 -> Fill(muon->mvaId           ,weight);
  pfIsoId               -> Fill(muon->pfIsoId         ,weight);
  tkIsoId               -> Fill(muon->tkIsoId         ,weight);
  genPartFlav           -> Fill(muon->genPartFlav     ,weight);


  dxybs                  -> Fill (muon->dxybs              , weight);
  dz                     -> Fill (muon->dz                 , weight);
  dzErr                  -> Fill (muon->dzErr              , weight);
  miniPFRelIso_all       -> Fill (muon->miniPFRelIso_all   , weight);
  miniPFRelIso_chg       -> Fill (muon->miniPFRelIso_chg   , weight);
  mvaTTH                 -> Fill (muon->mvaTTH             , weight);
  nStations              -> Fill (muon->nStations          , weight);
  nTrackerLayers         -> Fill (muon->nTrackerLayers     , weight);
  highPurity             -> Fill (muon->highPurity         , weight);
  cleanmask              -> Fill (muon->cleanmask          , weight);


  mvaLowPtId             -> Fill (muon->mvaLowPtId      ,weight);
  inTimeMuon             -> Fill (muon->inTimeMuon      ,weight);
  triggerIdLoose         -> Fill (muon->triggerIdLoose  ,weight);
  jetPtRelv2             -> Fill (muon->jetPtRelv2      ,weight);
  fsrPhotonIdx           -> Fill (muon->fsrPhotonIdx    ,weight);
  isPFcand               -> Fill (muon->isPFcand        ,weight);
  softMva                -> Fill (muon->softMva         ,weight);
  isTracker              -> Fill (muon->isTracker       ,weight);
  mvaLowPt               -> Fill (muon->mvaLowPt        ,weight);
  puppiIsoId             -> Fill (muon->puppiIsoId      ,weight);
  segmentComp            -> Fill (muon->segmentComp     ,weight);
  jetNDauCharged         -> Fill (muon->jetNDauCharged  ,weight);
  multiIsoId             -> Fill (muon->multiIsoId      ,weight);
  isGlobal               -> Fill (muon->isGlobal        ,weight);
  isStandalone           -> Fill (muon->isStandalone    ,weight);
  tunepRelPt             -> Fill (muon->tunepRelPt      ,weight);
  miniIsoId              -> Fill (muon->miniIsoId       ,weight);
  charge                 -> Fill (muon->charge          ,weight);
  softMvaId              -> Fill (muon->softMvaId       ,weight);
  tightCharge            -> Fill (muon->tightCharge     ,weight);
  jetRelIso              -> Fill (muon->jetRelIso       ,weight);
  jetIdx                 -> Fill (muon->jetIdx          ,weight);




  return;
}

muonHists::~muonHists(){} 
