#include "nTupleAnalysis/baseClasses/interface/btaggingHists.h"

using namespace nTupleAnalysis;


btaggingHists::btaggingHists(std::string name, fwlite::TFileService& fs, std::string title) {
  TFileDirectory dir = fs.mkdir(name);
  this->makeHists(name, dir, title);
}

btaggingHists::btaggingHists(std::string name, TFileDirectory& dir, std::string title) {
  this->makeHists(name, dir, title);
}


void btaggingHists::makeHists(std::string name, TFileDirectory& dir, std::string title) {

  sv_NTracks                    = dir.make<TH1F>("sv_NTracks"                ,"vertexNTracks;nVertex Tracks;Entries"                 ,22, -2.5, 19.5);
  sv_Mass                       = dir.make<TH1F>("sv_Mass"                   ,"vertexMass;Vertex Mass [GeV]"                    ,100, -0.5, 10);
  sv_JetDeltaR                  = dir.make<TH1F>("sv_JetDeltaR"              ,"vertexJetDeltaR;Vertex-Jet #Delta R"               ,100, -0.01, 0.4);
  //FitProb                    = dir.make<TH1F>("sv_FitProb"                ,"vertexFitProb;Vertex Fit Prob"                 ,100, -50, 50);
  sv_EnergyRatio                = dir.make<TH1F>("sv_EnergyRatio"            ,"vertexEnergyRatio;Vertex Energy Fraction "             ,100, -0.1, 3);
  sv_R              = dir.make<TH1F>("sv_R          "            ,"R          ;Vertex R           "             ,100, -0.1, 5);
  sv_Z              = dir.make<TH1F>("sv_Z          "            ,"Z          ;Vertex Z           "             ,100, -20, 20);
  sv_Chi2           = dir.make<TH1F>("sv_Chi2       "            ,"Chi2       ;Vertex Chi2        "             ,100, -0.1, 10);
  sv_NDF            = dir.make<TH1F>("sv_NDF        "            ,"NDF        ;Vertex NDF         "             ,20, -0.5, 19.5);
  sv_Flight         = dir.make<TH1F>("sv_Flight     "            ,"Flight     ;Vertex Flight      "             ,100, -0.1, 5);
  sv_FlightSig      = dir.make<TH1F>("sv_FlightSig  "            ,"FlightSig  ;Vertex FlightSig   "             ,100, -0.1, 30);
  sv_Flight2D       = dir.make<TH1F>("sv_Flight2D   "            ,"Flight2D   ;Vertex Flight2D    "             ,100, -0.1, 5);
  sv_FlightSig2D    = dir.make<TH1F>("sv_FlightSig2D"            ,"FlightSig2D;Vertex FlightSig2D "             ,100, -0.1, 30);
  sv_Pt             = dir.make<TH1F>("sv_Pt         "            ,"Pt         ;Vertex Pt          "             ,100, -0.1, 100);
  sv_Eta            = dir.make<TH1F>("sv_Eta        "            ,"Eta        ;Vertex Eta         "             ,100, -2.5, 2.5);
  sv_Phi            = dir.make<TH1F>("sv_Phi        "            ,"Phi        ;Vertex Phi         "             ,100, -3.2, 3.2);
  sv_DistJetAxis    = dir.make<TH1F>("sv_DistJetAxis"            ,"DistJetAxis;Vertex DistJetAxis "             ,100, -0.1, 4e-3);
  sv_nSVs           = dir.make<TH1F>("sv_nSVs",     ("nSVs;    " +title+" Number of Sec. Verticies; Entries").c_str(),  10,-0.5,9.5);
  sv_boostOverSqrtJetPt         = dir.make<TH1F>("sv_BoostOverSqrtJetPt"     ,"vertexBoostOverSqrtJetPt;Vertex Boost/#sqrt{jet P_{T}}"      ,100, -0.1, 1.1);
  sv_massVertexEnergyFraction   = dir.make<TH1F>("sv_massVertexEnergyFraction"     ,"massVertexEnergyFraction;massVertexEnergyFraction"      ,100, -0.1,2.5);
  sv_totCharge   = dir.make<TH1F>("sv_totCharge"     ,"totCharge;totCharge"      ,11, -5.5,5.5);


  trkTag_ip3d_l = dir.make<TH1F>("ip3d_l","ip3d;IP3D [cm]",100,-0.2,0.2);
  trkTag_ip3d   = dir.make<TH1F>("ip3d",  "ip3d;IP3D [cm]",100,-0.05,0.05);
  trkTag_ip3d_sig_l = dir.make<TH1F>("ip3d_sig_l","ip3d sig;IP3D significance",100,-100,100);
  trkTag_ip3d_sig   = dir.make<TH1F>("ip3d_sig",  "ip3d sig;IP3D significance",100,-10,10);
  trkTag_ip3d_err_l = dir.make<TH1F>("ip3d_err_l","ip3d err;IP3D uncertianty [cm]",100,-0.01,0.1);
  trkTag_ip3d_err   = dir.make<TH1F>("ip3d_err",  "ip3d err;IP3D uncertianty [cm]",100,-0.001,0.01);
  
  trkTag_ip2d_l = dir.make<TH1F>("ip2d_l","ip2d;IP2D [cm]",100,-0.2,0.2);
  trkTag_ip2d   = dir.make<TH1F>("ip2d",  "ip2d;IP2D [cm]",100,-0.05,0.05);
  trkTag_ip2d_sig_l = dir.make<TH1F>("ip2d_sig_l","ip2d sig;IP2D significance",100,-100,100);
  trkTag_ip2d_sig   = dir.make<TH1F>("ip2d_sig",  "ip2d sig;IP2D significance",100,-10,10);
  trkTag_ip2d_err_l = dir.make<TH1F>("ip2d_err_l","ip2d err;IP2D uncertianty [cm]",100,-0.01,0.1);
  trkTag_ip2d_err   = dir.make<TH1F>("ip2d_err",  "ip2d err;IP2D uncertianty [cm]",100,-0.001,0.01);
    
  trkTag_trackDecayLenVal_vl        = dir.make<TH1F>("trackDecayLenVal_vl" ,    "trackDecayLenVal;trackDecayLenVal [cm];Entries", 100, -0.1,  60);
  trkTag_trackDecayLenVal_l         = dir.make<TH1F>("trackDecayLenVal_l"  ,    "trackDecayLenVal;trackDecayLenVal [cm];Entries", 100, -0.1,  6);
  trkTag_trackDecayLenVal           = dir.make<TH1F>("trackDecayLenVal"    ,    "trackDecayLenVal;trackDecayLenVal [cm];Entries", 100, -0.1,  0.5);
  trkTag_trackJetDistVal            = dir.make<TH1F>("trackJetDistVal"     ,    "trackJetDistVal;trackJetDistVal [cm];Entries",  100, -0.1,0.01);      
  trkTag_trackJetDistVal_l          = dir.make<TH1F>("trackJetDistVal_l"   ,    "trackJetDistVal;trackJetDistVal [cm];Entries",  100, -1,0.01);      
  trkTag_trackJetDistVal_vl         = dir.make<TH1F>("trackJetDistVal_vl"  ,    "trackJetDistVal;trackJetDistVal [cm];Entries",  100, -10,0.01);      
  trkTag_trackPtRel                 = dir.make<TH1F>("trackPtRel"          ,    "trackPtRel;track p_{T} Rel [GeV];Entries", 100, -0.1, 7);          
  trkTag_trackPt                    = dir.make<TH1F>("trackPt"             ,    "trackPt;track pt [GeV];Entries", 100, 0, 20);       
  trkTag_trackPt_l                  = dir.make<TH1F>("trackPt_l"           ,    "trackPt;track pt [GeV];Entries", 100, 0, 200);       
  trkTag_trackMomentum              = dir.make<TH1F>("trackMomentum"       ,    "trackMomentum;track momentum [GeV];Entries", 60, 0, 60);       

  Double_t binsPt[28] = {0.9, 1.116, 1.3838, 1.716, 2.1278, 2.6385, 3.2717, 4.0569, 5.0306, 6.2379, 7.735, 9.5914, 11.8933, 14.7477, 18.2872, 22.6761, 28.1183, 34.8667, 43.2347, 53.6111, 66.4777, 82.4324, 102.2162, 126.748, 157.1676, 194.8878, 241.6609, 299.6595};
  trkTag_trackPt_logx               = dir.make<TH1F>("trackPt_logx", "trackPt;track p_{T} [GeV];Entries", 27, binsPt);
  trkTag_trackEta                   = dir.make<TH1F>("trackEta"            ,    "trackEta;track #eta;Entries", 100, -2.6, 2.6);            
  trkTag_trackEta_l                 = dir.make<TH1F>("trackEta_l"          ,    "trackEta;track #eta;Entries", 100, -5, 5);            
  trkTag_trackPhi                   = dir.make<TH1F>("trackPhi"            ,    "trackPhi;track #phi;Entries", 100, -3.2, 3.2);            
  trkTag_trackPPar                  = dir.make<TH1F>("trackPPar"           ,    "trackPPar;track PPar [GeV];Entries",60, 0, 60);           
  trkTag_trackDeltaR                = dir.make<TH1F>("trackDeltaR"         ,    "trackDeltaR;track #DeltaR;Entries", 160, -0.05, 0.35);         
  trkTag_trackDeltaR_l              = dir.make<TH1F>("trackDeltaR_l"       ,    "trackDeltaR;track #DeltaR;Entries", 160, -0.05, 0.6);         
  trkTag_trackEtaRel                = dir.make<TH1F>("trackEtaRel"         ,    "trackEtaRel;track Eta Rel;Entries", 100, 0, 7);         
  trkTag_trackPtRatio               = dir.make<TH1F>("trackPtRatio"        ,    "trackPtRatio;track p_{T} Ratio;Entries", 100, -0.01, 0.3); 
  trkTag_trackPParRatio             = dir.make<TH1F>("trackPParRatio"      ,    "trackPParRatio;track P Par Ratio;Entries", 100, 0.95, 1.02);  
  
  trkTag_trackChi2                  = dir.make<TH1F>("trackChi2"            ,    "trackChi2;track Chi2;Entries", 100, -0.1, 6);            
  trkTag_trackNTotalHits            = dir.make<TH1F>("trackNTotalHits"      ,    "trackNTotalHits;trackNTotalHits;Entries", 30, -0.5, 29.5);
  trkTag_trackNPixelHits            = dir.make<TH1F>("trackNPixelHits"      ,    "trackNPixelHits;trackNPixelHits;Entries", 10, -0.5,  9.5);  
  trkTag_nTracks                    = dir.make<TH1F>("nTracks",     ("nTrkTags;    " +title+" Number of Tracks; Entries").c_str(),  20,-0.5,19.5);
  trkTag_isFromV0                    = dir.make<TH1F>("trackIsFromV0"  ,  "IsFromV0;Is from V0;Entries", 2, -0.5,  1.5);  

  tag_jetNTracks                       = dir.make<TH1F>("jetNTracks"                   ,"jetNTracks;Number Tracks"                    ,42, -1.5, 40.5);
  tag_jetNSecondaryVertices               = dir.make<TH1F>("jetNSecondaryVertices"           ,"jetNSelectedTracks;Number Secondary Vertices"            ,42, -1.5, 40.5);

  tag_chargedMultiplicity               = dir.make<TH1F>("chargedMultiplicity"           ,"chargedMultiplicity;charged multiplicity"            ,42, -1.5, 40.5);
  tag_chargedHadronEnergyFraction       = dir.make<TH1F>("chargedHadronEnergyFraction"         ,"chargedHadronEnergyFraction;charged Hadron energy fraction"          ,100, -0.1,1.5);
  tag_chargedHadronMultiplicity         = dir.make<TH1F>("chargedHadronMultiplicity"           ,"chargedHadronMultiplicity;charged hadron multiplicity"            ,42, -1.5, 40.5);
  tag_chargedEmEnergyFraction           = dir.make<TH1F>("chargedEmEnergyFraction"         ,"chargedEmEnergyFraction;charged Em energy fraction"          ,100, -0.1,1.5);

  tag_neutralMultiplicity               = dir.make<TH1F>("neutralMultiplicity"           ,"neutralMultiplicity;neutral multiplicity"            ,42, -1.5, 40.5);
  tag_neutralHadronEnergyFraction       = dir.make<TH1F>("neutralHadronEnergyFraction"         ,"neutralHadronEnergyFraction;neutral Hadron energy fraction"          ,100, -0.1,1.5);
  tag_neutralHadronMultiplicity         = dir.make<TH1F>("neutralHadronMultiplicity"           ,"neutralHadronMultiplicity;neutral hadron multiplicity"            ,42, -1.5, 40.5);
  tag_neutralEmEnergyFraction           = dir.make<TH1F>("neutralEmEnergyFraction"         ,"neutralEmEnergyFraction;neutral Em energy fraction"          ,100, -0.1,1.5);

  tag_photonMultiplicity               = dir.make<TH1F>("photonMultiplicity"           ,"photonMultiplicity;photon multiplicity"            ,42, -1.5, 40.5);
  tag_photonEnergyFraction             = dir.make<TH1F>("photonEnergyFraction"         ,"photonEnergyFraction;photon energy fraction"          ,100, -0.1,1.5);
   
  tag_muonMultiplicity                 = dir.make<TH1F>("muonMultiplicity"             ,"muonMultiplicity;muonMultiplicity"              ,12, -1.5, 10.5);
  tag_muonEnergyFraction               = dir.make<TH1F>("muonEnergyFraction"           ,"muonEnergyFraction;muonEnergyFraction"            ,100, -0.1,1.5);

  tag_elecMultiplicity                 = dir.make<TH1F>("elecMultiplicity"             ,"elecMultiplicity;elecMultiplicity"              ,12, -1.5, 10.5);
  tag_elecEnergyFraction               = dir.make<TH1F>("elecEnergyFraction"           ,"elecEnergyFraction;elecEnergyFraction"            ,100, -0.1,1.5);

  tag_totalMultiplicity                = dir.make<TH1F>("totalMultiplicity"            ,"totalMultiplicity;total multiplicity"             ,62, -1.5, 60.5);

  //
  //  DeepCSV NN inputs
  //
  tag_trackSumJetEtRatio               = dir.make<TH1F>("trackSumJetEtRatio"           ,"trackSumJetEtRatio;Track-jet/Jet E_{T} Ratio"            ,100, -0.1,1.5);
  tag_trackSumJetDeltaR                = dir.make<TH1F>("trackSumJetDeltaR"            ,"trackSumJetDeltaR; Track-Jet - Jet #Delta R"             ,100, -0.1, 0.35);
  tag_vertexCategory                   = dir.make<TH1F>("vertexCategory"               ,"vertexCategory;Vertex Category"                ,4 ,-1.5,2.5);
  tag_trackSip2dValAboveCharm          = dir.make<TH1F>("trackSip2dValAboveCharm"      ,"trackSip2dValAboveCharm;trackSip2dValAboveCharm"       ,100, -0.2, 0.2);
  tag_trackSip2dSigAboveCharm          = dir.make<TH1F>("trackSip2dSigAboveCharm"      ,"trackSip3dSigAboveCharm;trackSip2SiglAboveCharm"       ,100, -50, 50);
  tag_trackSip3dValAboveCharm          = dir.make<TH1F>("trackSip3dValAboveCharm"      ,"trackSip3dValAboveCharm;trackSip3dValAboveCharm"       ,100, -0.2, 0.2); 
  tag_trackSip3dSigAboveCharm          = dir.make<TH1F>("trackSip3dSigAboveCharm"      ,"trackSip3dSigAboveCharm;trackSip3dSigAboveCharm"       ,100, -50, 50);
  tag_jetNTracksEtaRel                 = dir.make<TH1F>("jetNTracksEtaRel"             ,"jetNTracksEtaRel;Number Tracks for eta rel"                    ,42, -1.5, 40.5);
  tag_vertexMass                       = dir.make<TH1F>("vertexMass"                   ,"vertexMass;Vertex Mass [GeV]"                    ,100, -0.5, 50);
  tag_vertexNTracks                    = dir.make<TH1F>("vertexNTracks"                ,"vertexNTracks;nVertex Tracks;Entries"                 ,22, -2.5, 19.5);
  tag_vertexJetDeltaR                  = dir.make<TH1F>("vertexJetDeltaR"              ,"vertexJetDeltaR;Vertex-Jet #Delta R"               ,100, -0.01, 0.4);
  tag_vertexEnergyRatio                = dir.make<TH1F>("vertexEnergyRatio"            ,"vertexEnergyRatio;Vertex Energy Fraction "             ,100, -0.1, 3);
  tag_flightDistance2dSig              = dir.make<TH1F>("flightDistance2dSig"          ,"flightDistance2dSig;flightDistance2dSig"           ,100, -10, 150);
  tag_flightDistance2dVal              = dir.make<TH1F>("flightDistance2dVal"          ,"flightDistance2dVal;flightDistance2dVal"           ,100, -0.1, 5);
  tag_flightDistance3dSig              = dir.make<TH1F>("flightDistance3dSig"          ,"flightDistance3dSig;flightDistance3dSig"           ,100, -10, 150);
  tag_flightDistance3dVal              = dir.make<TH1F>("flightDistance3dVal"          ,"flightDistance3dVal;flightDistance3dVal"           ,100, -0.1, 5);
  tag_trackEtaRel                      = dir.make<TH1F>("etaRel"                       ,"etaRel;etaRel"                                     ,100,  0, 7);
  
} 

