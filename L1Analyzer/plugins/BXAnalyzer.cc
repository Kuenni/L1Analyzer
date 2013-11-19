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
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

//Gen particles
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

///DT input
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhDigi.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThDigi.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTTrackContainer.h"

#include "CommonTools/CandUtils/interface/pdgIdUtils.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

//Root
#include <TH1D.h>
#include <TH2D.h>

//L1TriggerDPGUpgrade input
#include "L1TriggerDPGUpgrade/DataFormats/interface/L1TMuonTriggerPrimitive.h"
#include "L1TriggerDPGUpgrade/DataFormats/interface/L1TMuonTriggerPrimitiveFwd.h"

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

	edm::InputTag dtTrackSrc, phiContainterSrc,thetaContainerSrc;

	int bxMin, bxMax;
	bool verbose;
	std::map<std::string, TH1*> histoMap;
	std::map<std::string, TH2*> histo2DMap;
	double etaMax;



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
	dtTrackSrc 			= iConfig.getParameter<edm::InputTag>("dtTrackSrc");

	phiContainterSrc	= iConfig.getParameter<edm::InputTag>("chambPhiContSrc");
	thetaContainerSrc	= iConfig.getParameter<edm::InputTag>("chambThetaContSrc");

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

	edm::Handle<reco::GenParticleCollection> genParticles;
	iEvent.getByLabel("genParticles",genParticles);

	edm::Handle<L1TMuon::TriggerPrimitiveCollection> dtTriggerPrimitives;
	iEvent.getByLabel("L1TMuonTriggerPrimitives","DT",dtTriggerPrimitives);

	edm::Handle<L1MuDTTrackContainer> dtTracks;
	iEvent.getByLabel(dtTrackSrc,dtTracks);

	edm::Handle<L1MuDTChambPhContainer> chambPhiContainer;
	iEvent.getByLabel(phiContainterSrc,chambPhiContainer);

	edm::Handle<L1MuDTChambThContainer> chambThetaContainer;
	iEvent.getByLabel(thetaContainerSrc,chambThetaContainer);

	L1MuDTTrackContainer::TrackContainer::const_iterator track		= dtTracks->getContainer()->begin();
	L1MuDTTrackContainer::TrackContainer::const_iterator trackEnd	= dtTracks->getContainer()->end();

	//Fill Histogram for Track based BX ID
	for ( ; track != trackEnd; ++track ) {
		histoMap["histDttfTrackBx"]->Fill(track->bx());
	}

	L1MuDTChambPhContainer::Phi_Container::const_iterator phiSeg	= chambPhiContainer->getContainer()->begin();
	L1MuDTChambPhContainer::Phi_Container::const_iterator phiSegEnd	= chambPhiContainer->getContainer()->end();

	//Fill histogram for phi SL based BX ID
	for ( ; phiSeg != phiSegEnd; ++phiSeg ) {
		if(phiSeg->stNum() == 1){
			histoMap["histPhiSegBxSt1"]->Fill(phiSeg->bxNum());
		} else if(phiSeg->stNum() == 2){
			histoMap["histPhiSegBxSt2"]->Fill(phiSeg->bxNum());
		} else if(phiSeg->stNum() == 3){
			histoMap["histPhiSegBxSt3"]->Fill(phiSeg->bxNum());
		} else if(phiSeg->stNum() == 4){
			histoMap["histPhiSegBxSt4"]->Fill(phiSeg->bxNum());
		} else {
			std::cout << "Phi segment with invalid station number " << phiSeg->stNum() << std::endl;
		}

		//Make a Distribution of phi values for out of time BX IDs
		if(phiSeg->bxNum() != 0){
			histoMap["histPhiDigiPhiDistrOOT"]->Fill(phiSeg->phi());
		}
		histoMap["histPhiDigiPhiDistr"]->Fill(phiSeg->phi()%360);
		if(verbose && ( phiSeg->phi()>360 || phiSeg->phi()<-360 ) )
			std::cout << "Phi: " << phiSeg->phi() << std::endl;
	}

	//Fill histogram for theta SL based BX ID
	L1MuDTChambThContainer::The_Container::const_iterator thetaSeg		= chambThetaContainer->getContainer()->begin();
	L1MuDTChambThContainer::The_Container::const_iterator thetaSegEnd	= chambThetaContainer->getContainer()->end();

	for ( ; thetaSeg != thetaSegEnd; ++thetaSeg ) {
		if(thetaSeg->stNum() == 1){
			histoMap["histThetaSegBxSt1"]->Fill(thetaSeg->bxNum());
		} else if(thetaSeg->stNum() == 2){
			histoMap["histThetaSegBxSt2"]->Fill(thetaSeg->bxNum());
		} else if(thetaSeg->stNum() == 3){
			histoMap["histThetaSegBxSt3"]->Fill(thetaSeg->bxNum());
		} else {
			//No check for theta SL statiopn 4 since it does not exist
			std::cout << "Theta segment with invalid station number " << phiSeg->stNum() << std::endl;
		}

		//TODO:
		//# out of time bx over theta information
		if(verbose){
			std::cout << "Theta digi info" << std::endl;
			std::cout << "Wheel: " << thetaSeg->whNum() << ", Sector: " << thetaSeg->scNum()
						  << ", Station: " << thetaSeg->stNum() << ", BX: " << thetaSeg->bxNum() << "." << std::endl;
			std::cout << "Theta pos: ";

			for(int i = 0 ; i < 7 ; i++){
				std::cout << thetaSeg->position(i);
			}
			std::cout << std::endl;
			std::cout << "Theta qua: ";
			for(int i = 0 ; i < 7 ; i++){
				std::cout << thetaSeg->quality(i);
			}
			std::cout << std::endl;
			std::cout << std::endl;
		}
	}


	//Fill the correlation histogram for TP counter and gen particle counter
	int genMuonCounter = 0;
		reco::GenParticleCollection::const_iterator iterGenParticleCollection;
		for(iterGenParticleCollection = genParticles->begin(); iterGenParticleCollection != genParticles->end() ; ++iterGenParticleCollection){
			if( isMuon(*iterGenParticleCollection) ){ //Check whether gen particle is a muon
				genMuonCounter++;
			}
		}
	histo2DMap["hist2dGenPartTrigPrimCount"]->Fill(genMuonCounter,dtTriggerPrimitives->size());
	edm::LogInfo("Number of GenMuons in Event") << genMuonCounter;

}


