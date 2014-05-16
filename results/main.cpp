#include "Analyse.h"

#include "PlotStyle.h"
#include "CanvasManager.h"
#include "AnalysisWrapper.h"
#include "PlotTitle.h"

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
#include "TPaveText.h"

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>

int main(int argc, char** argv){
	std::cout << "Starting application" << std::endl;
	TApplication* app = new TApplication("Analyse",&argc,argv);

	//Set plot style for own root design
	PlotStyle* s = new PlotStyle();

	CanvasManager* cManager = new CanvasManager("combinedPlots");

	//#######################
	//# Creating Trees and Analyse objects
	//#######################

	AnalysisWrapper doubleMuPt100dR0_3("deltaPhiGun/DeltaPhiGunPt100dPhi0_3/TrigTestDeltaPhiGun.root","DeltaPhiGunPt100dR0_3",10.,true);
		doubleMuPt100dR0_3.analyseBti();
		doubleMuPt100dR0_3.analyseTraco();
		doubleMuPt100dR0_3.analyseGenParticles();
		doubleMuPt100dR0_3.savePlots();

	AnalysisWrapper doubleMuPt100dR0_1("deltaPhiGun/DeltaPhiGunPt100dPhi0_1/TrigTestDeltaPhiGun.root","DeltaPhiGunPt100dR0_1",10.,true);
	//	doubleMuPt100dR0_1.analyseBti();
	//	doubleMuPt100dR0_1.analyseTraco();
	//	doubleMuPt100dR0_1.analyseGenParticles();
	//	doubleMuPt100dR0_1.savePlots();

	AnalysisWrapper doubleMuPt100dR0_05("deltaPhiGun/DeltaPhiGunPt100dPhi0_05/TrigTestDeltaPhiGun.root","DeltaPhiGunPt100dR0_05",10.,true);
	//	doubleMuPt100dR0_05.analyseBti();
	//	doubleMuPt100dR0_05.analyseTraco();
	//	doubleMuPt100dR0_05.analyseGenParticles();
	//	doubleMuPt100dR0_05.savePlots();

	AnalysisWrapper doubleMuPt100dR0_01("deltaPhiGun/DeltaPhiGunPt100dPhi0_01/TrigTestDeltaPhiGun.root","DeltaPhiGunPt100dR0_01",10.,true);
	//	doubleMuPt100dR0_01.analyseBti();
	//	doubleMuPt100dR0_01.analyseTraco();
	//	doubleMuPt100dR0_01.analyseGenParticles();
	//	doubleMuPt100dR0_01.savePlots();

	AnalysisWrapper doubleMuPt100dR0_005("deltaPhiGun/DeltaPhiGunPt100dPhi0_005/TrigTestDeltaPhiGun.root","DeltaPhiGunPt100dR0_005",10.,true);
	//	doubleMuPt100dR0_005.analyseBti();
	//	doubleMuPt100dR0_005.analyseTraco();
	//	doubleMuPt100dR0_005.analyseGenParticles();
	//	doubleMuPt100dR0_005.savePlots();

	//Create a vector with colors to access during scenario iterations
	std::vector<int> colorVector;
	colorVector.push_back(kBlack);
	colorVector.push_back(kBlue);
	colorVector.push_back(kViolet);
	colorVector.push_back(kRed);
	colorVector.push_back(kOrange);
	colorVector.push_back(kGreen);
	colorVector.push_back(kTeal);
	colorVector.push_back(kCyan - 1);

	//Create a vector with scenarios to access during scenario iterations
	std::vector<TString> legendNameVector;
	legendNameVector.push_back(TString("#DeltaR 0.3"));
	legendNameVector.push_back(TString("#DeltaR 0.1"));
	legendNameVector.push_back(TString("#DeltaR 0.05"));
	legendNameVector.push_back(TString("#DeltaR 0.01"));
	legendNameVector.push_back(TString("#DeltaR 0.005"));

	std::vector<std::vector<TH1*> > btiScenariosBestCase;

	btiScenariosBestCase.push_back(doubleMuPt100dR0_3.analyseBtiTrigPerStatAndSlBestCase());
	btiScenariosBestCase.push_back(doubleMuPt100dR0_1.analyseBtiTrigPerStatAndSlBestCase());
	btiScenariosBestCase.push_back(doubleMuPt100dR0_05.analyseBtiTrigPerStatAndSlBestCase());
	btiScenariosBestCase.push_back(doubleMuPt100dR0_01.analyseBtiTrigPerStatAndSlBestCase());
	btiScenariosBestCase.push_back(doubleMuPt100dR0_005.analyseBtiTrigPerStatAndSlBestCase());

	std::vector<std::vector<TH1*> > btiScenariosHtrg;

	btiScenariosHtrg.push_back(doubleMuPt100dR0_3.analyseBtiTrigPerStatAndSlHtrg());
	btiScenariosHtrg.push_back(doubleMuPt100dR0_1.analyseBtiTrigPerStatAndSlHtrg());
	btiScenariosHtrg.push_back(doubleMuPt100dR0_05.analyseBtiTrigPerStatAndSlHtrg());
	btiScenariosHtrg.push_back(doubleMuPt100dR0_01.analyseBtiTrigPerStatAndSlHtrg());
	btiScenariosHtrg.push_back(doubleMuPt100dR0_005.analyseBtiTrigPerStatAndSlHtrg());


	TCanvas* btiBestCaseCanvas = cManager->getDividedCanvas(1,1);
	btiBestCaseCanvas->SetName("btiTrigsPerStatAndSlTogetherBestCase");
	TCanvas* btiHtrgCanvas = cManager->getDividedCanvas(1,1);
	btiHtrgCanvas->SetName("btiTrigsPerStatAndSlTogetherHtrg");

	//Get the size of the first vector stored in the scenarios
	for (int i = 0 ; i < btiScenariosBestCase[0].size()/8. ; i++){
		int scenarioCounter = 0;
		TLegend* lBestCase = new TLegend(0.5,.525,0.7,0.9);
		TLegend* lBestCase2 = new TLegend(0.7,.525,0.9,0.9);
		TLegend* lHtrg = new TLegend(0.5,.525,0.7,0.9);
		TLegend* lHtrg2 = new TLegend(0.7,.525,0.9,0.9);

		btiBestCaseCanvas->cd(i+1)->SetLogy();
		//Build the frame
		TString frameName = "BTI Trigger (Best Case) f#ddot{u}r Station ";
		frameName += i+1;
		frameName += ";# BTI Trigger;Relative H#ddot{a}ufigkeit";

		TH2D* frame = new TH2D("frameBtiBestCase",frameName,1,-0.5,10.5,1,0.000001,1);
		frame->SetStats(kFALSE);
		frame->Draw();

		for (std::vector<std::vector<TH1*> >::const_iterator scenarioIt = btiScenariosBestCase.begin();
				scenarioIt != btiScenariosBestCase.end() ; scenarioIt++){

			//Loop over the scenarios
			scenarioIt->at(2*i)->SetLineColor(colorVector[scenarioCounter]);
			scenarioIt->at(2*i)->Scale(1/scenarioIt->at(2*i)->Integral());
			scenarioIt->at(2*i)->Draw("same");
			scenarioIt->at(2*i+1)->SetLineColor(colorVector[scenarioCounter]);
			scenarioIt->at(2*i+1)->SetLineStyle(2);
			scenarioIt->at(2*i+1)->Scale(1/scenarioIt->at(2*i+1)->Integral());
			scenarioIt->at(2*i+1)->Draw("same");

			lBestCase->AddEntry(scenarioIt->at(2*i),(legendNameVector[scenarioCounter] + " SL 1").Data());
			lBestCase2->AddEntry(scenarioIt->at(2*i+1),(legendNameVector[scenarioCounter] + " SL 3").Data());

			scenarioCounter++;
		}
		lBestCase->Draw();
		lBestCase2->Draw();

		btiBestCaseCanvas->Update();
		TString plotTitle("BTI Trigger (Best Case) f#ddot{u}r Station ");
		plotTitle += i+1;
		(new PlotTitle(plotTitle.Data()))->Draw();

		scenarioCounter = 0;

		btiHtrgCanvas->cd(i+1)->SetLogy();
		//Build the frame
		frameName = "BTI Trigger (HTRG) f#ddot{u}r Station ";
		frameName += i+1;
		frameName += ";# BTI Trigger;Relative H#ddot{a}ufigkeit";

		frame = new TH2D("frameBtiHtrg",frameName,1,-0.5,25.5,1,0.000001,1);
		frame->SetStats(kFALSE);
		frame->Draw();

		for (std::vector<std::vector<TH1*> >::const_iterator scenarioIt = btiScenariosHtrg.begin();
				scenarioIt != btiScenariosHtrg.end() ; scenarioIt++){

			//Loop over the scenarios
			scenarioIt->at(2*i)->SetLineColor(colorVector[scenarioCounter]);
			scenarioIt->at(2*i)->Scale(1/scenarioIt->at(2*i)->Integral());
			scenarioIt->at(2*i)->Draw("same");
			scenarioIt->at(2*i+1)->SetLineColor(colorVector[scenarioCounter]);
			scenarioIt->at(2*i+1)->SetLineStyle(2);
			scenarioIt->at(2*i+1)->Scale(1/scenarioIt->at(2*i+1)->Integral());
			scenarioIt->at(2*i+1)->Draw("same");

			lHtrg->AddEntry(scenarioIt->at(2*i),(legendNameVector[scenarioCounter] + " SL 1").Data());
			lHtrg2->AddEntry(scenarioIt->at(2*i+1),(legendNameVector[scenarioCounter] + " SL 3").Data());

			scenarioCounter++;
		}
		lHtrg->Draw();
		lHtrg2->Draw();

		btiHtrgCanvas->Update();

		plotTitle = "BTI Trigger (HTRG) f#ddot{u}r Station ";
		plotTitle += i+1;
		(new PlotTitle(plotTitle.Data()))->Draw();
	}

	cManager->addCanvas("btiTrigsPerStatAndSlTogetherBestCase",btiBestCaseCanvas);
	cManager->addCanvas("btiTrigsPerStatAndSlTogetherHtrg",btiHtrgCanvas);


	//################################
	//### plot TRACO triggers together
	//################################

	std::vector<std::vector<TH1*> > tracoScenariosBestCase;

	tracoScenariosBestCase.push_back(doubleMuPt100dR0_3.analyseTracoTrigPerStationBestCase());
	tracoScenariosBestCase.push_back(doubleMuPt100dR0_1.analyseTracoTrigPerStationBestCase());
	tracoScenariosBestCase.push_back(doubleMuPt100dR0_05.analyseTracoTrigPerStationBestCase());
	tracoScenariosBestCase.push_back(doubleMuPt100dR0_01.analyseTracoTrigPerStationBestCase());
	tracoScenariosBestCase.push_back(doubleMuPt100dR0_005.analyseTracoTrigPerStationBestCase());

	std::vector<std::vector<TH1*> > tracoScenariosHtrg;

	tracoScenariosHtrg.push_back(doubleMuPt100dR0_3.analyseTracoTrigPerStationHtrig());
	tracoScenariosHtrg.push_back(doubleMuPt100dR0_1.analyseTracoTrigPerStationHtrig());
	tracoScenariosHtrg.push_back(doubleMuPt100dR0_05.analyseTracoTrigPerStationHtrig());
	tracoScenariosHtrg.push_back(doubleMuPt100dR0_01.analyseTracoTrigPerStationHtrig());
	tracoScenariosHtrg.push_back(doubleMuPt100dR0_005.analyseTracoTrigPerStationHtrig());


	TCanvas* tracoBestCaseCanvas = cManager->getDividedCanvas(1,1);
	tracoBestCaseCanvas->SetName("tracoTrigsPerStatTogetherBestCase");
	TCanvas* tracoHtrgCanvas = cManager->getDividedCanvas(1,1);
	tracoHtrgCanvas->SetName("tracoTrigsPerStatTogetherHtrg");

	//Get the size of the first vector stored in the scenarios
	for (int i = 0 ; i < tracoScenariosBestCase[0].size()/4. ; i++){
		int scenarioCounter = 0;
		TLegend* lBestCase = new TLegend(0.75,.45,0.90,0.90);
		TLegend* lHtrg = new TLegend(0.75,.45,0.90,0.90);

		tracoBestCaseCanvas->cd(i+1)->SetLogy();
		//Build the frame
		TString frameName = "TRACO Trigger (Best Case) f#ddot{u}r Station ";
		frameName += i+1;
		frameName += ";# TRACO Trigger;Relative H#ddot{a}ufigkeit";

		TH2D* frame = new TH2D("frameTracoBestCase",frameName,1,-0.5,7.5,1,0.000001,1);
		frame->SetStats(kFALSE);
		frame->Draw();

		for (std::vector<std::vector<TH1*> >::const_iterator scenarioIt = tracoScenariosBestCase.begin();
				scenarioIt != tracoScenariosBestCase.end() ; scenarioIt++){

			//Loop over the scenarios
			scenarioIt->at(i)->SetLineColor(colorVector[scenarioCounter]);
			scenarioIt->at(i)->Scale(1/scenarioIt->at(i)->Integral());
			scenarioIt->at(i)->Draw("same");

			lBestCase->AddEntry(scenarioIt->at(i),legendNameVector[scenarioCounter]);

			scenarioCounter++;
		}
		lBestCase->Draw();

		tracoBestCaseCanvas->Update();
		TString plotTitle("TRACO Trigger (Best Case) f#ddot{u}r Station ");
		plotTitle += i+1;
		(new PlotTitle(plotTitle.Data()))->Draw();

		scenarioCounter = 0;
		tracoHtrgCanvas->cd(i+1)->SetLogy();
		//Build the frame
		frameName = "TRACO Trigger (HTRG) f#ddot{u}r Station ";
		frameName += i+1;
		frameName += ";# TRACO Trigger;Relative H#ddot{a}ufigkeit";

		frame = new TH2D("frameTracoHtrg",frameName,1,-0.5,7.5,1,0.000001,1);
		frame->SetStats(kFALSE);
		frame->Draw();
		for (std::vector<std::vector<TH1*> >::const_iterator scenarioIt = tracoScenariosHtrg.begin();
				scenarioIt != tracoScenariosHtrg.end() ; scenarioIt++){

			//Loop over the scenarios
			scenarioIt->at(i)->SetLineColor(colorVector[scenarioCounter]);
			scenarioIt->at(i)->Scale(1/scenarioIt->at(i)->Integral());
			scenarioIt->at(i)->Draw("same");

			lHtrg->AddEntry(scenarioIt->at(i),legendNameVector[scenarioCounter]);

			scenarioCounter++;
		}
		lHtrg->Draw();

		tracoHtrgCanvas->Update();
		plotTitle = "TRACO Trigger (HTRG) f#ddot{u}r Station ";
		plotTitle += i+1;
		(new PlotTitle(plotTitle.Data()))->Draw();

	}

	cManager->addCanvas("tracoTrigsPerStatTogetherBestCase",tracoBestCaseCanvas);
	cManager->addCanvas("tracoTrigsPerStatTogetherHtrg",tracoHtrgCanvas);

	cManager->storePlots();

	int scenarioCounter = 0;
	std::cout << "N Entries in traco HTRIG Scenarios:" << std::endl;
	for (std::vector<std::vector<TH1*> >::const_iterator scenarioIt = tracoScenariosHtrg.begin();
			scenarioIt != tracoScenariosHtrg.end() ; scenarioIt++) {
		std::cout << "\t" << legendNameVector[scenarioCounter] << ":\t" << scenarioIt->at(0)->GetEntries() << std::endl;
		scenarioCounter++;
	}
	std::cout << std::endl;
	scenarioCounter = 0;
	std::cout << "N Entries in traco BestCase Scenarios:" << std::endl;
	for (std::vector<std::vector<TH1*> >::const_iterator scenarioIt = tracoScenariosBestCase.begin();
			scenarioIt != tracoScenariosBestCase.end() ; scenarioIt++) {
		std::cout << "\t" << legendNameVector[scenarioCounter] << ":\t" << scenarioIt->at(0)->GetEntries() << std::endl;
		scenarioCounter++;
	}
	std::cout << std::endl;
	scenarioCounter = 0;
	std::cout << "N Entries in bti Best case Scenarios:" << std::endl;
	for (std::vector<std::vector<TH1*> >::const_iterator scenarioIt = btiScenariosBestCase.begin();
			scenarioIt != btiScenariosBestCase.end() ; scenarioIt++) {
		std::cout << "\t" << legendNameVector[scenarioCounter] << ":\t" << scenarioIt->at(0)->GetEntries() << std::endl;
		scenarioCounter++;
	}
	std::cout << std::endl;
	scenarioCounter = 0;
	std::cout << "N Entries in bti HTRG Scenarios:" << std::endl;
	for (std::vector<std::vector<TH1*> >::const_iterator scenarioIt = btiScenariosHtrg.begin();
			scenarioIt != btiScenariosHtrg.end() ; scenarioIt++) {
		std::cout << "\t" << legendNameVector[scenarioCounter] << ":\t" << scenarioIt->at(0)->GetEntries() << std::endl;
		scenarioCounter++;
	}
	std::cout << std::endl;

	delete btiBestCaseCanvas;
	delete btiHtrgCanvas;
	delete tracoBestCaseCanvas;
	delete tracoHtrgCanvas;

	std::cout << "All done!\nExit via ctrl+c..." << std::endl;
	//	app->Run();
	delete cManager;
	return 0;
}
