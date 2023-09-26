#include <sstream>      // std::stringstream, std::stringbuf

#include "TChain.h"

#include "nTupleAnalysis/baseClasses/interface/trackJetData.h"
#include "DataFormats/BTauReco/interface/ParticleMasses.h"
#include "DataFormats/Math/interface/deltaR.h"

using namespace nTupleAnalysis;
using std::cout;  using std::endl;


//jet object
trackJet::trackJet(){}
trackJet::trackJet(UInt_t i, trackJetData* data){

  tree_idx = i;


  pt  = data->pt [i];
  eta = data->eta[i];
  phi = data->phi[i];
  m   = 0;
  p = TLorentzVector();
  p.SetPtEtaPhiM(pt, eta, phi, m);
  e = p.E();


}




trackJet::~trackJet(){
}

//
//access tree
//
trackJetData::trackJetData(std::string name, TTree* tree, bool readIn){

  m_name = name;

  connectBranches(readIn, tree);

}





std::vector< trackJetPtr > trackJetData::getJets(float ptMin, float ptMax, float etaMax){
  
  std::vector< trackJetPtr > outputTrackJets;


  if(debug) std::cout << "We have " << nTrackJets << " track jets"<< std::endl;
  for(Int_t i = 0; i < int(nTrackJets); ++i){

    if(i > int(MAXTRACKJETS-1)) {
      std::cout  << m_name << "::Warning too many track jets! " << nTrackJets << " jets. Skipping. "<< std::endl;
      break;
    }

    if(debug) std::cout << " track jet   " << pt[i] << " " << eta[i] << " " << phi[i] << std::endl;

      

    if(          pt[i]  <  ptMin ){
      if(debug) std::cout << "... failed ptMin  " << pt[i] << " < " << ptMin <<  std::endl;
      continue;
    }

    if(          pt[i]  >= ptMax ){
      if(debug) std::cout << "... failed ptMax  " << pt[i] << " >= " << ptMax <<  std::endl;
      continue;
    }

    if(    fabs(eta[i]) > etaMax ) continue;
    outputTrackJets.push_back(std::make_shared<trackJet>(trackJet(i, this)));
  }

  return outputTrackJets;
}



trackJetData::~trackJetData(){ 
  std::cout << "trackJetData::destroyed " << std::endl;
}


void trackJetData::connectBranches(bool readIn, TTree* tree){
  if(debug) std::cout << "trackJetData::connectBranches(bool readIn, TTree* tree)" << std::endl;

  std::string jetName =  m_name;
  std::string NjetName = "n"+m_name;

  connectBranch(readIn, tree, NjetName, nTrackJets, "i");

  connectBranchArr(readIn, tree, jetName+"_pt",           pt,  NjetName,  "F");
  connectBranchArr(readIn, tree, jetName+"_eta",          eta, NjetName,  "F");
  connectBranchArr(readIn, tree, jetName+"_phi",          phi, NjetName,  "F");


  return ;
}

