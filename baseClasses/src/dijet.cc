#include "nTupleAnalysis/baseClasses/interface/dijet.h"

using namespace nTupleAnalysis;

//dijet object
//dijet::dijet(){}
dijet::dijet(std::shared_ptr<jet> &jet1, std::shared_ptr<jet> &jet2, bool undo_bJES, nTupleAnalysis::truthData* truth){

  p1 = jet1->p;
  p2 = jet2->p;
  if(undo_bJES){
    if(jet1->AppliedBRegression()) p1 = p1 * (1.0/jet1->bRegCorr);
    if(jet2->AppliedBRegression()) p2 = p2 * (1.0/jet2->bRegCorr);
  }

  if(jet1->pt > jet2->pt){
    lead = jet1;
    subl = jet2;
  }else{
    lead = jet2;
    subl = jet1;
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

  pW  = p*(mW/m);
  pZ  = p*(mZ/m);
  pH  = p*(mH/m);

  xW  = m>0 ? (m-mW)/(0.10*m) : -1;
  xZ  = m>0 ? (m-mZ)/(0.10*m) : -1;
  xH  = m>0 ? (m-mH)/(0.10*m) : -1;

  if(truth){
    for(auto &B: truth->Bbbs){
      if( (B->daughters[0]->p.DeltaR(p1) < 0.4 && B->daughters[1]->p.DeltaR(p2) < 0.4) || 
	  (B->daughters[0]->p.DeltaR(p2) < 0.4 && B->daughters[1]->p.DeltaR(p1) < 0.4) ){ // dijet dR matched to massive boson decay products
	truthMatch = B;
      }//dR matching
    }//Bbbs

    for(auto &W: truth->Wqqs){
      if( (W->daughters[0]->p.DeltaR(p1) < 0.4 && W->daughters[1]->p.DeltaR(p2) < 0.4) || 
	  (W->daughters[0]->p.DeltaR(p2) < 0.4 && W->daughters[1]->p.DeltaR(p1) < 0.4) ){ // dijet dR matched to massive boson decay products
	truthMatch = W;
      }//dR matching
    }//Bbbs


  }//truth

}

dijet::~dijet(){}


