#include "Analyse.h"
#include "TString.h"
#include "TH1.h"
#include <vector>

Analyse::Analyse(std::string treeName,std::string sampleName, double ptCut, bool debug) :
	TrigTestTreeData((TTree*)(new TFile(treeName.c_str()))->Get("h1"))
	, sampleName(sampleName)
	, ptCut(ptCut)
	, debug(debug){
	std::cout << "[Analyse " << sampleName << "] Loading Tree: " << LoadTree(0) << std::endl;
}

/**
 * Make the plots for number of hit BTIs
 */
/*TH1D* Analyse::plotBtiTriggers(){
	if(debug)
		std::cout << "[Analyse " << sampleName << "] plotBtiTriggers called" << std::endl;
	TString histName("histNBtiTrg");
	histName += sampleName;
	TH1D* hist = new TH1D(histName,"Distribution of number of BTI triggers per event;# BTI triggers per evt;# Entries",201,-1.5,199.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		//if(Nbti == 0)
		//	continue;
		hist->Fill(Nbti);
	}
	hist->SetLineWidth(2);
	return hist;
}
*/
/**
 * Plot the number of BTI triggers vs Bx
 */
/*TH1D* Analyse::plotBtiTrgVsBx(){
	if(debug)
		std::cout << "[Analyse " << sampleName << "] plotBtiTrgVsBx called" << std::endl;
	TString histName("histBtiTrgVsBx");
	histName += sampleName;
	TH1D* hist = new TH1D(histName,"Distribution of BTI triggers over BX ID;BX ID;# Entries",31,-0.5,30.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		for( int j = 0 ; j < bbx->size() ; j++ ){
			hist->Fill( bbx->at(j) );
		}
	}
	hist->SetLineWidth(2);
	return hist;
}*/

/**
 * Plot the number of BTI triggers vs Bx
 */
/*TH2D* Analyse::plotNoBtiTheta(int station){
	if(debug)
		std::cout << "[Analyse " << sampleName << "] plotNoBtiTheta called" << std::endl;
	TString histName("histNoBtiTheta");
	histName += sampleName;
	histName += "St";
	histName += station;

	TString histTitle("Distribution of no BTI theta information Station ");
	histTitle += station;
	histTitle += " " + sampleName;
	histTitle += ";Wheel;Sector";

	TH2D* hist = new TH2D( histName , histTitle , 7, -3.5 , 3.5 , 14 , -1.5 , 13.5 );
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		int counter = 0;

		//Loop over BTI triggers
		for( int j = 0 ; j < Nbti ; j++ ){
			int wheel  = -1;
			int sector = -1;
			//Only start loop if we haven't sl2 (i.e. Theta) already at the beginning
			if( ( bsl-> at(j) != 2 ) && ( bstat->at(j) == station ) ){
				//Save wheel and sector for later
				wheel = bwh->at(j);
				sector = bsect->at(j);
			} else {
				continue;
			}
			//Now loop over remaining trigger and look for sl2 entries
			for( int k = j ; k < Nbti ; k++ ){
				//If we find a trigger with same station, wheel, and sector:
				//break, because it is not what we are looking for
				if( 	( bsl->at(k) == 2 )
						&& ( bstat->at(k)	== station )
						&& ( bwh->at(k)		== wheel )
						&& ( bsect->at(k)	== sector )
						){
					counter++;
					break;
				}
			}
			//After inner loop, if nothing raised the counter, we are missing the theta
			//information for this bti trigger
			if(counter == 0)
				hist->Fill(wheel,sector);
		}
	}
	return hist;
}*/

