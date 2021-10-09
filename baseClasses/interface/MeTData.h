// -*- C++ -*-

#if !defined(MeTData_H)
#define MeTData_H
#include <TChain.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"

namespace nTupleAnalysis {
  //forward declaration for use in elec constructor from tree
  class MeTData;

  //class for tree access
  class MeTData {

  public:
    std::string m_name;

    Float_t phi  ; 
    Float_t pt   ; 
    Float_t sumEt; 


    MeTData(std::string name, TChain* tree, bool readIn = true, bool isMC = false); 

    //void writeMeT(std::vector< std::shared_ptr<elec> > outputElecs) ;
    void connectBranches(bool readIn, TTree* tree);


    ~MeTData(); 

  };

}
#endif // MeTData_H

