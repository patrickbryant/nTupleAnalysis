#include "nTupleAnalysis/baseClasses/interface/elecHists.h"

using namespace nTupleAnalysis;

elecHists::elecHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);
    v = new fourVectorHists(name, dir);

    dr03EcalRecHitSumEt        =  dir.make<TH1F>("dr03EcalRecHitSumEt"          ,(name+"/dr03EcalRecHitSumEt;       "+title+"    ; Entries").c_str(), 50, 0, 10);  
    dr03HcalDepth1TowerSumEt   =  dir.make<TH1F>("dr03HcalDepth1TowerSumEt"     ,(name+"/dr03HcalDepth1TowerSumEt;  "+title+"    ; Entries").c_str(), 50, 0, 10);
    dr03TkSumPt                =  dir.make<TH1F>("dr03TkSumPt"                  ,(name+"/dr03TkSumPt;               "+title+"    ; Entries").c_str(), 50, 0, 10);
    eCorr                      =  dir.make<TH1F>("eCorr"                        ,(name+"/eCorr;                     "+title+"    ; Entries").c_str(), 50, 0, 10);
    eInvMinusPInv              =  dir.make<TH1F>("eInvMinusPInv"                ,(name+"/eInvMinusPInv;             "+title+"    ; Entries").c_str(), 50, -1, 1);
    hoe                        =  dir.make<TH1F>("hoe"                          ,(name+"/hoe;                       "+title+"    ; Entries").c_str(), 50, 0, 10);
    miniPFRelIso_all           =  dir.make<TH1F>("miniPFRelIso_all"             ,(name+"/miniPFRelIso_all;          "+title+"    ; Entries").c_str(), 50, 0, 10);
    miniPFRelIso_chg           =  dir.make<TH1F>("miniPFRelIso_chg"             ,(name+"/miniPFRelIso_chg;;         "+title+"    ; Entries").c_str(), 50, 0, 10);
    mvaFall17V1Iso             =  dir.make<TH1F>("mvaFall17V1Iso"               ,(name+"/mvaFall17V1Iso;            "+title+"    ; Entries").c_str(), 50, -1.1, 1.1);
    mvaFall17V1noIso           =  dir.make<TH1F>("mvaFall17V1noIso"             ,(name+"/mvaFall17V1noIso;          "+title+"    ; Entries").c_str(), 50, -1.1, 1.1);
    mvaFall17V2Iso             =  dir.make<TH1F>("mvaFall17V2Iso"               ,(name+"/mvaFall17V2Iso;            "+title+"    ; Entries").c_str(), 50, -1.1, 1.1);
    mvaFall17V2noIso           =  dir.make<TH1F>("mvaFall17V2noIso"             ,(name+"/mvaFall17V2noIso;          "+title+"    ; Entries").c_str(), 50, -1.1, 1.1);
    pfRelIso03_all             =  dir.make<TH1F>("pfRelIso03_all"               ,(name+"/pfRelIso03_all;            "+title+"    ; Entries").c_str(), 50, 0, 10);
    pfRelIso03_chg             =  dir.make<TH1F>("pfRelIso03_chg"               ,(name+"/pfRelIso03_chg;            "+title+"    ; Entries").c_str(), 50, 0, 10);
    r9                         =  dir.make<TH1F>("r9"                           ,(name+"/r9;                        "+title+"    ; Entries").c_str(), 50, 0, 5);
    scEtOverPt                 =  dir.make<TH1F>("scEtOverPt"                   ,(name+"/scEtOverPt;                "+title+"    ; Entries").c_str(), 50, -5, 5);
    sieie                      =  dir.make<TH1F>("sieie"                        ,(name+"/sieie;                     "+title+"    ; Entries").c_str(), 50,  0, 0.1);
    cutBased                   =  dir.make<TH1F>("cutBased"                     ,(name+"/cutBased;                  "+title+"    ; Entries").c_str(), 10, -0.5, 9.5);
    cutBased_Fall17_V1         =  dir.make<TH1F>("cutBased_Fall17_V1"           ,(name+"/cutBased_Fall17_V1;        "+title+"    ; Entries").c_str(), 10, -0.5, 9.5);
    pdgId                      =  dir.make<TH1F>("pdgId"                        ,(name+"/pdgId;                     "+title+"    ; Entries").c_str(), 25, -12.5, 12.5);
    convVeto                   =  dir.make<TH1F>("convVeto"                     ,(name+"/convVeto;                  "+title+"    ; Entries").c_str(), 2, -0.5, 1.5);
    mvaFall17V2Iso_WP80        =  dir.make<TH1F>("mvaFall17V2Iso_WP80"          ,(name+"/mvaFall17V2Iso_WP80;       "+title+"    ; Entries").c_str(), 2, -0.5, 1.5);
    mvaFall17V2Iso_WP90        =  dir.make<TH1F>("mvaFall17V2Iso_WP90"          ,(name+"/mvaFall17V2Iso_WP90;       "+title+"    ; Entries").c_str(), 2, -0.5, 1.5);
    mvaFall17V2Iso_WPL         =  dir.make<TH1F>("mvaFall17V2Iso_WPL"           ,(name+"/mvaFall17V2Iso_WPL;        "+title+"    ; Entries").c_str(), 2, -0.5, 1.5);
    genPartFlav                =  dir.make<TH1F>("genPartFlav"                  ,(name+"/genPartFlav;               "+title+"    ; Entries").c_str(), 25, -0.5, 24.5);

    nElecs    = dir.make<TH1F>("nElecs",    (name+"/nElecs;    "+title+" Number of Electrons; Entries").c_str(),  6,-0.5,5.5);
    
    SF      = dir.make<TH1F>("SF",     (name+"/SF;SF;Entries").c_str(),50,-0.1,2);
} 

