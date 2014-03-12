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

	AnalysisWrapper doubleMuPt100dR0_3("crab/MuGunPt100dR0_3/TrigTest.root","MuGunPt100dR0_3",10.,true);
	doubleMuPt100dR0_3.analyseBti();
	doubleMuPt100dR0_3.analyseTraco();
//	doubleMuPt100dR0_3.analyseGenParticles();
	doubleMuPt100dR0_3.savePlots();

	AnalysisWrapper doubleMuPt100dR0_2("crab/MuGunPt100dR0_2/TrigTest.root","MuGunPt100dR0_2",10.,true);
	doubleMuPt100dR0_2.analyseBti();
//	doubleMuPt100dR0_2.analyseTraco();
//	doubleMuPt100dR0_2.analyseGenParticles();
	doubleMuPt100dR0_2.savePlots();

	AnalysisWrapper doubleMuPt100dR0_1("crab/MuGunPt100dR0_1/TrigTest.root","MuGunPt100dR0_1",10.,true);
	doubleMuPt100dR0_1.analyseBti();
//	doubleMuPt100dR0_1.analyseTraco();
//	doubleMuPt100dR0_1.analyseGenParticles();
	doubleMuPt100dR0_1.savePlots();

	AnalysisWrapper doubleMuPt100dR0_075("crab/MuGunPt100dR0_075/TrigTest.root","MuGunPt100dR0_075",10.,true);
	doubleMuPt100dR0_075.analyseBti();
//	doubleMuPt100dR0_075.analyseTraco();
//	doubleMuPt100dR0_075.analyseGenParticles();
	doubleMuPt100dR0_075.savePlots();

	AnalysisWrapper doubleMuPt100dR0_05("crab/MuGunPt100dR0_05/TrigTest.root","MuGunPt100dR0_05",10.,true);
	doubleMuPt100dR0_05.analyseBti();
//	doubleMuPt100dR0_05.analyseTraco();
//	doubleMuPt100dR0_05.analyseGenParticles();
	doubleMuPt100dR0_05.savePlots();

	AnalysisWrapper doubleMuPt100dR0_025("crab/MuGunPt100dR0_025/TrigTest.root","MuGunPt100dR0_025",10.,true);
	doubleMuPt100dR0_025.analyseBti();
//	doubleMuPt100dR0_025.analyseTraco();
//	doubleMuPt100dR0_025.analyseGenParticles();
	doubleMuPt100dR0_025.savePlots();

	AnalysisWrapper doubleMuPt100dR0_01("crab/MuGunPt100dR0_01/TrigTest.root","MuGunPt100dR0_01",10.,true);
	doubleMuPt100dR0_01.analyseBti();
//	doubleMuPt100dR0_01.analyseTraco();
//	doubleMuPt100dR0_01.analyseGenParticles();
	doubleMuPt100dR0_01.savePlots();

	AnalysisWrapper doubleMuPt100dR0_005("crab/MuGunPt100dR0_005/TrigTest.root","MuGunPt100dR0_005",10.,true);
	doubleMuPt100dR0_005.analyseBti();
