#include "nTupleAnalysis/baseClasses/interface/trijet.h"

using namespace nTupleAnalysis;

//trijet object
//trijet::trijet(){}
trijet::trijet(std::shared_ptr<jet> &jet1, std::shared_ptr<jet> &jet2, std::shared_ptr<jet> &jet3, nTupleAnalysis::truthData* truth){

  //// sanity checks
  //float dr12 = jet1->p.DeltaR(jet2->p);
  //float dr13 = jet1->p.DeltaR(jet3->p);
  //float dr23 = jet2->p.DeltaR(jet3->p);
  //assert(dr12 >= 0.1);
  //assert(dr13 >= 0.1);
  //assert(dr23 >= 0.1);


  b = jet1;
  jet_j = jet2;
  jet_l = jet3;
  W = std::make_shared<dijet>(dijet(jet2, jet3, true, truth)); // bool specifiess to use regular JES for the constituent four-vectors
  
  st  = jet1->pt + W->p1.Pt() + W->p2.Pt();
  p   = jet1->p  + W->p1      + W->p2;
  pt  = p.Pt();
  eta = p.Eta();
  phi = p.Phi();
  m   = p.M();
  e   = p.E();

  mbW  = (b->p + W->pW).M();
  //pbW  = (b->p + W->pW)*(mt/mbW); // this would get the wrong W mass. Really want the correction to only be applied to the b-jet

  dRbW = W->p.DeltaR(b->p);

  xt   = (m  -mt)/(0.10*m);
  xbW  = (mbW-mt)/(0.05*mbW);//smaller resolution term because there are fewer degrees of freedom. FWHM=25GeV, about the same as mW 
  xWt  = sqrt(pow(W->xW, 2) + pow(xt, 2));
  xWbW = sqrt(pow(W->xW, 2) + pow(xbW,2));

  rWbW = sqrt(pow((xbW-0.25),2) + pow((W->xW-0.5),2)); // after minimizing, the ttbar distribution is centered around ~(0.5, 0.25) with surfaces of constant density approximiately constant radii

}

trijet::~trijet(){}


