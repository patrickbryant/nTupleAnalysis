#include <iostream>

#include "nTupleAnalysis/baseClasses/interface/truthData.h"

using namespace nTupleAnalysis;

truthData::truthData(TChain* t, bool d, std::string truthName){
  tree  = t;
  debug = d;

  truthParticles  = new truthParticle(truthName,  tree, true);
} 

void truthData::reset(){
  Zbbs.clear();
  Hbbs.clear();
  HWWs.clear();
  Bbbs.clear();
  Zqqs.clear();
  Wqqs.clear();
  Wlnus.clear();
  Vqqs.clear();
  m4b = -99;
  mbbWW = -99;
}

void truthData::update(){
  if(debug) std::cout<<"Reset truthData"<<std::endl;
  this->reset();



  //Objects
  //std::vector< std::shared_ptr<particle> > bsFromZs = truthParticles->getParticles(5, 23); // all b quarks from Z decays
  std::vector< std::shared_ptr<particle> > bsFromHs   = truthParticles->getParticles(5, 25); // all b quarks from H decays
  std::vector< std::shared_ptr<particle> > qsFromZs   = truthParticles->getParticles(-1, 23, 6); // all quarks from Z decays
  std::vector< std::shared_ptr<particle> > qsFromWs   = truthParticles->getParticles(-1, 24, 6); // all quarks from W decays
  std::vector< std::shared_ptr<particle> > lsFromWs   = truthParticles->getParticles(-1, 24, 16, 11); // all leptons from W decays
  std::vector< std::shared_ptr<particle> > WsFromHs   = truthParticles->getParticles(24, 25); // all W quarks from H decays
  std::vector< std::shared_ptr<particle> >       Zs   = truthParticles->getParticles(23); //all Z bosons
  std::vector< std::shared_ptr<particle> >       Ws   = truthParticles->getParticles(24); //all W bosons
  std::vector< std::shared_ptr<particle> >       Hs   = truthParticles->getParticles(25); //all H bosons
 
  // Get Zs that decayed to bbbar
  for(auto &Z: Zs){
    Z->getDaughters(qsFromZs);
    if(Z->tobbbar){
      Zbbs.push_back(Z);
      Bbbs.push_back(Z);
    }
    
    if(Z->toqqbar){
      Zqqs.push_back(Z);
      Vqqs.push_back(Z);
    }

  }

  // Get Hs that decayed to bbbar
  for(auto &H: Hs){
    H->getDaughters(bsFromHs);
    if(H->tobbbar){
      Hbbs.push_back(H);
      Bbbs.push_back(H);
    }

    H->getDaughters(WsFromHs);
    if(H->toWW){
      HWWs.push_back(H);
    }

  }

  for(auto &W: Ws){
    W->getDaughters(qsFromWs);
    if(W->toqqbar){
      Wqqs.push_back(W);
      Vqqs.push_back(W);
    }

    W->getDaughters(lsFromWs);
    if(W->tolnu){
      Wlnus.push_back(W);
    }


  }


  // Compute four body mass for diboson to bbbb events
  if(Bbbs.size() == 2){ //HH, ZZ or ZH
    m4b = (Bbbs[0]->p + Bbbs[1]->p).M();
  } 

  if(Hbbs.size() == 1 && HWWs.size() == 1){ 
    mbbWW = (Hbbs[0]->p + HWWs[0]->p).M();
  } 


  if(debug) dump();

  if(debug) std::cout<<"truthData updated\n";
  return;
}

void truthData::dump(){
  std::cout << "truthData:\n";
  std::cout << "nZbbs: " << Zbbs.size() << std::endl; 
  for(auto &Z: Zbbs) Z->dump("  ");
  std::cout << "nHbbs: " << Hbbs.size() << std::endl; 
  for(auto &H: Hbbs) H->dump("  ");
  std::cout << "nHWWs: " << HWWs.size() << std::endl; 
  for(auto &H: HWWs) H->dump("  ");

  std::cout << "nZqqs: " << Zqqs.size() << std::endl; 
  for(auto &Z: Zqqs) Z->dump("  ");
  std::cout << "nWqqs: " << Wqqs.size() << std::endl; 
  for(auto &W: Wqqs) W->dump("  ");
  std::cout << "nWlnus: " << Wlnus.size() << std::endl; 
  for(auto &W: Wlnus) W->dump("  ");


  std::cout << "m4b = " << m4b << std::endl;
  std::cout << "mbbWW = " << mbbWW << std::endl;
  return;
}

truthData::~truthData(){} 

