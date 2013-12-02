#include "Analyse.h"
#include "TString.h"

Analyse::Analyse(TTree* tree,std::string sampleName, bool debug) : TrigTestTreeData(tree),sampleName(sampleName),debug(debug){
	std::cout << "[Analyse " << sampleName << "] Loading Tree: " << LoadTree(0) << std::endl;
}

/**
 * Make the plots for number of hit BTIs
 */
TH1D* Analyse::plotBtiTriggers(){
	if(debug)
		std::cout << "[Analyse " << sampleName << "] plotBtiTriggers called" << std::endl;
	TString histName("histNBtiTrg");
	histName += sampleName;
	TH1D* hist = new TH1D(histName,"",201,-1.5,199.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		hist->Fill(Nbti);
	}
	hist->SetTitle("Distribution of number of BTI triggers per event");
	hist->GetXaxis()->SetTitle("# BTI triggers per evt");
	hist->GetYaxis()->SetTitle("# Entries");
	hist->SetLineWidth(2);
	return hist;
}

/**
 * Make the plots for number of hit BTIs per station
 */
TH1D* Analyse::plotBtiTriggersPerStation(int stationNr){
	if(debug)
		std::cout << "[Analyse " << sampleName << "] plotBtiTriggersPerStation called" << std::endl;
	TString histName("histNBtiTrg");
	histName += sampleName;
	histName += "St";
	histName += stationNr;
	TH1D* hist = new TH1D(histName,"",201,-1.5,199.5);
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
	TString histTitle("Distribution of number of BTI triggers per event for station ");
	histTitle += stationNr;
	hist->SetTitle(histTitle.Data());
	hist->GetXaxis()->SetTitle("# BTI triggers per evt");
	hist->GetYaxis()->SetTitle("# Entries");
	hist->SetLineWidth(2);
	return hist;
}

/**
 * Make the plots for number of hit TRACOs
 */
TH1D* Analyse::plotTracoTriggers(){
	if(debug)
		std::cout << "[Analyse " << sampleName << "] plotTracoTriggers called" << std::endl;
	TString histName("histNTracoTrg");
	histName += sampleName;
	TH1D* hist = new TH1D(histName,"",41,-1.5,39.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		hist->Fill(Ntraco);
	}
	hist->SetTitle("Distribution of number of TRACO triggers per event");
	hist->GetXaxis()->SetTitle("# TRACO triggers per evt");
	hist->GetYaxis()->SetTitle("# Entries");
	hist->SetLineWidth(2);
	return hist;
}

/**
 * Plot the number of gen muon distribution
 */
TH1D* Analyse::plotNGenMuons(){
	if(debug)
		std::cout << "[Analyse " << sampleName << "] plotGenMuons called" << std::endl;
	TString histName("histNGenMuons");
	histName += sampleName;
	TH1D* hist = new TH1D(histName.Data(),"",50,-0.5,49.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		hist->Fill(nGenParticles);
	}
	hist->SetTitle("Distribution of the number of gen muons per Event");
	hist->GetXaxis()->SetTitle("# N gen muons per evt");
	hist->GetYaxis()->SetTitle("# Entries");
	hist->SetLineWidth(2);
	return hist;
}

/**
 * Plot gen particle distribution
 */

TH1D* Analyse::plotGenParticles(){
	if(debug)
		std::cout << "[Analyse " << sampleName << "] plotGenParticles called" << std::endl;
	TString histName("histGenParticles");
	histName += sampleName;
	TH1D* hist = new TH1D(histName.Data(),"",201,-100.5,100.5);
	for (int n = 0 ; n < fChain->GetEntries() ; n++ ){
		GetEntry(n);
		for( unsigned int j = 0 ; j < genParticleId->size() ; j++ ){
			hist->Fill(genParticleId->at(j));
		}
	}
	hist->SetTitle("Distribution of gen particle ID");
	hist->GetXaxis()->SetTitle("gen particle ID");
	hist->GetYaxis()->SetTitle("# Entries");
	hist->SetLineWidth(2);
	return hist;
}

