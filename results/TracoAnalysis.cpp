/*
 * TracoAnalysis.cpp
 *
 *  Created on: 06.12.2013
 *      Author: kuensken
 */

#include "TracoAnalysis.h"

/**
 * Make the plots for number of hit TRACOs
 */
TH1D* TracoAnalysis::plotTracoTriggers(){
	if(getDebug())
		std::cout << "[TracoAnalyis " << getSampleName() << "] plotTracoTriggers called" << std::endl;
	TString histName("histNTracoTrg");
	histName += getSampleName();
	TH1D* hist = new TH1D(histName,"Distribution of number of TRACO triggers per event;# TRACO triggers per evt;# Entries",41,-1.5,39.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		hist->Fill(Ntraco);
	}
	return hist;
}

/**
 * Make the plots for BX Id of TRACOs
 */
TH1D* TracoAnalysis::plotTracoBx(){
	if(getDebug())
		std::cout << "[TracoAnalyis " << getSampleName() << "] plotTracoBx called" << std::endl;
	TString histName("histNTracoBx");
	histName += getSampleName();
	TH1D* hist = new TH1D(histName,"Distribution of BX ID for TRACO triggers;BX ID;# Entries",32,-1.5,30.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		for( int j = 0 ; j < tbx->size() ; j++ ){
					hist->Fill( tbx->at(j) );
		}
	}
	return hist;
}
