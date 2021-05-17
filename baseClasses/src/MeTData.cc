#include "TChain.h"
#include "TFile.h"

#include "nTupleAnalysis/baseClasses/interface/MeTData.h"

using namespace nTupleAnalysis;


//access tree
MeTData::MeTData(std::string name, TChain* tree, bool readIn, bool isMC){

  m_name = name;

  connectBranches(readIn, tree);

  
}

void MeTData::connectBranches(bool readIn, TTree* tree){

  std::string MeTName =  m_name;

  connectBranch(readIn, tree, MeTName+"_phi",     phi, "F" );
  connectBranch(readIn, tree, MeTName+"_pt",       pt, "F" );
  connectBranch(readIn, tree, MeTName+"_sumEt", sumEt, "F" );

}    




MeTData::~MeTData(){
  std::cout << "MeTData::destroyed " << std::endl;
}
