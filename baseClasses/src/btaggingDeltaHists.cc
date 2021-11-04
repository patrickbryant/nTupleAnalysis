#include "nTupleAnalysis/baseClasses/interface/btaggingDeltaHists.h"

using namespace nTupleAnalysis;
using std::cout; using std::endl; 

btaggingDeltaHists::btaggingDeltaHists(std::string name, fwlite::TFileService& fs, std::string title) {
  TFileDirectory dir = fs.mkdir(name);
  this->makeHists(name, dir, title);
}

btaggingDeltaHists::btaggingDeltaHists(std::string name, TFileDirectory& dir, std::string title) {
  TFileDirectory matchedDir = dir.mkdir(name);
  this->makeHists(name, matchedDir, title);
}


void btaggingDeltaHists::makeHists(std::string name, TFileDirectory& dir, std::string title) {

  dsv_NTracks                    = dir.make<TH1F>("dsv_NTracks"                ,"vertexNTracks;#Delta nVertex Tracks;Entries"                 ,11, -5.5, 5.5);
  dsv_Mass                       = dir.make<TH1F>("dsv_Mass"                   ,"vertexMass;#Delta Vertex Mass [GeV]"                    ,100, -5, 5);
  dsv_JetDeltaR                  = dir.make<TH1F>("dsv_JetDeltaR"              ,"vertexJetDeltaR;#Delta Vertex-Jet #Delta R"               ,100, -0.04, 0.04);
  //FitProb                    = dir.make<TH1F>("dsv_FitProb"                ,"vertexFitProb;Vertex Fit Prob"                 ,100, -50, 50);
  dsv_EnergyRatio                = dir.make<TH1F>("dsv_EnergyRatio"            ,"vertexEnergyRatio;#Delta Vertex Energy Fraction "             ,100, -0.3, 0.3);
  dsv_R              = dir.make<TH1F>("dsv_R"            ,"R          ;#Delta Vertex R           "             ,100, -0.02, 0.02);
  dsv_Z              = dir.make<TH1F>("dsv_Z"            ,"Z          ;#Delta Vertex Z           "             ,100, -0.02, 0.02);
  dsv_Chi2           = dir.make<TH1F>("dsv_Chi2"         ,"Chi2       ;#Delta Vertex Chi2        "             ,100, -0.1, 0.1);
  dsv_Chi2_l         = dir.make<TH1F>("dsv_Chi2_l"       ,"Chi2       ;#Delta Vertex Chi2        "           ,100, -5, 5);
  dsv_NDF            = dir.make<TH1F>("dsv_NDF"          ,"NDF        ;#Delta Vertex NDF         "             ,19, -9.5, 9.5);
  dsv_Flight         = dir.make<TH1F>("dsv_Flight"       ,"Flight     ;#Delta Vertex Flight      "             ,100, -0.02, 0.02);
  dsv_FlightSig      = dir.make<TH1F>("dsv_FlightSig"    ,"FlightSig  ;#Delta Vertex FlightSig   "             ,100, -5, 5);
  dsv_Flight2D       = dir.make<TH1F>("dsv_Flight2D"     ,"Flight2D   ;#Delta Vertex Flight2D    "             ,100, -0.02, 0.02);
  dsv_FlightSig2D    = dir.make<TH1F>("dsv_FlightSig2D"  ,"FlightSig2D;#Delta Vertex FlightSig2D "             ,100, -5, 5);
  dsv_Pt             = dir.make<TH1F>("dsv_Pt"           ,"Pt         ;#Delta Vertex Pt          "             ,100, -20, 20);
  dsv_Eta            = dir.make<TH1F>("dsv_Eta"          ,"Eta        ;#Delta Vertex Eta         "             ,100, -0.1, 0.1);
  dsv_Phi            = dir.make<TH1F>("dsv_Phi"          ,"Phi        ;#Delta Vertex Phi         "             ,100, -0.1, 0.1);
  dsv_DistJetAxis    = dir.make<TH1F>("dsv_DistJetAxis"  ,"DistJetAxis;#Delta Vertex DistJetAxis "             ,100, -5e-5, 5e-5);
  dsv_boostOverSqrtJetPt         = dir.make<TH1F>("dsv_BoostOverSqrtJetPt"     ,"vertexBoostOverSqrtJetPt;#Delta Vertex Boost/#sqrt{jet P_{T}}"      ,100, -0.05, 0.05);
  dsv_massVertexEnergyFraction   = dir.make<TH1F>("dsv_massVertexEnergyFraction"     ,"massVertexEnergyFraction;#Delta massVertexEnergyFraction"      ,100, -0.2,0.2);
  dsv_totCharge   = dir.make<TH1F>("dsv_totCharge"     ,"totCharge;#Delta totCharge"      ,11, -5.5,5.5);


  dtrkTag_ip3d_l = dir.make<TH1F>("dip3d_l","ip3d;#Delta IP3D [cm]",100,-0.05,0.05);
  dtrkTag_ip3d   = dir.make<TH1F>("dip3d",  "ip3d;#Delta IP3D [cm]",100,-0.02,0.02);

  dtrkTag_ip3d_sig_l = dir.make<TH1F>("dip3d_sig_l","ip3d sig;#Delta IP3D significance",100,-10,10);
  dtrkTag_ip3d_sig   = dir.make<TH1F>("dip3d_sig",  "ip3d sig;#Delta IP3D significance",100,-1,1);
  dtrkTag_ip3d_err_l = dir.make<TH1F>("dip3d_err_l","ip3d err;#Delta IP3D uncertianty [cm]",100,-0.01,0.01);
  dtrkTag_ip3d_err   = dir.make<TH1F>("dip3d_err",  "ip3d err;#Delta IP3D uncertianty [cm]",100,-0.001,0.001);
  
  dtrkTag_ip2d_l = dir.make<TH1F>("dip2d_l","ip2d;IP2D [cm]",100,-0.05,0.05);
  dtrkTag_ip2d   = dir.make<TH1F>("dip2d",  "ip2d;IP2D [cm]",100,-0.02,0.02);
  dtrkTag_ip2d_sig_l = dir.make<TH1F>("dip2d_sig_l","ip2d sig;#Delta IP2D significance",100,-10,10);
  dtrkTag_ip2d_sig   = dir.make<TH1F>("dip2d_sig",  "ip2d sig;#Delta IP2D significance",100,-1,1);
  dtrkTag_ip2d_err_l = dir.make<TH1F>("dip2d_err_l","ip2d err;#Delta IP2D uncertianty [cm]",100,-0.01,0.01);
  dtrkTag_ip2d_err   = dir.make<TH1F>("dip2d_err",  "ip2d err;#Delta IP2D uncertianty [cm]",100,-0.001,0.001);
    
  dtrkTag_trackDecayLenVal_l         = dir.make<TH1F>("dtrackDecayLenVal_l"  ,    "trackDecayLenVal;#Delta trackDecayLenVal [cm];Entries", 100, -0.5,  0.5);
  dtrkTag_trackDecayLenVal           = dir.make<TH1F>("dtrackDecayLenVal"    ,    "trackDecayLenVal;#Delta trackDecayLenVal [cm];Entries", 100, -0.1,  0.1);
  dtrkTag_trackJetDistVal            = dir.make<TH1F>("dtrackJetDistVal"     ,    "trackJetDistVal;#Delta trackJetDistVal [cm];Entries",  100, -0.01,  0.01);      
  dtrkTag_trackPtRel                 = dir.make<TH1F>("dtrackPtRel"          ,    "trackPtRel;#Delta track p_{T} Rel [GeV];Entries", 100, -1, 1);          
  dtrkTag_trackPt                    = dir.make<TH1F>("dtrackPt"             ,    "trackPt;#Delta track pt [GeV];Entries", 100, -5, 5);       
  dtrkTag_trackMomentum              = dir.make<TH1F>("dtrackMomentum"       ,    "trackMomentum;#Delta track momentum [GeV];Entries", 100, -5, 5);       

  dtrkTag_trackEta                   = dir.make<TH1F>("dtrackEta"            ,    "trackEta;#Delta track #eta;Entries", 100, -0.05, 0.05);            
  dtrkTag_trackPhi                   = dir.make<TH1F>("dtrackPhi"            ,    "trackPhi;#Delta track #phi;Entries", 100, -0.05, 0.05);            
  dtrkTag_trackPPar                  = dir.make<TH1F>("dtrackPPar"           ,    "trackPPar;#Delta track PPar [GeV];Entries",100, -5, 5);           
  dtrkTag_trackDeltaR                = dir.make<TH1F>("dtrackDeltaR"         ,    "trackDeltaR;#Delta track #DeltaR;Entries", 100, -0.05, 0.05);         
  dtrkTag_trackDeltaR_l              = dir.make<TH1F>("dtrackDeltaR_l"       ,    "trackDeltaR;#Delta track #DeltaR;Entries", 100, -0.05, 0.05);         
  dtrkTag_trackEtaRel                = dir.make<TH1F>("dtrackEtaRel"         ,    "trackEtaRel;#Delta track Eta Rel;Entries", 100, -1, 1);         
  dtrkTag_trackPtRatio               = dir.make<TH1F>("dtrackPtRatio"        ,    "trackPtRatio;#Delta track p_{T} Ratio;Entries", 100, -0.02, 0.02); 
  dtrkTag_trackPParRatio             = dir.make<TH1F>("dtrackPParRatio"      ,    "trackPParRatio;#Delta track P Par Ratio;Entries", 100, -0.02, 0.02);  

  dtrkTag_trackChi2                  = dir.make<TH1F>("dtrackChi2"            ,    "trackChi2;#Delta track Chi2;Entries", 100, -1, 1);            
  dtrkTag_trackNTotalHits            = dir.make<TH1F>("dtrackNTotalHits"      ,    "trackNTotalHits;#Delta trackNTotalHits;Entries", 21, -10.5, 10.5);
  dtrkTag_trackNPixelHits            = dir.make<TH1F>("dtrackNPixelHits"      ,    "trackNPixelHits;#Delta trackNPixelHits;Entries", 9, -4.5, 4.5);  
  //dtrkTag_nTracks                    = dir.make<TH1F>("d_nTracks",     ("nTrkTags;    " +title+" Number of Tracks; Entries").c_str(),  20,-0.5,19.5);
  dtrkTag_isFromV0                    = dir.make<TH1F>("dtrackIsFromV0"  ,  "IsFromV0;#Delta Is from V0;Entries", 3, -1.5,  1.5);  



  dtag_jetNTracks                       = dir.make<TH1F>("djetNTracks"                   ,"jetNTracks;#Delta Number Tracks"                    ,19, -9.5, 9.5);
  dtag_jetNSecondaryVertices            = dir.make<TH1F>("djetNSecondaryVertices"        ,"jetNSelectedTracks;#Delta Number Secondary Verticies"            ,9, -4.5, 4.5);

  dtag_chargedMultiplicity               = dir.make<TH1F>("dchargedMultiplicity"           ,"chargedMultiplicity;#Delta charged multiplicity"            ,41, -20.5, 20.5);
  dtag_chargedHadronEnergyFraction       = dir.make<TH1F>("dchargedHadronEnergyFraction"   ,"chargedHadronEnergyFraction;#Delta charged Hadron energy fraction"          ,100, -1,1.);
  dtag_chargedHadronMultiplicity         = dir.make<TH1F>("dchargedHadronMultiplicity"     ,"chargedHadronMultiplicity;#Delta charged hadron multiplicity"            ,41, -20.5, 20.5);
  dtag_chargedEmEnergyFraction           = dir.make<TH1F>("dchargedEmEnergyFraction"       ,"chargedEmEnergyFraction;#Delta charged Em energy fraction"          ,100, -1,1.);

  dtag_neutralMultiplicity               = dir.make<TH1F>("dneutralMultiplicity"           ,"neutralMultiplicity;#Delta neutral multiplicity"            ,41, -20.5, 20.5);
  dtag_neutralHadronEnergyFraction       = dir.make<TH1F>("dneutralHadronEnergyFraction"   ,"neutralHadronEnergyFraction;#Delta neutral Hadron energy fraction"          ,100, -1,1.);
  dtag_neutralHadronMultiplicity         = dir.make<TH1F>("dneutralHadronMultiplicity"     ,"neutralHadronMultiplicity;#Delta neutral hadron multiplicity"           ,41, -20.5, 20.5);
  dtag_neutralEmEnergyFraction           = dir.make<TH1F>("dneutralEmEnergyFraction"       ,"neutralEmEnergyFraction;#Delta neutral Em energy fraction"          ,100, -1,1);

  dtag_photonMultiplicity               = dir.make<TH1F>("dphotonMultiplicity"           ,"photonMultiplicity;#Delta photon multiplicity"             ,41, -20.5, 20.5);
  dtag_photonEnergyFraction             = dir.make<TH1F>("dphotonEnergyFraction"         ,"photonEnergyFraction;#Delta photon energy fraction"          ,100, -1,1.);

  dtag_muonMultiplicity                 = dir.make<TH1F>("dmuonMultiplicity"             ,"muonMultiplicity;#Delta muonMultiplicity"              ,11, -4.5, 4.5);
  dtag_muonEnergyFraction               = dir.make<TH1F>("dmuonEnergyFraction"           ,"muonEnergyFraction;#Delta muonEnergyFraction"            ,100, -1,1.);

  dtag_elecMultiplicity                 = dir.make<TH1F>("delecMultiplicity"             ,"elecMultiplicity;#Delta elecMultiplicity"              ,11, -4.5, 4.5);
  dtag_elecEnergyFraction               = dir.make<TH1F>("delecEnergyFraction"           ,"elecEnergyFraction;#Delta elecEnergyFraction"            ,100, -1,1.);

  dtag_totalMultiplicity                = dir.make<TH1F>("dtotalMultiplicity"            ,"totalMultiplicity;#Delta total multiplicity"             ,41, -20.5, 20.5);


} 

