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

/**
 * Make the plots for number of hit BTIs per station and given SL
 */
TH1D* TracoAnalysis::plotTracoTriggersPerStationAndSL(int stationNr,int sl){
	if(getDebug())
		std::cout << "[TracoAnalysis " << getSampleName() << "] plotBtiTriggersPerStationAndSL called" << std::endl;
	//Build histogram name
	TString histName("histNTracoTrg");
	histName += getSampleName();
	histName += "St";
	histName += stationNr;
	histName += "SL";
	histName += sl;
	//Build histogram title
	TString histTitle("Distribution of number of BTI triggers per event for station ");
	histTitle += stationNr;
	histTitle += ";# BTI triggers per evt;# Entries";

	TH1D* hist = new TH1D( histName , histTitle ,43,-1.5,41.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		int stationCounter = 0;
		for( unsigned int j = 0 ; j < bstat->size() ; j++ ){
			//Filter for the requested station
			//bcod: Look only at HTRG, since LTRG are not used for DT Trig
			if( bstat->at(j) == stationNr && bsl->at(j) == sl && bcod->at(j) == 8){
				stationCounter++;
			}
		}
		hist->Fill(stationCounter);
	}
	hist->SetStats(kFALSE);
	return hist;
}
