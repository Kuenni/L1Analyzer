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
TH1D* TracoAnalysis::plotTracoTriggersPerStation(int stationNr, int trigQuality, bool useRightBx){


	TString quality("");
	switch (trigQuality) {
	case LTRG:
		quality += "(LTRG) ";
		break;
	case HTRG:
		quality += "(HTRG) ";
		break;
	case BOTH:
		quality += "(BOTH) ";
		break;
	default:
		break;
	}

	if(getDebug())
		std::cout << "[TracoAnalysis " << getSampleName() << "] plotTracoTriggersPerStation called "
		<< "Station " << stationNr << " " << quality.Data() << std::endl;
	//Build histogram name
	TString histName("histNTracoTrg");
	histName += quality;
	histName += getSampleName();
	histName += "St";
	histName += stationNr;

	//Build histogram title
	TString histTitle("Distribution of number of TRACO triggers ");
	histTitle += quality;
	histTitle += " per event for station ";
	histTitle += stationNr;
	histTitle += ";# TRACO triggers per evt;Fraction of all Events";

	TH1D* histTemp = new TH1D( histName+"Temp" , histName+"Temp" ,92,-1.5,90.5);

	TH1D* hist = new TH1D( histName , histTitle ,43,-1.5,41.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		int stationCounter = 0;
		std::map<int,int> idMap;
		GetEntry(n);
		for( unsigned int j = 0 ; j < tstat->size() ; j++ ){
			unsigned int chamberId;
			bool bxRight = false;
			bool qualiRight = false;

			//Filter for the requested station
			if( tstat->at(j) == stationNr){

				if(useRightBx){
					if(bx->at(j) == 16){
						bxRight = true;
					}
				} else {
					bxRight = true;
				}

				//Look, if the trigger quality is the one we are looking for
				/** tcod: Look only at HTRG, since LTRG are not used for DT Trig
				 *  the traco code function calculates the code from the bti trigger codes
				 *  building the traco trigger via code = codeInner*10 + codeOuter
				 *  Two HTRG --> code = 88
				 */
				switch (trigQuality) {
				case HTRG:
					if(tcod->at(j) == 88){
						qualiRight = true;
					}
					break;
				case LTRG:
					if(tcod->at(j) != 88){
						qualiRight = true;
					}
					break;
				case BOTH:
					qualiRight = true;
					break;
				default:
					break;
				}

				if(bxRight && qualiRight){
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
