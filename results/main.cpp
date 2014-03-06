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

//	AnalysisWrapper muGunPt10Wrapper("DIMUGUN_studies/DTTrigTest.root","muGun",10.,false);
//	muGunPt10Wrapper.analyseBti();
//	muGunPt10Wrapper.analyseTraco();
//	muGunPt10Wrapper.analyseGenParticles();
//	muGunPt10Wrapper.savePlots();
//
//	AnalysisWrapper des17Pt10Wrapper("UPG2017-v2_studies/DTTrigTest_Pt10.root","des17",10.,false);
//	des17Pt10Wrapper.analyseBti();
//	des17Pt10Wrapper.analyseTraco();
//	des17Pt10Wrapper.analyseGenParticles();
//	des17Pt10Wrapper.savePlots();

	AnalysisWrapper SingleMuPt100dR0_3("crab/MuGunPt100dR0_3/TrigTest.root","MuGunPt100dR0_3",10.,false);
	SingleMuPt100dR0_3.analyseBti();
//	SingleMuPt100dR0_3.analyseTraco();
//	SingleMuPt100dR0_3.analyseGenParticles();
	SingleMuPt100dR0_3.savePlots();

	AnalysisWrapper SingleMuPt100dR0_2("crab/MuGunPt100dR0_2/TrigTest.root","MuGunPt100dR0_2",10.,false);
//	SingleMuPt100dR0_2.analyseBti();
//	SingleMuPt100dR0_2.analyseTraco();
//	SingleMuPt100dR0_2.analyseGenParticles();
//	SingleMuPt100dR0_2.savePlots();

	AnalysisWrapper SingleMuPt100dR0_1("crab/MuGunPt100dR0_1/TrigTest.root","MuGunPt100dR0_1",10.,false);
//	SingleMuPt100dR0_1.analyseBti();
//	SingleMuPt100dR0_1.analyseTraco();
//	SingleMuPt100dR0_1.analyseGenParticles();
//	SingleMuPt100dR0_1.savePlots();

//	AnalysisWrapper SingleMuPt100dR0_025("SingleMuGun/TrigTestSingleMu.root","MuGunPt100dR0_025",10.,false);
//	SingleMuPt100dR0_025.analyseBti();
//	SingleMuPt100dR0_025.analyseTraco();
//	SingleMuPt100dR0_025.analyseGenParticles();
//	SingleMuPt100dR0_025.savePlots();




	//Plot the bti trigs per Station and sl together
//	std::vector<TH1*> muGunVect = muGunPt10Wrapper.analyseBtiTrigPerStatAndSL();
//	std::vector<TH1*> des17Vect = des17Pt10Wrapper.analyseBtiTrigPerStatAndSL();


	std::vector<TH1*> sMuPt100dR0_3vect = SingleMuPt100dR0_3.analyseBtiTrigPerStatAndSL();
	std::vector<TH1*> sMuPt100dR0_2vect = SingleMuPt100dR0_2.analyseBtiTrigPerStatAndSL();
	std::vector<TH1*> sMuPt100dR0_1vect = SingleMuPt100dR0_1.analyseBtiTrigPerStatAndSL();
