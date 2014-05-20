//-------------------------------------------------
//
/**  \class DTTrigTest
 *
 *   EDAnalyzer that generates a rootfile useful
 *   for L1-DTTrigger debugging and performance 
 *   studies
 *
 *
 *   $Date: 2009/12/22 09:36:34 $
 *   $Revision: 1.13 $
 *
 *   \author C. Battilana
 */
//
//--------------------------------------------------

//###################################
// File edited for use in L1Analyzer
// 22.11.2013 A. Kuensken
//
//###################################
// This class's header
#include "L1Analyzer/DTTrigger/interface/DTTrigTest.h"

// Framework related classes
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "L1TriggerConfig/DTTPGConfig/interface/DTConfigManager.h"
#include "L1TriggerConfig/DTTPGConfig/interface/DTConfigManagerRcd.h"

// Trigger and DataFormats headers
#include "L1Trigger/DTSectorCollector/interface/DTSectCollPhSegm.h"
#include "L1Trigger/DTSectorCollector/interface/DTSectCollThSegm.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"

//Gen particles
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "SimDataFormats/DigiSimLinks/interface/DTDigiSimLink.h"
#include "SimDataFormats/DigiSimLinks/interface/DTDigiSimLinkCollection.h"
#include "DataFormats/MuonDetId/interface/DTLayerId.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

//Root
#include <TH1D.h>
#include <TH2D.h>
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"

// Collaborating classes
#include "DataFormats/Math/interface/LorentzVector.h"
#include <CLHEP/Vector/LorentzVector.h>

#include "CommonTools/CandUtils/interface/pdgIdUtils.h"

// C++ headers
#include <iostream>
#include <math.h>
#include<time.h>

using namespace std;
using namespace edm;

const double DTTrigTest::my_TtoTDC = 32./25.;



DTTrigTest::DTTrigTest(const ParameterSet& pset): my_trig(0) { 

	my_debug= pset.getUntrackedParameter<bool>("debug");
	string outputfile = pset.getUntrackedParameter<string>("outputFileName");
	runOnData = pset.getUntrackedParameter<bool>("runOnData");
	if (my_debug)
		cout << "[DTTrigTest] Creating rootfile " <<  outputfile <<endl;
	my_rootfile = new TFile(outputfile.c_str(),"RECREATE");
	my_tree = new TTree("h1","GMT",0);
	my_params = pset;
	if (my_debug) cout << "[DTTrigTest] Constructor executed!!!" << endl;


}

DTTrigTest::~DTTrigTest(){ 

	if (my_trig != 0) delete my_trig;
	delete my_rootfile;
	if (my_debug)
		cout << "[DTTrigTest] Destructor executed!!!" << endl;

}

void DTTrigTest::endJob(){

	if (my_debug)
		cout << "[DTTrigTest] Writing Tree and Closing File" << endl;
	my_rootfile->cd();
	my_tree->Write();
	delete my_tree;
	my_rootfile->Close();

}

