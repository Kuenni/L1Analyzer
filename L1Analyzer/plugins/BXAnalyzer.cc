// -*- C++ -*-
//
// Package:    L1Analyzer
// Class:      BXAnalyzer
// 
/**\class BXAnalyzer BXAnalyzer.cc L1Analyzer/L1Analyzer/plugins/BXAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andreas Künsken
//         Created:  Mon, 11 Nov 2013 13:14:22 GMT
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

/// DT input
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhDigi.h"
// #include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"
// #include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThDigi.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTTrackContainer.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include <TH1D.h>


//
// class declaration
//

//Auf DtBxAnalyzer �ndern, und den code DT-spezifisch machen?
class BXAnalyzer : public edm::EDAnalyzer {
   public:
      explicit BXAnalyzer(const edm::ParameterSet&);
      ~BXAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

	edm::InputTag dtTrackSrc, phiContainterSrc;

	int bxMin, bxMax;
	bool verbose;
	std::map<std::string, TH1*> histoMap;



      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
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
BXAnalyzer::BXAnalyzer(const edm::ParameterSet& iConfig){
	//Get the edm Input tags for the source collections
	dtTrackSrc 		= iConfig.getParameter<edm::InputTag>("dtTrackSrc");

	phiContainterSrc= iConfig.getParameter<edm::InputTag>("chambPhiContSrc");

	//Get other numerical parameters
	bxMin = iConfig.getParameter<int>("bxMin");
	bxMax = iConfig.getParameter<int>("bxMax");

	verbose = iConfig.getParameter<bool>("verbose");

	if(verbose){
		std::cout << "BXAnalyzer: bxMin = " << bxMin << "." << std::endl;
		std::cout << "BXAnalyzer: bxMax = " << bxMax << "." << std::endl;
	}

}


BXAnalyzer::~BXAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
BXAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){

	edm::Handle<L1MuDTTrackContainer> dtTracks;
	iEvent.getByLabel(dtTrackSrc,dtTracks);

	edm::Handle<L1MuDTChambPhContainer> chambPhiContainer;
		iEvent.getByLabel(phiContainterSrc,chambPhiContainer);


	L1MuDTTrackContainer::TrackContainer::const_iterator track		= dtTracks->getContainer()->begin();
	L1MuDTTrackContainer::TrackContainer::const_iterator trackEnd	= dtTracks->getContainer()->end();

	for ( ; track != trackEnd; ++track ) {
		histoMap["histDttfTrackBx"]->Fill(track->bx());
	}

	L1MuDTChambPhContainer::Phi_Container::const_iterator phiSeg	= chambPhiContainer->getContainer()->begin();
	L1MuDTChambPhContainer::Phi_Container::const_iterator phiSegEnd	= chambPhiContainer->getContainer()->end();

	for ( ; phiSeg != phiSegEnd; ++phiSeg ) {
		histoMap["histPhiSegBx"]->Fill(phiSeg->bxNum());
	}

}


// ------------ method called once each job just before starting event loop  ------------
void 
BXAnalyzer::beginJob()
{
	edm::Service<TFileService> fs;
	histoMap["histDttfTrackBx"]	= fs->make<TH1D>("histDttfTrackBx","BX ID of DTTF Tracks;BX-ID;# Entries",20,-10,10);
	histoMap["histPhiSegBx"]	= fs->make<TH1D>("histPhiSegBx","BX ID of DTTF Tracks;BX-ID;# Entries",20,-10,10);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
BXAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
BXAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
BXAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
BXAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
BXAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BXAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(BXAnalyzer);
