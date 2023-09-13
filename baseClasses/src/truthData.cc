#include <iostream>

#include "nTupleAnalysis/baseClasses/interface/truthData.h"

using namespace nTupleAnalysis;

truthData::truthData(TChain* t, bool _debug, std::string truthName, bool _doBBWW, bool _doTTbar){
  tree    = t;
  debug   = _debug;
  doBBWW  = _doBBWW;
  doTTbar = _doTTbar;

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
  TWbs.clear();
  m4b = -99;
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

  std::vector< std::shared_ptr<particle> >       Ts   = truthParticles->getParticles(6); //all top quarks
  std::vector< std::shared_ptr<particle> > WsFromTs   = truthParticles->getParticles(24, 6); // all W bosons from T decays 
  std::vector< std::shared_ptr<particle> > bsFromTs   = truthParticles->getParticles(5, 6); // all b quarks from T decays 

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

    if(doBBWW){
      H->getDaughters(WsFromHs);
      if(H->toWW){
	HWWs.push_back(H);
      }
    }

  }

  if(doBBWW){
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
  }
  

  // Get Tops that decayed to Wb
  for(auto &T: Ts){
    std::vector< std::shared_ptr<particle> > psFromTs;
    for(auto b : bsFromTs) psFromTs.push_back(b);
    for(auto W : WsFromTs) psFromTs.push_back(W);
    
    T->getDaughters(psFromTs);
    if(T->toWb){
      TWbs.push_back(T);
    }
  }



  // Compute four body mass for diboson to bbbb events
  if(Bbbs.size() == 2){ //HH, ZZ or ZH
    m4b = (Bbbs[0]->p + Bbbs[1]->p).M();
  } 

//  if(Hbbs.size() == 1 && HWWs.size() == 1){ 
//    mbbWW = (Hbbs[0]->p + HWWs[0]->p).M();
//  } 


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
  std::cout << "nZqqs: " << Zqqs.size() << std::endl; 
  for(auto &Z: Zqqs) Z->dump("  ");
  std::cout << "m4b = " << m4b << std::endl;

  if(doBBWW){
    std::cout << "nHWWs: " << HWWs.size() << std::endl; 
    for(auto &H: HWWs) H->dump("  ");
  }

  
  if(doTTbar){
    std::cout << "n T->Wb: " << TWbs.size() << std::endl; 
    for(auto &T: TWbs) T->dump("  ");

  }

  if(doBBWW || doTTbar){
    std::cout << "nWqqs: " << Wqqs.size() << std::endl; 
    for(auto &W: Wqqs) W->dump("  ");
    
    std::cout << "nWlnus: " << Wlnus.size() << std::endl; 
    for(auto &W: Wlnus) W->dump("  ");
  }


  return;
}

truthData::~truthData(){} 