//	std::vector<TH1*> sMuPt100dR0_075vect = SingleMuPt100dR0_3.analyseBtiTrigPerStatAndSL();
//	std::vector<TH1*> sMuPt100dR0_05vect = SingleMuPt100dR0_3.analyseBtiTrigPerStatAndSL();
//	std::vector<TH1*> sMuPt100dR0_025vect = SingleMuPt100dR0_025.analyseBtiTrigPerStatAndSL();
//	std::vector<TH1*> sMuPt100dR0_01vect = SingleMuPt100dR0_3.analyseBtiTrigPerStatAndSL();
//	std::vector<TH1*> sMuPt100dR0_005vect = SingleMuPt100dR0_3.analyseBtiTrigPerStatAndSL();

	TCanvas* c = cManager->getDividedCanvas(2,2);
	for (int i = 0; i < sMuPt100dR0_3vect.size()/2. ; ++i) {
		c->cd(i+1)->SetLogy();
		TString frameName = "BTI triggers for station ";
		frameName += i+1;

		TH2D* frame = new TH2D("frame",frameName,1,0,25,1,0.000001,1);
		frame->SetStats(kFALSE);
		frame->Draw();

		sMuPt100dR0_3vect[2*i]->SetLineColor(kBlack);
		sMuPt100dR0_3vect[2*i]->Scale(1/sMuPt100dR0_3vect[2*i]->Integral());
		sMuPt100dR0_3vect[2*i]->Draw("same");
		sMuPt100dR0_3vect[2*i+1]->SetLineColor(kBlack);
		sMuPt100dR0_3vect[2*i+1]->SetLineStyle(2);
		sMuPt100dR0_3vect[2*i+1]->Scale(1/sMuPt100dR0_3vect[2*i+1]->Integral());
		sMuPt100dR0_3vect[2*i+1]->Draw("same");

		sMuPt100dR0_2vect[2*i]->SetLineColor(kRed);
		sMuPt100dR0_2vect[2*i+1]->SetLineColor(kRed);
		sMuPt100dR0_2vect[2*i+1]->SetLineStyle(2);
		sMuPt100dR0_2vect[2*i]->Scale(1/sMuPt100dR0_2vect[2*i]->Integral());
		sMuPt100dR0_2vect[2*i+1]->Scale(1/sMuPt100dR0_2vect[2*i+1]->Integral());
		sMuPt100dR0_2vect[2*i]->Draw("same");
		sMuPt100dR0_2vect[2*i+1]->Draw("same");

		sMuPt100dR0_1vect[2*i]->SetLineColor(kBlue);
		sMuPt100dR0_1vect[2*i+1]->SetLineColor(kBlue);
		sMuPt100dR0_1vect[2*i+1]->SetLineStyle(2);
		sMuPt100dR0_1vect[2*i]->Scale(1/sMuPt100dR0_1vect[2*i]->Integral());
		sMuPt100dR0_1vect[2*i+1]->Scale(1/sMuPt100dR0_1vect[2*i+1]->Integral());
		sMuPt100dR0_1vect[2*i]->Draw("same");
		sMuPt100dR0_1vect[2*i+1]->Draw("same");

//		sMuPt100dR0_025vect[2*i]->SetLineColor(kGreen);
//		sMuPt100dR0_025vect[2*i+1]->SetLineColor(kGreen);
//		sMuPt100dR0_025vect[2*i+1]->SetLineStyle(2);
//		sMuPt100dR0_025vect[2*i]->Scale(1/sMuPt100dR0_025vect[2*i]->Integral());
//		sMuPt100dR0_025vect[2*i+1]->Scale(1/sMuPt100dR0_025vect[2*i+1]->Integral());
//		sMuPt100dR0_025vect[2*i]->Draw("same");
//		sMuPt100dR0_025vect[2*i+1]->Draw("same");

//		sMuPt100dR0_1vect[2*i]->SetLineColor(kRed);
//		sMuPt100dR0_1vect[2*i+1]->SetLineColor(kRed);
//		sMuPt100dR0_1vect[2*i+1]->SetLineStyle(2);
//		sMuPt100dR0_1vect[2*i]->Scale(1/sMuPt100dR0_1vect[2*i]->GetEntries());
//		sMuPt100dR0_1vect[2*i+1]->Scale(1/sMuPt100dR0_1vect[2*i+1]->GetEntries());
//		sMuPt100dR0_1vect[2*i]->Draw("same");
//		sMuPt100dR0_1vect[2*i+1]->Draw("same");



		TLegend* l = new TLegend(0.75,.55,0.95,0.75);

		l->AddEntry(sMuPt100dR0_3vect[2*i],"#DeltaR 0.3 SL 1");
		l->AddEntry(sMuPt100dR0_3vect[2*i+1],"#DeltaR 0.3 SL 3");
		l->AddEntry(sMuPt100dR0_2vect[2*i],"#DeltaR 0.2 SL 1");
		l->AddEntry(sMuPt100dR0_2vect[2*i+1],"#DeltaR 0.2 SL 3");
		l->AddEntry(sMuPt100dR0_1vect[2*i],"#DeltaR 0.1 SL 1");
		l->AddEntry(sMuPt100dR0_1vect[2*i+1],"#DeltaR 0.1 SL 3");
//		l->AddEntry(sMuPt100dR0_025vect[2*i],"#DeltaR 0.025 SL 1");
//		l->AddEntry(sMuPt100dR0_025vect[2*i+1],"#DeltaR 0.025 SL 3");

		l->Draw();

	}
	cManager->addCanvas("btiTrigsPerStatAndSlTogether",c);
	cManager->storePlots();

	std::cout << "All done!\nExit via ctrl+c..." << std::endl;
//	app->Run();
	delete cManager;
	return 0;
}
