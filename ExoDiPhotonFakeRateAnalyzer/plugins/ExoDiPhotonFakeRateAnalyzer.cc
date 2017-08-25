// -*- C++ -*-
//
// Package:    DiPhotonAnalysis/ExoDiPhotonFakeRateAnalyzer
// Class:      ExoDiPhotonFakeRateAnalyzer
// 
/**\class ExoDiPhotonFakeRateAnalyzer ExoDiPhotonFakeRateAnalyzer.cc DiPhotonAnalysis/ExoDiPhotonFakeRateAnalyzer/plugins/ExoDiPhotonFakeRateAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andrew Buccilli
//         Created:  Wed, 02 Mar 2016 14:43:55 GMT
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

class ExoDiPhotonFakeRateAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit ExoDiPhotonFakeRateAnalyzer(const edm::ParameterSet&);
      ~ExoDiPhotonFakeRateAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

  // ----------member data ---------------------------
  
  // miniAOD photon token
  edm::EDGetToken photonsMiniAODToken_;

  // AK4 jet token and cuts
  edm::EDGetToken jetsMiniAODToken_;
  double jetPtThreshold;
  double jetEtaThreshold;
  bool   isReMINIAOD_;
    
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

  // BeamHaloSummary token
  edm::EDGetToken beamHaloSummaryToken_;

  // Filter decisions token
  edm::EDGetToken filterDecisionToken_;

  // Trigger decisions token
  edm::EDGetToken triggerDecisionToken_;

  // Trigger prescales token
  edm::EDGetToken prescalesToken_;

    // vertex token
  edm::EDGetTokenT<reco::VertexCollection> verticesToken_;
  
  // trees
  TTree *fTree;

  // photons
  ExoDiPhotons::photonInfo_t fPhotonInfo;

  // jets
  ExoDiPhotons::jetInfo_t fJetInfo;
  
  // event
  ExoDiPhotons::eventInfo_t fEventInfo;

  //triggers
  ExoDiPhotons::triggerInfo_t fTriggerBitInfo;
  ExoDiPhotons::triggerInfo_t fTriggerPrescaleInfo;
  
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
ExoDiPhotonFakeRateAnalyzer::ExoDiPhotonFakeRateAnalyzer(const edm::ParameterSet& iConfig)
  : isReMINIAOD_(iConfig.getParameter<bool>("isReMINIAOD")),
    rhoToken_(consumes<double> (iConfig.getParameter<edm::InputTag>("rho"))),
    effAreaChHadrons_( (iConfig.getParameter<edm::FileInPath>("effAreaChHadFile")).fullPath() ),
    effAreaNeuHadrons_( (iConfig.getParameter<edm::FileInPath>("effAreaNeuHadFile")).fullPath() ),
    effAreaPhotons_( (iConfig.getParameter<edm::FileInPath>("effAreaPhoFile")).fullPath() ),
    phoLooseIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoLooseIdMap"))),
    phoMediumIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoMediumIdMap"))),
    phoTightIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoTightIdMap")))
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
  
  // MiniAOD tokens
  photonsMiniAODToken_ = mayConsume<edm::View<pat::Photon> >(iConfig.getParameter<edm::InputTag>("photonsMiniAOD"));

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
  filterDecisionToken_ = consumes<edm::TriggerResults>( edm::InputTag("TriggerResults","",(isReMINIAOD_)?("PAT"):("RECO")) );

  // Trigger decisions
  triggerDecisionToken_ = consumes<edm::TriggerResults>( edm::InputTag("TriggerResults","","HLT") );

  // trigger prescales
  prescalesToken_ = consumes<pat::PackedTriggerPrescales>( edm::InputTag("patTrigger","",(isReMINIAOD_)?("PAT"):("RECO")) );

  // vertices
  verticesToken_ = consumes<reco::VertexCollection>( edm::InputTag("offlineSlimmedPrimaryVertices") );
  
}


ExoDiPhotonFakeRateAnalyzer::~ExoDiPhotonFakeRateAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
ExoDiPhotonFakeRateAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace pat;

  // =====
  // EVENT
  // =====

  edm::Handle< reco::BeamHaloSummary > bhsHandle;
  iEvent.getByToken(beamHaloSummaryToken_,bhsHandle);
  const reco::BeamHaloSummary* bhs = &(*bhsHandle);
  
  ExoDiPhotons::InitEventInfo(fEventInfo);
  ExoDiPhotons::FillBasicEventInfo(fEventInfo, iEvent);
  ExoDiPhotons::FillBeamHaloEventInfo(fEventInfo, bhs);
  
  cout <<  "Run: " << iEvent.id().run() << ", LS: " <<  iEvent.id().luminosityBlock() << ", Event: " << iEvent.id().event() << endl;

  // ===
  // JET
  // ===

  ExoDiPhotons::InitJetInfo(fJetInfo);
  
  // add jet HT information
  edm::Handle< edm::View<pat::Jet> > jets;
  iEvent.getByToken(jetsMiniAODToken_,jets);

  ExoDiPhotons::FillJetInfo(fJetInfo, &(*jets), jetPtThreshold, jetEtaThreshold);

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
  if (!passEEBadScFilter){
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


  // =======
  // PHOTONS
  // =======
  
  ExoDiPhotons::InitPhotonInfo(fPhotonInfo);
  
  // Get pat::Photon collection
  edm::Handle<edm::View<pat::Photon> > photons;
  iEvent.getByToken(photonsMiniAODToken_,photons);
  
  //for (edm::View<pat::Photon>::const_iterator pho = photons->begin(); pho != photons->end(); ++pho) {
  for (size_t i = 0; i < photons->size(); ++i){
    const auto pho = photons->ptrAt(i);

    // print photon info
    cout << "Photon: " << "pt = " << pho->pt() << "; eta = " << pho->eta() << "; phi = " << pho->phi() << endl;
    
    // fill photon saturation
    fPhotonInfo.isSaturated = ExoDiPhotons::isSaturated(&(*pho), &(*recHitsEB), &(*recHitsEE), &(*subDetTopologyEB_), &(*subDetTopologyEE_));
    cout << "isSat: " << fPhotonInfo.isSaturated << endl;

    // fill photon info
    ExoDiPhotons::FillBasicPhotonInfo(fPhotonInfo, &(*pho));
    ExoDiPhotons::FillPhotonIDInfo(fPhotonInfo, &(*pho), rho_,false,fPhotonInfo.isSaturated);
    
    // fill EGM ID info
    ExoDiPhotons::FillPhotonEGMidInfo(fPhotonInfo, &(*pho), rho_, effAreaChHadrons_, effAreaNeuHadrons_, effAreaPhotons_);
    fPhotonInfo.passEGMLooseID  = (*loose_id_decisions)[pho];
    fPhotonInfo.passEGMMediumID = (*medium_id_decisions)[pho];
    fPhotonInfo.passEGMTightID  = (*tight_id_decisions)[pho];

    // fill our tree
    if ( ExoDiPhotons::passNumeratorCandCut(&(*pho), rho_,false) ||
         ExoDiPhotons::passDenominatorCut(&(*pho), rho_, false, fPhotonInfo.isSaturated)
       ) fTree->Fill();
										  
  } // end of photon loop
  
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
ExoDiPhotonFakeRateAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ExoDiPhotonFakeRateAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ExoDiPhotonFakeRateAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ExoDiPhotonFakeRateAnalyzer);