//void DTTrigTest::beginJob(const EventSetup & iEventSetup){
void DTTrigTest::beginJob(){
	edm::Service<TFileService> fs;
	histoMap["histBtiVtxId"]	= fs->make<TH1D>("histBtiVtxId","Vertex ID of BTI triggers;Vertex-ID;# Entries",32,-2.5,29.5);
	histoMap["histBtiGenPart"]	= fs->make<TH1D>("histBtiGenPart","Gen particle ID of BTI triggers;Gen-ID;# Entries",22,-2.5,19.5);
	histoMap["histSimTrackSimTrackIds"]	= fs->make<TH1D>("histSimTrackSimTrackIds","SimTrackIds;SimTrack-ID;# Entries",22,-2.5,19.5);
	histoMap["histSimLinkSimTrackIds"]	= fs->make<TH1D>("histSimLinkSimTrackIds","SimLinkSimTrackIds;SimTrack-ID;# Entries",22,-2.5,19.5);
	histoMap["histTracoVtxId"]	= fs->make<TH1D>("histTracoVtxId","histTracoVtxId;SimTrack-ID;# Entries",22,-2.5,19.5);
	histoMap["histTracoGenPart"]	= fs->make<TH1D>("histTracoGenPart","histTracoGenPart;SimTrack-ID;# Entries",22,-2.5,19.5);
	histoMap["histSimTrackTracoSimTrackIds"]	= fs->make<TH1D>("histSimTrackTracoSimTrackIds",
			"histSimTrackTracoSimTrackIds;SimTrack-ID;# Entries",22,-2.5,19.5);
	histoMap["histSimLinkTracoSimTrackIds"]	= fs->make<TH1D>("histSimLinkTracoSimTrackIds",
			"histSimLinkTracoSimTrackIds;SimTrack-ID;# Entries",22,-2.5,19.5);

	//Histograms for station 1
	histoMap["histBtiBxIdStat1"]		= fs->make<TH1D>("histBtiBxIdStat1",
			"BX ID of all generated BTI triggers;BX ID;# Entries",30,-0.5,29.5);
	histoMap["histBtiBxIdGenPartNotNullStat1"]	= fs->make<TH1D>("histBtiBxIdGenPartNotNullStat1",
			"BX ID of all generated BTI triggers with sim track Id > 0",30,-0.5,29.5);
	histoMap["histBtiBxIdGenPartNullStat1"]	= fs->make<TH1D>("histBtiBxIdGenPartNullStat1",
			"BX ID of all generated BTI triggers with sim track id <= 0",30,-0.5,29.5);
	histoMap["histBtiBxIdVtxNotNullStat1"]	= fs->make<TH1D>("histBtiBxIdVtxNotNullStat1",
			"BX ID of all generated BTI triggers with Vtx Id #neq 0",30,-0.5,29.5);
	histoMap["histBtiBxIdVtxNullStat1"]	= fs->make<TH1D>("histBtiBxIdVtxNullStat1",
			"BX ID of all generated BTI triggers with Vtx Id = 0",30,-0.5,29.5);
	histoMap["histSimLinkMatchesPerBti"] = fs->make<TH1D>("histSimLinkMatchesPerBti",
			"Number of matching Sim Link IDs per BTI Trig Data;# Matches;# Entries",100,-0.5,99.5);
	histoMap["histBtiBxHtrgStat1"] = fs->make<TH1D>("histBtiBxHtrgStat1","BXID for BTI HTRG Stat1",30,-0.5,29.5);
	histoMap["histBtiBxHtrgVtxNotNullStat1"] = fs->make<TH1D>("histBtiBxHtrgVtxNotNullStat1",
			"BXID for BTI HTRG with Vtx ID #neq 0",30,-0.5,29.5);
	// get DTConfigManager
	// ESHandle< DTConfigManager > confManager ;
	// iEventSetup.get< DTConfigManagerRcd >().get( confManager ) ;

	//for testing purpose....
	//DTBtiId btiid(1,1,1,1,1);
	//confManager->getDTConfigBti(btiid)->print();

	//   my_trig = new DTTrig(my_params);

	//   my_trig->createTUs(iEventSetup);
	//   if (my_debug)
	//     cout << "[DTTrigTest] TU's Created" << endl;

	// BOOKING of the tree's varables
	// GENERAL block branches
	my_tree->Branch("Run",&runn,"Run/I");
	my_tree->Branch("Event",&eventn,"Event/I");
	my_tree->Branch("Weight",&weight,"Weight/F");
	// GEANT block branches
	my_tree->Branch("Ngen",&ngen,"Ngen/I");
	my_tree->Branch("Pxgen",&pxgen);
	my_tree->Branch("Pygen",&pygen);
	my_tree->Branch("Pzgen",&pzgen);
	my_tree->Branch("Ptgen",&ptgen);
	my_tree->Branch("Etagen",&etagen);
	my_tree->Branch("Phigen",&phigen);
	my_tree->Branch("Chagen",&chagen);
	my_tree->Branch("Vxgen",&vxgen);
	my_tree->Branch("Vygen",&vygen);
	my_tree->Branch("Vzgen",&vzgen);

	//GenParticle information
	my_tree->Branch("nGenParticles",&nGenParticles,"nGenParticles/I");
	my_tree->Branch("etaGenParticles",&etaGenParticles);
	my_tree->Branch("phiGenParticles",&phiGenParticles);
	my_tree->Branch("genParticleId",&genParticleId);

	// L1MuDTBtiChipS block
	my_tree->Branch("Nbti",&nbti,"Nbti/I");
	my_tree->Branch("bwh",&bwh);
	my_tree->Branch("bstat",&bstat);
	my_tree->Branch("bsect",&bsect);
	my_tree->Branch("bsl",&bsl);
	my_tree->Branch("bnum",&bnum);
	my_tree->Branch("bbx",&bbx);
	my_tree->Branch("bcod",&bcod);
	my_tree->Branch("bk",&bk);
	my_tree->Branch("bx",&bx);
	my_tree->Branch("bposx",&bposx);
	my_tree->Branch("bposy",&bposy);
	my_tree->Branch("bposz",&bposz);
	my_tree->Branch("bdirx",&bdirx);
	my_tree->Branch("bdiry",&bdiry);
	my_tree->Branch("bdirz",&bdirz);
	my_tree->Branch("beta",&beta);
	// L1MuDTTracoChipS block
	my_tree->Branch("Ntraco",&ntraco,"Ntraco/I");
	my_tree->Branch("twh",&twh);
	my_tree->Branch("tstat",&tstat);
	my_tree->Branch("tsect",&tsect);
	my_tree->Branch("tnum",&tnum);
	my_tree->Branch("tbx",&tbx);
	my_tree->Branch("tcod",&tcod);
	my_tree->Branch("tk",&tk);
	my_tree->Branch("tx",&tx);
	my_tree->Branch("tposx",&tposx);
	my_tree->Branch("tposy",&tposy);
	my_tree->Branch("tposz",&tposz);
	my_tree->Branch("tdirx",&tdirx);
	my_tree->Branch("tdiry",&tdiry);
	my_tree->Branch("tdirz",&tdirz);
	// TSPHI block
	my_tree->Branch("Ntsphi",&ntsphi,"Ntsphi/I");
	my_tree->Branch("swh",&swh);
	my_tree->Branch("sstat",&sstat);
	my_tree->Branch("ssect",&ssect);
	my_tree->Branch("sbx",&sbx);
	my_tree->Branch("scod",&scod);
	my_tree->Branch("sphi",&sphi);
	my_tree->Branch("sphib",&sphib);
	my_tree->Branch("sposx",&sposx);
	my_tree->Branch("sposy",&sposy);
	my_tree->Branch("sposz",&sposz);
	my_tree->Branch("sdirx",&sdirx);
	my_tree->Branch("sdiry",&sdiry);
	my_tree->Branch("sdirz",&sdirz);
	// TSTHETA block
	my_tree->Branch("Ntstheta",&ntstheta,"Ntstheta/I");
	my_tree->Branch("thwh",&thwh);
	my_tree->Branch("thstat",&thstat);
	my_tree->Branch("thsect",&thsect);
	my_tree->Branch("thbx",&thbx);
	my_tree->Branch("thcode",thcode,"thcode[Ntstheta][7]/I");
	my_tree->Branch("thpos",thpos,"thpos[Ntstheta][7]/I");
	my_tree->Branch("thqual",thqual,"thqual[Ntstheta][7]/I");
	// SC PHI block
	my_tree->Branch("Nscphi",&nscphi,"Nscphi/I");
	my_tree->Branch("scphwh",&scphwh);
	my_tree->Branch("scphstat",&scphstat);
	my_tree->Branch("scphsect",&scphsect);
	my_tree->Branch("scphbx",&scphbx);
	my_tree->Branch("scphcod",&scphcod);
	my_tree->Branch("scphphi",&scphphi);
	my_tree->Branch("scphphib",&scphphib);
	my_tree->Branch("scphposx",&scphposx);
	my_tree->Branch("scphposy",&scphposy);
	my_tree->Branch("scphposz",&scphposz);
	my_tree->Branch("scphdirx",&scphdirx);
	my_tree->Branch("scphdiry",&scphdiry);
	my_tree->Branch("scphdirz",&scphdirz);
	// SC THETA block
	my_tree->Branch("Nsctheta",&nsctheta,"Nsctheta/I");
	my_tree->Branch("scthwh",&scthwh);
	my_tree->Branch("scthstat",&scthstat);
	my_tree->Branch("scthsect",&scthsect);
	my_tree->Branch("scthbx",&scthbx);
	my_tree->Branch("scthcode",scthcode,"scthcode[Nsctheta][7]/I");
	my_tree->Branch("scthpos",scthpos,"scthpos[Nsctheta][7]/I");
	my_tree->Branch("scthqual",scthqual,"scthqual[Nsctheta][7]/I");

}

