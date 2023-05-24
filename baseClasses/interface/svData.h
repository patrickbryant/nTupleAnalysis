// -*- C++ -*-

#if !defined(svData_H)
#define svData_H
#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"


namespace nTupleAnalysis {


  //forward declaration for use in track constructor from tree
  class svData;
  //track object
  class sv {

  public:

    Short_t   charge  ;  //  sum of the charge of the SV tracks             *
    Float_t   dlen    ;  //  decay length in cm                             *
    Float_t   dlenSig ;  //  decay length significance                     *
    Float_t   dxy     ;  //  2D decay length in cm                          *
    Float_t   dxySig  ;  //  2D decay length significance                   *
    Float_t   pAngle  ;  //  pointing angle, i.e. acos(p_SV * (SV - PV))    *
    UChar_t   ntracks ;  //  number of tracks                              *
    Float_t   chi2    ;  //  reduced chi2, i.e. chi/ndof                    *
    Float_t   eta     ;  //  eta                                            *
    Float_t   mass    ;  //  mass                                           *
    Float_t   ndof    ;  //  number of degrees of freedom                   *
    Float_t   phi     ;  //  phi                                            *
    Float_t   pt      ;  //  pt                                             *
    Float_t   x       ;  //  secondary vertex X position, in cm             *
    Float_t   y       ;  //  secondary vertex Y position, in cm             *
    Float_t   z       ;  //  secondary vertex Z position, in cm             *

    sv();
    sv(UInt_t, svData*); 

    ~sv(); 

  };

  typedef std::shared_ptr<sv> svPtr;


  //class for tree access
  class svData {

  public:

    static const unsigned int MAXNSVS = 1000;

    Int_t     nSVs  = 0;       // secondary vertices from IVF algorithm            *
    Short_t   charge  [MAXNSVS];  //  sum of the charge of the SV tracks             *
    Float_t   dlen    [MAXNSVS];  //  decay length in cm                             *
    Float_t   dlenSig [MAXNSVS];  //  decay length significance                     *
    Float_t   dxy     [MAXNSVS];  //  2D decay length in cm                          *
    Float_t   dxySig  [MAXNSVS];  //  2D decay length significance                   *
    Float_t   pAngle  [MAXNSVS];  //  pointing angle, i.e. acos(p_SV * (SV - PV))    *
    UChar_t   ntracks [MAXNSVS];  //  number of tracks                              *
    Float_t   chi2    [MAXNSVS];  //  reduced chi2, i.e. chi/ndof                    *
    Float_t   eta     [MAXNSVS];  //  eta                                            *
    Float_t   mass    [MAXNSVS];  //  mass                                           *
    Float_t   ndof    [MAXNSVS];  //  number of degrees of freedom                   *
    Float_t   phi     [MAXNSVS];  //  phi                                            *
    Float_t   pt      [MAXNSVS];  //  pt                                             *
    Float_t   x       [MAXNSVS];  //  secondary vertex X position, in cm             *
    Float_t   y       [MAXNSVS];  //  secondary vertex Y position, in cm             *
    Float_t   z       [MAXNSVS];  //  secondary vertex Z position, in cm             *


    svData(std::string, TTree*); 
    std::vector< std::shared_ptr<sv> > getSVs();

    ~svData(); 

    //void dump();
  };



}
#endif // svData_H