void btaggingHists::FillSVHists(const secondaryVertexPtr &sv, const jetPtr& jet, float weight){

  
  sv_NTracks                ->Fill(sv->nTrk, weight);
  sv_Mass                   ->Fill(sv->mass, weight);
  sv_JetDeltaR              ->Fill(sv->deltaR_jet, weight);
  //svFitProb                ->Fill(sv->, weight);
  sv_EnergyRatio            ->Fill(sv->EnergyRatio, weight);
  sv_totCharge              ->Fill(sv->totCharge, weight);

  float svR = sqrt(sv->x*sv->x + sv->y*sv->y);
  sv_R                ->Fill(svR, weight);
  sv_Z                ->Fill(sv->z, weight);
  sv_Chi2             ->Fill(sv->chi2, weight);
  sv_NDF              ->Fill(sv->ndf, weight);
  
  sv_Flight           ->Fill(sv->flight, weight);
  sv_FlightSig        ->Fill(sv->flightSig, weight);
  
  sv_Flight2D           ->Fill(sv->flight2D, weight);
  sv_FlightSig2D        ->Fill(sv->flight2DSig, weight);
  
  sv_Pt                ->Fill(sv->vtx_pt, weight);
  sv_Eta               ->Fill(sv->vtx_eta, weight);
  sv_Phi               ->Fill(sv->vtx_phi, weight);
  sv_DistJetAxis       ->Fill(sv->vtxDistJetAxis, weight);

  sv_boostOverSqrtJetPt ->Fill(sv->p.BoostVector().Mag()/ sqrt(jet->p.Pt()), weight);
  sv_massVertexEnergyFraction -> Fill(sv->p.M() / sv->p.E(), weight);

  return;
}


