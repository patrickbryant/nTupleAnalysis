#include "TChain.h"

#include "nTupleAnalysis/baseClasses/interface/trackData.h"
#include "DataFormats/BTauReco/interface/ParticleMasses.h"

using namespace nTupleAnalysis;



//track object
track::track(){}
track::track(UInt_t i, trackData* data){


  if(data->doPFNano){

    pt  = data->PFCands_pt                 [i];
    eta = data->PFCands_eta                [i];
    phi = data->PFCands_phi                [i];
    m   = data->PFCands_mass               [i];
    p = TLorentzVector();
    p.SetPtEtaPhiM(pt, eta, phi, m);
    e = p.E();


    dxy       = data->PFCands_d0                 [i];
    dxyError  = data->PFCands_d0Err              [i];
    IP2D                 = dxy;
    IP2Dsig              = dxyError ? dxy / dxyError : -1;
    IP2Derr              = dxyError;

    dz        = data->PFCands_dz                 [i];
    dzError   = data->PFCands_dzErr              [i];
    chi2      = data->PFCands_trkChi2            [i];
    charge    = data->PFCands_charge             [i];
    nHitAll   = data->PFCands_numberOFHits       [i];
    nHitPixel = data->PFCands_numberOfPixelHits  [i];

    PFCands_puppiWeight    = data->PFCands_puppiWeight        [i];
    PFCands_vtxChi2        = data->PFCands_vtxChi2            [i];
    PFCands_lostInnerHits  = data->PFCands_lostInnerHits      [i];
    PFCands_pdgId          = data->PFCands_pdgId              [i];
    PFCands_pvAssocQuality = data->PFCands_pvAssocQuality     [i];
    PFCands_trkQuality     = data->PFCands_trkQuality         [i];

  }else{

    pt  = data->pt[i];
    eta = data->eta[i];
    phi = data->phi[i];
    m   = reco::ParticleMasses::piPlus;
    p = TLorentzVector();
    p.SetPtEtaPhiM(pt, eta, phi, m);
    e = p.E();

    dxy                  = data->dxy                  [i];
    dz                   = data->dz                   [i];
    dxyError             = data->dxyError             [i];
    dzError              = data->dzError              [i];
    sign2D               = data->sign2D               [i];
    sign3D               = data->sign3D               [i];
    length               = data->length               [i];
    dist                 = data->dist                 [i];
    IP2D                 = data->IP2D                 [i];
    IP2Dsig              = data->IP2Dsig              [i];
    IP2Derr              = data->IP2Derr              [i];
    IP                   = data->IP                   [i];
    IPsig                = data->IPsig                [i];
    IPerr                = data->IPerr                [i];
    Proba                = data->Proba                [i];
    chi2                 = data->chi2                 [i];
    charge               = data->charge               [i];
    history              = data->history              [i];
    nHitStrip            = data->nHitStrip            [i];
    nHitPixel            = data->nHitPixel            [i];
    nHitAll              = data->nHitAll              [i];
    nHitTIB              = data->nHitTIB              [i];
    nHitTID              = data->nHitTID              [i];
    nHitTOB              = data->nHitTOB              [i];
    nHitTEC              = data->nHitTEC              [i];
    nHitPXB              = data->nHitPXB              [i];
    nHitPXF              = data->nHitPXF              [i];
    isHitL1              = data->isHitL1              [i];
    PV                   = data->PV                   [i];
    SV                   = data->SV                   [i];
    PVweight             = data->PVweight             [i];
    SVweight             = data->SVweight             [i];
    isfromSV             = data->isfromSV             [i];
    isfromV0             = data->isfromV0             [i];
    category             = data->category             [i];
    algo                 = data->algo                 [i];
    originalAlgo         = data->originalAlgo         [i];
    //TPAssociationQuality = data->TPAssociationQuality [i];
    //idxMatchedTP         = data->idxMatchedTP         [i];
  }

}


track::~track(){}


