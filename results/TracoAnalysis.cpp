/*
 * TracoAnalysis.cpp
 *
 *  Created on: 06.12.2013
 *      Author: kuensken
 */

#include "TracoAnalysis.h"
#include "TCanvas.h"

/**
 * Make the plots for number of hit TRACOs
 */
TH1D* TracoAnalysis::plotTracoTriggers(){
	if(getDebug())
		std::cout << "[TracoAnalysis " << getSampleName() << "] plotTracoTriggers called" << std::endl;
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
		std::cout << "[TracoAnalysis " << getSampleName() << "] plotTracoBx called" << std::endl;
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
TH1D* TracoAnalysis::plotTracoTriggersPerStation(int stationNr,bool useHtrigOnly){
	if(getDebug())
		std::cout << "[TracoAnalysis " << getSampleName() << "] plotTracoTriggersPerStation called "
		<< "Station " << stationNr << " " << (useHtrigOnly ? "HTRG" : "") << std::endl;
	//Build histogram name
	TString histName("histNTracoTrg");
	if(useHtrigOnly){
		histName += "Htrig";
	}
	histName += getSampleName();
	histName += "St";
	histName += stationNr;

	//Build histogram title
	TString histTitle("Distribution of number of TRACO triggers ");
	if(useHtrigOnly){
		histTitle += "(HTRIG)";
	}
	histTitle += " per event for station ";
	histTitle += stationNr;
	histTitle += ";# TRACO triggers per evt;# Entries";

	TH1D* histTemp = new TH1D( histName+"Temp" , histName+"Temp" ,92,-1.5,90.5);

	TH1D* hist = new TH1D( histName , histTitle ,43,-1.5,41.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		int stationCounter = 0;
		std::map<int,int> idMap;
		GetEntry(n);
		for( unsigned int j = 0 ; j < tstat->size() ; j++ ){
			unsigned int chamberId;

			//Filter for the requested station
			/** tcod: Look only at HTRG, since LTRG are not used for DT Trig
			 *  the traco code function calculates the code from the bti trigger codes
			 *  building the traco trigger via code = codeInner*10 + codeOuter
			 *  Two HTRG --> code = 88
			 */

			if( tstat->at(j) == stationNr){
				if(useHtrigOnly){
					if(tcod->at(j) == 88){
						chamberId = (((unsigned int)twh->at(j)) << 16 ) | (((unsigned int)tsect->at(j)) << 8 ) | (((unsigned int)tstat->at(j))) ;
						idMap[chamberId] = 1;
						stationCounter++;
					}
				} else {
					chamberId = (((unsigned int)twh->at(j)) << 16 ) | (((unsigned int)tsect->at(j)) << 8 ) | (((unsigned int)tstat->at(j))) ;
					idMap[chamberId] = 1;
					stationCounter++;
				}
			}
			histTemp->Fill(tcod->at(j));
		}
		if(idMap.size() != 0){
			double res = stationCounter/((double) idMap.size());
			hist->Fill(res);
		}else{
			//If no triggers, just add the 0 to the hist
			hist->Fill(0);
		}
		idMap.clear();
	}

	TCanvas* c = new TCanvas();
	//	c->cd()->SetLogy();
	histTemp->Draw();
	c->SaveAs(histName + ".png");

	hist->SetStats(kFALSE);
	return hist;
}
