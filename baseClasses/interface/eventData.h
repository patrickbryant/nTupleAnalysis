// -*- C++ -*-

#if !defined(eventData_H)
#define eventData_H
#include <TChain.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"
#include "nTupleAnalysis/baseClasses/interface/trigData.h"
#include "nTupleAnalysis/baseClasses/interface/MeTData.h"

namespace nTupleAnalysis {
  //forward declaration for use in elec constructor from tree
  class eventData;

  //class for tree access
  class eventData {

  public:
    std::string m_name;

    Int_t    run       =  0;
    UInt_t   luminosityBlock =  0;
    Int_t    event     =  0;

    Float_t  PV_ndof         = 0;
    Float_t  PV_x            = 0;
    Float_t  PV_y            = 0;
    Float_t  PV_z            = 0;
    Float_t  PV_chi2         = 0;
    Float_t  PV_score        = 0;
    Int_t    PV_npvs         = 0;
    Int_t    PV_npvsGood     = 0;

    trigData* triggerData  = NULL;
    MeTData*  puppiMetData = NULL;

    eventData(std::string name, TChain* tree, bool readIn = true, bool isMC = false); 

    //void writeMeT(std::vector< std::shared_ptr<elec> > outputElecs) ;
    void connectBranches(bool readIn, TTree* tree);


    ~eventData(); 

  };

}
#endif // eventData_H