//access tree
trackData::trackData(std::string name, TTree* tree){

  //inputBranch(tree, (name+"nTrack").c_str(), nTrack );    
  std::cout << "Creating trackData " << name << std::endl;
  if(doPFNano){
    
    inputBranch(tree, ("n"+name).c_str(), nTracks);

    inputBranch(tree, (name+"_d0"                ).c_str(),   PFCands_d0                 );
    inputBranch(tree, (name+"_d0Err"             ).c_str(),   PFCands_d0Err              );
    inputBranch(tree, (name+"_dz"                ).c_str(),   PFCands_dz                 );
    inputBranch(tree, (name+"_dzErr"             ).c_str(),   PFCands_dzErr              );
    inputBranch(tree, (name+"_eta"               ).c_str(),   PFCands_eta                );
    inputBranch(tree, (name+"_mass"              ).c_str(),   PFCands_mass               );
    inputBranch(tree, (name+"_phi"               ).c_str(),   PFCands_phi                );
    inputBranch(tree, (name+"_pt"                ).c_str(),   PFCands_pt                 );
    inputBranch(tree, (name+"_puppiWeight"       ).c_str(),   PFCands_puppiWeight        );
    inputBranch(tree, (name+"_puppiWeightNoLep"  ).c_str(),   PFCands_puppiWeightNoLep   );
    inputBranch(tree, (name+"_trkChi2"           ).c_str(),   PFCands_trkChi2            );
    inputBranch(tree, (name+"_vtxChi2"           ).c_str(),   PFCands_vtxChi2            );
    inputBranch(tree, (name+"_charge"            ).c_str(),   PFCands_charge             );
    inputBranch(tree, (name+"_lostInnerHits"     ).c_str(),   PFCands_lostInnerHits      );
    inputBranch(tree, (name+"_numberOFHits"      ).c_str(),   PFCands_numberOFHits       );
    inputBranch(tree, (name+"_numberOfPixelHits" ).c_str(),   PFCands_numberOfPixelHits  );
    inputBranch(tree, (name+"_pdgId"             ).c_str(),   PFCands_pdgId              );
    inputBranch(tree, (name+"_pvAssocQuality"    ).c_str(),   PFCands_pvAssocQuality     );
    inputBranch(tree, (name+"_trkQuality"        ).c_str(),   PFCands_trkQuality         );

  }else{

    inputBranch(tree, (name+"Track_dxy"                  ).c_str(),          dxy                   );
    inputBranch(tree, (name+"Track_dz"                   ).c_str(),          dz                    );
    inputBranch(tree, (name+"Track_dxyError"             ).c_str(),          dxyError              );
    inputBranch(tree, (name+"Track_dzError"              ).c_str(),          dzError               );
    inputBranch(tree, (name+"Track_sign2D"               ).c_str(),          sign2D                );
    inputBranch(tree, (name+"Track_sign3D"               ).c_str(),          sign3D                );
    inputBranch(tree, (name+"Track_length"               ).c_str(),          length                );
    inputBranch(tree, (name+"Track_dist"                 ).c_str(),          dist                  );
    inputBranch(tree, (name+"Track_IP2D"                 ).c_str(),          IP2D                  );
    inputBranch(tree, (name+"Track_IP2Dsig"              ).c_str(),          IP2Dsig               );
    inputBranch(tree, (name+"Track_IP2Derr"              ).c_str(),          IP2Derr               );
    inputBranch(tree, (name+"Track_IP"                   ).c_str(),          IP                    );
    inputBranch(tree, (name+"Track_IPsig"                ).c_str(),          IPsig                 );
    inputBranch(tree, (name+"Track_IPerr"                ).c_str(),          IPerr                 );
    inputBranch(tree, (name+"Track_Proba"                ).c_str(),          Proba                 );
    inputBranch(tree, (name+"Track_p"                    ).c_str(),          p                     );
    inputBranch(tree, (name+"Track_pt"                   ).c_str(),          pt                    );
    inputBranch(tree, (name+"Track_eta"                  ).c_str(),          eta                   );
    inputBranch(tree, (name+"Track_phi"                  ).c_str(),          phi                   );
    inputBranch(tree, (name+"Track_chi2"                 ).c_str(),          chi2                  );
    inputBranch(tree, (name+"Track_charge"               ).c_str(),          charge                );
    inputBranch(tree, (name+"Track_history"              ).c_str(),          history               );
    inputBranch(tree, (name+"Track_nHitStrip"            ).c_str(),          nHitStrip             );
    inputBranch(tree, (name+"Track_nHitPixel"            ).c_str(),          nHitPixel             );
    inputBranch(tree, (name+"Track_nHitAll"              ).c_str(),          nHitAll               );
    inputBranch(tree, (name+"Track_nHitTIB"              ).c_str(),          nHitTIB               );
    inputBranch(tree, (name+"Track_nHitTID"              ).c_str(),          nHitTID               );
    inputBranch(tree, (name+"Track_nHitTOB"              ).c_str(),          nHitTOB               );
    inputBranch(tree, (name+"Track_nHitTEC"              ).c_str(),          nHitTEC               );
    inputBranch(tree, (name+"Track_nHitPXB"              ).c_str(),          nHitPXB               );
    inputBranch(tree, (name+"Track_nHitPXF"              ).c_str(),          nHitPXF               );
    inputBranch(tree, (name+"Track_isHitL1"              ).c_str(),          isHitL1               );
    inputBranch(tree, (name+"Track_PV"                   ).c_str(),          PV                    );
    inputBranch(tree, (name+"Track_SV"                   ).c_str(),          SV                    );
    inputBranch(tree, (name+"Track_PVweight"             ).c_str(),          PVweight              );
    inputBranch(tree, (name+"Track_SVweight"             ).c_str(),          SVweight              );
    inputBranch(tree, (name+"Track_isfromSV"             ).c_str(),          isfromSV              );
    inputBranch(tree, (name+"Track_isfromV0"             ).c_str(),          isfromV0              );
    inputBranch(tree, (name+"Track_category"             ).c_str(),          category              );
    inputBranch(tree, (name+"Track_algo"                 ).c_str(),          algo                  );
    inputBranch(tree, (name+"Track_originalAlgo"         ).c_str(),          originalAlgo          );
    inputBranch(tree, (name+"Track_TPAssociationQuality" ).c_str(),          TPAssociationQuality  );
    inputBranch(tree, (name+"Track_idxMatchedTP"         ).c_str(),          idxMatchedTP          );
  }


}


std::vector< std::shared_ptr<track> > trackData::getTracks(int nFirstTrack, int nLastTrack){
  
  std::vector< std::shared_ptr<track> > outputTracks;
  for(int i = nFirstTrack; i < nLastTrack; ++i){
    outputTracks.push_back(std::make_shared<track>(track(i, this)));
  }
  return outputTracks;
}


std::vector< std::shared_ptr<track> > trackData::getTracks(){
  
  std::vector< std::shared_ptr<track> > outputTracks;
  for(Int_t i = 0; i < int(nTracks); ++i){
    outputTracks.push_back(std::make_shared<track>(track(i, this)));
  }
  return outputTracks;
}



trackData::~trackData(){
  std::cout << "track::destroyed " << std::endl;
}

