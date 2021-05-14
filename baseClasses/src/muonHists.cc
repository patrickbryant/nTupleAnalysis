#include "nTupleAnalysis/baseClasses/interface/muonHists.h"

using namespace nTupleAnalysis;

muonHists::muonHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);
    v = new fourVectorHists(name, dir);

    quality   = dir.make<TH1F>("quality",   (name+"/quality;   "+title+" Quality;   Entries").c_str(), 3,-0.5,2.5);
    isolation = dir.make<TH1F>("isolation", (name+"/isolation; "+title+" Isolation; Entries").c_str(), 50,0,1);
    isolation_cor = dir.make<TH1F>("iso_cor", (name+"/iso_cor; "+title+" Isolation; Entries").c_str(), 50,0,1);
    isolation_cor_s = dir.make<TH1F>("iso_cor_s", (name+"/iso_cor_s; "+title+" Isolation; Entries").c_str(), 50,0,0.1);
    dR        = dir.make<TH1F>("dR",        (name+"/dR;        "+title+" Min #DeltaR(muon,jet); Entries").c_str(), 50, 0, 5);
    nMuons    = dir.make<TH1F>("nMuons",    (name+"/nMuons;    "+title+" Number of Muons; Entries").c_str(),  6,-0.5,5.5);
    SF      = dir.make<TH1F>("SF",     (name+"/SF;SF;Entries").c_str(),50,-0.1,2);



    ip3d              = dir.make<TH1F>("ip3d",            (name+"/ip3d             ; "+title+" ip3d           ; Entries").c_str(), 50,0,2);
    ip3d_l            = dir.make<TH1F>("ip3d_l",          (name+"/ip3d_l           ; "+title+" ip3d           ; Entries").c_str(), 50,0,20);
    sip3d             = dir.make<TH1F>("sip3d",           (name+"/sip3d            ; "+title+" sip3d          ; Entries").c_str(), 50,-0.1,10);
    sip3d_l           = dir.make<TH1F>("sip3d_l",         (name+"/sip3d            ; "+title+" sip3d          ; Entries").c_str(), 50,-0.1,100);
    pfRelIso03_all    = dir.make<TH1F>("pfRelIso03_all",  (name+"/pfRelIso03_all   ; "+title+" pfRelIso03_all ; Entries").c_str(), 50,0,10);
    pfRelIso03_chg    = dir.make<TH1F>("pfRelIso03_chg",  (name+"/pfRelIso03_chg   ; "+title+" pfRelIso03_chg ; Entries").c_str(), 50,0,10);
    tkRelIso          = dir.make<TH1F>("tkRelIso",        (name+"/tkRelIso         ; "+title+" tkRelIso       ; Entries").c_str(), 50,0,10);
    pdgId             = dir.make<TH1F>("pdgId",           (name+"/pdgId            ; "+title+" pdgId          ; Entries").c_str(), 31,-15.5,15.5);
    looseId           = dir.make<TH1F>("looseId",         (name+"/looseId          ; "+title+" looseId        ; Entries").c_str(), 2,-0.5,1.5);
    mediumPromptId    = dir.make<TH1F>("mediumPromptId",  (name+"/mediumPromptId   ; "+title+" mediumPromptId ; Entries").c_str(), 2,-0.5,1.5);
    mvaId             = dir.make<TH1F>("mvaId",           (name+"/mvaId            ; "+title+" mvaId          ; Entries").c_str(), 10,-0.5,9.5);
    pfIsoId           = dir.make<TH1F>("pfIsoId",         (name+"/pfIsoId          ; "+title+" pfIsoId        ; Entries").c_str(), 10,-0.5,9.5);
    tkIsoId           = dir.make<TH1F>("tkIsoId",         (name+"/tkIsoId          ; "+title+" tkIsoId        ; Entries").c_str(), 10,-0.5,9.5);
    genPartFlav       = dir.make<TH1F>("genPartFlav",     (name+"/genPartFlav      ; "+title+" genPartFlav    ; Entries").c_str(), 25, -0.5, 24.5);


} 

void muonHists::Fill(const muonPtr &muon, float weight){

  v->Fill(muon->p, weight);

  quality  ->Fill(muon->quality,   weight);
  isolation->Fill(muon->isolation, weight);
  isolation_cor->Fill(muon->isolation_corrected, weight);
  isolation_cor_s->Fill(muon->isolation_corrected, weight);
  dR       ->Fill(muon->dR,        weight);
  SF               ->Fill(muon->SF      , weight);

  ip3d                  -> Fill(muon->ip3d            ,weight);
  ip3d_l                -> Fill(muon->ip3d            ,weight);
  sip3d                 -> Fill(muon->sip3d           ,weight);
  sip3d_l               -> Fill(muon->sip3d           ,weight);
  pfRelIso03_all        -> Fill(muon->pfRelIso03_all  ,weight);
  pfRelIso03_chg        -> Fill(muon->pfRelIso03_chg  ,weight);
  tkRelIso              -> Fill(muon->tkRelIso        ,weight);
  pdgId                 -> Fill(muon->pdgId           ,weight);
  looseId               -> Fill(muon->looseId         ,weight);
  mediumPromptId        -> Fill(muon->mediumPromptId  ,weight);
  mvaId                 -> Fill(muon->mvaId           ,weight);
  pfIsoId               -> Fill(muon->pfIsoId         ,weight);
  tkIsoId               -> Fill(muon->tkIsoId         ,weight);
  genPartFlav           -> Fill(muon->genPartFlav     ,weight);

  return;
}

muonHists::~muonHists(){} 