void btaggingDeltaHists::FillSVHists(const svPtr &sv1, const jetPtr& jet1, 
				     const svPtr &sv2, const jetPtr& jet2, 
				     float weight){

  
  dsv_NTracks                ->Fill(sv1->nTrk        - sv2->nTrk,        weight);
  dsv_Mass                   ->Fill(sv1->mass        - sv2->mass,        weight);
  dsv_JetDeltaR              ->Fill(sv1->deltaR_jet  - sv2->deltaR_jet,  weight);
  dsv_EnergyRatio            ->Fill(sv1->EnergyRatio - sv2->EnergyRatio, weight);
  dsv_totCharge              ->Fill(sv1->totCharge   - sv2->totCharge,   weight);

  float svR_1 = sqrt(sv1->x*sv1->x + sv1->y*sv1->y);
  float svR_2 = sqrt(sv2->x*sv2->x + sv2->y*sv2->y);
  dsv_R                ->Fill(svR_1 - svR_2, weight);
  dsv_Z                ->Fill(sv1->z    - sv2->z   , weight);
  dsv_Chi2             ->Fill(sv1->chi2 - sv2->chi2, weight);
  dsv_Chi2_l             ->Fill(sv1->chi2 - sv2->chi2, weight);
  dsv_NDF              ->Fill(sv1->ndf  - sv2->ndf , weight);
  
  dsv_Flight           ->Fill(sv1->flight - sv2->flight, weight);
  float flightSig_1 = sv1->flightErr ? sv1->flight/sv1->flightErr : -1;
  float flightSig_2 = sv2->flightErr ? sv2->flight/sv2->flightErr : -1;
  dsv_FlightSig        ->Fill(flightSig_1 - flightSig_2, weight);
  
  dsv_Flight2D           ->Fill(sv1->flight2D - sv2->flight2D, weight);
  float flightSig2D_1 = sv1->flight2DErr ? sv1->flight2D/sv1->flight2DErr : -1;
  float flightSig2D_2 = sv2->flight2DErr ? sv2->flight2D/sv2->flight2DErr : -1;
  dsv_FlightSig2D        ->Fill(flightSig2D_1 - flightSig2D_2, weight);
  
  dsv_Pt                ->Fill(sv1->vtx_pt         - sv2->vtx_pt        , weight);
  dsv_Eta               ->Fill(sv1->vtx_eta        - sv2->vtx_eta       , weight);
  dsv_Phi               ->Fill(sv1->vtx_phi        - sv2->vtx_phi       , weight);
  dsv_DistJetAxis       ->Fill(sv1->vtxDistJetAxis - sv2->vtxDistJetAxis, weight);

  dsv_boostOverSqrtJetPt ->Fill(sv1->p.BoostVector().Mag()/ sqrt(jet1->p.Pt()) - sv2->p.BoostVector().Mag()/ sqrt(jet2->p.Pt()), weight);
  dsv_massVertexEnergyFraction -> Fill(sv1->p.M() / sv1->p.E() - sv2->p.M() / sv2->p.E(), weight);

  return;
}


