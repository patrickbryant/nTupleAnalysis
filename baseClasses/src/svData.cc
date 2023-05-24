#include "TChain.h"

#include "nTupleAnalysis/baseClasses/interface/svData.h"
#include "DataFormats/BTauReco/interface/ParticleMasses.h"

using namespace nTupleAnalysis;



//track object
sv::sv(){}
sv::sv(UInt_t i, svData* data){

  charge   = data-> charge  [i]; //  sum of the charge of the SV tracks             *
  dlen     = data-> dlen    [i]; //  decay length in cm                             *
  dlenSig  = data-> dlenSig [i]; //  decay length significance                     *
  dxy      = data-> dxy     [i]; //  2D decay length in cm                          *
  dxySig   = data-> dxySig  [i]; //  2D decay length significance                   *
  pAngle   = data-> pAngle  [i]; //  pointing angle, i.e. acos(p_SV * (SV - PV))    *
  ntracks  = data-> ntracks [i]; //  number of tracks                              *
  chi2     = data-> chi2    [i]; //  reduced chi2, i.e. chi/ndof                    *
  eta      = data-> eta     [i]; //  eta                                            *
  mass     = data-> mass    [i]; //  mass                                           *
  ndof     = data-> ndof    [i]; //  number of degrees of freedom                   *
  phi      = data-> phi     [i]; //  phi                                            *
  pt       = data-> pt      [i]; //  pt                                             *
  x        = data-> x       [i]; //  secondary vertex X position, in cm             *
  y        = data-> y       [i]; //  secondary vertex Y position, in cm             *
  z        = data-> z       [i]; //  secondary vertex Z position, in cm             *b

}


sv::~sv(){}


//access tree
svData::svData(std::string name, TTree* tree){

  //inputBranch(tree, (name+"nTrack").c_str(), nTrack );    
  std::cout << "Creating svData " << name << std::endl;
    
  inputBranch(tree, ("n"+name).c_str(), nSVs);

  inputBranch(tree, (name+"_charge"   ).c_str(),         charge  );
  inputBranch(tree, (name+"_dlen"     ).c_str(),         dlen    );
  inputBranch(tree, (name+"_dlenSig"  ).c_str(),         dlenSig );
  inputBranch(tree, (name+"_dxy"      ).c_str(),         dxy     );
  inputBranch(tree, (name+"_dxySig"   ).c_str(),         dxySig  );
  inputBranch(tree, (name+"_pAngle"   ).c_str(),         pAngle  );
  inputBranch(tree, (name+"_ntracks"  ).c_str(),         ntracks );
  inputBranch(tree, (name+"_chi2"     ).c_str(),         chi2    );
  inputBranch(tree, (name+"_eta"      ).c_str(),         eta     );
  inputBranch(tree, (name+"_mass"     ).c_str(),         mass    );
  inputBranch(tree, (name+"_ndof"     ).c_str(),         ndof    );
  inputBranch(tree, (name+"_phi"      ).c_str(),         phi     );
  inputBranch(tree, (name+"_pt"       ).c_str(),         pt      );
  inputBranch(tree, (name+"_x"        ).c_str(),         x       );
  inputBranch(tree, (name+"_y"        ).c_str(),         y       );
  inputBranch(tree, (name+"_z"        ).c_str(),         z       );

}



std::vector< std::shared_ptr<sv> > svData::getSVs(){
  
  std::vector< std::shared_ptr<sv> > outputSVs;
  for(Int_t i = 0; i < int(nSVs); ++i){

    //if(isCharged && charge[i] == 0) continue;

    outputSVs.push_back(std::make_shared<sv>(sv(i, this)));
  }
  return outputSVs;
}



svData::~svData(){
  std::cout << "track::destroyed " << std::endl;
}

