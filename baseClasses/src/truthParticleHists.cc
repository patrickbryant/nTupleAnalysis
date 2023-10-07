#include "nTupleAnalysis/baseClasses/interface/truthParticleHists.h"

using namespace nTupleAnalysis;

truthParticleHists::truthParticleHists(std::string name, fwlite::TFileService& fs, std::string title) {
  TFileDirectory dir = fs.mkdir(name);
  this->makeHists(name, dir, title);
}


truthParticleHists::truthParticleHists(std::string name, TFileDirectory& dir, std::string title) {
  this->makeHists(name, dir, title);
}


void truthParticleHists::makeHists(std::string name, TFileDirectory& dir, std::string title) {

  v = new fourVectorHists(name, dir, title);
    //v->pt_s->SetBins(100, 0, 20);
    //v->pt_m->SetBins(100, 0, 40);
    //v->pt_l->SetBins(100, 0, 100);



  pdgId             = dir.make<TH1F>("pdgId",   (name+"/pdgId;   "+title+" pdgID;   Entries").c_str(), 51,-25.5,25.5);
  hadronFlavour     = dir.make<TH1F>("hadronFlavour",     (name+"/hadronFlavour;    " +title+" Hadron Flavour; Entries").c_str(),  31,-5.5,25.5);
  partonFlavour     = dir.make<TH1F>("partonFlavour",     (name+"/partonFlavour;    " +title+" Parton Flavour; Entries").c_str(),  31,-5.5,25.5);


} 



void truthParticleHists::Fill(const particlePtr &truthP, float weight){

  v->Fill(truthP->p, weight);

  pdgId  ->Fill(truthP->pdgId,   weight);
  hadronFlavour  ->Fill(truthP->hadronFlavour,   weight);
  partonFlavour  ->Fill(truthP->partonFlavour,   weight);


  return;
}

truthParticleHists::~truthParticleHists(){} 
