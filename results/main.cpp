#include "Analyse.h"

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

//Function declarations for plotting all histograms togther.
//Definitions are below the main function
TCanvas* analyseBtiTriggers(std::vector<TH1D*>);
TCanvas* analyseTracoTriggers(std::vector<TH1D*>);
TCanvas* analyseBtiTriggersPerStation(std::vector<TH1D*>,std::string);

int main(int argc, char** argv){
	std::cout << "Starting application" << std::endl;
	TApplication* app = new TApplication("Analyse",&argc,argv);

	//#######################
	//# Creating Trees and Analyse objects
	//#######################

	std::cout << "Getting Tree for mu gun sample" << std::endl;
	TTree* muGunTree = (TTree*)(new TFile("DIMUGUN_studies/DTTrigTest.root"))->Get("h1");
	if(!muGunTree){
		std::cout << "Error! Mu gun tree is null pointer!" << std::endl;
		return -1;
	}
	std::cout << "Creating Analyse object with mu gun tree" << std::endl;
	Analyse muGunAnalyse(muGunTree,"muGun",true);

	std::cout << "Getting Tree for PU140 14TeV sample" << std::endl;
	TTree* pu140Tree = (TTree*)(new TFile("UPG2017-v2_studies/DTTrigTest.root"))->Get("h1");
	if(!pu140Tree){
		std::cout << "Error! PU 140 14 TeV tree is null pointer!" << std::endl;
		return -1;
	}
	std::cout << "Creating Analyse object with PU 140 14TeV" << std::endl;
	Analyse pu140Analyse(pu140Tree,"pu140",true);

	//#######################
	//# N Gen Muons
	//#######################

	std::cout << "Making N gen muons plots" << std::endl;
	TCanvas* cGenMuons = new TCanvas( "nGen" , "Gen Muon distribution" , 1600 , 1200 );
	//Pu 140 sample
	TH1D* genMuonsPu140 = pu140Analyse.plotNGenMuons();
	genMuonsPu140->SetLineWidth(2);
	genMuonsPu140->Draw();

	//Mu gun sample
	TH1D* genMuonsMuGun = muGunAnalyse.plotNGenMuons();
	genMuonsMuGun->SetLineWidth(2);
	genMuonsMuGun->SetLineColor(TColor::GetColorBright(1));
	genMuonsMuGun->Draw("same");

	cGenMuons->SetLogy();

	TLegend* leg = new TLegend(0.3,0.7,0.68,0.9);
	leg->AddEntry(genMuonsPu140,"PU 140","l");
	leg->AddEntry(genMuonsMuGun,"Mu Gun","l");
	leg->Draw();

	//#######################
	//# BTI Triggers
	//#######################

	std::cout << "Making BTI trigger plots" << std::endl;
	std::vector<TH1D*> btiVector;

	btiVector.push_back(muGunAnalyse.plotBtiTriggers());
	btiVector.push_back(pu140Analyse.plotBtiTriggers());

	TCanvas* cBtiTriggers = analyseBtiTriggers(btiVector);

	//#######################
	//# BTI Triggers per station
	//#######################

	//Mu Gun sample
	std::vector<TH1D*> btiPerStationMuGun;
	for( int i = 0 ; i < 4 ; i++){
		btiPerStationMuGun.push_back(muGunAnalyse.plotBtiTriggersPerStation( i+1 ));
	}
	TCanvas* cBtiPerStMuGun = analyseBtiTriggersPerStation(btiPerStationMuGun,"muGun");

	//PU 140 sample
	std::vector<TH1D*> btiPerStationPu140;
	for( int i = 0 ; i < 4 ; i++){
		btiPerStationPu140.push_back(pu140Analyse.plotBtiTriggersPerStation( i+1 ));
	}
	TCanvas* cBtiPerStPu140 = analyseBtiTriggersPerStation(btiPerStationPu140,"pu140");

	//#######################
	//# TRACO Triggers
	//#######################

	std::cout << "Making TRACO trigger plots" << std::endl;
	std::vector<TH1D*> tracoVector;

	tracoVector.push_back(muGunAnalyse.plotTracoTriggers());
	tracoVector.push_back(pu140Analyse.plotTracoTriggers());

	TCanvas* cTracoTriggers = analyseTracoTriggers(tracoVector);

	//All done. Save canvases and run root app

	gSystem->MakeDirectory("./plots");

	cTracoTriggers->SaveAs("plots/tracoTriggers.png");
	cBtiPerStPu140->SaveAs("plots/btiTriggersPerStationPu140.png");
	cBtiPerStMuGun->SaveAs("plots/btiTriggersPerStationMuGun.png");
	cBtiTriggers->SaveAs("plots/btiTriggers.png");
	cGenMuons->SaveAs("plots/genMuons.png");

	std::cout << "All done!\nExit via ctrl+c..." << std::endl;
	app->Run();
}

