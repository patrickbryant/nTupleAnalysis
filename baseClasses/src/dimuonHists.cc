#include "nTupleAnalysis/baseClasses/interface/dimuonHists.h"

using namespace nTupleAnalysis;

dimuonHists::dimuonHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);
    v = new fourVectorHists(name, dir, title);
    v->m_s->SetBins(100, 2.5, 3.5);
    v->m->SetBins(100, 2, 5);
    v->m_l->SetBins(100, 0, 10);

    dR = dir.make<TH1F>("dR", (name+"/dR; "+title+" #DeltaR(j,j); Entries").c_str(), 50,0,5);
    dPhi = dir.make<TH1F>("dPhi", (name+"/dPhi; "+title+" #DeltaPhi(j,j); Entries").c_str(), 50,-3.2,3.2);  
    nDiMuons    = dir.make<TH1F>("nDiMuons",    (name+"/nDiMuons;    "+title+" Number of Di Muons; Entries").c_str(),  15,-0.5,14.5);
    charge    = dir.make<TH1F>("charge",    (name+"/charge;    "+title+" Dimuon Charge; Entries").c_str(),  5,-2.5,2.5);

    lead = new muonHists(name+"/lead", fs, title);
    subl = new muonHists(name+"/subl", fs, title);

} 

void dimuonHists::Fill(std::shared_ptr<dimuon> &dimuon, float weight){

  v->Fill(dimuon->p, weight);

  dR->Fill(dimuon->dR, weight);
  dPhi->Fill(dimuon->dPhi, weight);
  charge->Fill(dimuon->charge, weight);

  lead->Fill(dimuon->lead, weight);
  subl->Fill(dimuon->subl, weight);

  return;
}

dimuonHists::~dimuonHists(){} 
