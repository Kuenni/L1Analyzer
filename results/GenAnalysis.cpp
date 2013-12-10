/*
 * GenAnalysis.cpp
 *
 *  Created on: 09.12.2013
 *      Author: kuensken
 */

#include "GenAnalysis.h"

/**
 * Plot the number of gen muon distribution
 */
TH1D* GenAnalysis::plotNGenMuons(){
	if(getDebug())
		std::cout << "[GenAnalysis " << getSampleName() << "] plotGenMuons called" << std::endl;
	TString histName("histNGenMuons");
	histName += getSampleName();
	TH1D* hist = new TH1D(histName.Data(),"Distribution of the number of gen muons per Event;# gen muons per evt;# Entries",50,-0.5,49.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		hist->Fill(nGenParticles);
	}
	return hist;
}


/**
 * Plot gen particle distribution
 */
TH1D* GenAnalysis::plotGenParticleIds(){
	if(getDebug())
		std::cout << "[GenAnalysis " << getSampleName() << "] plotGenParticleIds called" << std::endl;
	TString histName("histGenParticles");
	histName += getSampleName();
	TH1D* hist = new TH1D(histName.Data(),"Distribution of gen particle IDs with status 1;gen particle ID;# Entries",63,-31.5,31.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		for( unsigned int j = 0 ; j < genParticleId->size() ; j++ ){
			hist->Fill(genParticleId->at(j));
		}
	}
	hist->SetStats(false);
	return hist;
}

/**
 * Plot the gen particle eta distribution
 */
TH1D* GenAnalysis::plotGenParticleEta(){
	if(getDebug())
		std::cout << "[GenAnalysis " << getSampleName() << "] plotGenParticleEta called" << std::endl;
	TString histName("histGenPartEta");
	histName += getSampleName();
	TH1D* hist = new TH1D(histName.Data(),"Distribution of #eta of gen particles;#eta;# Entries / 0.01 #eta",403,-2.015,2.015);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		for( unsigned int j = 0 ; j < etaGenParticles->size() ; j++ ){
			hist->Fill(etaGenParticles->at(j));
		}
	}
	return hist;
}

/**
 * Plot the gen particle phi distribution
 */
TH1D* GenAnalysis::plotGenParticlePhi(){
	if(getDebug())
		std::cout << "[GenAnalysis " << getSampleName() << "] plotGenParticlePhi called" << std::endl;
	TString histName("histGenPartPhi");
	histName += getSampleName();
	TH1D* hist = new TH1D(histName.Data(),"Distribution of #phi of gen particles;#phi;# Entries / 0.1 #phi",67,-0.15,6.55);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		for( unsigned int j = 0 ; j < phiGenParticles->size() ; j++ ){
			hist->Fill(phiGenParticles->at(j));
		}
	}
	return hist;
}