/**
 * Run over all histograms with BTI triggers per station and plot them together on one canvas
 */
TCanvas* analyseBtiTriggersPerStation(std::vector<TH1D*> input , std::string sampleInfo){
	if( !( &input ) ){
		std::cout << "[main] Null pointer for BTI trigger per station hist vector.\nReturning." << std::endl;
		return NULL;
	} else if ( input.size() == 0 ){
		std::cout << "[main] Empty BTI trigger per station hist vector.\nReturning." << std::endl;
		return NULL;
	}
	TString name("btiTriggersPerSt");
	name += sampleInfo;

	TString title("BTI Triggers per Station ");
	title += sampleInfo;

	TCanvas* canvas = new TCanvas( name.Data() , title.Data() , 1600 , 1200);
	int nHistos = input.size();
	int rowsX,rowsY;
	rowsX = ceil( sqrt(nHistos) );
	rowsY = ceil( sqrt(nHistos) );
	canvas->Divide( rowsX , rowsY );

	canvas->cd(1);
	input[0]->Draw();
	for( int i = 1 ; i < nHistos ; i++ ){
		canvas->cd(i+1);
		input[i]->SetLineColor( TColor::GetColorBright(i) );
		input[i]->Draw();
	}
	return canvas;
}

/**
 * Run over all bti trigger plots to plot them together in one histogram
 */
TCanvas* analyseBtiTriggers(std::vector<TH1D*> input){
	if( !( &input ) ){
		std::cout << "[main] Null pointer for BTI trigger hist vector.\nReturning." << std::endl;
		return NULL;
	} else if ( input.size() == 0 ){
		std::cout << "[main] Empty BTI trigger hist vector.\nReturning." << std::endl;
		return NULL;
	}
	TCanvas* canvas = new TCanvas("btiTriggersCanvas","BTI Triggers",1600,1200);
	int nHistos = input.size();
	int rowsX,rowsY;
	rowsX = ceil(sqrt(nHistos));
	rowsY = ceil(sqrt(nHistos));
	canvas->Divide(rowsX,rowsY);

	canvas->cd(1);
	input[0]->Draw();
	for( int i = 1 ; i < nHistos ; i++ ){
		canvas->cd(i+1);
		input[i]->SetLineColor( TColor::GetColorBright(i) );
		input[i]->Draw("Same");
	}
	return canvas;
}

/**
 * Run over all traco trigger plots to plot them together in one histogram
 */
TCanvas* analyseTracoTriggers(std::vector<TH1D*> input){
	if( !( &input ) ){
		std::cout << "[main] Null pointer for TRACO trigger hist vector.\nReturning." << std::endl;
		return NULL;
	} else if ( input.size() == 0 ){
		std::cout << "[main] Empty TRACO trigger hist vector.\nReturning." << std::endl;
		return NULL;
	}
	TCanvas* canvas = new TCanvas("tracoTriggersCanvas","TRACO Triggers",1600,1200);
	int nHistos = input.size();
	int rowsX,rowsY;
	rowsX = ceil(sqrt(nHistos));
	rowsY = ceil(sqrt(nHistos));
	canvas->Divide(rowsX,rowsY);

	canvas->cd(1);
	input[0]->Draw();
	for( int i = 1 ; i < nHistos ; i++ ){
		canvas->cd(i+1);
		input[i]->SetLineColor( TColor::GetColorBright(i) );
		input[i]->Draw("Same");
	}
	return canvas;

}
