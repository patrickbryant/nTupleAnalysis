#include "nTupleAnalysis/baseClasses/interface/dijetHists.h"

using namespace nTupleAnalysis;

dijetHists::dijetHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);
    v = new fourVectorHists(name, dir, title);
    nDiJets     = dir.make<TH1F>("nDiJets",     (name+"/nDiJets;    " +title+" Number of DiJets; Entries").c_str(),  30,-0.5,29.5);

    dR = dir.make<TH1F>("dR", (name+"/dR; "+title+" #DeltaR(j,j); Entries").c_str(), 50,0,5);
    dPhi = dir.make<TH1F>("dPhi", (name+"/dPhi; "+title+" #DeltaPhi(j,j); Entries").c_str(), 50,-3.2,3.2);
    leadPt_vs_sublPt   = dir.make<TH2F>("leadPt_vs_sublPt",  "leadPt_vs_sublPt;Lead P_{T} [GeV]; Subl P_{T} [GeV]",50,0,150,50,0,150);

    lead = new jetHists(name+"/lead", fs, "Lead Jet");
    subl = new jetHists(name+"/subl", fs, "Subl Jet");

} 

void dijetHists::Fill(std::shared_ptr<dijet> &dijet, float weight){

  v->Fill(dijet->p, weight);

  dR->Fill(dijet->dR, weight);
  dPhi->Fill(dijet->dPhi, weight);

  lead->Fill(dijet->lead, weight);
  subl->Fill(dijet->subl, weight);

  leadPt_vs_sublPt->Fill(dijet->lead->p.Pt(), dijet->subl->p.Pt(),weight);
  return;
}

dijetHists::~dijetHists(){} 
