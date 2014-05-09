/*
 *  $Date: 07. May 2014$
 *  \author Andreas Kuensken
 *  kuensken@physik.rwth-aachen.de
 *  Derived from MultiParticleInConeGunProducer
 */





#include <ostream>

#include "L1Analyzer/ParticleGuns/interface/DeltaPhiGunProducer.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


using namespace edm;
using namespace std;

DeltaPhiGunProducer::DeltaPhiGunProducer(const ParameterSet& pset) :
		   BaseFlatGunProducer(pset)
{


	ParameterSet defpset ;
	ParameterSet pgun_params =
			pset.getParameter<ParameterSet>("PGunParameters") ;

	fPt = pgun_params.getParameter<double>("Pt");

	fInConeIds = pgun_params.getParameter< vector<int> >("InConeID");
	fMinDeltaPhi = pgun_params.getParameter<double>("MinDeltaPhi");
	fMaxDeltaPhi = pgun_params.getParameter<double>("MaxDeltaPhi");
	fMinMomRatio = pgun_params.getParameter<double>("MinMomRatio");
	fMaxMomRatio = pgun_params.getParameter<double>("MaxMomRatio");

	fParticleMinEta = pgun_params.getParameter<double>("ParticleMinEta");
	fParticleMaxEta = pgun_params.getParameter<double>("ParticleMaxEta");
	fParticleMinPhi = pgun_params.getParameter<double>("ParticleMinPhi");
	fParticleMaxPhi = pgun_params.getParameter<double>("ParticleMaxPhi");
	fInConeMaxTry = pgun_params.getParameter<unsigned int>("InConeMaxTry");

	produces<HepMCProduct>();
	produces<GenEventInfoProduct>();
}

DeltaPhiGunProducer::~DeltaPhiGunProducer()
{
	// no need to cleanup GenEvent memory - done in HepMCProduct
}

void DeltaPhiGunProducer::produce(Event &e, const EventSetup& es)
{
	if ( fVerbosity > 0 )
	{
		cout << " DeltaPhiGunProducer : Begin New Event Generation" << endl ;
	}
	// event loop (well, another step in it...)

	// no need to clean up GenEvent memory - done in HepMCProduct
	//

	// here re-create fEvt (memory)
	//
	fEvt = new HepMC::GenEvent() ;

	// now actually, cook up the event from PDGTable and gun parameters
	//
	// 1st, primary vertex
	//
	//HepMC::GenVertex* Vtx = new HepMC::GenVertex(CLHEP::HepLorentzVector(0.,0.,0.));
	HepMC::GenVertex* Vtx = new HepMC::GenVertex(HepMC::FourVector(0.,0.,0.));

	// loop over particles
	//
	int barcode = 1 ;
	for (unsigned int ip=0; ip<fPartIDs.size(); ++ip)
	{

		double pt     = fPt;
		double eta    = fRandomGenerator->fire(fParticleMinEta, fParticleMaxEta) ;
		double phi    = fRandomGenerator->fire(fParticleMinPhi, fParticleMaxPhi) ;
		int PartID = fPartIDs[ip] ;
		const HepPDT::ParticleData*
		PData = fPDGTable->particle(HepPDT::ParticleID(abs(PartID))) ;
		double mass   = PData->mass().value() ;
		double theta  = 2.*atan(exp(-eta)) ;
		double mom    = pt/sin(theta) ;
		double px     = pt*cos(phi) ;
		double py     = pt*sin(phi) ;
		double pz     = mom*cos(theta) ;
		double energy2= mom*mom + mass*mass ;
		double energy = sqrt(energy2) ;

		HepMC::FourVector p(px,py,pz,energy) ;
		HepMC::GenParticle* Part =
				new HepMC::GenParticle(p,PartID,1);
		Part->suggest_barcode( barcode ) ;
		barcode++ ;
		Vtx->add_particle_out(Part);

		if ( fAddAntiParticle ){}

		// now add the particles in the cone
		for (unsigned iPic=0; iPic!=fInConeIds.size();iPic++){
			unsigned int nTry=0;
			while(true){

				//shoot delta phi
				double dPhi = fRandomGenerator->fire(fMinDeltaPhi,fMaxDeltaPhi);
				//shoot flat Deltar
				//    		   double dR = fRandomGenerator->fire(fMinDeltaR, fMaxDeltaR);
				//shoot flat eta/phi mixing
				//    		   double alpha = fRandomGenerator->fire(-3.14159265358979323846, 3.14159265358979323846);
				//   		   double dEta = dR*cos(alpha);
				//  		   double dPhi = dR*sin(alpha);

				//	 get kinematics
				double etaIc = eta;
				double phiIc = phi+dPhi;
				//put it back in -Pi:Pi if necessary. multiple time might be necessary if dR > 3
				const unsigned int maxL=100;
				unsigned int iL=0;
				while(iL++<maxL){
					if (phiIc > 3.14159265358979323846) phiIc-=2*3.14159265358979323846;
					else if(phiIc <-3.14159265358979323846) phiIc+=2*3.14159265358979323846;

					if (abs(phiIc)<3.14159265358979323846) break;
				}


				//allow to skip it if you did not run out of possible drawing
				if (nTry++<=fInConeMaxTry){
					//draw another one if this one is not in acceptance
					if (phiIc<fParticleMinPhi || phiIc > fParticleMaxPhi) continue;
				}
				else{
					if ( fVerbosity > 0 )
					{
						cout << " DeltaPhiGunProducer : could not produce a particle "
								<<  fInConeIds[iPic]<<" in cone "
								<<  fMinDeltaPhi<<" to "<<fMaxDeltaPhi<<" within the "<<fInConeMaxTry<<" allowed tries."<<endl;
					}
				}
				int PartIDIc=fInConeIds[iPic];
				const HepPDT::ParticleData*
				PDataIc = fPDGTable->particle(HepPDT::ParticleID(abs(PartIDIc)));

				//shoot momentum ratio
				double momR = fRandomGenerator->fire(fMinMomRatio, fMaxMomRatio);
				double massIc= PDataIc->mass().value() ;
				double momIc = momR * mom;
				double energyIc = sqrt(momIc*momIc + massIc*massIc);

				double thetaIc = 2.*atan(exp(-etaIc)) ;
				double pxIc = momIc*sin(thetaIc)*cos(phiIc);
				double pyIc = momIc*sin(thetaIc)*sin(phiIc);
				double pzIc = momIc*cos(thetaIc);

				HepMC::FourVector pIc(pxIc,pyIc,pzIc,energyIc) ;
				HepMC::GenParticle* PartIc = new HepMC::GenParticle(pIc, PartIDIc, 1);
				PartIc->suggest_barcode( barcode ) ;
				barcode++ ;
				Vtx->add_particle_out(PartIc);
				break;
			}//try many times while not in acceptance
		}//loop over the particle Ids in the cone
	}

	fEvt->add_vertex(Vtx) ;
	fEvt->set_event_number(e.id().event()) ;
	fEvt->set_signal_process_id(20) ;

	if ( fVerbosity > 0 )
	{
		fEvt->print() ;
	}

	auto_ptr<HepMCProduct> BProduct(new HepMCProduct()) ;
	BProduct->addHepMCData( fEvt );
	e.put(BProduct);

	auto_ptr<GenEventInfoProduct> genEventInfo(new GenEventInfoProduct(fEvt));
	e.put(genEventInfo);

	if ( fVerbosity > 0 )
	{
		cout << " DeltaPhiGunProducer : Event Generation Done " << endl;
	}
}

