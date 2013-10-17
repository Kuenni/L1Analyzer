// -*- C++ -*-
//
// Package:    L1Analyzer
// Class:      L1Analyzer
// 
/**\class L1Analyzer L1Analyzer.cc L1Analysis/L1Analyzer/src/L1Analyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andreas Künsken
//         Created:  Wed Oct  2 13:51:22 CEST 2013
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

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/TriggerAlgorithm.h"
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/CandUtils/interface/pdgIdUtils.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
//
// class declaration
//

class L1Analyzer : public edm::EDAnalyzer {
   public:
      explicit L1Analyzer(const edm::ParameterSet&);
      ~L1Analyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------
	TH1D* histRecoMuPt;
	TH1D* histRecoMuPerEvt;
	TH1D* histSimMuPt;
	TH1D* histSimMuPerEvt;
	TH1D* histSimMuBxId;
	TTree* treeEvent;
	TTree* treeEvtIdsMultiGenMatch;

	int nRecoMuons;
	int nGenMuons;
	int nPatMuons;
	int nCosmicMuons;
	int nGenMatches;
	int runnumber;
	double recoToGenMatchRatio;
	double genMatchToGenRatio;

	int runNr;
	int eventNr;
	int lumiBlock;
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
L1Analyzer::L1Analyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


L1Analyzer::~L1Analyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
L1Analyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	//Get run number from event
	runnumber = iEvent.run();

	//get reco muon collection
	edm::Handle< reco::MuonCollection > muonHandle;
	iEvent.getByLabel("muons",muonHandle);
	nRecoMuons = muonHandle->size(); //Fill in for TTree

	edm::Handle< pat::MuonCollection > patMuonHandle;
	iEvent.getByLabel("patMuons",patMuonHandle);
	nPatMuons = patMuonHandle->size();

	//get gen particle collection
	edm::Handle< reco::GenParticleCollection > genParticleHandle;
	iEvent.getByLabel("genParticles",genParticleHandle);

	//get cosmic muon collection
	edm::Handle< edm::View<reco::Muon> > cosmicMuonHandle;
	iEvent.getByLabel("muonsFromCosmics",cosmicMuonHandle);
	nCosmicMuons = cosmicMuonHandle->size(); //Fill in for TTree


	//Get association with genParticle matches
	edm::Handle< reco::GenParticleMatch > genParticleMatchHandle;
	iEvent.getByLabel("muonMatch",genParticleMatchHandle);
	nGenMatches = genParticleMatchHandle->size(); //Fill for TTree

	reco::MuonCollection::const_iterator iterMuonCollection;
	//Loop over all general muons in collection
	for(iterMuonCollection = muonHandle->begin();iterMuonCollection!=muonHandle->end();++iterMuonCollection){
		histRecoMuPt->Fill(iterMuonCollection->pt());
	}
	histRecoMuPerEvt->Fill(muonHandle->size());

	//Get the trigger event and the refs to the accepted algorithms
	edm::Handle<pat::TriggerEvent> triggerHandle;
	iEvent.getByLabel("patTriggerEvent",triggerHandle);
	const pat::helper::TriggerMatchHelper matchHelper;


	//Loop over all Generator level particles in collection
	int genParticleCounter = 0;
	reco::GenParticleCollection::const_iterator iterGenParticleCollection;
	for(iterGenParticleCollection = genParticleHandle->begin(); iterGenParticleCollection != genParticleHandle->end() ; ++iterGenParticleCollection){
		if( isMuon(*iterGenParticleCollection) ){ //Check whether gen particle is a muon
			genParticleCounter++;
			histSimMuBxId->Fill(iterGenParticleCollection->collisionId());
			histSimMuPt->Fill(iterGenParticleCollection->pt());
		}
	}
	nGenMuons = genParticleCounter; //Fill for TTree
	histSimMuPerEvt->Fill(genParticleCounter);

	/**
	 * Calculate ratio of # reco muons to # of matches with gen muons
	 * and ratio of #  of matches with gen muons to # of gen muons
	 *
	 * recoToGenMatchRatio < 1:
	 * 	not all reco muons could be mapped to a gen muon
	 *
	 * genMatchtoGenRatio > 1:
	 * 	reco muons were matched several times to (different) gen muons
	 */
	recoToGenMatchRatio = nRecoMuons/( (double) nGenMatches );
	genMatchToGenRatio	= nGenMatches/( (double) nGenMuons );


