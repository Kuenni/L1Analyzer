#include "Analyse.h"

#include "TTree.h"
#include "TH1.h"
#include "TFile.h"
#include "TApplication.h"
#include "TStyle.h"
#include "TROOT.h"

#include <stdio.h>
#include <iostream>

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
	TH1D* btiTriggers = muGunAnalyse.analyseBtiTriggers();
	btiTriggers->Draw();
	
	std::cout << "All done!\nExit via ctrl+c..." << std::endl;
	app->Run();
}
