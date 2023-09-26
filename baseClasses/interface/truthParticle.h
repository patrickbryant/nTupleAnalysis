// -*- C++ -*-

#if !defined(truthParticle_H)
#define truthParticle_H
#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"

namespace nTupleAnalysis {
  //forward declaration for use in particle constructor from tree
  class truthParticle;
  class jet;
  class trackJet;
  //particle object
  class particle {

  public:
    float pt;
    float eta;
    float phi;
    float m;
    float e;
    TLorentzVector p;

    Int_t genPartIdxMother;
    Int_t pdgId;
    Int_t idx;
    std::weak_ptr<jet>  matchedJet;
    std::weak_ptr<trackJet>  matchedTrackJet;


    particle();
    particle(UInt_t, truthParticle*); 
    void getDaughters(std::vector< std::shared_ptr<particle> > particles);
    std::vector< std::shared_ptr<particle> > daughters;
    bool tobbbar = false;
    bool toqqbar = false;
    bool tolnu = false;
    bool toWW = false;
    bool toWb = false;
    ~particle(); 

    void dump(std::string prefix = "");
  };

  typedef std::shared_ptr<particle> particlePtr;

  //class for tree access
  class truthParticle {

  public:
    std::string m_name;
    UInt_t nTruth;
    static const unsigned int MAXTRUTH = 10000;

    float pt [MAXTRUTH];
    float eta[MAXTRUTH];
    float phi[MAXTRUTH];
    float m  [MAXTRUTH];

    Int_t genPartIdxMother[MAXTRUTH];
    Int_t pdgId[MAXTRUTH];

    truthParticle(std::string name, TTree* tree, bool readIn = true); 
    void connectBranches(bool readIn, TTree* tree);
    void writeTruth(std::vector< std::shared_ptr<particle> > outputTruth);

    std::vector< std::shared_ptr<particle> > getParticles(Int_t absPDG = -1, Int_t absMomPDG = -1, Int_t maxAbsPDG = -1, Int_t minAbsPDG = -1);
    ~truthParticle(); 

    //void dump();
  };

}
#endif // truthParticle_H

