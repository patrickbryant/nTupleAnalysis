// -*- C++ -*-

#if !defined(trackData_H)
#define trackData_H
#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"


namespace nTupleAnalysis {


  //forward declaration for use in track constructor from tree
  class trackData;
  //track object
  class track {

  public:

    float pt;
    float eta;
    float phi;
    float m;
    float e;
    TLorentzVector p;

    float dxy                  ;
    float dz                   ;
    float dxyError             ;
    float dzError              ;
    int   sign2D               ;
    int   sign3D               ;
    float length               ;
    float dist                 ;
    float IP2D                 ;
    float IP2Dsig              ;
    float IP2Derr              ;
    float IP                   ;
    float IPsig                ;
    float IPerr                ;
    float Proba                ;
    float chi2                 ;
    int   charge               ;
    int   history              ;
    int   nHitStrip            ;
    int   nHitPixel            ;
    int   nHitAll              ;
    int   nHitTIB              ;
    int   nHitTID              ;
    int   nHitTOB              ;
    int   nHitTEC              ;
    int   nHitPXB              ;
    int   nHitPXF              ;
    int   isHitL1              ;
    int   PV                   ;
    int   SV                   ;
    float PVweight             ;
    float SVweight             ;
    int   isfromSV             ;
    int   isfromV0             ;
    int   category             ;
    int   algo                 ;
    int   originalAlgo         ;
    float TPAssociationQuality ;
    int   idxMatchedTP         ;

    float puppiWeight    ;
    float vtxChi2        ;
    int   lostInnerHits  ;
    int   pdgId          ;
    float pvAssocQuality ;
    float trkQuality     ;


    float dR                   ;
    float ptRel                   ;
    float pPar                   ;

    float match_dR = -99;
    int   nMatches = 0;
    std::weak_ptr<track>  matchedTrack;
    std::weak_ptr<track>  secondClosest;

    bool hasTrkTagVarMatch = false;

    track();
    track(UInt_t, trackData*); 

    ~track(); 

    //void dump();
  };

  typedef std::shared_ptr<track> trackPtr;


  //class for tree access
  class trackData {

  public:

    static const unsigned int MAXNTRKS = 100000;
    bool doPFNano = true;

    UInt_t nTracks = 0;

    float dxy                   [MAXNTRKS];
    float dz                    [MAXNTRKS];
    float dxyError              [MAXNTRKS];
    float dzError               [MAXNTRKS];
    int   sign2D                [MAXNTRKS];
    int   sign3D                [MAXNTRKS];
    float length                [MAXNTRKS];
    float dist                  [MAXNTRKS];
    float IP2D                  [MAXNTRKS];
    float IP2Dsig               [MAXNTRKS];
    float IP2Derr               [MAXNTRKS];
    float IP                    [MAXNTRKS];
    float IPsig                 [MAXNTRKS];
    float IPerr                 [MAXNTRKS];
    float Proba                 [MAXNTRKS];
    float p                     [MAXNTRKS];
    float pt                    [MAXNTRKS];
    float eta                   [MAXNTRKS];
    float phi                   [MAXNTRKS];
    float chi2                  [MAXNTRKS];
    int   charge                [MAXNTRKS];
    int   history               [MAXNTRKS];
    int   nHitStrip             [MAXNTRKS];
    int   nHitPixel             [MAXNTRKS];
    int   nHitAll               [MAXNTRKS];
    int   nHitTIB               [MAXNTRKS];
    int   nHitTID               [MAXNTRKS];
    int   nHitTOB               [MAXNTRKS];
    int   nHitTEC               [MAXNTRKS];
    int   nHitPXB               [MAXNTRKS];
    int   nHitPXF               [MAXNTRKS];
    int   isHitL1               [MAXNTRKS];
    int   PV                    [MAXNTRKS];
    int   SV                    [MAXNTRKS];
    float PVweight              [MAXNTRKS];
    float SVweight              [MAXNTRKS];
    int   isfromSV              [MAXNTRKS];
    int   isfromV0              [MAXNTRKS];
    int   category              [MAXNTRKS];
    int   algo                  [MAXNTRKS];
    int   originalAlgo          [MAXNTRKS];
    float TPAssociationQuality  [MAXNTRKS];
    int   idxMatchedTP          [MAXNTRKS];

    //   nPFCands        = 32
    Float_t d0                 [MAXNTRKS];
    Float_t d0Err              [MAXNTRKS];
    Float_t mass               [MAXNTRKS];
    Float_t puppiWeight        [MAXNTRKS];
    Float_t puppiWeightNoLep   [MAXNTRKS];
    Float_t trkChi2            [MAXNTRKS];
    Float_t vtxChi2            [MAXNTRKS];
    Int_t   lostInnerHits      [MAXNTRKS];
    Int_t   numberOFHits       [MAXNTRKS];
    Int_t   numberOfPixelHits  [MAXNTRKS];
    Int_t   pdgId              [MAXNTRKS];
    Int_t   pvAssocQuality     [MAXNTRKS];
    Int_t   trkQuality         [MAXNTRKS];

    trackData(std::string, TTree*); 
    std::vector< std::shared_ptr<track> > getTracks(int nFirstTrack, int nLastTrack);
    std::vector< std::shared_ptr<track> > getTracks(bool isCharged);

    ~trackData(); 

    //void dump();
  };



}
#endif // trackData_H

