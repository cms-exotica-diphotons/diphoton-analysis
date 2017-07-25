// -*- C++ -*-
//
// Package:    diphoton-analysis/PhotonCollectionConcatenator
// Class:      PhotonCollectionConcatenator
// 
/**\class PhotonCollectionConcatenator PhotonCollectionConcatenator.cc diphoton-analysis/PhotonCollectionConcatenator/plugins/PhotonCollectionConcatenator.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  steven kaplan
//         Created:  Tue, 25 Jul 2017 20:40:28 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/PatCandidates/interface/Photon.h"


//
// class declaration
//

class PhotonCollectionConcatenator : public edm::stream::EDProducer<> {
   public:
      explicit PhotonCollectionConcatenator(const edm::ParameterSet&);
      ~PhotonCollectionConcatenator();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//
edm::EDGetToken photonsToken1_;
edm::EDGetToken photonsToken2_;


//
// static data member definitions
//

//
// constructors and destructor
//
PhotonCollectionConcatenator::PhotonCollectionConcatenator(const edm::ParameterSet& iConfig)
{
   //register your products
  produces< std::vector<pat::Photon> >();

  photonsToken1_ = consumes<std::vector<pat::Photon> >(iConfig.getParameter<edm::InputTag>("photonColl1"));
  photonsToken2_ = consumes<std::vector<pat::Photon> >(iConfig.getParameter<edm::InputTag>("photonColl2"));

  
}


PhotonCollectionConcatenator::~PhotonCollectionConcatenator()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
PhotonCollectionConcatenator::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

  edm::Handle<std::vector<pat::Photon> > photonHandle1;
  iEvent.getByToken(photonsToken1_,photonHandle1);

  edm::Handle<std::vector<pat::Photon> > photonHandle2;
  iEvent.getByToken(photonsToken2_,photonHandle2);

  std::unique_ptr <std::vector<pat::Photon>> finalPhotons( new std::vector<pat::Photon> );

  for (unsigned int i=0; i< photonHandle1->size(); i++){
    pat::Photon pho = *(&(photonHandle1->at(i)));
    finalPhotons->push_back( pho );
  }

  for (unsigned int i=0; i< photonHandle2->size(); i++){
    pat::Photon pho = *(&(photonHandle2->at(i)));
    finalPhotons->push_back( pho );
  }

  iEvent.put( std::move(finalPhotons) );

/* This is an event example
   //Read 'ExampleData' from the Event
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);

   //Use the ExampleData to create an ExampleData2 which 
   // is put into the Event
   std::unique_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
   iEvent.put(std::move(pOut));
*/

/* this is an EventSetup example
   //Read SetupData from the SetupRecord in the EventSetup
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
*/
 
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
PhotonCollectionConcatenator::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
PhotonCollectionConcatenator::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
PhotonCollectionConcatenator::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
PhotonCollectionConcatenator::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
PhotonCollectionConcatenator::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
PhotonCollectionConcatenator::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PhotonCollectionConcatenator::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PhotonCollectionConcatenator);
