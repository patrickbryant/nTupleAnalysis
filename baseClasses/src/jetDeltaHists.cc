#include "nTupleAnalysis/baseClasses/interface/jetDeltaHists.h"

using namespace nTupleAnalysis;

jetDeltaHists::jetDeltaHists(std::string name, fwlite::TFileService& fs, std::string title) {
  TFileDirectory dir = fs.mkdir(name);
  this->makeHists(name, dir, title);
}

jetDeltaHists::jetDeltaHists(std::string name, TFileDirectory& dir, std::string title) {
  this->makeHists(name, dir, title);
}

void jetDeltaHists::makeHists(std::string name, TFileDirectory& dir, std::string title) {

    dPt      = dir.make<TH1F>("dPt",     (name+"/dPt     ;P_{T}-P_{T}^{matched} [GeV];Entries").c_str()  ,100,-50, 50);
    dEta     = dir.make<TH1F>("dEta",    (name+"/dEta    ;#eta-#eta^{matched};Entries"        ).c_str()  ,100,-0.5,0.5);
    dPhi     = dir.make<TH1F>("dPhi",    (name+"/dPhi    ;#phi-#phi^{matched};Entries"        ).c_str()  ,100,-0.5,0.5);
    dR       = dir.make<TH1F>("dR",      (name+"/dR      ;#DeltaR(Online,Offline);;Entries"   ).c_str()  ,100, 0,0.45);
    dcsv     = dir.make<TH1F>("dcsv",    (name+"/dcsv;CSV-CSV^{matched};Entries"              ).c_str()  ,100,-1,1);
    dDeepcsv = dir.make<TH1F>("dDeepcsv",(name+"/dDeepcsv;DeepCSV-DeepCSV^{matched};Entries"  ).c_str()  ,100,-1,1);

    ddeepFlavB      = dir.make<TH1F>("ddeepFlavB",      (name+"/ddeepFlavB; "     +title+"#Delta Deep (Jet) Flavour B; Entries").c_str(), 120,-1.,1.1);
    dntracks        = dir.make<TH1F>("dnTracks",        (name+"/dnTracks;    "    +title+"#Delta Number of Tracks; Entries").c_str(),  21,-10.5,10.5);
    dnseltracks     = dir.make<TH1F>("dnSelTracks",     (name+"/dnSelTracks;    " +title+"#Delta Number of Selected Tracks; Entries").c_str(),  21,-10.5,10.5);
    dIp2N           = dir.make<TH1F>("dIp2N"         ,  (name+"/dIp2N;     "      +title+"#Delta Ip2N     ;Entries").c_str(), 100, -1.2, 1.2);
    dIp2P           = dir.make<TH1F>("dIp2P"         ,  (name+"/dIp2P;     "      +title+"#Delta Ip2P     ;Entries").c_str(), 100, -1.2, 1.2);
    dIp3N           = dir.make<TH1F>("dIp3N"         ,  (name+"/dIp3N;     "      +title+"#Delta Ip3N     ;Entries").c_str(), 100, -1.2, 1.2);
    dIp3P           = dir.make<TH1F>("dIp3P"         ,  (name+"/dIp3P;     "      +title+"#Delta Ip3P     ;Entries").c_str(), 100, -1.2, 1.2);
    dProbaN         = dir.make<TH1F>("dProbaN"       ,  (name+"/dProbaN;   "      +title+"#Delta ProbaN   ;Entries").c_str(), 100, -1.2, 1.2);
    dProba          = dir.make<TH1F>("dProba"        ,  (name+"/dProba;    "      +title+"#Delta Proba    ;Entries").c_str(), 100, -1.2, 1.2);
    dBprobN         = dir.make<TH1F>("dBprobN"       ,  (name+"/dBprobN;   "      +title+"#Delta BprobN   ;Entries").c_str(), 100, -1.2, 1.2);
    dBprob          = dir.make<TH1F>("dBprob"        ,  (name+"/dBprob;    "      +title+"#Delta Bprob    ;Entries").c_str(), 100, -1.2, 1.2);
    dSvx            = dir.make<TH1F>("dSvx"          ,  (name+"/dSvx;      "      +title+"#Delta Svx      ;Entries").c_str(), 100, -1.2, 1.2);
    dSvxHP          = dir.make<TH1F>("dSvxHP"        ,  (name+"/dSvxHP;    "      +title+"#Delta SvxHP    ;Entries").c_str(), 100, -1.2, 1.2);
    dCombIVF        = dir.make<TH1F>("dCombIVF"      ,  (name+"/dCombIVF;  "      +title+"#Delta CombIVF  ;Entries").c_str(), 100, -1.2, 1.2);
    dCombIVF_N      = dir.make<TH1F>("dCombIVF_N"    ,  (name+"/dCombIVF_N;"      +title+"#Delta CombIVF_N;Entries").c_str(), 100, -1.2, 1.2);
    dSoftMuN        = dir.make<TH1F>("dSoftMuN"      ,  (name+"/dSoftMuN;  "      +title+"#Delta SoftMuN  ;Entries").c_str(), 100, -1.2, 1.2);
    dSoftMu         = dir.make<TH1F>("dSoftMu"       ,  (name+"/dSoftMu;   "      +title+"#Delta SoftMu   ;Entries").c_str(), 100, -1.2, 1.2);
    dSoftElN        = dir.make<TH1F>("dSoftElN"      ,  (name+"/dSoftElN;  "      +title+"#Delta SoftElN  ;Entries").c_str(), 100, -1.2, 1.2);
    dSoftEl         = dir.make<TH1F>("dSoftEl"       ,  (name+"/dSoftEl;   "      +title+"#Delta SoftEl   ;Entries").c_str(), 100, -1.2, 1.2);
    dcMVAv2         = dir.make<TH1F>("dcMVAv2"       ,  (name+"/dcMVAv2;   "      +title+"#Delta cMVAv2   ;Entries").c_str(), 100, -1.2, 1.2);
    dcMVAv2N        = dir.make<TH1F>("dcMVAv2N"      ,  (name+"/dcMVAv2N;  "      +title+"#Delta cMVAv2N  ;Entries").c_str(), 100, -1.2, 1.2);

    dbtagging = new btaggingDeltaHists("btags", dir, title);


    return;
} 

