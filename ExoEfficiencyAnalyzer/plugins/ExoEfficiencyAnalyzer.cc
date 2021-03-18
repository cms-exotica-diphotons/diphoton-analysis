// -*- C++ -*-
//
// Package:    diphoton-analysis/ExoEfficiencyAnalyzer
// Class:      ExoEfficiencyAnalyzer
//
/**\class ExoEfficiencyAnalyzer ExoEfficiencyAnalyzer.cc diphoton-analysis/ExoEfficiencyAnalyzer/plugins/ExoEfficiencyAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Bhim Bam
//         Created:  Fri, 05 Mar 2021 23:29:50 GMT
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
 #include "FWCore/Utilities/interface/InputTag.h"
 #include "DataFormats/TrackReco/interface/Track.h"
 #include "DataFormats/TrackReco/interface/TrackFwd.h"


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
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


using reco::TrackCollection;

class ExoEfficiencyAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit ExoEfficiencyAnalyzer(const edm::ParameterSet&);
      ~ExoEfficiencyAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
//edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file


edm::EDGetTokenT<edm::View<reco::GenParticle> > genParticlesToken_;
edm::EDGetTokenT<GenEventInfoProduct>           genInfoToken_;
//edm::EDGetTokenT<std::vector<PileupSummaryInfo> > pileupToken_;
//edm::EDGetToken beamHaloSummaryToken_;
//edm::EDGetToken photonsMiniAODToken_;
//double fMinPt;
edm::Service<TFileService> fs;
// output file name
 //TString outputFile_;
 // number of events in sample
 //uint32_t nEventsSample_;

TTree *fTree;
ExoDiPhotons::eventInfo_t fEventInfo;
ExoDiPhotons::genParticleInfo_t fGenPhoton1; // leading
ExoDiPhotons::genParticleInfo_t fGenPhoton2; // subleading
// ExoDiPhotons::photonInfo_t fPhoton1Info;
// ExoDiPhotons::photonInfo_t fPhoton2Info;

// struct eventInfo_t {
//   Long64_t run;
//   Long64_t LS;
//   Long64_t evnum;
// };
// eventInfo_t fEventInfo;
// struct genPhotonInfo_t{
//   double pt;
//   double eta;
//   double phi;
//
// };
// genPhotonInfo_t fGenPhoton1;
// genPhotonInfo_t fGenPhoton2;



// edm::Service<TFileService> fs;
//edm::EDGetTokenT<edm::View<reco::GenParticle> > genParticlesToken_;
// edm::EDGetTokenT<edm::View<reco::GenParticle> > genParticlesMiniAODToken_;
// edm::EDGetTokenT<GenEventInfoProduct>           genInfoToken_;
//
// edm::InputTag genParticles_;
// TTree *fTree;
//
//
//  ExoDiPhotons::eventInfo_t         fEventInfo;
//  ExoDiPhotons::genParticleInfo_t   fGenPhotonInfo; // Each entry is an in an individual photons not whole event
//  int fGenPhotonNumber;


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
ExoEfficiencyAnalyzer::ExoEfficiencyAnalyzer(const edm::ParameterSet& iConfig)
 //:
  //tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks")))
:genParticlesToken_ (consumes<edm::View<reco::GenParticle> > (iConfig.getParameter<edm::InputTag>("genparticles"))),
genInfoToken_ (consumes<GenEventInfoProduct> (iConfig.getParameter<edm::InputTag>("genInfo")))
//pileupToken_ (consumes<std::vector<PileupSummaryInfo> >( edm::InputTag("slimmedAddPileupInfo"))),
//beamHaloSummaryToken_ (consumes<reco::BeamHaloSummary>( edm::InputTag("BeamHaloSummary")))

{
  // genParticlesToken_ = consumes<edm::View<reco::GenParticle> > (iConfig.getParameter<edm::InputTag>("genparticles"));
  // genInfoToken_ = consumes<GenEventInfoProduct> (iConfig.getParameter<edm::InputTag>("genInfo"));
  // pileupToken_ = consumes<std::vector<PileupSummaryInfo> >( edm::InputTag("slimmedAddPileupInfo") );
  // beamHaloSummaryToken_ = consumes<reco::BeamHaloSummary>( edm::InputTag("BeamHaloSummary") );
//photonsMiniAODToken_ = consumes<edm::View<pat::Photon> > (iConfig.getParameter<edm::InputTag>("photonsMiniAOD"));
//fMinPt = iConfig.getParameter<double>("minPhotonPt");
fTree = fs->make<TTree>("fTree", "GENDiphotonTree");
// fTree->Branch("Event", &fEventInfo, "run/L:LS:evnum");
// fTree->Branch("genPhoton1", &fGenPhoton1, "pt/D:eta:phi");
// fTree->Branch("genPhoton2", &fGenPhoton2, "pt/D:eta:phi");
fTree->Branch("Event",&fEventInfo,ExoDiPhotons::eventBranchDefString.c_str());
fTree->Branch("GenPhoton1",&fGenPhoton1,ExoDiPhotons::genParticleBranchDefString.c_str());
fTree->Branch("GenPhoton2",&fGenPhoton2,ExoDiPhotons::genParticleBranchDefString.c_str());
// fTree->Branch("Photon1",&fPhoton1Info,ExoDiPhotons::photonBranchDefString.c_str());
// fTree->Branch("Photon2",&fPhoton2Info,ExoDiPhotons::photonBranchDefString.c_str());

//genParticlesToken_        = consumes<edm::View<reco::GenParticle> > (ps.getParameter<InputTag>("genparticles"));
// genInfoToken_             = consumes<GenEventInfoProduct>          (ps.getParameter<edm::InputTag>("genInfo"));
// fTree = fs->make<TTree>("fTree", "DiphotonTree");
// fTree->Branch("Event",         &fEventInfo,       ExoDiPhotons::eventBranchDefString.c_str());
// fTree->Branch("GenPhoton",     &fGenPhotonInfo, ExoDiPhotons::genParticleBranchDefString.c_str());
// fTree->Branch("GenPhotonNum",  &fGenPhotonNumber, "num/I");






   //now do what ever initialization is needed
}

ExoEfficiencyAnalyzer::~ExoEfficiencyAnalyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
ExoEfficiencyAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

    // Handle<TrackCollection> tracks;
    // iEvent.getByToken(tracksToken_, tracks);
    // for(TrackCollection::const_iterator itTrack = tracks->begin();
    //     itTrack != tracks->end();
    //     ++itTrack) {
    //   // do something with track parameters, e.g, plot the charge.
    //   // int charge = itTrack->charge();
    // }



      edm::Handle<edm::View<reco::GenParticle> > genParticles;
      iEvent.getByToken(genParticlesToken_, genParticles);
      edm::Handle<GenEventInfoProduct>           genInfo;
      iEvent.getByToken(genInfoToken_,         genInfo);
      // edm::Handle<std::vector< PileupSummaryInfo > > puSummary;
      // iEvent.getByToken(pileupToken_, puSummary);
      // edm::Handle< reco::BeamHaloSummary > bhsHandle;
      // iEvent.getByToken(beamHaloSummaryToken_, bhsHandle);
      // const reco::BeamHaloSummary* bhs = &(*bhsHandle);
      // get photon collection
      // edm::Handle<edm::View<pat::Photon> > photons;
      // iEvent.getByToken(photonsMiniAODToken_,photons);


    ExoDiPhotons::InitEventInfo(fEventInfo);
    ExoDiPhotons::InitGenParticleInfo(fGenPhoton1);
    ExoDiPhotons::InitGenParticleInfo(fGenPhoton2);
    // ExoDiPhotons::InitPhotonInfo(fPhoton1Info);
    // ExoDiPhotons::InitPhotonInfo(fPhoton2Info);


      // fEventInfo.run = -99999.99;
      // fEventInfo.LS = -99999.99;
      // fEventInfo.evnum = -99999.99;

      // fGenPhoton1.pt = -99999.99;
      // fGenPhoton1.eta =-99999.99;
      // fGenPhoton1.phi =-99999.99;
      // fGenPhoton2.pt =-99999.99;
      // fGenPhoton2.eta =-99999.99;
      // fGenPhoton2.phi =-99999.99;

      ExoDiPhotons::FillBasicEventInfo(fEventInfo, iEvent);
      ExoDiPhotons::FillGenEventInfo(fEventInfo, &(*genInfo));
      // ExoDiPhotons::FillPileupInfo(fEventInfo, &(*puSummary));
      // ExoDiPhotons::FillBeamHaloEventInfo(fEventInfo, bhs);
      //ExoDiPhotons::FillEventWeights(fEventInfo, outputFile_, nEventsSample_);

      // for(size_t i=0; i<genParticles->size(); i++) {
      // const auto gen = genParticles->ptrAt(i);
      // if(gen->pdgId()==22){
      // //genphotoncount++;
      //   double pt = gen->pt();
      //   double eta = gen->eta();
      //   double phi = gen->phi();
      //   if (pt> fGenPhoton1.pt){
      //       fGenPhoton2.pt = fGenPhoton1.pt;
      //       fGenPhoton2.eta = fGenPhoton1.eta;
      //       fGenPhoton2.phi = fGenPhoton1.phi;
      //       fGenPhoton1.pt = pt;
      //       fGenPhoton1.eta = eta;
      //       fGenPhoton1.phi = phi;
      //     }
      //   if ((pt< fGenPhoton1.pt) && (pt> fGenPhoton2.pt)){
      //       fGenPhoton2.pt = pt;
      //       fGenPhoton2.eta = eta;
      //       fGenPhoton2.phi = phi;
      //     }}}

        std::vector< edm::Ptr<const reco::GenParticle> > genPhotons;
        for (size_t i = 0; i < genParticles->size(); ++i) {  // begain for loop
          edm::Ptr<const reco::GenParticle> gen = genParticles->ptrAt(i);
          //std::cout<<"status"<<gen->status()<<std::endl;
          if (gen->pdgId() == 22) {genPhotons.push_back(gen);// status still need to be include
            // std::cout<<"genPhoton pt:" <<gen->pt()<<" ; eta:"<< gen->eta() <<" ; phi:"<< gen->phi()<<"; pdgId:"<<gen->pdgId() <<
            // " status:" <<gen->status()<<" ; motherStatus:"<< gen->motherStatus() <<" ; motherPdgId:"<< gen->motherPdgId()<<"; grandmotherStatus:"<<gen->grandmotherStatus()<< std::endl;
             }
           } // end of genParticle loop.
        // std::vector<edm::Ptr<const pat::Photon>> goodPhotons;
        // for (size_t i = 0; i < photons->size(); ++i) {   // begain for loop
        //   edm::Ptr<const pat::Photon> pho = photons->ptrAt(i);
        //   goodPhotons.push_back(pho);
        //   std::cout<<"pt"<<pho->pt()<<std::endl;}  //end for loop

            sort(genPhotons.begin(), genPhotons.end(), ExoDiPhotons::comparePhotonsByPt);
            const reco::GenParticle *genPhoton1 = &(*genPhotons.at(0));
            const reco::GenParticle *genPhoton2 = &(*genPhotons.at(1));
            ExoDiPhotons::FillGenParticleInfo(fGenPhoton1, genPhoton1);
            ExoDiPhotons::FillGenParticleInfo(fGenPhoton2, genPhoton2);

            // sort(goodPhotons.begin(), goodPhotons.end(), ExoDiPhotons::comparePhotonsByPt);
            // const pat::Photon *goodPhoton1 = &(*goodPhotons.at(0));
            // const pat::Photon *goodPhoton2 = &(*goodPhotons.at(1));
            // FillBasicPhotonInfo(fPhoton1Info, goodPhoton1);
            // FillBasicPhotonInfo(fPhoton2Info, goodPhoton2);





        //std::cout<<"genPhoton pt:" <<pt<<"; eta:"<< eta <<"; phi:"<< phi <<std::endl;

fTree->Fill();

  //   edm::Handle<edm::View<reco::GenParticle> > genParticles;
  //   edm::Handle<GenEventInfoProduct>           genInfo;
  //   iEvent.getByToken(genParticlesToken_,    genParticles);
  //   iEvent.getByToken(genInfoToken_,         genInfo);
  //
  // //---Initialize
  //  ExoDiPhotons::InitEventInfo(fEventInfo);
  //  ExoDiPhotons::InitGenParticleInfo(fGenPhotonInfo);
  //  fGenPhotonNumber = -1;
  //
  //  //---Update
  //  ExoDiPhotons::FillBasicEventInfo(fEventInfo, iEvent);
  //  ExoDiPhotons::FillGenEventInfo(fEventInfo, &(*genInfo));
  //  fillInfo(genParticles);
  //
  //   void fillInfo(const edm::Handle<edm::View<reco::GenParticle> > genParticles);
  //
  //
  //
  //
  //  fTree->Fill();






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
ExoEfficiencyAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
ExoEfficiencyAnalyzer::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ExoEfficiencyAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ExoEfficiencyAnalyzer);
