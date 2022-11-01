#include "nTupleAnalysis/baseClasses/interface/elecHists.h"

using namespace nTupleAnalysis;

elecHists::elecHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);
    v = new fourVectorHists(name, dir);

    dr03EcalRecHitSumEt        =  dir.make<TH1F>("dr03EcalRecHitSumEt"          ,(name+"/dr03EcalRecHitSumEt;       "+title+"    ; Entries").c_str(), 50, 0, 10);  
    dr03HcalDepth1TowerSumEt   =  dir.make<TH1F>("dr03HcalDepth1TowerSumEt"     ,(name+"/dr03HcalDepth1TowerSumEt;  "+title+"    ; Entries").c_str(), 50, 0, 10);
    dr03TkSumPt                =  dir.make<TH1F>("dr03TkSumPt"                  ,(name+"/dr03TkSumPt;               "+title+"    ; Entries").c_str(), 50, 0, 10);
    eInvMinusPInv              =  dir.make<TH1F>("eInvMinusPInv"                ,(name+"/eInvMinusPInv;             "+title+"    ; Entries").c_str(), 50, -0.2, 0.2);
    hoe                        =  dir.make<TH1F>("hoe"                          ,(name+"/hoe;                       "+title+"    ; Entries").c_str(), 50, 0, 0.5);
    miniPFRelIso_all           =  dir.make<TH1F>("miniPFRelIso_all"             ,(name+"/miniPFRelIso_all;          "+title+"    ; Entries").c_str(), 50, 0, 2);
    miniPFRelIso_chg           =  dir.make<TH1F>("miniPFRelIso_chg"             ,(name+"/miniPFRelIso_chg;;         "+title+"    ; Entries").c_str(), 50, 0, 2);
    pfRelIso03_all             =  dir.make<TH1F>("pfRelIso03_all"               ,(name+"/pfRelIso03_all;            "+title+"    ; Entries").c_str(), 50, 0, 2);
    pfRelIso03_chg             =  dir.make<TH1F>("pfRelIso03_chg"               ,(name+"/pfRelIso03_chg;            "+title+"    ; Entries").c_str(), 50, 0, 2);
    r9                         =  dir.make<TH1F>("r9"                           ,(name+"/r9;                        "+title+"    ; Entries").c_str(), 50, 0, 2);
    scEtOverPt                 =  dir.make<TH1F>("scEtOverPt"                   ,(name+"/scEtOverPt;                "+title+"    ; Entries").c_str(), 50, -1, 1);
    sieie                      =  dir.make<TH1F>("sieie"                        ,(name+"/sieie;                     "+title+"    ; Entries").c_str(), 50,  0, 0.1);
    cutBased                   =  dir.make<TH1F>("cutBased"                     ,(name+"/cutBased;                  "+title+"    ; Entries").c_str(), 10, -0.5, 9.5);
    pdgId                      =  dir.make<TH1F>("pdgId"                        ,(name+"/pdgId;                     "+title+"    ; Entries").c_str(), 25, -12.5, 12.5);
    convVeto                   =  dir.make<TH1F>("convVeto"                     ,(name+"/convVeto;                  "+title+"    ; Entries").c_str(), 2, -0.5, 1.5);
    genPartFlav                =  dir.make<TH1F>("genPartFlav"                  ,(name+"/genPartFlav;               "+title+"    ; Entries").c_str(), 25, -0.5, 24.5);

    deltaEtaSC             = dir.make<TH1F>("deltaEtaSC"         ,(name+"/deltaEtaSC    "+title+"    ; Entries").c_str(), 50, -0.2, 0.2);
    dxy           	   = dir.make<TH1F>("dxy"                ,(name+"/dxy           "+title+"    ; Entries").c_str(), 50, -1, 1);
    dxyErr        	   = dir.make<TH1F>("dxyErr"             ,(name+"/dxyErr        "+title+"    ; Entries").c_str(), 50, 0, 1);
    dz            	   = dir.make<TH1F>("dz"                 ,(name+"/dz            "+title+"    ; Entries").c_str(), 50, -10, 10);
    dzErr         	   = dir.make<TH1F>("dzErr"              ,(name+"/dzErr         "+title+"    ; Entries").c_str(), 50, 0, 1);
    energyErr     	   = dir.make<TH1F>("energyErr"          ,(name+"/energyErr     "+title+"    ; Entries").c_str(), 50, 0, 50);
    ip3d          	   = dir.make<TH1F>("ip3d"               ,(name+"/ip3d          "+title+"    ; Entries").c_str(), 50, -0, 1);
    jetPtRelv2    	   = dir.make<TH1F>("jetPtRelv2"         ,(name+"/jetPtRelv2    "+title+"    ; Entries").c_str(), 50, 0, 100);
    jetRelIso     	   = dir.make<TH1F>("jetRelIso"          ,(name+"/jetRelIso     "+title+"    ; Entries").c_str(), 50, 0, 10);
    mvaHZZIso     	   = dir.make<TH1F>("mvaHZZIso"          ,(name+"/mvaHZZIso     "+title+"    ; Entries").c_str(), 50, -1, 1);
    mvaIso        	   = dir.make<TH1F>("mvaIso"             ,(name+"/mvaIso        "+title+"    ; Entries").c_str(), 50, -1, 1);
    mvaNoIso      	   = dir.make<TH1F>("mvaNoIso"           ,(name+"/mvaNoIso      "+title+"    ; Entries").c_str(), 50, -1, 1);
    sip3d         	   = dir.make<TH1F>("sip3d"              ,(name+"/sip3d         "+title+"    ; Entries").c_str(), 50,  0, 20);
    mvaTTH        	   = dir.make<TH1F>("mvaTTH"             ,(name+"/mvaTTH        "+title+"    ; Entries").c_str(), 50, -1, 1);
    mvaIso_WP80   	   = dir.make<TH1F>("mvaIso_WP80"        ,(name+"/mvaIso_WP80   "+title+"    ; Entries").c_str(), 2, -0.5, 1.5);
    mvaIso_WP90   	   = dir.make<TH1F>("mvaIso_WP90"        ,(name+"/mvaIso_WP90   "+title+"    ; Entries").c_str(), 2, -0.5, 1.5);
    mvaIso_WPL    	   = dir.make<TH1F>("mvaIso_WPL"         ,(name+"/mvaIso_WPL    "+title+"    ; Entries").c_str(), 2, -0.5, 1.5);
    mvaNoIso_WP80 	   = dir.make<TH1F>("mvaNoIso_WP80"      ,(name+"/mvaNoIso_WP80 "+title+"    ; Entries").c_str(), 2, -0.5, 1.5);
    mvaNoIso_WP90 	   = dir.make<TH1F>("mvaNoIso_WP90"      ,(name+"/mvaNoIso_WP90 "+title+"    ; Entries").c_str(), 2, -0.5, 1.5);
    mvaNoIso_WPL  	   = dir.make<TH1F>("mvaNoIso_WPL"       ,(name+"/mvaNoIso_WPL  "+title+"    ; Entries").c_str(), 2, -0.5, 1.5);
    tightCharge   	   = dir.make<TH1F>("tightCharge"        ,(name+"/tightCharge   "+title+"    ; Entries").c_str(), 3, -1.5, 1.5);
    charge        	   = dir.make<TH1F>("charge"             ,(name+"/charge        "+title+"    ; Entries").c_str(), 3, -1.5, 1.5);
    lostHits      	   = dir.make<TH1F>("lostHits"           ,(name+"/lostHits      "+title+"    ; Entries").c_str(), 10, -0.5, 9.5);

    nElecs    = dir.make<TH1F>("nElecs",    (name+"/nElecs;    "+title+" Number of Electrons; Entries").c_str(),  6,-0.5,5.5);
    
    SF      = dir.make<TH1F>("SF",     (name+"/SF;SF;Entries").c_str(),50,-0.1,2);
} 