void DTTrigTest::beginRun(const edm::Run& iRun, const edm::EventSetup& iEventSetup) {

	if (!my_trig) {
		my_trig = new DTTrig(my_params);
		my_trig->createTUs(iEventSetup);
		if (my_debug)
			cout << "[DTTrigTest] TU's Created" << endl;
	}
}



void DTTrigTest::analyze(const Event & iEvent, const EventSetup& iEventSetup){
	const int MAXGEN  = 20;
	//	const float ptcut  = 1.0;
	//	const float etacut = 2.4;

	// GEANT Block
	Handle<vector<SimTrack> > simTracks;
	Handle<vector<SimVertex> > simVertices;

	if(!runOnData){
		//	std::cout << "###################" << std::endl;
		//	std::cout << "Event nr. " << iEvent.id().event() << std::endl;
		//	std::cout << "###################" << std::endl;

		//### The DTDigis
		edm::Handle<MuonDigiCollection<DTLayerId, DTDigi> > dtDigis;
		iEvent.getByLabel("simMuonDTDigis", dtDigis);

		//### The Gen-particle info
		edm::Handle<reco::GenParticleCollection> genParticles;
		iEvent.getByLabel("genParticles",genParticles);

		int genMuonCounter = 0;
		reco::GenParticleCollection::const_iterator iterGenParticleCollection;
		for(iterGenParticleCollection = genParticles->begin(); iterGenParticleCollection != genParticles->end() ; ++iterGenParticleCollection){
			if( isMuon(*iterGenParticleCollection) ){ //Check whether gen particle is a muon
				etaGenParticles.push_back( iterGenParticleCollection->eta() );
				double phi = iterGenParticleCollection->phi();
				if ( phi < 0 )
					phi += 2*M_PI;
				phiGenParticles.push_back( phi );
				genMuonCounter++;
			}
			if( iterGenParticleCollection->status() == 1 )
				genParticleId.push_back(iterGenParticleCollection->pdgId());
		}
		if(my_debug)
			cout << "[DTTrigTest] Found " << genMuonCounter << " gen muons in this event." << endl;
		nGenParticles = genMuonCounter;


		iEvent.getByLabel("g4SimHits",simTracks);
		iEvent.getByLabel("g4SimHits",simVertices);
		vector<SimTrack>::const_iterator itrack;


		ngen=0;
		if (my_debug)
			cout  << "[DTTrigTest] Tracks found in the detector (not only muons) " << simTracks->size() <<endl;

		for (itrack=simTracks->begin(); itrack!=simTracks->end(); itrack++){
			//TODO: Keep in mind the filter on muons with certain eta range
			if ( abs(itrack->type())==13){
				math::XYZTLorentzVectorD momentum = itrack->momentum();
				float pt  = momentum.Pt();
				float eta = momentum.eta();
				//				if ( pt>ptcut && fabs(eta)<etacut ){
				float phi = momentum.phi();
				int charge = static_cast<int> (-itrack->type()/13); //static_cast<int> (itrack->charge());
				if ( phi<0 ){
					phi = 2*M_PI + phi;
				}

				int vtxindex = itrack->vertIndex();
				float gvx=0,gvy=0,gvz=0;
				if (vtxindex >-1){
					gvx = simVertices->at( vtxindex ).position().x();
					gvy = simVertices->at( vtxindex ).position().y();
					gvz = simVertices->at( vtxindex ).position().z();
				}
				if ( ngen < MAXGEN ) {
					pxgen.push_back( 	momentum.x() );
					pygen.push_back( 	momentum.y() );
					pzgen.push_back( 	momentum.z() );
					ptgen.push_back( 	pt );
					etagen.push_back( 	eta );
					phigen.push_back( 	phi );
					chagen.push_back( 	charge );
					vxgen.push_back( 	gvx );
					vygen.push_back( 	gvy );
					vzgen.push_back( 	gvz );
					ngen++;
				}
				//}
			}
		}
	}// runOnData


	std::cout << "running on simulation" << std::endl;

	my_trig->triggerReco(iEvent,iEventSetup);
	if (my_debug)
		cout << "[DTTrigTest] Trigger algorithm executed for run " << iEvent.id().run() <<" event " << iEvent.id().event() << endl;

	//Clear all vector Data from last event
	clearVectors();

	// GENERAL Block
	runn   = iEvent.id().run();
	eventn = iEvent.id().event();
	weight = 1; // FIXME what to do with this variable?



	// L1 Local Trigger Block
	// BTI
	vector<DTBtiTrigData> btitrigs = my_trig->BtiTrigs();
	vector<DTBtiTrigData>::const_iterator pbti;


	int ibti = 0;
	if (my_debug)
		cout << "[DTTrigTest] " << btitrigs.size() << " BTI triggers found" << endl;

	edm::Handle<MuonDigiCollection<DTLayerId,DTDigiSimLink> > dtSimLinks;
	iEvent.getByLabel("simMuonDTDigis",dtSimLinks);

	for ( pbti = btitrigs.begin(); pbti != btitrigs.end(); pbti++ ) {

		histoMap["histSimLinkMatchesPerBti"]->Fill(
				(double) countSimLinkMatchesPerBti(*pbti,dtSimLinks,simTracks)
		);

		bool continueBtiLoop = false;
		if(!runOnData){
			//### The DTDigiSimLink

			for (DTDigiSimLinkCollection::DigiRangeIterator detUnit=dtSimLinks->begin();
					detUnit !=dtSimLinks->end() && !continueBtiLoop;
					++detUnit) {

				const DTLayerId& layerid = (*detUnit).first;

				if(pbti->ChamberId() == layerid.chamberId()){	//check for same chamber
					if(pbti->SLId() == layerid.superlayerId()){	//check for same Superlayer
						const DTDigiSimLinkCollection::Range& range = (*detUnit).second;
						DTDigiSimLinkCollection::const_iterator link;
						/*
						 * Now loop over all Digis ( i.e. Wire hits in that layer (Not Superlayer!!))
						 * and then look for the same TrackId in the sim tracks.
						 * On match fill the vertex index and genParticle index of the track
						 */
						for (link=range.first; link!=range.second && !continueBtiLoop; ++link){
							for(std::vector<SimTrack>::const_iterator trackIt = simTracks->begin();
									trackIt != simTracks->end() && !continueBtiLoop; trackIt++){
								if((*link).SimTrackId() == trackIt->trackId() ){
									//Add all Sim track ids to histo
									histoMap["histBtiVtxId"]->Fill(trackIt->vertIndex());
									histoMap["histBtiGenPart"]->Fill(trackIt->genpartIndex());
									if(pbti->station() == 1){
										if(trackIt->genpartIndex() > 0)
											histoMap["histBtiBxIdGenPartNotNullStat1"]->Fill(pbti->step());
										else{
											histoMap["histBtiBxIdGenPartNullStat1"]->Fill(pbti->step());
										}
										if(trackIt->vertIndex() == 0){
											histoMap["histBtiBxIdVtxNotNullStat1"]->Fill(pbti->step());
										}
										else{
											histoMap["histBtiBxIdVtxNullStat1"]->Fill(pbti->step());
										}
										histoMap["histBtiBxIdStat1"]->Fill(pbti->step());
										histoMap["histBtiBxHtrgStat1"]->Fill(pbti->step());
										if(pbti->code() == 8)
											histoMap["histBtiBxHtrgVtxNotNullStat1"]->Fill(pbti->step());
									}
									continueBtiLoop = true;
								}
								histoMap["histSimTrackSimTrackIds"]->Fill(trackIt->trackId());
							}
							histoMap["histSimLinkSimTrackIds"]->Fill(link->SimTrackId());

						}
					}
				}
			}
		}

		bwh.push_back( 		pbti->wheel() );
		bstat.push_back( 	pbti->station() );
		bsect.push_back( 	pbti->sector() );
		bsl.push_back( 		pbti->btiSL() );
		bnum.push_back( 	pbti->btiNumber() );
		bbx.push_back( 		pbti->step() );
		bcod.push_back( 	pbti->code() );
		bk.push_back( 		pbti->K() );
		bx.push_back( 		pbti->X() );
		GlobalPoint pos = my_trig->CMSPosition( &(*pbti) );
		GlobalVector dir = my_trig->CMSDirection( &(*pbti) );
		bposx.push_back( pos.x() );
		bposy.push_back( pos.y() );
		bposz.push_back( pos.z() );
		bdirx.push_back( dir.x() );
		bdiry.push_back( dir.y() );
		bdirz.push_back( dir.z() );
		beta.push_back( pos.eta() );
		ibti++;
	}
	nbti = ibti;

	//TRACO
	vector<DTTracoTrigData> tracotrigs = my_trig->TracoTrigs();
	vector<DTTracoTrigData>::const_iterator ptc;
	int itraco = 0;
	if (my_debug)
		cout << "[DTTrigTest] " << tracotrigs.size() << " TRACO triggers found" << endl;

	for (ptc=tracotrigs.begin(); ptc!=tracotrigs.end(); ptc++) {

		if(!runOnData){
			edm::Handle<MuonDigiCollection<DTLayerId,DTDigiSimLink> > dtSimLinks;
			iEvent.getByLabel("simMuonDTDigis",dtSimLinks);
			for (DTDigiSimLinkCollection::DigiRangeIterator detUnit=dtSimLinks->begin();
					detUnit !=dtSimLinks->end();
					++detUnit) {

				const DTLayerId& layerid = (*detUnit).first;
				if(ptc->ChamberId() == layerid.chamberId()){
					const DTDigiSimLinkCollection::Range& range = (*detUnit).second;
					DTDigiSimLinkCollection::const_iterator link;
					/*
					 * Now loop over all Digis ( i.e. Wire hits in that layer (Not Superlayer!!))
					 * and then look for the same TrackId im the sim tracks.
					 * On match fill the vertex index and genParticle index of the track
					 */
					bool nextChamber = false;
					for (link=range.first; link!=range.second && !nextChamber ; ++link){
						//	std::cout << "Begin SimLink loop\n";
						for(std::vector<SimTrack>::const_iterator trackIt = simTracks->begin();
								trackIt != simTracks->end() && !nextChamber; trackIt++){
							if((*link).SimTrackId() == trackIt->trackId() ){
								//Add all Sim track ids to histo
								histoMap["histTracoVtxId"]->Fill(trackIt->vertIndex());
								histoMap["histTracoGenPart"]->Fill(trackIt->genpartIndex());
							}
							histoMap["histSimTrackTracoSimTrackIds"]->Fill(trackIt->trackId());
						}
						histoMap["histSimLinkTracoSimTrackIds"]->Fill(link->SimTrackId());

					}
				}
			}
		}

		twh.push_back(		ptc->wheel() );
		tstat.push_back( 	ptc->station() );
		tsect.push_back( 	ptc->sector() );
		tnum.push_back( 	ptc->tracoNumber() );
		tbx.push_back( 		ptc->step() );
		tcod.push_back( 	ptc->code() );
		tk.push_back( 		ptc->K() );
		tx.push_back( 		ptc->X() );
		GlobalPoint pos = my_trig->CMSPosition( &(*ptc) );
		GlobalVector dir = my_trig->CMSDirection( &(*ptc) );
		tposx.push_back( pos.x() );
		tposy.push_back( pos.y() );
		tposz.push_back( pos.z() );
		tdirx.push_back( dir.x() );
		tdiry.push_back( dir.y() );
		tdirz.push_back( dir.z() );
		itraco++;
	}
	ntraco = itraco;

	//TSPHI
	vector<DTChambPhSegm> tsphtrigs = my_trig->TSPhTrigs();
	vector<DTChambPhSegm>::const_iterator ptsph;
	int itsphi = 0;
	if (my_debug )
		cout << "[DTTrigTest] " << tsphtrigs.size() << " TSPhi triggers found" << endl;

	for (ptsph=tsphtrigs.begin(); ptsph!=tsphtrigs.end(); ptsph++) {
		//    if (itsphi<40 ) {
		swh.push_back( 		ptsph->wheel() );
		sstat.push_back( 	ptsph->station() );
		ssect.push_back( 	ptsph->sector() );
		sbx.push_back( 		ptsph->step() );
		scod.push_back( 	ptsph->oldCode() );
		sphi.push_back( 	ptsph->phi() );
		sphib.push_back(	ptsph->phiB() );
		GlobalPoint pos = my_trig->CMSPosition( &(*ptsph) );
		GlobalVector dir = my_trig->CMSDirection( &(*ptsph) );
		sposx.push_back( pos.x() );
		sposy.push_back( pos.y() );
		sposz.push_back( pos.z() );
		sdirx.push_back( dir.x() );
		sdiry.push_back( dir.y() );
		sdirz.push_back( dir.z() );
		itsphi++;
		//    }
	}
	ntsphi = itsphi;

	//TSTHETA
	vector<DTChambThSegm> tsthtrigs = my_trig->TSThTrigs();
	vector<DTChambThSegm>::const_iterator ptsth;
	int itstheta = 0;
	if (my_debug)
		cout << "[DTTrigTest] " << tsthtrigs.size() << " TSTheta triggers found" << endl;

	for (ptsth=tsthtrigs.begin(); ptsth!=tsthtrigs.end(); ptsth++) {
		if (itstheta<40 ) {
			thwh.push_back( 	ptsth->ChamberId().wheel() );
			thstat.push_back(	ptsth->ChamberId().station() );
			thsect.push_back( 	ptsth->ChamberId().sector() );
			thbx.push_back( 	ptsth->step() );
			for(int i=0;i<7;i++) {
				thcode[itstheta][i] = ptsth->code(i);
				thpos[itstheta][i] = ptsth->position(i);
				thqual[itstheta][i] = ptsth->quality(i);
			}
			itstheta++;
		} else {
			if(my_debug)
				std::cout << "[DTTrigTest] More trigger server theta triggers than array could handle.\nIncrease array length!" << std::endl;
		}
	}
	ntstheta = itstheta;

	//SCPHI
	vector<DTSectCollPhSegm> scphtrigs = my_trig->SCPhTrigs();
	vector<DTSectCollPhSegm>::const_iterator pscph;
	int iscphi = 0;
	if (my_debug )
		cout << "[DTTrigTest] " << scphtrigs.size() << " SectCollPhi triggers found" << endl;

	for (pscph=scphtrigs.begin(); pscph!=scphtrigs.end(); pscph++) {
		if (iscphi<40 ) {
			const DTChambPhSegm *seg = (*pscph).tsPhiTrig();
			scphwh.push_back( 	pscph->wheel() );
			scphstat.push_back( pscph->station() );
			scphsect.push_back( pscph->sector() );
			scphbx.push_back( 	pscph->step() );
			scphcod.push_back( 	pscph->oldCode() );
			scphphi.push_back( 	pscph->phi() );
			scphphib.push_back( pscph->phiB() );
			GlobalPoint pos = my_trig->CMSPosition(seg);
			GlobalVector dir = my_trig->CMSDirection(seg);
			scphposx.push_back( pos.x() );
			scphposy.push_back( pos.y() );
			scphposz.push_back( pos.z() );
			scphdirx.push_back( dir.x() );
			scphdiry.push_back( dir.y() );
			scphdirz.push_back( dir.z() );
			iscphi++;
		}
	}
	nscphi = iscphi;

	//SCTHETA
	vector<DTSectCollThSegm> scthtrigs = my_trig->SCThTrigs();
	vector<DTSectCollThSegm>::const_iterator pscth;
	int isctheta = 0;
	if (my_debug)
		cout << "[DTTrigTest] " << scthtrigs.size() << " SectCollTheta triggers found" << endl;

	for (pscth=scthtrigs.begin(); pscth!=scthtrigs.end(); pscth++) {
		if (isctheta<40 ) {
			scthwh.push_back( 	pscth->ChamberId().wheel() );
			scthstat.push_back( 	pscth->ChamberId().station() );
			scthsect.push_back( 	pscth->ChamberId().sector() );
			scthbx.push_back( 	pscth->step() );
			for(int i=0;i<7;i++) {
				scthcode[isctheta][i] = pscth->code(i);
				scthpos[isctheta][i] = pscth->position(i);
				scthqual[isctheta][i] = pscth->quality(i);
			}
			isctheta++;
		} else {
			if(my_debug)
				std::cout << "[DTTrigTest] More sector collector theta triggers than array could handle.\nIncrease array length!" << std::endl;
		}
	}
	nsctheta = isctheta;

	//Fill the tree
	my_tree->Fill();

}

