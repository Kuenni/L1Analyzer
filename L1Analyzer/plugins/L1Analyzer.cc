// -*- C++ -*-
//
// Package:    L1Analyzer
// Class:      L1Analyzer
// 
/**\class L1Analyzer L1Analyzer.cc L1Analysis/L1Analyzer/plugins/L1Analyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
 */
//
// Original Author:  Andreas Künsken
//         Created:  Mon, 04 Nov 2013 15:57:54 GMT
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

//Own includes
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
	virtual void beginJob() override;
	virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
	virtual void endJob() override;

	//virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
	//virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
	//virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
	//virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

	// ----------member data ---------------------------

	std::map<std::string, TH1*> histoMap;

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

	double etaCut;

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


L1Analyzer::~L1Analyzer(){

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

	//get gen particle collection
	edm::Handle< reco::GenParticleCollection > genParticleHandle;
	iEvent.getByLabel("genParticles",genParticleHandle);


	//Loop over all Generator level particles in collection
	int genParticleCounter = 0;
	reco::GenParticleCollection::const_iterator iterGenParticleCollection;
	for(iterGenParticleCollection = genParticleHandle->begin(); iterGenParticleCollection != genParticleHandle->end() ; ++iterGenParticleCollection){
		if( isMuon(*iterGenParticleCollection) ){ //Check whether gen particle is a muon
			genParticleCounter++;
			histoMap["histSimMuBxId"]->Fill(iterGenParticleCollection->collisionId());
			histoMap["histSimMuPt"]->Fill(iterGenParticleCollection->pt());
		}
	}
	nGenMuons = genParticleCounter; //Fill for TTree
	histoMap["histSimMuPerEvt"]->Fill(genParticleCounter);


	treeEvent->Fill(); //finally fill data to TTree


}


// ------------ method called once each job just before starting event loop  ------------
void 
L1Analyzer::beginJob()
{

	std::cout << "Beginning L1Analyzer job." << std::endl;

	edm::Service<TFileService> fs;

	histoMap["histRecoMuPt"] 		= fs->make<TH1D>("histRecoMuPt","P_{T} of reconstructed muons;P_{T} / GeV;# Entries",101,-1,100);
	histoMap["histRecoMuPerEvt"] 	= fs->make<TH1D>("histRecoMuPerEvt","# reconstructed muons per event;# muons;# Entries",101,-1,100);
	histoMap["histSimMuPt"] 		= fs->make<TH1D>("histSimMuPt","P_{T} of simulated muons;P_{T} / GeV;# Entries",101,-1,100);
	histoMap["histSimMuPerEvt"] 	= fs->make<TH1D>("histSimMuPerEvt","# simulated muons per event;# muons;# Entries",101,-1,100);
	histoMap["histSimMuBxId"]		= fs->make<TH1D>("histSimMuBxId","BX ID for simulated muons",40,-20,20);
	histoMap["histSimMuPt"]->SetLineColor(kRed);
	histoMap["histSimMuPerEvt"]->SetLineColor(kRed);
	histoMap["histSimMuBxId"]->SetLineColor(kRed);

	treeEvent = fs->make<TTree>("treeEvent","Tree containing event by event info");
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

	etaCut = 9999.;
}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1Analyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
L1Analyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
 */

// ------------ method called when ending the processing of a run  ------------
/*
void 
L1Analyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
 */

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
L1Analyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
 */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
L1Analyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
 */

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
