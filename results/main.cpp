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

	CanvasManager* cManager = new CanvasManager("combinedPlots");

	//#######################
	//# Creating Trees and Analyse objects
	//#######################

	AnalysisWrapper muGunPt10Wrapper("DIMUGUN_studies/DTTrigTest.root","muGun",10.,true);
	muGunPt10Wrapper.analyseBti();
	muGunPt10Wrapper.analyseTraco();
	muGunPt10Wrapper.analyseGenParticles();
	muGunPt10Wrapper.savePlots();
	muGunPt10Wrapper.showPlot("btiTrgPerEta");

	AnalysisWrapper des17Pt10Wrapper("UPG2017-v2_studies/DTTrigTest_Pt10.root","des17",10.,true);
	des17Pt10Wrapper.analyseBti();
	des17Pt10Wrapper.analyseTraco();
	des17Pt10Wrapper.analyseGenParticles();
	des17Pt10Wrapper.savePlots();


	//Plot the bti trigs per Station and sl together
	std::vector<TH1*> muGunVect = muGunPt10Wrapper.analyseBtiTrigPerStatAndSL();
	std::vector<TH1*> des17Vect = des17Pt10Wrapper.analyseBtiTrigPerStatAndSL();
	TCanvas* c = cManager->getDividedCanvas(2,2);
	for (int i = 0; i < std::min(muGunVect.size(),des17Vect.size())/2.; ++i) {
		c->cd(i+1)->SetLogy();

		muGunVect[2*i]->SetLineColor(kBlack);
		muGunVect[2*i+1]->SetLineColor(kBlack);
		muGunVect[2*i+1]->SetLineStyle(2);
		muGunVect[2*i]->Draw();
		muGunVect[2*i+1]->Draw("same");

		des17Vect[2*i]->SetLineColor(kBlue);
		des17Vect[2*i+1]->SetLineColor(kBlue);
		des17Vect[2*i+1]->SetLineStyle(2);
		des17Vect[2*i]->Draw("same");
		des17Vect[2*i+1]->Draw("same");

		TLegend* l = new TLegend(0.75,.55,0.95,0.75);
		l->AddEntry(muGunVect[2*i],"mu gun SL 1");
		l->AddEntry(muGunVect[2*i+1],"mu gun SL 3");
		l->AddEntry(des17Vect[2*i],"des 17 SL 1");
		l->AddEntry(des17Vect[2*i+1],"des 17 SL 3");
		l->Draw();

	}
	cManager->addCanvas("btiTrigsPerStatAndSlTogether",c);


	std::cout << "All done!\nExit via ctrl+c..." << std::endl;
//	app->Run();
	return 0;
}
