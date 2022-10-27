#include "nTupleAnalysis/baseClasses/interface/eventHists.h"

using namespace nTupleAnalysis;

eventHists::eventHists(std::string name, fwlite::TFileService& fs) {

    dir = fs.mkdir(name);
    
    PV_ndof       = dir.make<TH1F>("PV_ndof"       ,  (name+"/PV_ndof         ;PV_ndof        ;Entries").c_str(),  50,-0.5, 199.5);
    PV_x          = dir.make<TH1F>("PV_x"          ,  (name+"/PV_x            ;PV_x           ;Entries").c_str(),  50,-1, 1);
    PV_y          = dir.make<TH1F>("PV_y"          ,  (name+"/PV_y            ;PV_y           ;Entries").c_str(),  50,-1, 1);
    PV_z          = dir.make<TH1F>("PV_z"          ,  (name+"/PV_z            ;PV_z           ;Entries").c_str(),  50,-20, 20);
    PV_chi2       = dir.make<TH1F>("PV_chi2"       ,  (name+"/PV_chi2         ;PV_chi2        ;Entries").c_str(),  50,-0.1, 3);
    PV_score      = dir.make<TH1F>("PV_score"      ,  (name+"/PV_score        ;PV_score       ;Entries").c_str(),  50,-0.0, 4000);
    PV_npvs       = dir.make<TH1F>("PV_npvs"       ,  (name+"/PV_npvs         ;PV_npvs        ;Entries").c_str(),  50,-0.5, 99.5);
    PV_npvsGood   = dir.make<TH1F>("PV_npvsGood"   ,  (name+"/PV_npvsGood     ;PV_npvsGood    ;Entries").c_str(),  50,-0.5, 99.5);



} 

void eventHists::Fill(const eventData& event, float weight){


  PV_ndof       -> Fill(event.PV_ndof      , weight);
  PV_x          -> Fill(event.PV_x         , weight);
  PV_y          -> Fill(event.PV_y         , weight);
  PV_z          -> Fill(event.PV_z         , weight);
  PV_chi2       -> Fill(event.PV_chi2      , weight);
  PV_score      -> Fill(event.PV_score     , weight);
  PV_npvs       -> Fill(event.PV_npvs      , weight);
  PV_npvsGood   -> Fill(event.PV_npvsGood  , weight);


  return;
}

eventHists::~eventHists(){} 
