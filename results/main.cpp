#include "Analyse.h"

#include "TTree.h"
#include "TH1.h"
#include "TFile.h"
#include "TApplication.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TCanvas.h"

#include <stdio.h>
#include <iostream>
#include <cmath>

TCanvas* analyseBtiTriggers(std::vector<TH1D*>);

int main(int argc, char** argv){
	std::cout << "Starting application" << std::endl;
	TApplication* app = new TApplication("Analyse",&argc,argv);

	std::cout << "Getting Tree for mu gun study" << std::endl;
	TTree* muGunTree = (TTree*)(new TFile("DIMUGUN_studies/DTTrigTest.root"))->Get("h1");
	if(!muGunTree){
		std::cout << "Error! Mu gun tree is null pointer!" << std::endl;
		return -1;
	}
	std::cout << "Creating Analyse object with mu gun tree" << std::endl;
	Analyse muGunAnalyse(muGunTree,true);
	
	std::cout << "Making N gen muons plots" << std::endl;
	TH1D* genMuons = muGunAnalyse.plotNGenMuons();
	genMuons->Draw();

	std::cout << "Making BTI trigger plots" << std::endl;
	std::vector<TH1D*> btiVector;
	btiVector.push_back(muGunAnalyse.plotBtiTriggers());
	TCanvas* c = analyseBtiTriggers(btiVector);
	
	std::cout << "All done!\nExit via ctrl+c..." << std::endl;
	app->Run();
}

TCanvas* analyseBtiTriggers(std::vector<TH1D*> input){
	if( !( &input ) ){
		std::cout << "[main] Null pointer for BTI trigger hist vector.\nReturning." << std::endl;
		return NULL;
	} else if ( input.size() == 0 ){
		std::cout << "[main] Empty BTI trigger hist vector.\nReturning." << std::endl;
		return NULL;
	}
	TCanvas* canvas = new TCanvas("btiTriggersCanvas","BTI Triggers");
	int nHistos = input.size();
	int rowsX,rowsY;
	rowsX = ceil(sqrt(nHistos));
	rowsY = ceil(sqrt(nHistos));
	canvas->Divide(rowsX,rowsY);

	canvas->cd(1);
	input[0]->Draw();
	for( int i = 1 ; i < nHistos ; i++ ){
		canvas->cd(i+1);
		input[i]->SetLineColor(kRed+i*10);
		input[i]->Draw("Same");
	}
	return canvas;
}
