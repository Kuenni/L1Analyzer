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
		std::cout << "[Analyse " << getSampleName() << "] plotTracoTriggers called" << std::endl;
	TString histName("histNTracoTrg");
	histName += getSampleName();
	TH1D* hist = new TH1D(histName,"Distribution of number of TRACO triggers per event;# TRACO triggers per evt;# Entries",41,-1.5,39.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		if( Ntraco == 0 )
			continue;
		hist->Fill(Ntraco);
	}
	hist->SetLineWidth(2);
	return hist;
}