int DTTrigTest::countSimLinkMatchesPerBti(DTBtiTrigData btiTrigData,edm::Handle<MuonDigiCollection<DTLayerId,DTDigiSimLink> > dtSimLinks
		,edm::Handle<std::vector<SimTrack> > simTracks){
	int nMatches = 0;
	for (DTDigiSimLinkCollection::DigiRangeIterator detUnit=dtSimLinks->begin();
			detUnit !=dtSimLinks->end();
			++detUnit) {

		const DTLayerId& layerid = (*detUnit).first;

		if(btiTrigData.ChamberId() == layerid.chamberId()){	//check for same chamber
			if(btiTrigData.SLId() == layerid.superlayerId()){	//check for same Superlayer
				const DTDigiSimLinkCollection::Range& range = (*detUnit).second;
				DTDigiSimLinkCollection::const_iterator link;
				/*
				 * Now loop over all Digis ( i.e. Wire hits in that layer (Not Superlayer!!))
				 * and then look for the same TrackId in the sim tracks.
				 * On match fill the vertex index and genParticle index of the track
				 */
				for (link=range.first; link!=range.second; ++link){
					for(std::vector<SimTrack>::const_iterator trackIt = simTracks->begin();
							trackIt != simTracks->end(); trackIt++){
						if((*link).SimTrackId() == trackIt->trackId() ){
							//Count the number of matches
							nMatches++;
						}
					}
				}
			}
		}
	}
	return nMatches;
}

