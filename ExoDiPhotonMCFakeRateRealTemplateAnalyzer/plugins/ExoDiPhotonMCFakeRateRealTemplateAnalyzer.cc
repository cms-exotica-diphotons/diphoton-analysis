// -*- C++ -*-
//
// Package:    diphoton-analysis/ExoDiPhotonMCFakeRateRealTemplateAnalyzer
// Class:      ExoDiPhotonMCFakeRateRealTemplateAnalyzer
// 
/**\class ExoDiPhotonMCFakeRateRealTemplateAnalyzer ExoDiPhotonMCFakeRateRealTemplateAnalyzer.cc diphoton-analysis/ExoDiPhotonMCFakeRateRealTemplateAnalyzer/plugins/ExoDiPhotonMCFakeRateRealTemplateAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andrew Buccilli
//         Created:  Wed, 09 Mar 2016 17:59:12 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// from our CommomClasses
#include "diphoton-analysis/CommonClasses/interface/EventInfo.h"
#include "diphoton-analysis/CommonClasses/interface/TriggerInfo.h"
#include "diphoton-analysis/CommonClasses/interface/JetInfo.h"
#include "diphoton-analysis/CommonClasses/interface/PhotonID.h"
#include "diphoton-analysis/CommonClasses/interface/PhotonInfo.h"
#include "diphoton-analysis/CommonClasses/interface/GenParticleInfo.h"
#include "diphoton-analysis/CommonClasses/interface/VertexInfo.h"

// for TFileService, trees
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "TTree.h"

// for ECAL topology
#include "Geometry/CaloTopology/interface/CaloTopology.h"
#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"

// for EGM ID
#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"

// for photons
#include "DataFormats/PatCandidates/interface/Photon.h"

// for jets
#include "DataFormats/PatCandidates/interface/Jet.h"

// for genParticles
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

// for genEventInfo
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

// for deltaR
#include "DataFormats/Math/interface/deltaR.h"

// for trigger and filter decisions
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class ExoDiPhotonMCFakeRateRealTemplateAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit ExoDiPhotonMCFakeRateRealTemplateAnalyzer(const edm::ParameterSet&);
      ~ExoDiPhotonMCFakeRateRealTemplateAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

  // ----------member data ---------------------------
  // photon token
  edm::EDGetToken photonsMiniAODToken_;

  // genParticle token
  edm::EDGetTokenT<edm::View<reco::GenParticle> > genParticlesMiniAODToken_;
  
  // AK4 jet token and cuts
  edm::EDGetToken jetsMiniAODToken_;
  double jetPtThreshold;
  double jetEtaThreshold;

  // BeamHaloSummary token
  edm::EDGetToken beamHaloSummaryToken_;
    
  // ECAL recHits
  edm::InputTag recHitsEBTag_;
  edm::InputTag recHitsEETag_;
  edm::EDGetTokenT<EcalRecHitCollection> recHitsEBToken;
  edm::EDGetTokenT<EcalRecHitCollection> recHitsEEToken;

  // rho token
  edm::EDGetTokenT<double> rhoToken_;
  
  // rho variable
  double rho_;

  // EGM eff. areas
  EffectiveAreas effAreaChHadrons_;
  EffectiveAreas effAreaNeuHadrons_;
  EffectiveAreas effAreaPhotons_;

  // EGM ID decision tokens
  edm::EDGetTokenT<edm::ValueMap<bool> > phoLooseIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > phoMediumIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> > phoTightIdMapToken_;

  // Filter decisions token
  edm::EDGetToken filterDecisionToken_;

  // Trigger decisions token
  edm::EDGetToken triggerDecisionToken_;

  // Trigger prescales token
  edm::EDGetToken prescalesToken_;

  // vertex token
  edm::EDGetTokenT<reco::VertexCollection> verticesToken_;
  
  // output file name
  TString outputFile_;
  
  // number of events in sample
  uint32_t nEventsSample_;
  
  // trees
  TTree *fTree;

  // photons
  ExoDiPhotons::photonInfo_t fPhotonInfo;

  // jets
  ExoDiPhotons::jetInfo_t fJetInfo;

  //triggers
  ExoDiPhotons::triggerInfo_t fTriggerBitInfo;
  ExoDiPhotons::triggerInfo_t fTriggerPrescaleInfo;
  
  // event
  ExoDiPhotons::eventInfo_t fEventInfo;

  // gen event info token
  edm::EDGetTokenT<GenEventInfoProduct> genInfoToken_;

  // genParticles
  ExoDiPhotons::genParticleInfo_t fGenParticleInfo;

  // vertex collection
  ExoDiPhotons::vertexCollInfo_t fVertexCollInfo;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
ExoDiPhotonMCFakeRateRealTemplateAnalyzer::ExoDiPhotonMCFakeRateRealTemplateAnalyzer(const edm::ParameterSet& iConfig)
  : rhoToken_(consumes<double> (iConfig.getParameter<edm::InputTag>("rho"))),
    effAreaChHadrons_( (iConfig.getParameter<edm::FileInPath>("effAreaChHadFile")).fullPath() ),
    effAreaNeuHadrons_( (iConfig.getParameter<edm::FileInPath>("effAreaNeuHadFile")).fullPath() ),
    effAreaPhotons_( (iConfig.getParameter<edm::FileInPath>("effAreaPhoFile")).fullPath() ),
    phoLooseIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoLooseIdMap"))),
    phoMediumIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoMediumIdMap"))),
    phoTightIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoTightIdMap"))),
    outputFile_(TString(iConfig.getParameter<std::string>("outputFile"))),
    nEventsSample_(iConfig.getParameter<uint32_t>("nEventsSample")),
    genInfoToken_(consumes<GenEventInfoProduct>(iConfig.getParameter<edm::InputTag>("genInfo")))
{
  //now do what ever initialization is needed
   usesResource("TFileService");

   edm::Service<TFileService> fs;

  // tree for objects passing numerator or denominator definitions
  fTree = fs->make<TTree>("fTree","PhotonTree");
  fTree->Branch("Event",&fEventInfo,ExoDiPhotons::eventBranchDefString.c_str());
  fTree->Branch("Jet",&fJetInfo,ExoDiPhotons::jetBranchDefString.c_str());
  fTree->Branch("TriggerBit",&fTriggerBitInfo,ExoDiPhotons::triggerBranchDefString.c_str());
  fTree->Branch("TriggerPrescale",&fTriggerPrescaleInfo,ExoDiPhotons::triggerBranchDefString.c_str());
  fTree->Branch("Photon",&fPhotonInfo,ExoDiPhotons::photonBranchDefString.c_str());
  fTree->Branch("PhotonGenMatch",&fGenParticleInfo,ExoDiPhotons::genParticleBranchDefString.c_str());

  // vertex information branches
  fTree->Branch("VertexCollInfo.vx","std::vector<double>",&fVertexCollInfo.vx);
  fTree->Branch("VertexCollInfo.vy","std::vector<double>",&fVertexCollInfo.vy);
  fTree->Branch("VertexCollInfo.vz","std::vector<double>",&fVertexCollInfo.vz);
  fTree->Branch("VertexCollInfo.vxError","std::vector<double>",&fVertexCollInfo.vxError);
  fTree->Branch("VertexCollInfo.vyError","std::vector<double>",&fVertexCollInfo.vyError);
  fTree->Branch("VertexCollInfo.vzError","std::vector<double>",&fVertexCollInfo.vzError);
  fTree->Branch("VertexCollInfo.ndof","std::vector<double>",&fVertexCollInfo.ndof);
  fTree->Branch("VertexCollInfo.d0","std::vector<double>",&fVertexCollInfo.d0);
  fTree->Branch("VertexCollInfo.nTracks","std::vector<int>",&fVertexCollInfo.nTracks);
  fTree->Branch("VertexCollInfo.isFake","std::vector<int>",&fVertexCollInfo.isFake);
  
  // photon token
  photonsMiniAODToken_ = mayConsume<edm::View<pat::Photon> >(iConfig.getParameter<edm::InputTag>("photonsMiniAOD"));

  // genParticle token
  genParticlesMiniAODToken_ = mayConsume<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("genParticlesMiniAOD"));
  
  // AK4 jets token
  jetsMiniAODToken_ = mayConsume< edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("jetsMiniAOD"));
  jetPtThreshold = iConfig.getParameter<double>("jetPtThreshold");
  jetEtaThreshold = iConfig.getParameter<double>("jetEtaThreshold");
  
  // ECAL RecHits
  recHitsEBTag_ = iConfig.getUntrackedParameter<edm::InputTag>("RecHitsEBTag",edm::InputTag("reducedEgamma:reducedEBRecHits"));
  recHitsEETag_ = iConfig.getUntrackedParameter<edm::InputTag>("RecHitsEETag",edm::InputTag("reducedEgamma:reducedEERecHits"));
  recHitsEBToken = consumes <edm::SortedCollection<EcalRecHit> > (recHitsEBTag_);
  recHitsEEToken = consumes <edm::SortedCollection<EcalRecHit> > (recHitsEETag_);

  // BeamHaloSummary
  beamHaloSummaryToken_ = consumes<reco::BeamHaloSummary>( edm::InputTag("BeamHaloSummary") );

  // Filter decisions
  filterDecisionToken_ = consumes<edm::TriggerResults>( edm::InputTag("TriggerResults","","PAT") );

  // Trigger decisions
  triggerDecisionToken_ = consumes<edm::TriggerResults>( edm::InputTag("TriggerResults","","HLT") );

  // trigger prescales
  prescalesToken_ = consumes<pat::PackedTriggerPrescales>( edm::InputTag("patTrigger","","PAT") );

  // vertices
  verticesToken_ = consumes<reco::VertexCollection>( edm::InputTag("offlineSlimmedPrimaryVertices") );
}


ExoDiPhotonMCFakeRateRealTemplateAnalyzer::~ExoDiPhotonMCFakeRateRealTemplateAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
ExoDiPhotonMCFakeRateRealTemplateAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace pat;

  // ==========
  // EVENT INFO
  // ==========

  edm::Handle< reco::BeamHaloSummary > bhsHandle;
  iEvent.getByToken(beamHaloSummaryToken_,bhsHandle);
  const reco::BeamHaloSummary* bhs = &(*bhsHandle);
  
  ExoDiPhotons::InitEventInfo(fEventInfo);
  ExoDiPhotons::FillBasicEventInfo(fEventInfo, iEvent);
  ExoDiPhotons::FillBeamHaloEventInfo(fEventInfo, bhs);
  
  cout <<  "Run: " << iEvent.id().run() << ", LS: " <<  iEvent.id().luminosityBlock() << ", Event: " << iEvent.id().event() << endl;

  // ==============
  // GEN EVENT INFO
  // ==============

  // get genEventInfo
  edm::Handle<GenEventInfoProduct> genInfo;
  iEvent.getByToken(genInfoToken_,genInfo);
  
  ExoDiPhotons::FillGenEventInfo(fEventInfo, &(*genInfo));
  ExoDiPhotons::FillEventWeights(fEventInfo, outputFile_, nEventsSample_);
  
  // ====
  // JETS
  // ====
  
  ExoDiPhotons::InitJetInfo(fJetInfo);
  
  // add jet HT information
  edm::Handle< edm::View<pat::Jet> > jets;
  iEvent.getByToken(jetsMiniAODToken_,jets);
  
  ExoDiPhotons::FillJetInfo(fJetInfo, &(*jets), jetPtThreshold, jetEtaThreshold);

  // =====================
  // FILTER DECISION INFO
  // =====================

  edm::Handle<edm::TriggerResults> filtHandle;
  iEvent.getByToken(filterDecisionToken_,filtHandle);
  const edm::TriggerResults *filterResults = filtHandle.product();
  std::vector<std::string> trigNames = iEvent.triggerNames(*filterResults).triggerNames();

  int EEBadScFilterNum = -1;
  for (unsigned int i=0; i < trigNames.size(); i++){
    std::string tempName = trigNames.at(i);
    if (tempName == "Flag_eeBadScFilter"){
      EEBadScFilterNum = i;
      break;
    }
  }
  if (EEBadScFilterNum < 0) throw cms::Exception("FilterDecisionInfo") << "Cannot find Flag_eeBadScFilter in the filter decision object!! This must be investigated!!!";

  bool passEEBadScFilter = filterResults->accept(EEBadScFilterNum);

  // Go to next photon if this filter is not passed
  if (!passEEBadScFilter) {
    cout << "Event did not pass the EE Bad Supercrystal Filter, skip it!" << endl;
    return;
  }

  // =====================
  // TRIGGER DECISION INFO
  // =====================

  edm::Handle<edm::TriggerResults> triggerHandle;
  iEvent.getByToken(triggerDecisionToken_,triggerHandle);
  const edm::TriggerResults* triggerResults = triggerHandle.product();

  edm::Handle<pat::PackedTriggerPrescales> prescalesHandle;
  iEvent.getByToken(prescalesToken_,prescalesHandle);
  const pat::PackedTriggerPrescales* prescales = prescalesHandle.product();

  ExoDiPhotons::FillTriggerBits(fTriggerBitInfo, triggerResults, iEvent); // fill trigger bits into trigger bit branch
  ExoDiPhotons::FillTriggerPrescales(fTriggerPrescaleInfo, triggerResults, prescales, iEvent); // fill trigger prescale info in trigger prescale branch

  // ========
  // VERTICES
  // ========

  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByToken(verticesToken_,vertices);
  const reco::VertexCollection* vtxColl = vertices.product();
  ExoDiPhotons::FillVertexCollInfo(fVertexCollInfo,vtxColl);
  
  // ===
  // RHO
  // ===
  
  // Get rho
  edm::Handle< double > rhoH;
  iEvent.getByToken(rhoToken_,rhoH);
  rho_ = *rhoH;
  
  cout << "rho: " << rho_ << endl;

  // ======
  // EGM ID
  // ======
  
  // EGM ID decisions
  edm::Handle<edm::ValueMap<bool> > loose_id_decisions;
  iEvent.getByToken(phoLooseIdMapToken_ ,loose_id_decisions);
  edm::Handle<edm::ValueMap<bool> > medium_id_decisions;
  iEvent.getByToken(phoMediumIdMapToken_,medium_id_decisions);
  edm::Handle<edm::ValueMap<bool> > tight_id_decisions;
  iEvent.getByToken(phoTightIdMapToken_ ,tight_id_decisions);

  // =========
  // ECAL INFO
  // =========
  
  // ECAL RecHits
  edm::Handle<EcalRecHitCollection> recHitsEB;
  iEvent.getByToken(recHitsEBToken,recHitsEB);   
  edm::Handle<EcalRecHitCollection> recHitsEE;
  iEvent.getByToken(recHitsEEToken,recHitsEE);

  // ECAL Topology
  const CaloSubdetectorTopology* subDetTopologyEB_;
  const CaloSubdetectorTopology* subDetTopologyEE_;
  edm::ESHandle<CaloTopology> caloTopology;
  iSetup.get<CaloTopologyRecord>().get(caloTopology);
  subDetTopologyEB_ = caloTopology->getSubdetectorTopology(DetId::Ecal,EcalBarrel);
  subDetTopologyEE_ = caloTopology->getSubdetectorTopology(DetId::Ecal,EcalEndcap);

  // ============
  // GENPARTICLES
  // ============

  ExoDiPhotons::InitGenParticleInfo(fGenParticleInfo);
  
  // get genParticle collection
  Handle<edm::View<reco::GenParticle> > genParticles;
  iEvent.getByToken(genParticlesMiniAODToken_,genParticles);

  //for (edm::View<reco::GenParticle>::const_iterator gen = genParticles->begin(); gen != genParticles->end(); ++gen) {
  //for (size_t i = 0; i < genParticles->size(); ++i) {
  //const auto gen = genParticles->ptrAt(i);
  //if (gen->pt() > 50)
  //cout << "GenParticle: " << "pt = " << gen->pt() << "; eta = " << gen->eta() << "; phi = " << gen->phi() << endl;
  //} // end of genParticle loop
  
  // =======
  // PHOTONS
  // =======
  
  ExoDiPhotons::InitPhotonInfo(fPhotonInfo);
  
  // get photon collection
  edm::Handle<edm::View<pat::Photon> > photons;
  iEvent.getByToken(photonsMiniAODToken_,photons);

  bool print_photon_info = false;
  
  //for (edm::View<pat::Photon>::const_iterator pho = photons->begin(); pho != photons->end(); ++pho) {
  for (size_t i = 0; i < photons->size(); ++i) {
    const auto pho = photons->ptrAt(i);

    // print photon info
    if (print_photon_info) cout << "Photon: " << "pt = " << pho->pt() << "; eta = " << pho->eta() << "; phi = " << pho->phi() << endl;

    // deltaR cut
    double minDeltaR = 0.1;
    
    // no match when starting loop
    const reco::GenParticle *photonMatch = NULL;
    
    // loop through genParticles to find real photon matches
    //for (edm::View<reco::GenParticle>::const_iterator gen = genParticles->begin(); gen != genParticles->end(); ++gen) {
    for (size_t i = 0; i < genParticles->size(); ++i) {
      const auto gen = genParticles->ptrAt(i);

      // only consider matching to final state gen particles
      if (gen->status() != 1) continue;
      
      // find best final state photon match //with at least 60% agreement between pT (try to prevent the same gen photon matching to two reco photons)
      if (gen->pdgId() == 22) { /*&& gen->fromHardProcessFinalState() && fabs(1 - pho->pt()/gen->pt()) < 0.40*/
	double deltaR = reco::deltaR(pho->eta(),pho->phi(),gen->eta(),gen->phi());
	if (deltaR <= minDeltaR) {
	  //cout << "GenParticle fromHPFS match: Status = " << gen->status()  << "; ID = " << gen->pdgId() << "; pt = "
	  //<< gen->pt() << "; eta = " << gen->eta() << "; phi = " << gen->phi()  << "; deltaR = " << deltaRfromHP << endl;
	  minDeltaR = deltaR;
	  photonMatch = &(*gen);
	}
      }
      
    } // end of genParticle loop
    
    // ***************************************************************************
    // if photon match, determine if it came from a photon in the hard interaction
    // ***************************************************************************
    // consider all mothers when matching (no deltaR cut)
    double minMotherMatchDeltaR = 10000;
    int matchMotherIndex = 0;
    // check if each mother is a photon
    bool is_mother_photon = true;
    
    if (photonMatch) {

      if (print_photon_info)
	cout << "PhotonMatch START   : Status = " << photonMatch->status()  << "; ID = " << photonMatch->pdgId() << "; pt = "
	     << photonMatch->pt() << "; eta = " << photonMatch->eta() << "; phi = " << photonMatch->phi()  << "; deltaR = " << minDeltaR << endl;

      bool photon_check = true;
      
      // trace back match to hard interaction proton by finding mothers
      // each mother may have multiple mothers, so sole, "true" mother is best dR match among all mothers
      while (photonMatch->mother()) {
	for (unsigned int j = 0; j < photonMatch->numberOfMothers(); j++) {
	  double deltaR = reco::deltaR(photonMatch->eta(),photonMatch->phi(),photonMatch->mother(j)->eta(),photonMatch->mother(j)->phi());
	  if (print_photon_info)
	    cout << "\t    Mother " << j << ": Status = " << photonMatch->mother(j)->status()  << "; ID = " << photonMatch->mother(j)->pdgId() << "; pt = "
		 << photonMatch->mother(j)->pt() << "; eta = " << photonMatch->mother(j)->eta() << "; phi = " << photonMatch->mother(j)->phi()  << "; deltaR = " << deltaR << endl;
	  if (deltaR < minMotherMatchDeltaR) {
	    minMotherMatchDeltaR = deltaR;
	    matchMotherIndex = j;
	  }
	}
	// select best mother as sole mother
	photonMatch = (reco::GenParticle *) photonMatch->mother(matchMotherIndex);
	// stop checking for photon history when the interacting (incoming) parton is found
	if ((photonMatch->pdgId() == 21 || std::abs(photonMatch->pdgId() < 9)) && photonMatch->pt() == 0) photon_check = false;
	// check if each mother in photon's history is a photon until the incoming, interacting parton is found
	if (photon_check && photonMatch->pdgId() != 22) is_mother_photon = false;
	// print each mother
	if (print_photon_info)
	  cout << "PhotonMatch MOTHER "<< matchMotherIndex <<": Status = " << photonMatch->status()  << "; ID = " << photonMatch->pdgId() << "; pt = "
	       << photonMatch->pt() << "; eta = " << photonMatch->eta() << "; phi = " << photonMatch->phi()  << "; deltaR = " << minMotherMatchDeltaR << endl;
	// reset cut! (and index to be safe)
	minMotherMatchDeltaR = 10000;
	matchMotherIndex = 0;
      } // end while loop through mothers

      // if any mother is not a photon, then don't fill the match
      if (!is_mother_photon) cout << "Not a photon. Not filling match." << endl;
      
      // only fill tree if every mother is a photon; in particular, the hard interatciton particle is a photon
      if (is_mother_photon) {
	
	cout << "Real template photon." << endl;
	
	// fill genParticle info
	ExoDiPhotons::FillGenParticleInfo(fGenParticleInfo,photonMatch);
	
	// fill photon saturation
	fPhotonInfo.isSaturated = ExoDiPhotons::isSaturated(&(*pho), &(*recHitsEB), &(*recHitsEE), &(*subDetTopologyEB_), &(*subDetTopologyEE_));
	if (print_photon_info) cout << "isSat: " << fPhotonInfo.isSaturated << endl;
	
	// fill photon info
	ExoDiPhotons::FillBasicPhotonInfo(fPhotonInfo, &(*pho));
	ExoDiPhotons::FillPhotonIDInfo(fPhotonInfo, &(*pho), rho_, true, fPhotonInfo.isSaturated);
	
	// fill EGM ID info
	ExoDiPhotons::FillPhotonEGMidInfo(fPhotonInfo, &(*pho), rho_, effAreaChHadrons_, effAreaNeuHadrons_, effAreaPhotons_);
	fPhotonInfo.passEGMLooseID  = (*loose_id_decisions)[pho];
	fPhotonInfo.passEGMMediumID = (*medium_id_decisions)[pho];
	fPhotonInfo.passEGMTightID  = (*tight_id_decisions)[pho];
	
	// fill our tree
	if ( ExoDiPhotons::passNumeratorCandCut(&(*pho), rho_, true) ) fTree->Fill();
      }
      
    } // end if photonMatch
    else cout << "No photon match in dR <= " << minDeltaR << endl;

  } // end of photon loop

  cout << endl;
  
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
ExoDiPhotonMCFakeRateRealTemplateAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ExoDiPhotonMCFakeRateRealTemplateAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ExoDiPhotonMCFakeRateRealTemplateAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ExoDiPhotonMCFakeRateRealTemplateAnalyzer);
