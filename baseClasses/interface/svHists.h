// -*- C++ -*-
#if !defined(svHists_H)
#define svHists_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include <TProfile.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/svData.h"
#include "nTupleAnalysis/baseClasses/interface/jetData.h"

namespace nTupleAnalysis {

  class svHists {
  public:

    TH1F* nSVs;

    TH1F*   charge   ; //  sum of the charge of the SV tracks             *
    TH1F*   dlen     ; //  decay length in cm                             *
    TH1F*   dlenSig  ; //  decay length significance                     *
    TH1F*   dlenSig_l  ; //  decay length significance                     *
    TH1F*   dxy      ; //  2D decay length in cm                          *
    TH1F*   dxySig   ; //  2D decay length significance                   *
    TH1F*   dxySig_l   ; //  2D decay length significance                   *
    TH1F*   pAngle   ; //  pointing angle, i.e. acos(p_SV * (SV - PV))    *
    TH1F*   ntracks  ; //  number of tracks                              *
    TH1F*   chi2     ; //  reduced chi2, i.e. chi/ndof                    *
    TH1F*   eta      ; //  eta                                            *
    TH1F*   mass     ; //  mass                                           *
    TH1F*   ndof     ; //  number of degrees of freedom                   *
    TH1F*   phi      ; //  phi                                            *
    TH1F*   pt       ; //  pt                                             *
    TH1F*   pt_s       ; //  pt                                             *
    TH1F*   z        ; //  secondary vertex Z position, in cm             *b

    TH1F*   dRjet      ; //  deltaR with Jet

    svHists(std::string,       TFileDirectory&, std::string title = "");
    svHists(std::string, fwlite::TFileService&, std::string title = "");

    void makeHists(std::string, TFileDirectory&, std::string title);
    void Fill(const svPtr& sv, const jetPtr& jet, float);

    ~svHists(); 

  };

}
#endif // svHists_H
