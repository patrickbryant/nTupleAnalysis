// -*- C++ -*-
#if !defined(helpers_H)
#define helpers_H


#include "nTupleAnalysis/baseClasses/interface/muonData.h"
#include "nTupleAnalysis/baseClasses/interface/elecData.h"
#include <TLorentzVector.h>

namespace nTupleAnalysis {
  
  bool failOverlap(const TLorentzVector& jet,const std::vector<muonPtr>& muons, float dRCut = 0.4);


  bool failOverlap(const TLorentzVector& jet,const std::vector<elecPtr>& elecs, float dRCut = 0.4);

  bool findSubStr(std::string inputStr, std::string subString);

}
#endif // helpers_H