//	if(genMatchToGenRatio > 1){
//		pat::MuonCollection::const_iterator patMuonIterator;
//		for( patMuonIterator = patMuonHandle->begin() ; patMuonIterator != patMuonHandle->end() ; ++patMuonIterator ){
//			edm::RefToBase<pat::Muon> mu = cosmicMuonHandle->refAt(i);
		/*	patMuonIterator == cosmicMuon */
//			const reco::GenParticle* gen = patMuonIterator->genLepton();
//		}
//	}

	//If the ratio is not 1, there were no cosmics in the event and we do have reco muons we might have found a ghost
	if(  genMatchToGenRatio > 1 || recoToGenMatchRatio != 1 ){
		if( nCosmicMuons == 0 && nRecoMuons != 0 ) {
			runNr 		= iEvent.id().run();
			eventNr 	= iEvent.id().event();
			lumiBlock 	= iEvent.id().luminosityBlock();
			treeEvtIdsMultiGenMatch->Fill();
		}
	}
	treeEvent->Fill(); //finally fill data to TTree

}




// ------------ method called once each job just before starting event loop  ------------
void 
L1Analyzer::beginJob()
{
	std::cout << "Beginning L1Analyzer job." << std::endl;

	edm::Service<TFileService> fs;

	histRecoMuPt 		= fs->make<TH1D>("histRecoMuPt","P_{T} of reconstructed muons;P_{T} / GeV;# Entries",101,-1,100);
	histRecoMuPerEvt 	= fs->make<TH1D>("histRecoMuPerEvt","# reconstructed muons per event;# muons;# Entries",101,-1,100);
	histSimMuPt 		= fs->make<TH1D>("histSimMuPt","P_{T} of simulated muons;P_{T} / GeV;# Entries",101,-1,100);
	histSimMuPerEvt 	= fs->make<TH1D>("histSimMuPerEvt","# simulated muons per event;# muons;# Entries",101,-1,100);
	histSimMuBxId		= fs->make<TH1D>("histSimMuBxId","BX ID for simulated muons",40,-20,20);
	histSimMuPt->SetLineColor(kRed);
	histSimMuPerEvt->SetLineColor(kRed);
	histSimMuBxId->SetLineColor(kRed);

	treeEvent			= fs->make<TTree>("treeEvent","Tree containing event by event info");
	treeEvent->Branch("nRecoMuons",&nRecoMuons);
	treeEvent->Branch("nGenMuons",&nGenMuons);
	treeEvent->Branch("nPatMuons",&nPatMuons);
	treeEvent->Branch("nCosmicMuons",&nCosmicMuons);
	treeEvent->Branch("nGenMatches",&nGenMatches);
	treeEvent->Branch("runnumber",&runnumber);
	treeEvent->Branch("recoToGenMatchRatio",&recoToGenMatchRatio);
	treeEvent->Branch("genMatchToGenRatio",&genMatchToGenRatio);

	treeEvtIdsMultiGenMatch = fs->make<TTree>("treeEvtIdsMultiGenMatch","Tree with the event IDs of events with more genMatches than genParticles");
	treeEvtIdsMultiGenMatch->Branch("runNr",&runNr);
	treeEvtIdsMultiGenMatch->Branch("eventNr",&eventNr);
	treeEvtIdsMultiGenMatch->Branch("lumiBlock",&lumiBlock);
	treeEvtIdsMultiGenMatch->Branch("recoToGenMatchRatio",&recoToGenMatchRatio);
	treeEvtIdsMultiGenMatch->Branch("genMatchToGenRatio",&genMatchToGenRatio);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1Analyzer::endJob() 
{
	std::cout << "End of L1Analyzer job." << std::endl;
}

// ------------ method called when starting to processes a run  ------------
void 
L1Analyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
L1Analyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
L1Analyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
L1Analyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
L1Analyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(L1Analyzer);
