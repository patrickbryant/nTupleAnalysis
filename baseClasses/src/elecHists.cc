#include "nTupleAnalysis/baseClasses/interface/elecHists.h"

using namespace nTupleAnalysis;

elecHists::elecHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);
    v = new fourVectorHists(name, dir);

    //quality   = dir.make<TH1F>("quality",   (name+"/quality;   "+title+" Quality;   Entries").c_str(), 3,-0.5,2.5);
    //isolation = dir.make<TH1F>("isolation", (name+"/isolation; "+title+" Isolation; Entries").c_str(), 50,0,1);
    //isolation_cor = dir.make<TH1F>("iso_cor", (name+"/iso_cor; "+title+" Isolation; Entries").c_str(), 50,0,1);
    //isolation_cor_s = dir.make<TH1F>("iso_cor_s", (name+"/iso_cor_s; "+title+" Isolation; Entries").c_str(), 50,0,0.1);
    //dR        = dir.make<TH1F>("dR",        (name+"/dR;        "+title+" Min #DeltaR(elec,jet); Entries").c_str(), 50, 0, 5);
    nElecs    = dir.make<TH1F>("nElecs",    (name+"/nElecs;    "+title+" Number of Electrons; Entries").c_str(),  6,-0.5,5.5);
    
    SF      = dir.make<TH1F>("SF",     (name+"/SF;SF;Entries").c_str(),50,-0.1,2);
} 

void elecHists::Fill(const elecPtr& elec, float weight){

  v->Fill(elec->p, weight);

  //quality  ->Fill(elec->quality,   weight);
  //isolation->Fill(elec->isolation, weight);
  //isolation_cor->Fill(elec->isolation_corrected, weight);
  //isolation_cor_s->Fill(elec->isolation_corrected, weight);
  //dR       ->Fill(elec->dR,        weight);

  SF               ->Fill(elec->SF      , weight);
  return;
}

elecHists::~elecHists(){} 
