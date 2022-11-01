#include "TChain.h"
#include "TFile.h"

#include "nTupleAnalysis/baseClasses/interface/eventData.h"

using namespace nTupleAnalysis;


//access tree
eventData::eventData(std::string name, TChain* tree, bool readIn, bool isMC){

  m_name = name;

  triggerData = new nTupleAnalysis::trigData("TrigObj",tree);

  connectBranches(readIn, tree);

  
}

void eventData::connectBranches(bool readIn, TTree* tree){

  if(connectBranch(readIn, tree, "Run",             run, "i" ) == -1){
    connectBranch(readIn, tree, "run",             run, "i" );
  }

  if(connectBranch(readIn, tree, "Evt",             event, "l" ) == -1){
    connectBranch(readIn, tree, "event",             event, "l" );
  }

  connectBranch(readIn, tree, "luminosityBlock", luminosityBlock, "i" );



  connectBranch(readIn, tree, "PV_ndof"       ,   PV_ndof         , "F");
  connectBranch(readIn, tree, "PV_x"          ,   PV_x            , "F");
  connectBranch(readIn, tree, "PV_y"          ,   PV_y            , "F");
  connectBranch(readIn, tree, "PV_z"          ,   PV_z            , "F");
  connectBranch(readIn, tree, "PV_chi2"       ,   PV_chi2         , "F");
  connectBranch(readIn, tree, "PV_score"      ,   PV_score        , "F");
  connectBranch(readIn, tree, "PV_npvs"       ,   PV_npvs         , "F");
  connectBranch(readIn, tree, "PV_npvsGood"   ,   PV_npvsGood     , "F");


}    




eventData::~eventData(){
  std::cout << "eventData::destroyed " << std::endl;
}
