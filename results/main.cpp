#include "Analyse.h"

#include "PlotStyle.h"
#include "CanvasManager.h"
#include "AnalysisWrapper.h"

#include "TTree.h"
#include "TH1.h"
#include "TFile.h"
#include "TApplication.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TSystem.h"
#include "TLegend.h"

#include <stdio.h>
#include <iostream>
#include <cmath>

int main(int argc, char** argv){
	std::cout << "Starting application" << std::endl;
	TApplication* app = new TApplication("Analyse",&argc,argv);

	//Set plot style for own root design
	PlotStyle* s = new PlotStyle();

	CanvasManager cManager("test");

	//#######################
	//# Creating Trees and Analyse objects
	//#######################

	AnalysisWrapper muGunPt10Wrapper("DIMUGUN_studies/DTTrigTest.root","muGun",10.,true);
	muGunPt10Wrapper.analyseBti();
	muGunPt10Wrapper.analyseTraco();
	muGunPt10Wrapper.analyseGenParticles();
	muGunPt10Wrapper.savePlots();
	muGunPt10Wrapper.showPlot("btiTrgPerEta");

	AnalysisWrapper Des17Pt10Wrapper("UPG2017-v2_studies/DTTrigTest_Pt10.root","des17",10.,true);
	Des17Pt10Wrapper.analyseBti();
	Des17Pt10Wrapper.analyseTraco();
	Des17Pt10Wrapper.analyseGenParticles();
	Des17Pt10Wrapper.savePlots();


	std::cout << "All done!\nExit via ctrl+c..." << std::endl;
//	app->Run();
}