/**
 * Plot number of BTI triggers per eta segment
 *//*
TH1D* Analyse::plotBtiTriggersPerEta(int nBins){
	if(debug)
			std::cout << "[Analyse " << sampleName << "] plotBtiTriggersPerEta called" << std::endl;

	//Build histogram name
	TString histName("histNBtiTrgPerEta");
	histName += sampleName;

	//Build Histogram title
	TString histTitle("Distribution of number of BTI triggers per #eta");
	histTitle += ";#eta of BTI Trigger Data;";

	//Calculate the bin width for the yAxis Title
	double binWidth = 3.1 / (double)(nBins + 1.);
	binWidth = (int) (binWidth*100 + 0.5);
	binWidth /= 100.;
	TString yAxisTitle("# Entries / ");
	yAxisTitle += binWidth;
	yAxisTitle += " #eta";

	histTitle += yAxisTitle;

	TH1D* hist = new TH1D( histName , histTitle , nBins+1 , -1.55 , 1.55 ); //-0.5 to center bins around value, +/- 1 to have a frame
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		for ( unsigned int j = 0 ; j < beta->size() ; j++ ){
			hist->Fill(beta->at(j));
		}
	}
	hist->SetLineWidth(2);
	return hist;
}*/

/**
 * Make the plots for number of hit BTIs per station

TH1D* Analyse::plotBtiTriggersPerStation(int stationNr){
	if(debug)
		std::cout << "[Analyse " << sampleName << "] plotBtiTriggersPerStation called" << std::endl;
	//Build histogram name
	TString histName("histNBtiTrg");
	histName += sampleName;
	histName += "St";
	histName += stationNr;
	//Build histogram title
	TString histTitle("Distribution of number of BTI triggers per event for station ");
	histTitle += stationNr;
	histTitle += ";# BTI triggers per evt;# Entries";

	TH1D* hist = new TH1D( histName , histTitle ,201,-1.5,199.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		int stationCounter = 0;
		for( unsigned int j = 0 ; j < bstat->size() ; j++ ){
			//Filter for the requested station
			if( bstat->at(j) == stationNr ){
				stationCounter++;
			}
		}
		hist->Fill(stationCounter);
	}
	hist->SetLineWidth(2);
	return hist;
}*/

/*
*
 * Make the plots for number of hit TRACOs

TH1D* Analyse::plotTracoTriggers(){
	if(debug)
		std::cout << "[Analyse " << sampleName << "] plotTracoTriggers called" << std::endl;
	TString histName("histNTracoTrg");
	histName += sampleName;
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
*/

/**
 * Plot the number of gen muon distribution

TH1D* Analyse::plotNGenMuons(){
	if(debug)
		std::cout << "[Analyse " << sampleName << "] plotGenMuons called" << std::endl;
	TString histName("histNGenMuons");
	histName += sampleName;
	TH1D* hist = new TH1D(histName.Data(),"Distribution of the number of gen muons per Event;# N gen muons per evt;# Entries",50,-0.5,49.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		hist->Fill(nGenParticles);
	}
	hist->SetLineWidth(2);
	return hist;
}*/

/**
 * Plot gen particle distribution

TH1D* Analyse::plotGenParticles(){
	if(debug)
		std::cout << "[Analyse " << sampleName << "] plotGenParticles called" << std::endl;
	TString histName("histGenParticles");
	histName += sampleName;
	TH1D* hist = new TH1D(histName.Data(),"Distribution of gen particle ID;gen particle ID;# Entries",63,-31.5,31.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		for( unsigned int j = 0 ; j < genParticleId->size() ; j++ ){
			hist->Fill(genParticleId->at(j));
		}
	}
	hist->SetStats(false);
	return hist;
}*/

/**
 * Plot eta of gen particles in an event which does not have
 * BTI trigger events

TH1D* Analyse::plotEtaNoBtiTriggers(){
	if(debug)
		std::cout << "[Analyse " << sampleName << "] plotEtaNiBtiTriggers called" << std::endl;
	TString histName("histEtanoBti");
	histName += sampleName;
	TH1D* hist = new TH1D(histName.Data(),"Distribution of gen particle eta with no BTI events in event;gen particle #eta;# Entries",101,-5.05,5.05);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		if( Nbti == 0 ){
			for( unsigned int j = 0 ; j < etaGenParticles->size() ; j++ ){
				hist->Fill(etaGenParticles->at(j));
			}
		}
	}
	hist->SetLineWidth(2);
	return hist;
}*/
