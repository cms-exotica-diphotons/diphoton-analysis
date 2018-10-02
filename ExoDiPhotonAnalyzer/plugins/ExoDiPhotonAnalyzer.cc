// -*- C++ -*-
//
// Package:    diphoton-analysis/ExoDiPhotonBackgroundAnalyzer
// Class:      ExoDiPhotonBackgroundAnalyzer
// 
/**\class ExoDiPhotonBackgroundAnalyzer ExoDiPhotonBackgroundAnalyzer.cc diphoton-analysis/ExoDiPhotonBackgroundAnalyzer/plugins/ExoDiPhotonBackgroundAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andrew Buccilli
//         Created:  Tue, 05 Apr 2016 22:30:14 GMT
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

// from our CommonClasses
#include "diphoton-analysis/CommonClasses/interface/EventInfo.h"
#include "diphoton-analysis/CommonClasses/interface/BeamSpotInfo.h"
#include "diphoton-analysis/CommonClasses/interface/VertexInfo.h"
#include "diphoton-analysis/CommonClasses/interface/TriggerInfo.h"
#include "diphoton-analysis/CommonClasses/interface/JetInfo.h"
#include "diphoton-analysis/CommonClasses/interface/PhotonID.h"
#include "diphoton-analysis/CommonClasses/interface/PhotonInfo.h"
#include "diphoton-analysis/CommonClasses/interface/GenParticleInfo.h"
#include "diphoton-analysis/CommonClasses/interface/DiPhotonInfo.h"
#include "diphoton-analysis/CommonClasses/interface/PileupInfo.h"

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

class ExoDiPhotonAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit ExoDiPhotonAnalyzer(const edm::ParameterSet&);
      ~ExoDiPhotonAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
      void fillGenInfo(const edm::Handle<edm::View<reco::GenParticle> > genParticles, const std::vector<edm::Ptr<pat::Photon>> selectedPhotons);
      void photonFiller(const std::vector<edm::Ptr<pat::Photon>>& photons, const edm::Handle<EcalRecHitCollection>& recHitsEB, const edm::Handle<EcalRecHitCollection>& recHitsEE, 
			const edm::Handle<edm::ValueMap<bool> >* id_decisions,
			ExoDiPhotons::photonInfo_t& photon1Info, ExoDiPhotons::photonInfo_t& photon2Info, ExoDiPhotons::diphotonInfo_t& diphotonInfo);
      void sherpaDiphotonFiller(const edm::Handle<edm::View<reco::GenParticle> > genParticles,
				std::vector<edm::Ptr<const reco::GenParticle>> sherpaDiphotons);
      void mcTruthFiller(const pat::Photon *photon, ExoDiPhotons::photonInfo_t& photonInfo, const edm::Handle<edm::View<reco::GenParticle> > genParticles);
  
   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

  // ----------member data ---------------------------
  // genParticle token
  edm::EDGetTokenT<edm::View<reco::GenParticle> > genParticlesMiniAODToken_;
  
  // miniAOD photon token
  edm::EDGetToken photonsMiniAODToken_;
  double fMinPt;

  // AK4 jet token and cuts
  edm::EDGetToken jetsMiniAODToken_;
  double jetPtThreshold;
  double jetEtaThreshold;
    
  // ECAL recHits
  edm::InputTag recHitsEBTag_;
  edm::InputTag recHitsEETag_;
  edm::EDGetTokenT<EcalRecHitCollection> recHitsEBToken;
  edm::EDGetTokenT<EcalRecHitCollection> recHitsEEToken;

  // BeamHaloSummary token
  edm::EDGetToken beamHaloSummaryToken_;

  // Filter decisions token
  edm::EDGetToken filterDecisionToken_;

  // trigger decisions token
  edm::EDGetToken triggerDecisionToken_;

  // trigger prescales token
  edm::EDGetToken prescalesToken_;

  // rho token
  edm::EDGetTokenT<double> rhoToken_;
  
  // vertex token
  edm::EDGetTokenT<reco::VertexCollection> verticesToken_;

  // Pileup summary token
  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > pileupToken_;

  // beam spot token
  edm::EDGetTokenT<reco::BeamSpot> beamSpotToken_;

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
  
  // output file name
  TString outputFile_;
  // number of events in sample
  uint32_t nEventsSample_;

  // trees
  TTree *fTree;
  TTree *fSherpaGenTree;

  // photons (all good)
  ExoDiPhotons::photonInfo_t fPhoton1Info; // leading
  ExoDiPhotons::photonInfo_t fPhoton2Info; // subleading

  // photons (separated by whether each of the two leading photons are true or fake)
  ExoDiPhotons::photonInfo_t fTrueOrFakePhoton1Info[2][2]; // leading, all combinations: TT, FT, TF and FF
  ExoDiPhotons::photonInfo_t fTrueOrFakePhoton2Info[2][2]; // subleading, all combinations: TT, FT, TF and FF

  // jets
  ExoDiPhotons::jetInfo_t fJetInfo;
  
  // event
  ExoDiPhotons::eventInfo_t fEventInfo;

  // vertex
  ExoDiPhotons::vertexInfo_t fVertex0Info;
  ExoDiPhotons::vertexInfo_t fPrimaryVertexInfo;

  // beam spot
  ExoDiPhotons::beamSpotInfo_t fBeamSpotInfo;

  // triggers
  ExoDiPhotons::triggerInfo_t fTriggerBitInfo;
  ExoDiPhotons::triggerInfo_t fTriggerPrescaleInfo;

  // gen event info token
  edm::EDGetTokenT<GenEventInfoProduct> genInfoToken_;

  // flag to determine if sample is data or MC
  bool isMC_;

  // flag to determine if MC sample is used for closure test
  bool isClosureTest_;
  
  // flag to determine if sample is reco or re-reco
  bool isReMINIAOD_;

  // genParticles
  ExoDiPhotons::genParticleInfo_t fGenPhoton1Info; // leading
  ExoDiPhotons::genParticleInfo_t fGenPhoton2Info; // subleading

  // diphotons
  ExoDiPhotons::diphotonInfo_t fDiphotonInfo; // all good photons
  // photons (separated by whether each of the two leading photons are true or fake)
  ExoDiPhotons::diphotonInfo_t fTrueOrFakeDiphotonInfo[2][2];

  // gen diphoton (two true)
  ExoDiPhotons::diphotonInfo_t fGenDiphotonInfo;
  // sherpa gen information
  ExoDiPhotons::genParticleInfo_t fSherpaGenPhoton1Info; // leading
  ExoDiPhotons::genParticleInfo_t fSherpaGenPhoton2Info; // subleading
  ExoDiPhotons::diphotonInfo_t fSherpaGenDiphotonInfo;

  const CaloSubdetectorTopology* subDetTopologyEB_;
  const CaloSubdetectorTopology* subDetTopologyEE_;

  // status flags
  bool isGood_;
  bool isTT_;
  bool isTF_;
  bool isFT_;
  bool isFF_;
  bool isSherpaDiphoton_;

  // extra variables that need to be handled by hand
  double SherpaGenPhoton0_iso_;
  double SherpaGenPhoton1_iso_;
  double SherpaWeightAll_;
  double isolationConeR_;

  // number of reconstructed primary vertices
  int nPV_;

  enum {
    LOOSE = 0,
    MEDIUM = 1,
    TIGHT = 2
  };

  enum {
    FAKE = 0,
    TRUE = 1
  };
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
ExoDiPhotonAnalyzer::ExoDiPhotonAnalyzer(const edm::ParameterSet& iConfig)
  : rhoToken_(consumes<double> (iConfig.getParameter<edm::InputTag>("rho"))),
    verticesToken_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertices"))),
    beamSpotToken_(consumes<reco::BeamSpot>(iConfig.getParameter<edm::InputTag>("beamSpot"))),
    effAreaChHadrons_( (iConfig.getParameter<edm::FileInPath>("effAreaChHadFile")).fullPath() ),
    effAreaNeuHadrons_( (iConfig.getParameter<edm::FileInPath>("effAreaNeuHadFile")).fullPath() ),
    effAreaPhotons_( (iConfig.getParameter<edm::FileInPath>("effAreaPhoFile")).fullPath() ),
    phoLooseIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoLooseIdMap"))),
    phoMediumIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoMediumIdMap"))),
    phoTightIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoTightIdMap"))),
    outputFile_(TString(iConfig.getParameter<std::string>("outputFile"))),
    nEventsSample_(iConfig.getParameter<uint32_t>("nEventsSample")),
    genInfoToken_(consumes<GenEventInfoProduct>(iConfig.getParameter<edm::InputTag>("genInfo"))),
    isMC_(iConfig.getParameter<bool>("isMC")),
    isClosureTest_(iConfig.getParameter<bool>("isClosureTest")),
    isReMINIAOD_(iConfig.getParameter<bool>("isReMINIAOD")),
    isolationConeR_(iConfig.getParameter<double>("isolationConeR"))
{
  //now do what ever initialization is needed
  usesResource("TFileService");

  edm::Service<TFileService> fs;
  
  // tree for objects passing numerator or denominator definitions
  fTree = fs->make<TTree>("fTree","DiPhotonTree");
  fTree->Branch("Event",&fEventInfo,ExoDiPhotons::eventBranchDefString.c_str());
  fTree->Branch("BeamSpot",&fBeamSpotInfo,ExoDiPhotons::beamSpotBranchDefString.c_str());
  fTree->Branch("Vertex0",&fVertex0Info,ExoDiPhotons::vertexBranchDefString.c_str());
  fTree->Branch("PrimaryVertex",&fPrimaryVertexInfo,ExoDiPhotons::vertexBranchDefString.c_str());
  fTree->Branch("Jet",&fJetInfo,ExoDiPhotons::jetBranchDefString.c_str());
  fTree->Branch("TriggerBit",&fTriggerBitInfo,ExoDiPhotons::triggerBranchDefString.c_str());
  fTree->Branch("TriggerPrescale",&fTriggerPrescaleInfo,ExoDiPhotons::triggerBranchDefString.c_str());
  fTree->Branch("Photon1",&fPhoton1Info,ExoDiPhotons::photonBranchDefString.c_str());
  fTree->Branch("Photon2",&fPhoton2Info,ExoDiPhotons::photonBranchDefString.c_str());
  fTree->Branch("GenPhoton1",&fGenPhoton1Info,ExoDiPhotons::genParticleBranchDefString.c_str());
  fTree->Branch("GenPhoton2",&fGenPhoton2Info,ExoDiPhotons::genParticleBranchDefString.c_str());
  fTree->Branch("Diphoton",&fDiphotonInfo,ExoDiPhotons::diphotonBranchDefString.c_str());
  fTree->Branch("GenDiphoton",&fGenDiphotonInfo,ExoDiPhotons::diphotonBranchDefString.c_str());

  isSherpaDiphoton_ = outputFile_.Contains("GGJets_M");
  // need a separate branch for sherpa photons so that k-factor reweighting can be applied
  // even if there is no RECO match
  if(isSherpaDiphoton_) {
    fSherpaGenTree = fs->make<TTree>("fSherpaGenTree", "SherpaGenTree");
    fSherpaGenTree->Branch("SherpaGenPhoton1",&fSherpaGenPhoton1Info,ExoDiPhotons::genParticleBranchDefString.c_str());
    fSherpaGenTree->Branch("SherpaGenPhoton2",&fSherpaGenPhoton2Info,ExoDiPhotons::genParticleBranchDefString.c_str());
    fSherpaGenTree->Branch("SherpaGenDiphoton",&fSherpaGenDiphotonInfo,ExoDiPhotons::diphotonBranchDefString.c_str());
    // these are actually correct! the ntuple uses indices 1 and 2
    // but the C++ code uses indices 0 and 1
    fSherpaGenTree->Branch("SherpaGenPhoton1_iso", &SherpaGenPhoton0_iso_);
    fSherpaGenTree->Branch("SherpaGenPhoton2_iso", &SherpaGenPhoton1_iso_);
    // This is a duplicate of the value in the main tree.
    // It is copied here to for convenience.
    fSherpaGenTree->Branch("weightAll", &SherpaWeightAll_);
  }

  // true and true photon
  fTree->Branch("TTPhoton1",&(fTrueOrFakePhoton1Info[TRUE][TRUE]),ExoDiPhotons::photonBranchDefString.c_str());
  fTree->Branch("TTPhoton2",&(fTrueOrFakePhoton2Info[TRUE][TRUE]),ExoDiPhotons::photonBranchDefString.c_str());
  fTree->Branch("TTDiphoton",&(fTrueOrFakeDiphotonInfo[TRUE][TRUE]),ExoDiPhotons::diphotonBranchDefString.c_str());

  // true and fake photon
  fTree->Branch("TFPhoton1",&(fTrueOrFakePhoton1Info[TRUE][FAKE]),ExoDiPhotons::photonBranchDefString.c_str());
  fTree->Branch("TFPhoton2",&(fTrueOrFakePhoton2Info[TRUE][FAKE]),ExoDiPhotons::photonBranchDefString.c_str());
  fTree->Branch("TFDiphoton",&(fTrueOrFakeDiphotonInfo[TRUE][FAKE]),ExoDiPhotons::diphotonBranchDefString.c_str());

  // fake and true photon
  fTree->Branch("FTPhoton1",&(fTrueOrFakePhoton1Info[FAKE][TRUE]),ExoDiPhotons::photonBranchDefString.c_str());
  fTree->Branch("FTPhoton2",&(fTrueOrFakePhoton2Info[FAKE][TRUE]),ExoDiPhotons::photonBranchDefString.c_str());
  fTree->Branch("FTDiphoton",&(fTrueOrFakeDiphotonInfo[FAKE][TRUE]),ExoDiPhotons::diphotonBranchDefString.c_str());

  // fake and fake photon
  fTree->Branch("FFPhoton1",&(fTrueOrFakePhoton1Info[FAKE][FAKE]),ExoDiPhotons::photonBranchDefString.c_str());
  fTree->Branch("FFPhoton2",&(fTrueOrFakePhoton2Info[FAKE][FAKE]),ExoDiPhotons::photonBranchDefString.c_str());
  fTree->Branch("FFDiphoton",&(fTrueOrFakeDiphotonInfo[FAKE][FAKE]),ExoDiPhotons::diphotonBranchDefString.c_str());

  fTree->Branch("isGood", &isGood_);
  fTree->Branch("isTT", &isTT_);
  fTree->Branch("isTF", &isTF_);
  fTree->Branch("isFT", &isFT_);
  fTree->Branch("isFF", &isFF_);

  // number of reconstructed primary vertices
  fTree->Branch("nPV", &nPV_);

  // photon token
  photonsMiniAODToken_ = mayConsume<edm::View<pat::Photon> >(iConfig.getParameter<edm::InputTag>("photonsMiniAOD"));
  fMinPt = iConfig.getParameter<double>("minPhotonPt");

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

  pileupToken_ = consumes<std::vector<PileupSummaryInfo> >( edm::InputTag("slimmedAddPileupInfo") );

  // Filter decisions (created in "PAT" process in MC but "RECO" in data)
  filterDecisionToken_ = consumes<edm::TriggerResults>( edm::InputTag("TriggerResults","",(isMC_||isReMINIAOD_)?("PAT"):("RECO")) );

  // Trigger decisions
  triggerDecisionToken_ = consumes<edm::TriggerResults>( edm::InputTag("TriggerResults","","HLT") );

  // trigger prescales
  prescalesToken_ = consumes<pat::PackedTriggerPrescales>( edm::InputTag("patTrigger","",(isMC_||isReMINIAOD_)?("PAT"):("RECO")) );

  // set appropriate year (used for pileup reweighting)
  if(outputFile_.Contains("2015")) year = 2015;
  if(outputFile_.Contains("2016")) year = 2016;
}


ExoDiPhotonAnalyzer::~ExoDiPhotonAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
ExoDiPhotonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace pat;
  using namespace reco;

  isGood_ = isTT_ = isTF_ = isFT_ = isFF_ = false;
  nPV_ = 0;
  // set to a large value so that photons will not be considered
  // isolated by default
  SherpaGenPhoton0_iso_ = SherpaGenPhoton1_iso_ = 9999.99;

  // ==========
  // EVENT INFO
  // ==========

  edm::Handle< reco::BeamHaloSummary > bhsHandle;
  iEvent.getByToken(beamHaloSummaryToken_,bhsHandle);
  const reco::BeamHaloSummary* bhs = &(*bhsHandle);

  
  ExoDiPhotons::InitEventInfo(fEventInfo);
  ExoDiPhotons::FillBasicEventInfo(fEventInfo, iEvent);
  ExoDiPhotons::FillBeamHaloEventInfo(fEventInfo, bhs);
  
  //  cout <<  "Run: " << iEvent.id().run() << ", LS: " <<  iEvent.id().luminosityBlock() << ", Event: " << iEvent.id().event() << endl;

  // ==============
  // GEN EVENT INFO
  // ==============

  // get genEventInfo
  edm::Handle<GenEventInfoProduct> genInfo;
  edm::Handle<std::vector< PileupSummaryInfo > > puSummary;
  if(isMC_) {
    iEvent.getByToken(genInfoToken_,genInfo);
    iEvent.getByToken(pileupToken_, puSummary);
    ExoDiPhotons::FillGenEventInfo(fEventInfo, &(*genInfo));
    ExoDiPhotons::FillPileupInfo(fEventInfo, &(*puSummary));
  }
  ExoDiPhotons::FillEventWeights(fEventInfo, outputFile_, nEventsSample_);

  // =========
  // BEAM SPOT
  // =========

  ExoDiPhotons::InitBeamSpotInfo(fBeamSpotInfo);

  edm::Handle<reco::BeamSpot> beamSpotHandle;
  iEvent.getByToken(beamSpotToken_,beamSpotHandle);

  ExoDiPhotons::FillBeamSpotInfo(fBeamSpotInfo,&(*beamSpotHandle));

  // ========
  // VERTICES
  // ========

  ExoDiPhotons::InitVertexInfo(fVertex0Info);
  ExoDiPhotons::InitVertexInfo(fPrimaryVertexInfo);

  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByToken(verticesToken_,vertices);

  // fill vertex0
  ExoDiPhotons::FillVertexInfo(fVertex0Info,&(vertices->at(0)));
  
  // select the primary vertex, if any
  const reco::Vertex *myPV = &(vertices->front());
  bool foundPV = false;
  for(unsigned int i = 0; i < vertices->size(); i++){
    if(vertices->at(i).isValid() && !vertices->at(i).isFake()){
      if (!foundPV) {
	myPV = &(vertices->at(i));
	foundPV = true;
      }
      nPV_++;
    }
  }

  // fill vertex0
  ExoDiPhotons::FillVertexInfo(fPrimaryVertexInfo,&(*myPV));

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

  // ===
  // RHO
  // ===
  
  // Get rho
  edm::Handle< double > rhoH;
  iEvent.getByToken(rhoToken_,rhoH);
  rho_ = *rhoH;
  
  //  cout << "rho: " << rho_ << endl;

  // ======
  // EGM ID
  // ======
  
  edm::Handle<edm::ValueMap<bool> > id_decisions[3];
  iEvent.getByToken(phoLooseIdMapToken_, id_decisions[LOOSE]);
  iEvent.getByToken(phoMediumIdMapToken_, id_decisions[MEDIUM]);
  iEvent.getByToken(phoTightIdMapToken_ , id_decisions[TIGHT]);

  // =========
  // ECAL INFO
  // =========
  
  // ECAL RecHits
  edm::Handle<EcalRecHitCollection> recHitsEB;
  iEvent.getByToken(recHitsEBToken,recHitsEB);   
  edm::Handle<EcalRecHitCollection> recHitsEE;
  iEvent.getByToken(recHitsEEToken,recHitsEE);

  // ECAL Topology
  edm::ESHandle<CaloTopology> caloTopology;
  iSetup.get<CaloTopologyRecord>().get(caloTopology);
  subDetTopologyEB_ = caloTopology->getSubdetectorTopology(DetId::Ecal,EcalBarrel);
  subDetTopologyEE_ = caloTopology->getSubdetectorTopology(DetId::Ecal,EcalEndcap);

  // =========
  // DIPHOTONS
  // =========

  ExoDiPhotons::InitDiphotonInfo(fDiphotonInfo);
  ExoDiPhotons::InitDiphotonInfo(fTrueOrFakeDiphotonInfo[0][0]);
  ExoDiPhotons::InitDiphotonInfo(fTrueOrFakeDiphotonInfo[0][1]);
  ExoDiPhotons::InitDiphotonInfo(fTrueOrFakeDiphotonInfo[1][0]);
  ExoDiPhotons::InitDiphotonInfo(fTrueOrFakeDiphotonInfo[1][1]);
  if(isMC_) ExoDiPhotons::InitDiphotonInfo(fGenDiphotonInfo);
  
  // ============
  // GENPARTICLES
  // ============

  Handle<edm::View<reco::GenParticle> > genParticles;
  if(isMC_) {
    ExoDiPhotons::InitGenParticleInfo(fGenPhoton1Info);
    ExoDiPhotons::InitGenParticleInfo(fGenPhoton2Info);

    // get genParticle collection
    iEvent.getByToken(genParticlesMiniAODToken_,genParticles);
  }
  if(isSherpaDiphoton_) {
    std::vector<edm::Ptr<const reco::GenParticle>> sherpaDiphotons;

    // find diphoton candidates
    for(size_t i=0; i<genParticles->size(); i++) {
      edm::Ptr<reco::GenParticle> gen = genParticles->ptrAt(i);
      if(gen->status()==3 && gen->pdgId()==22) sherpaDiphotons.push_back(gen);
    }

    // the following assumes that we have exactly two photons
    if(sherpaDiphotons.size()==2) sherpaDiphotonFiller(genParticles, sherpaDiphotons);
    else throw cms::Exception("Should always have exactly two photons with status==3 in the diphoton sample");
  }

  // =======
  // PHOTONS
  // =======
   
  ExoDiPhotons::InitPhotonInfo(fPhoton1Info);
  ExoDiPhotons::InitPhotonInfo(fPhoton2Info);
  
  // loop over combinations of true and fake
  for(unsigned int i=0; i<2; i++) {
    for(unsigned int j=0; j<2; j++) {
      ExoDiPhotons::InitPhotonInfo(fTrueOrFakePhoton1Info[i][j]);
      ExoDiPhotons::InitPhotonInfo(fTrueOrFakePhoton2Info[i][j]);
    }
  }

  // get photon collection
  edm::Handle<edm::View<pat::Photon> > photons;
  iEvent.getByToken(photonsMiniAODToken_,photons);

  // check if photon in loop is saturated
  bool isSat = false;

  // pointer to photon in collection that passes high pt ID
  std::vector<edm::Ptr<pat::Photon>> goodPhotons;
  std::vector<edm::Ptr<pat::Photon>> selectedPhotons[2][2]; // combinations of real and fake for both leading candidates
    
  std::vector<std::pair<edm::Ptr<pat::Photon>, int> > realAndFakePhotons;

  //for (edm::View<pat::Photon>::const_iterator pho = photons->begin(); pho != photons->end(); ++pho) {
  for (size_t i = 0; i < photons->size(); ++i) {
    const auto pho = photons->ptrAt(i);
    
    // print photon info
    //    cout << "Photon: " << "pt = " << pho->pt() << "; eta = " << pho->eta() << "; phi = " << pho->phi() << endl;
    
    // check if photon is saturated
    isSat = ExoDiPhotons::isSaturated(&(*pho), &(*recHitsEB), &(*recHitsEE), &(*subDetTopologyEB_), &(*subDetTopologyEE_));

    bool passID = ExoDiPhotons::passHighPtID(&(*pho), rho_, isSat);
    bool denominatorObject = ExoDiPhotons::passDenominatorCut(&(*pho), rho_, isSat);
    // fill photons that pass high pt ID
    if(passID) {
      goodPhotons.push_back(pho);
      realAndFakePhotons.push_back(std::pair<edm::Ptr<pat::Photon>, int>(pho, TRUE));
    }
    if(denominatorObject) {
      realAndFakePhotons.push_back(std::pair<edm::Ptr<pat::Photon>, int>(pho, FAKE));
    }
  } // end of photon loop

  // sort vector of photons by pt
  sort(goodPhotons.begin(),goodPhotons.end(),ExoDiPhotons::comparePhotonsByPt);
  sort(realAndFakePhotons.begin(), realAndFakePhotons.end(), ExoDiPhotons::comparePhotonPairsByPt);

  // sort events by whether the leading two photons are true or fake
  if(realAndFakePhotons.size()>=2) {
    // "first" is the photon candidate, "second" is "TRUE" or "FAKE"
    int photon1TrueOrFake = realAndFakePhotons.at(0).second;
    int photon2TrueOrFake = realAndFakePhotons.at(1).second;
    selectedPhotons[photon1TrueOrFake][photon2TrueOrFake].push_back(realAndFakePhotons.at(0).first);
    selectedPhotons[photon1TrueOrFake][photon2TrueOrFake].push_back(realAndFakePhotons.at(1).first);
    photonFiller(selectedPhotons[photon1TrueOrFake][photon2TrueOrFake],
		 recHitsEB, recHitsEE, &id_decisions[0],
		 fTrueOrFakePhoton1Info[photon1TrueOrFake][photon2TrueOrFake],
		 fTrueOrFakePhoton2Info[photon1TrueOrFake][photon2TrueOrFake],
		 fTrueOrFakeDiphotonInfo[photon1TrueOrFake][photon2TrueOrFake]);
    if(photon1TrueOrFake==TRUE && photon2TrueOrFake==TRUE) isTT_ = true;
    else if(photon1TrueOrFake==TRUE && photon2TrueOrFake==FAKE) isTF_ = true;
    else if(photon1TrueOrFake==FAKE && photon2TrueOrFake==TRUE) isFT_ = true;
    else if(photon1TrueOrFake==FAKE && photon2TrueOrFake==FAKE) isFF_ = true;
    else throw cms::Exception("If there are two photons, there should only be four true/fake combinations!");
    if (isMC_ && isClosureTest_) {
      mcTruthFiller(&(*selectedPhotons[photon1TrueOrFake][photon2TrueOrFake].at(0)), fTrueOrFakePhoton1Info[photon1TrueOrFake][photon2TrueOrFake], genParticles);
      mcTruthFiller(&(*selectedPhotons[photon1TrueOrFake][photon2TrueOrFake].at(1)), fTrueOrFakePhoton2Info[photon1TrueOrFake][photon2TrueOrFake], genParticles);
    }
  }
  
  if (goodPhotons.size() >= 2) {
    isGood_ = true;
    photonFiller(goodPhotons, recHitsEB, recHitsEE, &id_decisions[0], fPhoton1Info, fPhoton2Info, fDiphotonInfo);
    if (isMC_) {
      fillGenInfo(genParticles, goodPhotons);
      if (isClosureTest_) {
	mcTruthFiller(&(*goodPhotons[0]), fPhoton1Info, genParticles);
	//	cout << "fPhoton1Info.isMCTruthFake: " << fPhoton1Info.isMCTruthFake << endl;
	mcTruthFiller(&(*goodPhotons[1]), fPhoton2Info, genParticles);
	//	cout << "fPhoton2Info.isMCTruthFake: " << fPhoton2Info.isMCTruthFake << endl;
      }
    }
  }
  
  // fill tree with sherpa generator information
  // need to save _all_ events for Sherpa so that PDF uncertainties
  // can be calculated
  if(isSherpaDiphoton_) {
    fSherpaGenTree->Fill();
    fTree->Fill();
  }
  else {
  // really only the second is needed, but it's more understandable to write it this way
    if(goodPhotons.size() >= 2 || realAndFakePhotons.size() >= 2) {
      fTree->Fill();
    }
  }
  

  //  cout << endl;
  
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
ExoDiPhotonAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ExoDiPhotonAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ExoDiPhotonAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}


void ExoDiPhotonAnalyzer::fillGenInfo(const edm::Handle<edm::View<reco::GenParticle> > genParticles, const std::vector<edm::Ptr<pat::Photon>> selectedPhotons)
{
  using namespace std;

  // ========================================
  // GEN photon information
  // ========================================
  // gen photons to match to
  // const reco::GenParticle *genPhoton1 = NULL;
  // const reco::GenParticle *genPhoton2 = NULL;

  // min deltaR cut
  // double minDeltaR1 = 0.1;
  // double minDeltaR2 = 0.1;

  std::vector< edm::Ptr<const reco::GenParticle> > genPhotons;

  // store interacting partons in vector
  vector<int> interactingPartons;

  // loop over gen particle collection
  for (size_t i = 0; i < genParticles->size(); ++i) {
    edm::Ptr<const reco::GenParticle> gen = genParticles->ptrAt(i);

    // find initial state particles in hard process
    // checked for GGJets
    if (gen->isHardProcess() && gen->pt() == 0) {
      //cout << "Hard Process genParticle: " << "status = " << gen->status() << "; pdgId = " << gen->pdgId()
      //<< "; pt = " << gen->pt() << "; eta = " << gen->eta() << "; phi = " << gen->phi() << endl;
      interactingPartons.push_back(gen->pdgId());
    }

    if (gen->isHardProcess() && gen->pdgId() == 22) genPhotons.push_back( gen );

    // find photon matches in final state from hard process gen particles
 //    if (gen->fromHardProcessFinalState()) {
 //      //cout << "GenParticle fromHardProcessFinalState(): Status = " << gen->status()  << "; ID = " << gen->pdgId() << "; pt = "
 //      //<< gen->pt() << "; eta = " << gen->eta() << "; phi = " << gen->phi() << endl;

 //      // check for photon 1 (best) match
 //      double deltaR1 = reco::deltaR(selectedPhotons[0]->eta(),selectedPhotons[0]->phi(),gen->eta(),gen->phi());
 //      if (deltaR1 < minDeltaR1) {
	// minDeltaR1 = deltaR1;
	// genPhoton1 = &(*gen);
 //      }

 //      // check for photon 2 (best) match
 //      double deltaR2 = reco::deltaR(selectedPhotons[1]->eta(),selectedPhotons[1]->phi(),gen->eta(),gen->phi());
 //      if (deltaR2 < minDeltaR2) {
	// minDeltaR2 = deltaR2;
	// genPhoton2 = &(*gen);
 //      }

 //    } // end fromHardProcessFinalState check

  } // end of genParticle loop.

  sort(genPhotons.begin(), genPhotons.end(), ExoDiPhotons::comparePhotonsByPt);  

    // fill interacting partons
  if (interactingPartons.size() == 2) {
    fEventInfo.interactingParton1PdgId = interactingPartons[0];
    fEventInfo.interactingParton2PdgId = interactingPartons[1];
  }
  else std::cout << "Exactly two interacting partons not found!" << std::endl;

  // Samples with only fakes may have no hard-process photons
  if(genPhotons.size() < 1) return;
  const reco::GenParticle *genPhoton1 = &(*genPhotons.at(0));
  if (genPhoton1) ExoDiPhotons::FillGenParticleInfo(fGenPhoton1Info, genPhoton1);

  // Samples with one fake may have only one hard-process photon
  if(genPhotons.size() < 2) return;
  // fill gen photon info
  const reco::GenParticle *genPhoton2 = &(*genPhotons.at(1));
  if (genPhoton2) ExoDiPhotons::FillGenParticleInfo(fGenPhoton2Info, genPhoton2);

  // fill gen diphoton info
  if (genPhoton1 && genPhoton2) ExoDiPhotons::FillDiphotonInfo(fGenDiphotonInfo,genPhoton1,genPhoton2);

}

void ExoDiPhotonAnalyzer::photonFiller(const std::vector<edm::Ptr<pat::Photon>>& photons,
						 const edm::Handle<EcalRecHitCollection>& recHitsEB, const edm::Handle<EcalRecHitCollection>& recHitsEE,
						 const edm::Handle<edm::ValueMap<bool> >* id_decisions,
						 ExoDiPhotons::photonInfo_t& photon1Info, ExoDiPhotons::photonInfo_t& photon2Info, ExoDiPhotons::diphotonInfo_t& diphotonInfo)
{
  //  std::cout << "Photon 1 pt = " << photons[0]->pt() << "; eta = " << photons[0]->eta() << "; phi = " << photons[0]->phi() << std::endl;
  //  std::cout << "Photon 2 pt = " << photons[1]->pt() << "; eta = " << photons[1]->eta() << "; phi = " << photons[1]->phi() << std::endl;

  // ==================
  // fill photon 1 info
  // ==================
  // fill photon saturation
  photon1Info.isSaturated = ExoDiPhotons::isSaturated(&(*photons[0]), &(*recHitsEB), &(*recHitsEE), &(*subDetTopologyEB_), &(*subDetTopologyEE_));
  //  std::cout << "Photon 1 isSat: " << photon1Info.isSaturated << std::endl;

  // fill photon info
  ExoDiPhotons::FillBasicPhotonInfo(photon1Info, &(*photons[0]));
  ExoDiPhotons::FillPhotonIDInfo(photon1Info, &(*photons[0]), rho_, photon1Info.isSaturated);

  // fill EGM ID info
  ExoDiPhotons::FillPhotonEGMidInfo(photon1Info, &(*photons[0]), rho_, effAreaChHadrons_, effAreaNeuHadrons_, effAreaPhotons_);
  photon1Info.passEGMLooseID  = (*(id_decisions[LOOSE]))[photons[0]];
  photon1Info.passEGMMediumID = (*(id_decisions[MEDIUM]))[photons[0]];
  photon1Info.passEGMTightID  = (*(id_decisions[TIGHT]))[photons[0]];

  // ==================
  // fill photon 2 info
  // ==================
  // fill photon saturation
  photon2Info.isSaturated = ExoDiPhotons::isSaturated(&(*photons[1]), &(*recHitsEB), &(*recHitsEE), &(*subDetTopologyEB_), &(*subDetTopologyEE_));
  //  std::cout << "Photon 2 isSat: " << photon2Info.isSaturated << std::endl;

  // fill photon info
  ExoDiPhotons::FillBasicPhotonInfo(photon2Info, &(*photons[1]));
  ExoDiPhotons::FillPhotonIDInfo(photon2Info, &(*photons[1]), rho_, photon2Info.isSaturated);

  // fill EGM ID info
  ExoDiPhotons::FillPhotonEGMidInfo(photon2Info, &(*photons[1]), rho_, effAreaChHadrons_, effAreaNeuHadrons_, effAreaPhotons_);
  photon2Info.passEGMLooseID  = (*(id_decisions[LOOSE]))[photons[1]];
  photon2Info.passEGMMediumID = (*(id_decisions[MEDIUM]))[photons[1]];
  photon2Info.passEGMTightID  = (*(id_decisions[TIGHT]))[photons[1]];

  //cout << "photon 1 pt = " << photon1Info.pt << "; eta = " << photon1Info.eta << "; phi = " << photon1Info.phi << endl;
  //cout << "photon 2 pt = " << photon2Info.pt << "; eta = " << photon2Info.eta << "; phi = " << photon2Info.phi << endl;

  // ==================
  // fill diphoton info
  // ==================
  ExoDiPhotons::FillDiphotonInfo(diphotonInfo,&(*photons[0]),&(*photons[1]));

} // end photonFiller

void ExoDiPhotonAnalyzer::sherpaDiphotonFiller(const edm::Handle<edm::View<reco::GenParticle> > genParticles,
							 std::vector<edm::Ptr<const reco::GenParticle>> sherpaDiphotons)
{
  // ntuple assumes that photon list is sorted by pT
  sort(sherpaDiphotons.begin(), sherpaDiphotons.end(), ExoDiPhotons::comparePhotonsByPt);

  ExoDiPhotons::FillGenParticleInfo(fSherpaGenPhoton1Info, sherpaDiphotons.at(0).get());
  ExoDiPhotons::FillGenParticleInfo(fSherpaGenPhoton2Info, sherpaDiphotons.at(1).get());
  // fill gen diphoton info
  ExoDiPhotons::FillDiphotonInfo(fSherpaGenDiphotonInfo, sherpaDiphotons.at(0).get(), sherpaDiphotons.at(1).get());

  // isolation sums for photons 0 and 1
  SherpaGenPhoton0_iso_ = 0.0;
  SherpaGenPhoton1_iso_ = 0.0;
  // this is needed for the stitching together of Sherpa samples
  SherpaWeightAll_ = fEventInfo.weightAll;

  for(size_t k=0; k<genParticles->size(); k++ ){
    const auto gen = genParticles->ptrAt(k);
    //    if( gen->fromHardProcessFinalState() || (abs(gen->pdgId())>=11 && abs(gen->pdgId())<=16) ) continue;
    if( gen->status()!=3 || gen->pdgId()==22 ) continue;
    double deltaR0 = reco::deltaR(sherpaDiphotons.at(0)->eta(), sherpaDiphotons.at(0)->phi(), gen->eta(), gen->phi());
    double deltaR1 = reco::deltaR(sherpaDiphotons.at(1)->eta(), sherpaDiphotons.at(1)->phi(), gen->eta(), gen->phi());
    if( deltaR0 < isolationConeR_ ) SherpaGenPhoton0_iso_+=gen->pt();
    if( deltaR1 < isolationConeR_ ) SherpaGenPhoton1_iso_+=gen->pt();
  }
} // end sherpaDiphotonFiller

void ExoDiPhotonAnalyzer::mcTruthFiller(const pat::Photon *photon, ExoDiPhotons::photonInfo_t& photonInfo, const edm::Handle<edm::View<reco::GenParticle> > genParticles)
{
  bool printInfo = false;
  
  if (printInfo) std::cout << "Photon: pt = " << photon->pt() << "; eta = " << photon->eta() << "; phi = " << photon->phi() << std::endl;
  
  const double deltaR_cut = 0.1;
  double minDeltaR = deltaR_cut;
  
  const reco::GenParticle *photon_gen_match = NULL;
  
  // find best match to reco photon among all final state gen particles in dR cone 
  for (size_t i = 0; i < genParticles->size(); ++i) {
    const auto gen = genParticles->ptrAt(i);
    double deltaR = reco::deltaR(photon->eta(),photon->phi(),gen->eta(),gen->phi());
    if (gen->status() == 1) {
      if (printInfo) {
	std::cout << "Gen. particle: status = " << gen->status() << "; pdgId = " << gen->pdgId()
		  << "; pt = " << gen->pt() << "; eta = " << gen->eta() << "; phi = " << gen->phi() << "; dR = " << deltaR << std::endl;
      }
      if (deltaR <= minDeltaR) {
	minDeltaR = deltaR;
	photon_gen_match = &(*gen);
      }
    }
  } // end for loop over gen particles

  bool is_fake = false;
  
  // if matched, look at gen. history to determine if reco photon is fake
  if (photon_gen_match) {
    if (printInfo) {
      std::cout << "Final state gen particle match: status = " << photon_gen_match->status() << "; pdgId = " << photon_gen_match->pdgId()
		<< "; pt = " << photon_gen_match->pt() << "; eta = " << photon_gen_match->eta() << "; phi = " << photon_gen_match->phi() << std::endl;
    }
    // if matched to a photon, check mothers to determine if fake
    if (photon_gen_match->pdgId() == 22) {
      // if first non-photon mother is a hadron with pt > 0 (i.e., not a hard interaction hadron {proton}), then fake
      // particle whose mothers will looped through
      const reco::GenParticle *matchedMother = &(*photon_gen_match);
      // consider all mothers when tying to find best mother (no deltaR cut)
      double minMotherMatchDeltaR = 1000000;
      // store index of best mother
      int matchMotherIndex = 0;
      // used to check first non-photon mother
      bool is_photon_mother = true;
      bool is_first_non_photon_mother = true;
      // loop through all mothers until no mothers exist (will trace back to colliding proton)
      while (matchedMother->mother()) {
	// loop through all mothers and keep index of best deltaR match
	for (unsigned int j=0; j < matchedMother->numberOfMothers(); j++) {
	  // calculate deltaR between particle and mother
	  double deltaR = reco::deltaR(matchedMother->eta(),matchedMother->phi(),matchedMother->mother(j)->eta(),matchedMother->mother(j)->phi());
	  // print each mother
	  if (printInfo) {
	    std::cout << "\t           Mother " << j << ": Status = " << matchedMother->mother(j)->status()  << "; ID = " << matchedMother->mother(j)->pdgId() << "; pt = "
		      << matchedMother->mother(j)->pt() << "; eta = " << matchedMother->mother(j)->eta() << "; phi = " << matchedMother->mother(j)->phi()  << "; deltaR = " << deltaR << std::endl;
	  }
	  // if current deltaR is smallest, save index
	  if (deltaR < minMotherMatchDeltaR) {
	    minMotherMatchDeltaR = deltaR;
	    matchMotherIndex = j;
	  }
	} // end for loop through mothers
	// matched particle now becomes best mother
	matchedMother = (reco::GenParticle *) matchedMother->mother(matchMotherIndex);
	// print best mother's info
	if (printInfo) {
	  std::cout << "FinalState Matched MOTHER " << matchMotherIndex << ": Status = " << matchedMother->status()  << "; ID = " << matchedMother->pdgId() << "; pt = "
		    << matchedMother->pt() << "; eta = " << matchedMother->eta() << "; phi = " << matchedMother->phi()  << "; deltaR = " << minMotherMatchDeltaR << std::endl;
	}
	// find when first non-mother occurs
	if (matchedMother->pdgId() != 22) is_photon_mother = false;
	// check if current matchedMother is a hadron (colliding proton not considered true)
	if (!is_photon_mother && is_first_non_photon_mother && fabs(matchedMother->pdgId()) > 99 && matchedMother->pt() != 0.) {
	  is_fake = true;
	  // first non-photon mother checked
	  is_first_non_photon_mother = false;
	}
	// reset cut! so we will consider all mothers again during next loop
	minMotherMatchDeltaR = 1000000;
	// index could be > 0 and only one mother on next match and could be beam particle with very high deltaR
	// so reset index just to be safe
	matchMotherIndex = 0;
      } // end while loop through mothers
    } // end if photon match
    // if not matched to a photon, check match to determine if fake
    if (photon_gen_match->pdgId() != 22) {
      // if matched to a hadron with pt > 0 (i.e., not a hard interaction hadron {proton}), then fake
      if (fabs(photon_gen_match->pdgId()) > 99 && photon_gen_match->pt() != 0.) is_fake = true;
    } // end if not a photon match
  } // end if photon gen. match

  if (is_fake) photonInfo.isMCTruthFake = true;
  
} // end mcTruthFiller

//define this as a plug-in
DEFINE_FWK_MODULE(ExoDiPhotonAnalyzer);