void elecHists::Fill(const elecPtr& elec, float weight){

  v->Fill(elec->p, weight);

  dr03EcalRecHitSumEt            ->Fill(elec->dr03EcalRecHitSumEt        , weight);
  dr03HcalDepth1TowerSumEt       ->Fill(elec->dr03HcalDepth1TowerSumEt   , weight);
  dr03TkSumPt                    ->Fill(elec->dr03TkSumPt                , weight);
  eCorr                          ->Fill(elec->eCorr                      , weight);
  eInvMinusPInv                  ->Fill(elec->eInvMinusPInv              , weight);
  hoe                            ->Fill(elec->hoe                        , weight);
  miniPFRelIso_all               ->Fill(elec->miniPFRelIso_all           , weight);
  miniPFRelIso_chg               ->Fill(elec->miniPFRelIso_chg           , weight);
  mvaFall17V1Iso                 ->Fill(elec->mvaFall17V1Iso             , weight);
  mvaFall17V1noIso               ->Fill(elec->mvaFall17V1noIso           , weight);
  mvaFall17V2Iso                 ->Fill(elec->mvaFall17V2Iso             , weight);
  mvaFall17V2noIso               ->Fill(elec->mvaFall17V2noIso           , weight);
  pfRelIso03_all                 ->Fill(elec->pfRelIso03_all             , weight);
  pfRelIso03_chg                 ->Fill(elec->pfRelIso03_chg             , weight);
  r9                             ->Fill(elec->r9                         , weight);
  scEtOverPt                     ->Fill(elec->scEtOverPt                 , weight);
  sieie                          ->Fill(elec->sieie                      , weight);
  cutBased                       ->Fill(elec->cutBased                   , weight);
  cutBased_Fall17_V1             ->Fill(elec->cutBased_Fall17_V1         , weight);
  pdgId                          ->Fill(elec->pdgId                      , weight);
  convVeto                       ->Fill(elec->convVeto                   , weight);
  mvaFall17V2Iso_WP80            ->Fill(elec->mvaFall17V2Iso_WP80        , weight);
  mvaFall17V2Iso_WP90            ->Fill(elec->mvaFall17V2Iso_WP90        , weight);
  mvaFall17V2Iso_WPL             ->Fill(elec->mvaFall17V2Iso_WPL         , weight);
  genPartFlav                    ->Fill(elec->genPartFlav                , weight);

  SF               ->Fill(elec->SF      , weight);
  return;
}

elecHists::~elecHists(){} 