// ------------ method called once each job just before starting event loop  ------------
void 
BXAnalyzer::beginJob()
{
	edm::Service<TFileService> fs;
	histoMap["histDttfTrackBx"]	= fs->make<TH1D>("histDttfTrackBx","BX ID of DTTF Tracks;BX-ID;# Entries",20,-10,10);

	//Phi SL Digis
	histoMap["histPhiSegBxSt1"]	= fs->make<TH1D>("histPhiSegBxSt1","BX ID of Phi SL Digis Station 1;BX-ID;# Entries",20,-10,10);
	histoMap["histPhiSegBxSt2"]	= fs->make<TH1D>("histPhiSegBxSt2","BX ID of Phi SL Digis Station 2;BX-ID;# Entries",20,-10,10);
	histoMap["histPhiSegBxSt3"]	= fs->make<TH1D>("histPhiSegBxSt3","BX ID of Phi SL Digis Station 3;BX-ID;# Entries",20,-10,10);
	histoMap["histPhiSegBxSt4"]	= fs->make<TH1D>("histPhiSegBxSt4","BX ID of Phi SL Digis Station 4;BX-ID;# Entries",20,-10,10);

	histoMap["histPhiDigiPhiDistrOOT"]	= fs->make<TH1D>("histPhiDigiPhiDistrOOT","Phi of Phi Digis for Out Of Time BXs;BX-ID;# Entries",740,-370,370);

	histoMap["histPhiDigiPhiDistr"]	= fs->make<TH1D>("histPhiDigiPhiDistr","Distribution of Phi in Phi Digis;BX-ID;# Entries",740,-370,370);


	//Theta SL Digis
	histoMap["histThetaSegBxSt1"]	= fs->make<TH1D>("histThetaSegBxSt1","BX ID of Theta SL Digis Station 1;BX-ID;# Entries",20,-10,10);
	histoMap["histThetaSegBxSt2"]	= fs->make<TH1D>("histThetaSegBxSt2","BX ID of Theta SL Digis Station 2;BX-ID;# Entries",20,-10,10);
	histoMap["histThetaSegBxSt3"]	= fs->make<TH1D>("histThetaSegBxSt3","BX ID of Theta SL Digis Station 3;BX-ID;# Entries",20,-10,10);

	histoMap["histThDigiThDistrOOT"]	= fs->make<TH1D>("histThDigiThDistrOOT","Theta of Th Digis for Out Of Time BXs;BX-ID;# Entries",20,-10,10);


	//Correlation between n genParticles and n TriggerPrimitives
	histo2DMap["hist2dGenPartTrigPrimCount"]
	           = fs->make<TH2D>("hist2dGenPartTrigPrimCount","Correlation between Number of Trigger Primitives and genParticles;# gen Particles;# TP",
	        		   100,0,100,100,0,100);
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