void btaggingHists::FillTrkTagVarHists(const trkTagVarPtr &trkTag, float weight){

  trkTag_ip3d  ->Fill(trkTag->trackSip3dVal);
  trkTag_ip3d_l->Fill(trkTag->trackSip3dVal);
  trkTag_ip3d_sig  ->Fill(trkTag->trackSip3dSig);
  trkTag_ip3d_sig_l->Fill(trkTag->trackSip3dSig);

  float ip3d_err = trkTag->trackSip3dSig ? trkTag->trackSip3dVal/trkTag->trackSip3dSig : 0;
  trkTag_ip3d_err  ->Fill(ip3d_err);
  trkTag_ip3d_err_l->Fill(ip3d_err);

  trkTag_ip2d  ->Fill(trkTag->trackSip2dVal);
  trkTag_ip2d_l->Fill(trkTag->trackSip2dVal);
  trkTag_ip2d_sig  ->Fill(trkTag->trackSip2dSig);
  trkTag_ip2d_sig_l->Fill(trkTag->trackSip2dSig);

  float ip2d_err = trkTag->trackSip2dSig ? trkTag->trackSip2dVal/trkTag->trackSip2dSig : 0;
  trkTag_ip2d_err  ->Fill(ip2d_err);
  trkTag_ip2d_err_l->Fill(ip2d_err);
        

  trkTag_trackDecayLenVal_vl  ->Fill(trkTag->trackDecayLenVal,weight );
  trkTag_trackDecayLenVal_l   ->Fill(trkTag->trackDecayLenVal,weight );
  trkTag_trackDecayLenVal     ->Fill(trkTag->trackDecayLenVal,weight );
  trkTag_trackJetDistVal      ->Fill(trkTag->trackJetDistVal ,weight );
  trkTag_trackJetDistVal_l    ->Fill(trkTag->trackJetDistVal ,weight );
  trkTag_trackJetDistVal_vl   ->Fill(trkTag->trackJetDistVal ,weight );
  trkTag_trackPtRel           ->Fill(trkTag->trackPtRel      ,weight );
  trkTag_trackMomentum        ->Fill(trkTag->trackMomentum   ,weight ); 
  trkTag_trackPt              ->Fill(trkTag->pt   ,weight ); 
  trkTag_trackPt_l            ->Fill(trkTag->pt   ,weight ); 
  trkTag_trackPt_logx         ->Fill(trkTag->pt   ,weight ); 
  trkTag_trackEta             ->Fill(trkTag->trackEta        ,weight );
  trkTag_trackEta_l           ->Fill(trkTag->trackEta        ,weight );
  trkTag_trackPhi             ->Fill(trkTag->trackPhi        ,weight );
  trkTag_trackPPar            ->Fill(trkTag->trackPPar       ,weight );
  trkTag_trackDeltaR          ->Fill(trkTag->trackDeltaR         ,weight );
  trkTag_trackDeltaR_l        ->Fill(trkTag->trackDeltaR         ,weight );
  trkTag_trackEtaRel          ->Fill(trkTag->trackEtaRel     ,weight );
  trkTag_trackPtRatio         ->Fill(trkTag->trackPtRatio    ,weight );
  trkTag_trackPParRatio       ->Fill(trkTag->trackPParRatio  ,weight );

  trkTag_trackChi2                  ->Fill(trkTag->trackChi2      ,weight );
  trkTag_trackNTotalHits            ->Fill(trkTag->trackNTotalHits,weight ); 
  trkTag_trackNPixelHits            ->Fill(trkTag->trackNPixelHits,weight );

  trkTag_isFromV0->Fill(trkTag->matchIsFromV0, weight);



  return;
}


