#include <iostream>

#include "nTupleAnalysis/baseClasses/interface/truthData.h"

using namespace nTupleAnalysis;

truthData::truthData(TChain* t, bool d){
  tree  = t;
  debug = d;

  truthParticles  = new truthParticle("GenPart",  tree, true);
} 

void truthData::reset(){
  Zbbs.clear();
  Hbbs.clear();
  Bbbs.clear();
  m4b = -99;
}

void truthData::update(){
  if(debug) std::cout<<"Reset truthData"<<std::endl;
  this->reset();

  //Objects
  std::vector< std::shared_ptr<particle> > bsFromZs = truthParticles->getParticles(5, 23); // all b quarks from Z decays
  std::vector< std::shared_ptr<particle> > bsFromHs = truthParticles->getParticles(5, 25); // all b quarks from H decays
  std::vector< std::shared_ptr<particle> >       Zs = truthParticles->getParticles(23); //all Z bosons
  std::vector< std::shared_ptr<particle> >       Hs = truthParticles->getParticles(25); //all H bosons

  // Get Zs that decayed to bbbar
  for(auto &Z: Zs){
    Z->getDaughters(bsFromZs);
    if(Z->tobbbar){
      Zbbs.push_back(Z);
      Bbbs.push_back(Z);
    }
  }

  // Get Hs that decayed to bbbar
  for(auto &H: Hs){
    H->getDaughters(bsFromHs);
    if(H->tobbbar){
      Hbbs.push_back(H);
      Bbbs.push_back(H);
    }
  }

  // Compute four body mass for diboson to bbbb events
  if(Bbbs.size() == 2){ //HH, ZZ or ZH
    m4b = (Bbbs[0]->p + Bbbs[1]->p).M();
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
  std::cout << "m4b = " << m4b << std::endl;
  return;
}

truthData::~truthData(){} 