void btaggingDeltaHists::FillTrkTagVarHists(const trkTagVarPtr &trkTag1, 
					    const trkTagVarPtr &trkTag2, 
					    float weight){

  dtrkTag_ip3d      ->Fill(trkTag1->trackSip3dVal - trkTag2->trackSip3dVal);
  dtrkTag_ip3d_l    ->Fill(trkTag1->trackSip3dVal - trkTag2->trackSip3dVal);
  dtrkTag_ip3d_sig  ->Fill(trkTag1->trackSip3dSig - trkTag2->trackSip3dSig);
  dtrkTag_ip3d_sig_l->Fill(trkTag1->trackSip3dSig - trkTag2->trackSip3dSig);

  float ip3d_err_1 = trkTag1->trackSip3dSig ? trkTag1->trackSip3dVal/trkTag1->trackSip3dSig : 0;
  float ip3d_err_2 = trkTag2->trackSip3dSig ? trkTag2->trackSip3dVal/trkTag2->trackSip3dSig : 0;
  dtrkTag_ip3d_err  ->Fill(ip3d_err_1 - ip3d_err_2);
  dtrkTag_ip3d_err_l->Fill(ip3d_err_1 - ip3d_err_2);

  dtrkTag_ip2d      ->Fill(trkTag1->trackSip2dVal - trkTag2->trackSip2dVal);
  dtrkTag_ip2d_l    ->Fill(trkTag1->trackSip2dVal - trkTag2->trackSip2dVal);
  dtrkTag_ip2d_sig  ->Fill(trkTag1->trackSip2dSig - trkTag2->trackSip2dSig);
  dtrkTag_ip2d_sig_l->Fill(trkTag1->trackSip2dSig - trkTag2->trackSip2dSig);

  float ip2d_err_1 = trkTag1->trackSip2dSig ? trkTag1->trackSip2dVal/trkTag1->trackSip2dSig : 0;
  float ip2d_err_2 = trkTag2->trackSip2dSig ? trkTag2->trackSip2dVal/trkTag2->trackSip2dSig : 0;
  dtrkTag_ip2d_err  ->Fill(ip2d_err_1 - ip2d_err_2);
  dtrkTag_ip2d_err_l->Fill(ip2d_err_1 - ip2d_err_2);
        

  dtrkTag_trackDecayLenVal_l   ->Fill(trkTag1->trackDecayLenVal - trkTag2->trackDecayLenVal,weight );
  dtrkTag_trackDecayLenVal     ->Fill(trkTag1->trackDecayLenVal - trkTag2->trackDecayLenVal,weight );
  dtrkTag_trackJetDistVal      ->Fill(trkTag1->trackJetDistVal  - trkTag2->trackJetDistVal ,weight );
  dtrkTag_trackPtRel           ->Fill(trkTag1->trackPtRel       - trkTag2->trackPtRel      ,weight );
  dtrkTag_trackMomentum        ->Fill(trkTag1->trackMomentum    - trkTag2->trackMomentum   ,weight ); 
  dtrkTag_trackPt              ->Fill(trkTag1->pt               - trkTag2->pt              ,weight ); 

  dtrkTag_trackEta             ->Fill(trkTag1->trackEta       - trkTag2->trackEta        ,weight );
  dtrkTag_trackPhi             ->Fill(trkTag1->trackPhi       - trkTag2->trackPhi        ,weight );
  dtrkTag_trackPPar            ->Fill(trkTag1->trackPPar      - trkTag2->trackPPar       ,weight );
  dtrkTag_trackDeltaR          ->Fill(trkTag1->trackDeltaR    - trkTag2->trackDeltaR     ,weight );
  dtrkTag_trackDeltaR_l        ->Fill(trkTag1->trackDeltaR    - trkTag2->trackDeltaR     ,weight );
  dtrkTag_trackEtaRel          ->Fill(trkTag1->trackEtaRel    - trkTag2->trackEtaRel     ,weight );
  dtrkTag_trackPtRatio         ->Fill(trkTag1->trackPtRatio   - trkTag2->trackPtRatio    ,weight );
  dtrkTag_trackPParRatio       ->Fill(trkTag1->trackPParRatio - trkTag2->trackPParRatio  ,weight );

  dtrkTag_trackChi2                  ->Fill(trkTag1->trackChi2       - trkTag2->trackChi2      ,weight );
  dtrkTag_trackNTotalHits            ->Fill(trkTag1->trackNTotalHits - trkTag2->trackNTotalHits,weight ); 
  dtrkTag_trackNPixelHits            ->Fill(trkTag1->trackNPixelHits - trkTag2->trackNPixelHits,weight );

  dtrkTag_isFromV0->Fill(trkTag1->matchIsFromV0 - trkTag2->matchIsFromV0, weight);

  return;
}


