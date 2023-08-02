#include "nTupleAnalysis/baseClasses/interface/dimuon.h"

using namespace nTupleAnalysis;

//dimuon object
//dimuon::dimuon(){}
dimuon::dimuon(std::shared_ptr<muon> &muon1, std::shared_ptr<muon> &muon2){

  p1 = muon1->p;
  p2 = muon2->p;

  if(muon1->pt > muon2->pt){
    lead = muon1;
    subl = muon2;
  }else{
    lead = muon2;
    subl = muon1;
  }

  dR  = p1.DeltaR(p2);
  dPhi= p1.DeltaPhi(p2);
  st  = p1.Pt() + p2.Pt();
  p   = p1 + p2;
  pt  = p.Pt();
  eta = p.Eta();
  phi = p.Phi();
  m   = p.M();
  e   = p.E();

  charge   = muon1->charge + muon2->charge;



}

dimuon::~dimuon(){}


