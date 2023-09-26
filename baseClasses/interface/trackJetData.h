// -*- C++ -*-

#if !defined(trackJetData_H)
#define trackJetData_H
#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"



namespace nTupleAnalysis {

  //forward declaration for use in jet constructor from tree
  class trackJetData;

  //jet object
  class trackJet {


  public:

    UInt_t tree_idx;

    float pt;
    float eta;
    float phi;
    float m;
    float e;
    TLorentzVector p;

    trackJet();
    trackJet(UInt_t i, trackJetData* data); 

    ~trackJet(); 

  };

  typedef std::shared_ptr<trackJet> trackJetPtr;


  //class for tree access
  class trackJetData {

  public:

    std::string m_name ="";
    bool debug = false;

    static const unsigned int MAXTRACKJETS = 10000;

    UInt_t nTrackJets = 0;

    float pt [MAXTRACKJETS];
    float eta[MAXTRACKJETS];
    float phi[MAXTRACKJETS];
    float m  [MAXTRACKJETS];


    trackJetData(std::string name, TTree* tree, bool readIn = true);

    std::vector< trackJetPtr > getJets(float ptMin = -1e6, float ptMax = 1e6, float etaMax = 1e6);


    ~trackJetData(); 

    void connectBranches(bool readIn, TTree* tree);

    //void dump();
  };



}
#endif // trackJetData_H

