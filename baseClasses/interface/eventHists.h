// -*- C++ -*-
#if !defined(eventHists_H)
#define eventHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/eventData.h"
#include "nTupleAnalysis/baseClasses/interface/MeTHists.h"

namespace nTupleAnalysis {
  
class eventHists {
public:
  TFileDirectory dir;
  
  TH1F* run             =  0;
  TH1F* luminosityBlock =  0;
  TH1F* event           =  0;

  TH1F* PV_ndof         = 0;
  TH1F* PV_x            = 0;
  TH1F* PV_y            = 0;
  TH1F* PV_z            = 0;
  TH1F* PV_chi2         = 0;
  TH1F* PV_score        = 0;
  TH1F* PV_npvs         = 0;
  TH1F* PV_npvsGood     = 0;


  MeTHists* puppiMETHists = 0;

  eventHists(std::string, fwlite::TFileService&);
  void Fill(const eventData&, float);
  ~eventHists(); 

};

}
#endif // eventHists_H
