#include "TChain.h"

#include "nTupleAnalysis/baseClasses/interface/truthParticle.h"

using namespace nTupleAnalysis;

//particle object
particle::particle(){}
particle::particle(UInt_t i, truthParticle* data){

  pt  = data->pt [i];
  eta = data->eta[i];
  phi = data->phi[i];
  m   = data->m  [i];
  p = TLorentzVector();
  p.SetPtEtaPhiM(pt, eta, phi, m);
  e = p.E();

  pdgId = data->pdgId[i];
  genPartIdxMother = data->genPartIdxMother[i];
  idx = (Int_t) i;

}

void particle::getDaughters(std::vector< std::shared_ptr<particle> > particles){
  
  bool found_b     = false;
  bool found_bbar  = false;

  for(auto &p: particles){
    if(p->genPartIdxMother != this->idx) continue;
    this->daughters.push_back( p );
    if     (p->pdgId ==  5 && !found_b   ) found_b     = true;
    else if(p->pdgId == -5 && !found_bbar) found_bbar  = true;
  }
  this->tobbbar = found_b && found_bbar && this->daughters.size()==2;

  return;
}

void particle::dump(std::string prefix){
  std::cout << prefix;
  std::cout << "idx: " << this->idx;
  std::cout << " | pdgId: " << this->pdgId;
  std::cout << " | idxMother: " << this->genPartIdxMother;
  std::cout << "| pt: " << this->pt;
  std::cout << "| eta: " << this->eta;
  std::cout << "| phi: " << this->phi;
  std::cout << "| m: " << this->m;
  std::cout << std::endl;
  for(auto &d: this->daughters){
    d->dump(prefix+"  ->");
  }
}

particle::~particle(){}


//access tree
truthParticle::truthParticle(std::string name, TTree* tree, bool readIn){

  m_name = name;

  connectBranches(readIn, tree);


}

void truthParticle::connectBranches(bool readIn, TTree* tree){

  std::string truthName =  m_name;
  std::string NTruthName = "n"+m_name;

  connectBranch(readIn, tree, NTruthName, nTruth, "i" );

  connectBranchArr(readIn, tree, truthName+"_pt"  , pt  , NTruthName, "F");  
  connectBranchArr(readIn, tree, truthName+"_eta" , eta , NTruthName, "F");  
  connectBranchArr(readIn, tree, truthName+"_phi" , phi , NTruthName, "F");  
  connectBranchArr(readIn, tree, truthName+"_mass", m   , NTruthName, "F");  

  connectBranchArr(readIn, tree, truthName+"_genPartIdxMother", genPartIdxMother, NTruthName, "I" );
  connectBranchArr(readIn, tree, truthName+"_pdgId", pdgId, NTruthName, "I" );
  //inputBranch(tree, (name+"_").c_str(),  );


}


void truthParticle::writeTruth(std::vector< std::shared_ptr<particle> > outputTruth){
  
  int nOutputTruth = outputTruth.size();
  this->nTruth = outputTruth.size();
 
  for(Int_t i = 0; i < int(this->nTruth); ++i){
    if(i > int(MAXTRUTH-1)) {
      std::cout  << m_name << "::Warning too much truth! " << nOutputTruth << " particles. Skipping. "<< std::endl;
      break;
    }

    const particlePtr& thisParticle = outputTruth.at(i);

    this->pt    [i] = thisParticle->pt         ;
    this->eta   [i] = thisParticle->eta        ;
    this->phi   [i] = thisParticle->phi        ;
    this->m     [i] = thisParticle->m          ;
    this->genPartIdxMother  [i] = thisParticle->genPartIdxMother       ;
    this->pdgId [i] = thisParticle->pdgId	   ;

  }

  return ;
}


std::vector< std::shared_ptr<particle> > truthParticle::getParticles(Int_t absPDG, Int_t absMomPDG){
  
  std::vector< std::shared_ptr<particle> > outputParticles;

  for(UInt_t i = 0; i < nTruth; ++i){
    if(    absPDG != -1 && abs(pdgId[i])                   != absPDG    ) continue;
    if( absMomPDG != -1 && abs(pdgId[genPartIdxMother[i]]) != absMomPDG ) continue;
    outputParticles.push_back(std::make_shared<particle>(particle(i, this)));
  }

  return outputParticles;
}

truthParticle::~truthParticle(){}


 // nGenPart        = 56
 //  GenPart_eta     = 22912, 
 //  -23104, 0.503906, -1.61328, -1, 0.27832, 
 //  0.5, -1.6875, 0.495117, -1.6875, 0.496094, 
 //  -1.71484, 0.501953, -1.71094, -1.31641, -1.44531, 
 //  0.211426, 0.882812, 1.48828, -1.05078
 //  GenPart_mass    = 0, 
 //  0, 125, 81, 0, 0, 
 //  125, 81, 125, 81, 125, 
 //  81, 125, 81, 0, 0, 
 //  0, 0, 0, 0
 //  GenPart_phi     = 0, 
 //  0, -1.66016, 1.1875, 2.46094, 0.314453, 
 //  -1.65625, 1.14453, -1.66797, 1.21875, -1.67188, 
 //  1.22266, -1.66016, 1.22266, 2.125, 0.537109, 
 //  -1.44531, 2.58594, 1.44531, 2.48438
 //  GenPart_pt      = 0, 
 //  0, 113.5, 87.25, 44.75, 13, 
 //  115, 81.5, 114.5, 81.75, 115, 
 //  79.75, 114.25, 80.25, 50.75, 63.125, 
 //  131.5, 31.625, 7.48438, 38
 //  GenPart_genPartIdxMother = -1, 
 //  -1, 0, 0, 0, 0, 2, 3, 6, 7, 8, 
 //  9, 10, 11, 13, 13, 12, 12, 17, 4
 //  GenPart_pdgId   = 1, 
 //  -1, 25, 23, 5, -5, 25, 23, 25, 23, 25, 
 //  23, 25, 23, -1, 1, 5, -5, -5, 5
 //  GenPart_status  = 21, 
 //  21, 22, 22, 23, 23, 44, 44, 44, 44, 44, 
 //  44, 62, 62, 23, 23, 23, 23, 52, 71
 //  GenPart_statusFlags = 10625, 
 //  14721, 4481, 4481, 4481, 4481, 257, 257, 257, 257, 257, 
 //  257, 10497, 10497, 22913, 4481, 4481, 22913, 8449, 8449