void jetDeltaHists::Fill(const std::shared_ptr<nTupleAnalysis::jet> &jet1, const std::shared_ptr<nTupleAnalysis::jet> &jet2, float weight){
  dPt      ->Fill(jet1->pt  - jet2->pt ,weight);
  dEta     ->Fill(jet1->eta - jet2->eta,weight);
  dPhi     ->Fill(jet1->p.DeltaPhi(jet2->p),weight);
  dR       ->Fill(jet1->p.DeltaR(jet2->p),weight);
  dcsv     ->Fill(jet1->CSVv2 - jet2->CSVv2,weight);
  dDeepcsv ->Fill(jet1->DeepCSV - jet2->DeepCSV,weight);


  ddeepFlavB    ->Fill(jet1->deepFlavB  - jet2->deepFlavB  , weight);
  dntracks      ->Fill(jet1->ntracks    - jet2->ntracks    ,weight);
  dnseltracks   ->Fill(jet1->nseltracks - jet2->nseltracks ,weight);
  dIp2N         ->Fill(jet1-> Ip2N      - jet2-> Ip2N      , weight);
  dIp2P         ->Fill(jet1-> Ip2P      - jet2-> Ip2P      , weight);
  dIp3N         ->Fill(jet1-> Ip3N      - jet2-> Ip3N      , weight);
  dIp3P         ->Fill(jet1-> Ip3P      - jet2-> Ip3P      , weight);
  dProbaN       ->Fill(jet1-> ProbaN    - jet2-> ProbaN    , weight);
  dProba        ->Fill(jet1-> Proba     - jet2-> Proba     , weight);
  dBprobN       ->Fill(jet1-> BprobN    - jet2-> BprobN    , weight);
  dBprob        ->Fill(jet1-> Bprob     - jet2-> Bprob     , weight);
  dSvx          ->Fill(jet1-> Svx       - jet2-> Svx       , weight);
  dSvxHP        ->Fill(jet1-> SvxHP     - jet2-> SvxHP     , weight);
  dCombIVF      ->Fill(jet1-> CombIVF   - jet2-> CombIVF   , weight);
  dCombIVF_N    ->Fill(jet1-> CombIVF_N - jet2-> CombIVF_N , weight);
  dSoftMuN      ->Fill(jet1-> SoftMuN   - jet2-> SoftMuN   , weight);
  dSoftMu       ->Fill(jet1-> SoftMu    - jet2-> SoftMu    , weight);
  dSoftElN      ->Fill(jet1-> SoftElN   - jet2-> SoftElN   , weight);
  dSoftEl       ->Fill(jet1-> SoftEl    - jet2-> SoftEl    , weight);
  dcMVAv2       ->Fill(jet1-> cMVAv2    - jet2-> cMVAv2    , weight);
  dcMVAv2N      ->Fill(jet1-> cMVAv2N   - jet2-> cMVAv2N   , weight);

  //
  //  Fill delta SVs
  //
  dbtagging->dsv_nSVs->Fill(jet1->svs.size() - jet2->svs.size(), weight);  
  for(const svPtr& sv: jet1->svs) {
    // assuming this is the right matching object !!
    std::shared_ptr<nTupleAnalysis::secondaryVertex> matchedSV = sv->matchedSV.lock();
    if(matchedSV) dbtagging->FillSVHists(sv, jet1, matchedSV, jet2, weight);
  }

  for(const trkTagVarPtr& trkTag: jet1->trkTagVars) {
    // assuming this is the right matching object !!
    const nTupleAnalysis::trkTagVarPtr trkTagMatch = trkTag->matchedTrkTagVar.lock();
    if(trkTagMatch) dbtagging->FillTrkTagVarHists(trkTag, trkTagMatch, weight);
  }

  if(jet1->tagVars && jet2->tagVars){
    dbtagging->FillTagVarHists(jet1->tagVars, jet2->tagVars, weight);
  }


  return;
}

jetDeltaHists::~jetDeltaHists(){} 