/**
 * Clear vector data.
 *
 * Used to remove data in analyze() from previous event
 */
void DTTrigTest::clearVectors(){
	pxgen.clear();
	pygen.clear();
	pzgen.clear();
	ptgen.clear();
	etagen.clear();
	phigen.clear();
	chagen.clear();
	vxgen.clear();
	vygen.clear();
	vzgen.clear();
	etaGenParticles.clear();
	phiGenParticles.clear();
	genParticleId.clear();
	bwh.clear();
	bstat.clear();
	bsect.clear();
	bsl.clear();
	bnum.clear();
	bbx.clear();
	bcod.clear();
	bk.clear();
	bx.clear();
	bposx.clear();
	bposy.clear();
	bposz.clear();
	bdirx.clear();
	bdiry.clear();
	bdirz.clear();
	beta.clear();
	twh.clear();
	tstat.clear();
	tsect.clear();
	tnum.clear();
	tbx.clear();
	tcod.clear();
	tk.clear();
	tx.clear();
	tposx.clear();
	tposy.clear();
	tposz.clear();
	tdirx.clear();
	tdiry.clear();
	tdirz.clear();
	swh.clear();
	sstat.clear();
	ssect.clear();
	sbx.clear();
	scod.clear();
	sphi.clear();
	sphib.clear();
	sposx.clear();
	sposy.clear();
	sposz.clear();
	sdirx.clear();
	sdiry.clear();
	sdirz.clear();
	thwh.clear();
	thstat.clear();
	thsect.clear();
	thbx.clear();
	scphwh.clear();
	scphstat.clear();
	scphsect.clear();
	scphbx.clear();
	scphcod.clear();
	scphphi.clear();
	scphphib.clear();
	scphposx.clear();
	scphposy.clear();
	scphposz.clear();
	scphdirx.clear();
	scphdiry.clear();
	scphdirz.clear();
	scthwh.clear();
	scthstat.clear();
	scthsect.clear();
	scthbx.clear();
}