void btaggingDeltaHists::FillTagVarHists(const tagVarPtr &tag1, 
					 const tagVarPtr &tag2, 
					 float weight){
  
  dtag_jetNTracks                  ->Fill(tag1-> jetNTracks                  - tag2-> jetNTracks                  ,weight);
  dtag_jetNSecondaryVertices       ->Fill(tag1-> jetNSecondaryVertices       - tag2-> jetNSecondaryVertices       ,weight);
  dtag_chargedMultiplicity         ->Fill(tag1-> chargedMultiplicity         - tag2-> chargedMultiplicity         ,weight);
  dtag_chargedHadronEnergyFraction ->Fill(tag1-> chargedHadronEnergyFraction - tag2-> chargedHadronEnergyFraction ,weight);
  dtag_chargedHadronMultiplicity   ->Fill(tag1-> chargedHadronMultiplicity   - tag2-> chargedHadronMultiplicity   ,weight);
  dtag_chargedEmEnergyFraction     ->Fill(tag1-> chargedEmEnergyFraction     - tag2-> chargedEmEnergyFraction     ,weight);
  dtag_neutralMultiplicity         ->Fill(tag1-> neutralMultiplicity         - tag2-> neutralMultiplicity         ,weight);
  dtag_neutralHadronEnergyFraction ->Fill(tag1-> neutralHadronEnergyFraction - tag2-> neutralHadronEnergyFraction ,weight);
  dtag_neutralHadronMultiplicity   ->Fill(tag1-> neutralHadronMultiplicity   - tag2-> neutralHadronMultiplicity   ,weight);
  dtag_neutralEmEnergyFraction     ->Fill(tag1-> neutralEmEnergyFraction     - tag2-> neutralEmEnergyFraction     ,weight);
  dtag_photonEnergyFraction        ->Fill(tag1-> photonEnergyFraction        - tag2-> photonEnergyFraction        ,weight);
  dtag_photonMultiplicity          ->Fill(tag1-> photonMultiplicity          - tag2-> photonMultiplicity          ,weight);
  dtag_muonEnergyFraction          ->Fill(tag1-> muonEnergyFraction          - tag2-> muonEnergyFraction          ,weight);
  dtag_muonMultiplicity            ->Fill(tag1-> muonMultiplicity            - tag2-> muonMultiplicity            ,weight);
  dtag_elecEnergyFraction          ->Fill(tag1-> electronEnergyFraction      - tag2-> electronEnergyFraction      ,weight);
  dtag_elecMultiplicity            ->Fill(tag1-> electronMultiplicity        - tag2-> electronMultiplicity        ,weight);
  dtag_totalMultiplicity           ->Fill(tag1-> numberOfDaughters           - tag2-> numberOfDaughters           ,weight);



}

btaggingDeltaHists::~btaggingDeltaHists(){} 