void btaggingHists::FillTagVarHists(const tagVarPtr &tag, const jetPtr& jet, float weight){
  
  tag_jetNTracks                  ->Fill(tag-> jetNTracks                  ,weight);
  tag_jetNSecondaryVertices       ->Fill(tag-> jetNSecondaryVertices       ,weight);
  tag_chargedMultiplicity         ->Fill(tag-> chargedMultiplicity         ,weight);
  tag_chargedHadronEnergyFraction ->Fill(tag-> chargedHadronEnergyFraction ,weight);
  tag_chargedHadronMultiplicity   ->Fill(tag-> chargedHadronMultiplicity   ,weight);
  tag_chargedEmEnergyFraction     ->Fill(tag-> chargedEmEnergyFraction     ,weight);

  tag_neutralMultiplicity         ->Fill(tag-> neutralMultiplicity         ,weight);
  tag_neutralHadronEnergyFraction ->Fill(tag-> neutralHadronEnergyFraction ,weight);
  tag_neutralHadronMultiplicity   ->Fill(tag-> neutralHadronMultiplicity   ,weight);
  tag_neutralEmEnergyFraction     ->Fill(tag-> neutralEmEnergyFraction     ,weight);

  tag_photonEnergyFraction        ->Fill(tag-> photonEnergyFraction        ,weight);
  tag_photonMultiplicity          ->Fill(tag-> photonMultiplicity          ,weight);
  tag_muonEnergyFraction          ->Fill(tag-> muonEnergyFraction          ,weight);
  tag_muonMultiplicity            ->Fill(tag-> muonMultiplicity            ,weight);
  tag_elecEnergyFraction          ->Fill(tag-> electronEnergyFraction      ,weight);
  tag_elecMultiplicity            ->Fill(tag-> electronMultiplicity        ,weight);
  tag_totalMultiplicity           ->Fill(tag-> numberOfDaughters           ,weight);


  //
  //  DeepCSV NN inputs
  //
  tag_trackSumJetEtRatio     ->Fill(tag->trackSumJetEtRatio,  weight);
  tag_trackSumJetDeltaR      ->Fill(tag->trackSumJetDeltaR,  weight);
  tag_vertexCategory         ->Fill(tag->vertexCategory,  weight);
  tag_trackSip2dValAboveCharm->Fill(tag->trackSip2dValAboveCharm,  weight);
  tag_trackSip2dSigAboveCharm->Fill(tag->trackSip2dSigAboveCharm,  weight);
  tag_trackSip3dValAboveCharm->Fill(tag->trackSip3dValAboveCharm,  weight);
  tag_trackSip3dSigAboveCharm->Fill(tag->trackSip3dSigAboveCharm,  weight);
  tag_vertexEnergyRatio      ->Fill(tag->vertexEnergyRatio,  weight);
  tag_jetNTracksEtaRel       ->Fill(tag->jetNTracksEtaRel,  weight);
  tag_vertexMass             ->Fill(tag->vertexMass,  weight);
  tag_vertexNTracks          ->Fill(tag->vertexNTracks,  weight);
  tag_vertexJetDeltaR        ->Fill(tag->vertexJetDeltaR,  weight);
  tag_flightDistance2dVal    ->Fill(tag->flightDistance2dVal,  weight);
  tag_flightDistance2dSig    ->Fill(tag->flightDistance2dSig,  weight);
  tag_flightDistance3dVal    ->Fill(tag->flightDistance3dVal,  weight);
  tag_flightDistance3dSig    ->Fill(tag->flightDistance3dSig,  weight);

  for(unsigned int trkEtaRelItr = 0; trkEtaRelItr < 4; ++trkEtaRelItr){
    if(trkEtaRelItr < tag->TagVarCSV_trackEtaRel.size()){
      tag_trackEtaRel->Fill(tag->TagVarCSV_trackEtaRel.at(trkEtaRelItr));
    }
  }


}

btaggingHists::~btaggingHists(){} 
