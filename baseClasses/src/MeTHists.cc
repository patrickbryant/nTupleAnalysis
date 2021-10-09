#include "nTupleAnalysis/baseClasses/interface/MeTHists.h"

using namespace nTupleAnalysis;

MeTHists::MeTHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);


    pt_s = dir.make<TH1F>("pt_s", (name+"/pt_s; "+title+" p_T [GeV]; Entries").c_str(),  100,0, 100);
    pt_m = dir.make<TH1F>("pt_m", (name+"/pt_m; "+title+" p_T [GeV]; Entries").c_str(),  100,0, 500);
    pt_l = dir.make<TH1F>("pt_l", (name+"/pt_l; "+title+" p_T [GeV]; Entries").c_str(),  100,0,1000);

    phi = dir.make<TH1F>("phi", (name+"/phi; "+title+" #phi; Entries").c_str(), 64, -3.2, 3.2);

    sumEt_s = dir.make<TH1F>("sumEt_s", (name+"/sumEt_s; "+title+" sumE_T [GeV]; Entries").c_str(),  100,0, 100);
    sumEt_m = dir.make<TH1F>("sumEt_m", (name+"/sumEt_m; "+title+" sumE_T [GeV]; Entries").c_str(),  100,0, 500);
    sumEt_l = dir.make<TH1F>("sumEt_l", (name+"/sumEt_l; "+title+" sumE_T [GeV]; Entries").c_str(),  100,0,1000);



} 

void MeTHists::Fill(const MeTData &MeT, float weight){

  pt_s -> Fill(MeT.pt, weight);
  pt_m -> Fill(MeT.pt, weight);
  pt_l -> Fill(MeT.pt, weight);

  phi -> Fill(MeT.phi, weight);

  sumEt_s -> Fill(MeT.sumEt, weight);
  sumEt_m -> Fill(MeT.sumEt, weight);
  sumEt_l -> Fill(MeT.sumEt, weight);

  return;
}

MeTHists::~MeTHists(){} 
