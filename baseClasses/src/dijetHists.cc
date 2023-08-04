#include "nTupleAnalysis/baseClasses/interface/dijetHists.h"

using namespace nTupleAnalysis;

dijetHists::dijetHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);
    v = new fourVectorHists(name, dir, title);

    dR = dir.make<TH1F>("dR", (name+"/dR; "+title+" #DeltaR(j,j); Entries").c_str(), 50,0,5);
    dPhi = dir.make<TH1F>("dPhi", (name+"/dPhi; "+title+" #DeltaPhi(j,j); Entries").c_str(), 50,-3.2,3.2);

    lead = new jetHists(name+"/lead", fs, "Lead Jet");
    subl = new jetHists(name+"/subl", fs, "Subl Jet");

} 

void dijetHists::Fill(std::shared_ptr<dijet> &dijet, float weight){

  v->Fill(dijet->p, weight);

  dR->Fill(dijet->dR, weight);
  dPhi->Fill(dijet->dPhi, weight);

  lead->Fill(dijet->lead, weight);
  subl->Fill(dijet->subl, weight);

  return;
}

dijetHists::~dijetHists(){} 