//	doubleMuPt100dR0_005.analyseTraco();
//	doubleMuPt100dR0_005.analyseGenParticles();
	doubleMuPt100dR0_005.savePlots();

	AnalysisWrapper singleMuPt100("SingleMuGun/TrigTestSingleMu.root","SingleMuGun",10.,true);
	singleMuPt100.analyseBti();
	singleMuPt100.analyseTraco();
	singleMuPt100.savePlots();



	std::vector<TH1*> doubleMuPt100dR0_3vect 	= doubleMuPt100dR0_3.analyseBtiTrigPerStatAndSlBestCase();
	std::vector<TH1*> doubleMuPt100dR0_2vect 	= doubleMuPt100dR0_2.analyseBtiTrigPerStatAndSlBestCase();
	std::vector<TH1*> doubleMuPt100dR0_1vect 	= doubleMuPt100dR0_1.analyseBtiTrigPerStatAndSlBestCase();
	std::vector<TH1*> doubleMuPt100dR0_075vect 	= doubleMuPt100dR0_075.analyseBtiTrigPerStatAndSlBestCase();
	std::vector<TH1*> doubleMuPt100dR0_05vect 	= doubleMuPt100dR0_05.analyseBtiTrigPerStatAndSlBestCase();
	std::vector<TH1*> doubleMuPt100dR0_025vect 	= doubleMuPt100dR0_025.analyseBtiTrigPerStatAndSlBestCase();
	std::vector<TH1*> doubleMuPt100dR0_01vect 	= doubleMuPt100dR0_01.analyseBtiTrigPerStatAndSlBestCase();
	std::vector<TH1*> doubleMuPt100dR0_005vect 	= doubleMuPt100dR0_005.analyseBtiTrigPerStatAndSlBestCase();

	TCanvas* c = cManager->getDividedCanvas(1,1);
	for (int i = 0; i < doubleMuPt100dR0_3vect.size()/8. ; ++i) {
		c->cd(i+1)->SetLogy();
		TString frameName = "BTI triggers for station ";
		frameName += i+1;
		frameName += ";# BTI Triggers;Fraction of all events";

		TH2D* frame = new TH2D("frame",frameName,1,-0.50,10.5,1,0.000001,1);
		frame->SetStats(kFALSE);
		frame->Draw();

		doubleMuPt100dR0_3vect[2*i]->SetLineColor(kBlack);
		doubleMuPt100dR0_3vect[2*i]->Scale(1/doubleMuPt100dR0_3vect[2*i]->Integral());
		doubleMuPt100dR0_3vect[2*i]->Draw("same");
		doubleMuPt100dR0_3vect[2*i+1]->SetLineColor(kBlack);
		doubleMuPt100dR0_3vect[2*i+1]->SetLineStyle(2);
		doubleMuPt100dR0_3vect[2*i+1]->Scale(1/doubleMuPt100dR0_3vect[2*i+1]->Integral());
		doubleMuPt100dR0_3vect[2*i+1]->Draw("same");

		doubleMuPt100dR0_2vect[2*i]->SetLineColor(kBlue);
		doubleMuPt100dR0_2vect[2*i+1]->SetLineColor(kBlue);
		doubleMuPt100dR0_2vect[2*i+1]->SetLineStyle(2);
		doubleMuPt100dR0_2vect[2*i]->Scale(1/doubleMuPt100dR0_2vect[2*i]->Integral());
		doubleMuPt100dR0_2vect[2*i+1]->Scale(1/doubleMuPt100dR0_2vect[2*i+1]->Integral());
		doubleMuPt100dR0_2vect[2*i]->Draw("same");
		doubleMuPt100dR0_2vect[2*i+1]->Draw("same");

		doubleMuPt100dR0_1vect[2*i]->SetLineColor(kViolet);
		doubleMuPt100dR0_1vect[2*i+1]->SetLineColor(kViolet);
		doubleMuPt100dR0_1vect[2*i+1]->SetLineStyle(2);
		doubleMuPt100dR0_1vect[2*i]->Scale(1/doubleMuPt100dR0_1vect[2*i]->Integral());
		doubleMuPt100dR0_1vect[2*i+1]->Scale(1/doubleMuPt100dR0_1vect[2*i+1]->Integral());
		doubleMuPt100dR0_1vect[2*i]->Draw("same");
		doubleMuPt100dR0_1vect[2*i+1]->Draw("same");

		doubleMuPt100dR0_075vect[2*i]->SetLineColor(kRed);
		doubleMuPt100dR0_075vect[2*i+1]->SetLineColor(kRed);
		doubleMuPt100dR0_075vect[2*i+1]->SetLineStyle(2);
		doubleMuPt100dR0_075vect[2*i]->Scale(1/doubleMuPt100dR0_075vect[2*i]->Integral());
		doubleMuPt100dR0_075vect[2*i+1]->Scale(1/doubleMuPt100dR0_075vect[2*i+1]->Integral());
		doubleMuPt100dR0_075vect[2*i]->Draw("same");
		doubleMuPt100dR0_075vect[2*i+1]->Draw("same");

		doubleMuPt100dR0_05vect[2*i]->SetLineColor(kOrange);
		doubleMuPt100dR0_05vect[2*i+1]->SetLineColor(kOrange);
		doubleMuPt100dR0_05vect[2*i+1]->SetLineStyle(2);
		doubleMuPt100dR0_05vect[2*i]->Scale(1/doubleMuPt100dR0_05vect[2*i]->Integral());
		doubleMuPt100dR0_05vect[2*i+1]->Scale(1/doubleMuPt100dR0_05vect[2*i+1]->Integral());
		doubleMuPt100dR0_05vect[2*i]->Draw("same");
		doubleMuPt100dR0_05vect[2*i+1]->Draw("same");

		doubleMuPt100dR0_025vect[2*i]->SetLineColor(kGreen);
		doubleMuPt100dR0_025vect[2*i+1]->SetLineColor(kGreen);
		doubleMuPt100dR0_025vect[2*i+1]->SetLineStyle(2);
		doubleMuPt100dR0_025vect[2*i]->Scale(1/doubleMuPt100dR0_025vect[2*i]->Integral());
		doubleMuPt100dR0_025vect[2*i+1]->Scale(1/doubleMuPt100dR0_025vect[2*i+1]->Integral());
		doubleMuPt100dR0_025vect[2*i]->Draw("same");
		doubleMuPt100dR0_025vect[2*i+1]->Draw("same");

		doubleMuPt100dR0_01vect[2*i]->SetLineColor(kTeal);
		doubleMuPt100dR0_01vect[2*i+1]->SetLineColor(kTeal);
		doubleMuPt100dR0_01vect[2*i+1]->SetLineStyle(2);
		doubleMuPt100dR0_01vect[2*i]->Scale(1/doubleMuPt100dR0_01vect[2*i]->Integral());
		doubleMuPt100dR0_01vect[2*i+1]->Scale(1/doubleMuPt100dR0_01vect[2*i+1]->Integral());
		doubleMuPt100dR0_01vect[2*i]->Draw("same");
		doubleMuPt100dR0_01vect[2*i+1]->Draw("same");

		doubleMuPt100dR0_005vect[2*i]->SetLineColor(kCyan -1);
		doubleMuPt100dR0_005vect[2*i+1]->SetLineColor(kCyan -1);
		doubleMuPt100dR0_005vect[2*i+1]->SetLineStyle(2);
		doubleMuPt100dR0_005vect[2*i]->Scale(1/doubleMuPt100dR0_005vect[2*i]->Integral());
		doubleMuPt100dR0_005vect[2*i+1]->Scale(1/doubleMuPt100dR0_005vect[2*i+1]->Integral());
		doubleMuPt100dR0_005vect[2*i]->Draw("same");
		doubleMuPt100dR0_005vect[2*i+1]->Draw("same");


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



		TLegend* l = new TLegend(0.7,.1,0.9,0.9);

		l->AddEntry(doubleMuPt100dR0_3vect[2*i],"#DeltaR 0.3 SL 1");
		l->AddEntry(doubleMuPt100dR0_3vect[2*i+1],"#DeltaR 0.3 SL 3");
		l->AddEntry(doubleMuPt100dR0_2vect[2*i],"#DeltaR 0.2 SL 1");
		l->AddEntry(doubleMuPt100dR0_2vect[2*i+1],"#DeltaR 0.2 SL 3");
		l->AddEntry(doubleMuPt100dR0_1vect[2*i],"#DeltaR 0.1 SL 1");
		l->AddEntry(doubleMuPt100dR0_1vect[2*i+1],"#DeltaR 0.1 SL 3");
		l->AddEntry(doubleMuPt100dR0_075vect[2*i],"#DeltaR 0.075 SL 1");
		l->AddEntry(doubleMuPt100dR0_075vect[2*i+1],"#DeltaR 0.075 SL 3");
		l->AddEntry(doubleMuPt100dR0_05vect[2*i],"#DeltaR 0.05 SL 1");
		l->AddEntry(doubleMuPt100dR0_05vect[2*i+1],"#DeltaR 0.05 SL 3");
		l->AddEntry(doubleMuPt100dR0_025vect[2*i],"#DeltaR 0.025 SL 1");
		l->AddEntry(doubleMuPt100dR0_025vect[2*i+1],"#DeltaR 0.025 SL 3");
		l->AddEntry(doubleMuPt100dR0_01vect[2*i],"#DeltaR 0.01 SL 1");
		l->AddEntry(doubleMuPt100dR0_01vect[2*i+1],"#DeltaR 0.01 SL 3");
		l->AddEntry(doubleMuPt100dR0_005vect[2*i],"#DeltaR 0.005 SL 1");
		l->AddEntry(doubleMuPt100dR0_005vect[2*i+1],"#DeltaR 0.005 SL 3");

//		l->AddEntry(sMuPt100dR0_025vect[2*i],"#DeltaR 0.025 SL 1");
//		l->AddEntry(sMuPt100dR0_025vect[2*i+1],"#DeltaR 0.025 SL 3");

		l->Draw();

	}
	cManager->addCanvas("btiTrigsPerStatAndSlTogether",c);