void elecHists::Fill(const elecPtr& elec, float weight){

  v->Fill(elec->p, weight);

  dr03EcalRecHitSumEt            ->Fill(elec->dr03EcalRecHitSumEt        , weight);
  dr03HcalDepth1TowerSumEt       ->Fill(elec->dr03HcalDepth1TowerSumEt   , weight);
  dr03TkSumPt                    ->Fill(elec->dr03TkSumPt                , weight);
  eInvMinusPInv                  ->Fill(elec->eInvMinusPInv              , weight);
  hoe                            ->Fill(elec->hoe                        , weight);
  miniPFRelIso_all               ->Fill(elec->miniPFRelIso_all           , weight);
  miniPFRelIso_chg               ->Fill(elec->miniPFRelIso_chg           , weight);
  pfRelIso03_all                 ->Fill(elec->pfRelIso03_all             , weight);
  pfRelIso03_chg                 ->Fill(elec->pfRelIso03_chg             , weight);
  r9                             ->Fill(elec->r9                         , weight);
  scEtOverPt                     ->Fill(elec->scEtOverPt                 , weight);
  sieie                          ->Fill(elec->sieie                      , weight);
  cutBased                       ->Fill(elec->cutBased                   , weight);
  pdgId                          ->Fill(elec->pdgId                      , weight);
  convVeto                       ->Fill(elec->convVeto                   , weight);
  genPartFlav                    ->Fill(elec->genPartFlav                , weight);

  deltaEtaSC    ->Fill(elec->deltaEtaSC    ,weight);
  dxy           ->Fill(elec->dxy           ,weight);
  dxyErr        ->Fill(elec->dxyErr        ,weight);
  dz            ->Fill(elec->dz            ,weight);
  dzErr         ->Fill(elec->dzErr         ,weight);
  energyErr     ->Fill(elec->energyErr     ,weight);
  ip3d          ->Fill(elec->ip3d          ,weight);
  jetPtRelv2    ->Fill(elec->jetPtRelv2    ,weight);
  jetRelIso     ->Fill(elec->jetRelIso     ,weight);
  mvaHZZIso     ->Fill(elec->mvaHZZIso     ,weight);
  mvaIso        ->Fill(elec->mvaIso        ,weight);
  mvaNoIso      ->Fill(elec->mvaNoIso      ,weight);
  sip3d         ->Fill(elec->sip3d         ,weight);
  mvaTTH        ->Fill(elec->mvaTTH        ,weight);
  mvaIso_WP80   ->Fill(elec->mvaIso_WP80   ,weight);
  mvaIso_WP90   ->Fill(elec->mvaIso_WP90   ,weight);
  mvaIso_WPL    ->Fill(elec->mvaIso_WPL    ,weight);
  mvaNoIso_WP80 ->Fill(elec->mvaNoIso_WP80 ,weight);
  mvaNoIso_WP90 ->Fill(elec->mvaNoIso_WP90 ,weight);
  mvaNoIso_WPL  ->Fill(elec->mvaNoIso_WPL  ,weight);
  tightCharge   ->Fill(elec->tightCharge   ,weight);
  charge        ->Fill(elec->charge        ,weight);
  lostHits      ->Fill(elec->lostHits      ,weight);





  SF               ->Fill(elec->SF      , weight);
  return;
}

elecHists::~elecHists(){} 
