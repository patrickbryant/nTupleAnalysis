#include "nTupleAnalysis/baseClasses/interface/svHists.h"
#include "DataFormats/Math/interface/deltaR.h"
#include <cmath>


using namespace nTupleAnalysis;

svHists::svHists(std::string name, fwlite::TFileService& fs, std::string title) {
  TFileDirectory dir = fs.mkdir(name);
  this->makeHists(name, dir, title);
}

svHists::svHists(std::string name, TFileDirectory& dir, std::string title) {
  this->makeHists(name, dir, title);
}


void svHists::makeHists(std::string name, TFileDirectory& dir, std::string title) {

  nSVs         = dir.make<TH1F>("nSVs",     ("nSVs;    " +title+" Number of Second Vertecies; Entries").c_str(),  10,-0.5,9.5);

  charge    = dir.make<TH1F>("charge"        , ("charge;  "+title+" Charge; Entries").c_str(), 11,  -5.5, 5.5);  //  sum of the charge of the SV tracks             * 
  dlen      = dir.make<TH1F>("dlen"          , ("dlen;    "+title+" decay length [cm]; Entries").c_str(), 100, -0.1, 10);   //                               * 
  dlenSig   = dir.make<TH1F>("dlenSig"       , ("dlenSig; "+title+" decay length significance; Entries").c_str(), 100, -0.1, 30);   //                       *  
  dlenSig_l = dir.make<TH1F>("dlenSig_l"     , ("dlenSig; "+title+" decay length significance; Entries").c_str(), 100, -0.1, 50);   //                       *  
  dxy       = dir.make<TH1F>("dxy"           , ("dxy;     "+title+" 2D decay length in cm                         ; Entries").c_str(), 100, -0.1, 30);   //   * 
  dxySig    = dir.make<TH1F>("dxySig"        , ("dxySig;  "+title+" 2D decay length significance                  ; Entries").c_str(), 100, -0.1, 30);   //   * 
  dxySig_l  = dir.make<TH1F>("dxySig_l"      , ("dxySig;  "+title+" 2D decay length significance                  ; Entries").c_str(), 100, -0.1, 50);   //   * 
  pAngle    = dir.make<TH1F>("pAngle"        , ("pAngle;  "+title+" pointing angle, i.e. acos(p_SV * (SV - PV))   ; Entries").c_str(), 100, -3.14, 3.14);      //   * 
  ntracks   = dir.make<TH1F>("ntracks"       , ("ntracks; "+title+" number of tracks                              ; Entries").c_str(), 20, -0.5, 19.5);   //  *  
  chi2      = dir.make<TH1F>("chi2"          , ("chi2;    "+title+" reduced chi2, i.e. chi/ndof                   ; Entries").c_str(), 100, -0.1, 10);   //   * 
  eta       = dir.make<TH1F>("eta"           , ("eta;     "+title+" eta                                           ; Entries").c_str(), 100, -3, 3);      //   * 
  mass      = dir.make<TH1F>("mass"          , ("mass;    "+title+" mass                                          ; Entries").c_str(), 100, -0.1, 20);   //   * 
  ndof      = dir.make<TH1F>("ndof"          , ("ndof;    "+title+" number of degrees of freedom                  ; Entries").c_str(), 20, -0.5, 19.5);   //   * 
  phi       = dir.make<TH1F>("phi"           , ("phi;     "+title+" phi                                           ; Entries").c_str(), 100, -3.14, 3.14);//   * 
  pt_s      = dir.make<TH1F>("pt_s"          , ("pt;      "+title+" pt                                            ; Entries").c_str(), 100, -0.1, 20);   //   * 
  pt        = dir.make<TH1F>("pt"            , ("pt;      "+title+" pt                                            ; Entries").c_str(), 100, -0.1, 100);   //   * 
  z         = dir.make<TH1F>("z"             , ("z;       "+title+" secondary vertex Z position, in cm            ; Entries").c_str(), 100, -15, 15);    //   *b
  dRjet     = dir.make<TH1F>("dRjet"         , ("dRjet;   "+title+" deltaR SV and Jet                             ; Entries").c_str(), 100, -0.1, 1);    //  


} 

void svHists::Fill(const svPtr &sv, const jetPtr& jet,  float weight){


  charge    ->Fill(sv->charge     , weight);
  dlen      ->Fill(sv->dlen       , weight);
  dlenSig   ->Fill(sv->dlenSig    , weight);
  dlenSig_l ->Fill(sv->dlenSig    , weight);
  dxy       ->Fill(sv->dxy        , weight);
  dxySig    ->Fill(sv->dxySig     , weight);
  dxySig_l  ->Fill(sv->dxySig     , weight);
  pAngle    ->Fill(sv->pAngle     , weight);
  ntracks   ->Fill(sv->ntracks    , weight);
  chi2      ->Fill(sv->chi2       , weight);
  eta       ->Fill(sv->eta        , weight);
  mass      ->Fill(sv->mass       , weight);
  ndof      ->Fill(sv->ndof       , weight);
  phi       ->Fill(sv->phi        , weight);
  pt_s      ->Fill(sv->pt         , weight);
  pt        ->Fill(sv->pt         , weight);
  z         ->Fill(sv->z          , weight);

  // dR
 float dR2 = reco::deltaR2<float, float, float, float>(jet->p.Eta(),jet->p.Phi(), sv->eta, sv->phi);
 dRjet       ->Fill(std::sqrt(dR2)          , weight);


  return;
}



svHists::~svHists(){
} 