//################################
//### plot TRACO triggers together
//################################

	std::vector<TH1*> doubleMuPt100dR0_3tracoVect 	= doubleMuPt100dR0_3.analyseTracoTrigPerStationHtrig();
	std::vector<TH1*> doubleMuPt100dR0_2tracoVect 	= doubleMuPt100dR0_2.analyseTracoTrigPerStationHtrig();
	std::vector<TH1*> doubleMuPt100dR0_1tracoVect 	= doubleMuPt100dR0_1.analyseTracoTrigPerStationHtrig();
	std::vector<TH1*> doubleMuPt100dR0_075tracoVect	= doubleMuPt100dR0_075.analyseTracoTrigPerStationHtrig();
	std::vector<TH1*> doubleMuPt100dR0_05tracoVect 	= doubleMuPt100dR0_05.analyseTracoTrigPerStationHtrig();
	std::vector<TH1*> doubleMuPt100dR0_025tracoVect	= doubleMuPt100dR0_025.analyseTracoTrigPerStationHtrig();
	std::vector<TH1*> doubleMuPt100dR0_01tracoVect 	= doubleMuPt100dR0_01.analyseTracoTrigPerStationHtrig();
	std::vector<TH1*> doubleMuPt100dR0_005tracoVect	= doubleMuPt100dR0_005.analyseTracoTrigPerStationHtrig();


	c = cManager->getDividedCanvas(2,2);

	for (int i = 0; i < doubleMuPt100dR0_3tracoVect.size() ; ++i) {
		c->cd(i+1)->SetLogy();
		TString frameName = "TRACO triggers (HTRG) for station ";
		frameName += i+1;
		frameName += ";# TRACO Triggers;Fraction of all events events";

		TH2D* frame = new TH2D("frameTraco",frameName,1,-0.5,7.5,1,0.000001,1);
		frame->SetStats(kFALSE);
		frame->Draw();

		doubleMuPt100dR0_3tracoVect[i]->SetLineColor(kBlack);
		doubleMuPt100dR0_3tracoVect[i]->Scale(1/doubleMuPt100dR0_3tracoVect[i]->Integral());
		doubleMuPt100dR0_3tracoVect[i]->Draw("same");

		doubleMuPt100dR0_2tracoVect[i]->SetLineColor(kBlue);
		doubleMuPt100dR0_2tracoVect[i]->Scale(1/doubleMuPt100dR0_2tracoVect[i]->Integral());
		doubleMuPt100dR0_2tracoVect[i]->Draw("same");

		doubleMuPt100dR0_1tracoVect[i]->SetLineColor(kViolet);
		doubleMuPt100dR0_1tracoVect[i]->Scale(1/doubleMuPt100dR0_1tracoVect[i]->Integral());
		doubleMuPt100dR0_1tracoVect[i]->Draw("same");

		doubleMuPt100dR0_075tracoVect[i]->SetLineColor(kRed);
		doubleMuPt100dR0_075tracoVect[i]->Scale(1/doubleMuPt100dR0_075tracoVect[i]->Integral());
		doubleMuPt100dR0_075tracoVect[i]->Draw("same");

		doubleMuPt100dR0_05tracoVect[i]->SetLineColor(kOrange);
		doubleMuPt100dR0_05tracoVect[i]->Scale(1/doubleMuPt100dR0_05tracoVect[i]->Integral());
		doubleMuPt100dR0_05tracoVect[i]->Draw("same");

		doubleMuPt100dR0_025tracoVect[i]->SetLineColor(kGreen);
		doubleMuPt100dR0_025tracoVect[i]->Scale(1/doubleMuPt100dR0_025tracoVect[i]->Integral());
		doubleMuPt100dR0_025tracoVect[i]->Draw("same");

		doubleMuPt100dR0_01tracoVect[i]->SetLineColor(kTeal);
		doubleMuPt100dR0_01tracoVect[i]->Scale(1/doubleMuPt100dR0_01tracoVect[i]->Integral());
		doubleMuPt100dR0_01tracoVect[i]->Draw("same");

		doubleMuPt100dR0_005tracoVect[i]->SetLineColor(kCyan - 1);
		doubleMuPt100dR0_005tracoVect[i]->Scale(1/doubleMuPt100dR0_005tracoVect[i]->Integral());
		doubleMuPt100dR0_005tracoVect[i]->Draw("same");

		TLegend* l = new TLegend(0.75,.55,0.95,0.95);

		l->AddEntry(doubleMuPt100dR0_3tracoVect[i],"#DeltaR 0.3");
		l->AddEntry(doubleMuPt100dR0_2tracoVect[i],"#DeltaR 0.2");
		l->AddEntry(doubleMuPt100dR0_1tracoVect[i],"#DeltaR 0.1");
		l->AddEntry(doubleMuPt100dR0_075tracoVect[i],"#DeltaR 0.075");
		l->AddEntry(doubleMuPt100dR0_05tracoVect[i],"#DeltaR 0.05");
		l->AddEntry(doubleMuPt100dR0_025tracoVect[i],"#DeltaR 0.025");
		l->AddEntry(doubleMuPt100dR0_01tracoVect[i],"#DeltaR 0.01");
		l->AddEntry(doubleMuPt100dR0_005tracoVect[i],"#DeltaR 0.005");

		l->Draw();

	}
	cManager->addCanvas("tracoTrigsPerStatTogether",c);

	cManager->storePlots();

	std::cout << "All done!\nExit via ctrl+c..." << std::endl;
//	app->Run();
	delete cManager;
	return 0;
}
