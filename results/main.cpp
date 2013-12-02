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

	std::cout << "Getting Tree for DES17 14TeV sample" << std::endl;
	TTree* des17Tree = (TTree*)(new TFile("UPG2017-v2_studies/DTTrigTest.root"))->Get("h1");
	if(!des17Tree){
		std::cout << "Error! Des 17 14 TeV tree is null pointer!" << std::endl;
		return -1;
	}
	std::cout << "Creating Analyse object with Des 17 14TeV" << std::endl;
	Analyse des17Analyse(des17Tree,"des17",true);

	//#######################
	//# N Gen Muons
	//#######################

	std::cout << "Making N gen muons plots" << std::endl;
	TCanvas* cGenMuons = new TCanvas( "nGen" , "Gen Muon distribution" , 1600 , 1200 );
	//Des 17 sample
	TH1D* genMuonsDes17 = des17Analyse.plotNGenMuons();
	genMuonsDes17->Draw();

	//Mu gun sample
	TH1D* genMuonsMuGun = muGunAnalyse.plotNGenMuons();
	genMuonsMuGun->SetLineColor(TColor::GetColorBright(1));
	genMuonsMuGun->Draw("same");

	cGenMuons->SetLogy();

	TLegend* leg = new TLegend(0.3,0.7,0.68,0.9);
	leg->AddEntry(genMuonsDes17,"Des 17","l");
	leg->AddEntry(genMuonsMuGun,"Mu Gun","l");
	leg->Draw();

	//#######################
	//# Gen particle ID
	//#######################

	std::cout << "Making gen particles ID plots" << std::endl;
	TCanvas* cGenParticles = new TCanvas( "genParticles" , "Gen particle ID distribution" , 1600 , 1200 );
	//Des 17 sample
	TH1D* genParticlesDes17 = des17Analyse.plotGenParticles();
	genParticlesDes17->Draw();

	//Mu gun sample
	TH1D* genParticlesMuGun = muGunAnalyse.plotGenParticles();
	genParticlesMuGun->SetLineColor(TColor::GetColorBright(1));
	genParticlesMuGun->Draw("same");

	TLegend* leg2 = new TLegend(0.3,0.7,0.68,0.9);
	leg2->AddEntry(genParticlesDes17,"Des 17","l");
	leg2->AddEntry(genParticlesMuGun,"Mu Gun","l");
	leg2->Draw();

	//#######################
	//# BTI Triggers
	//#######################

	std::cout << "Making BTI trigger plots" << std::endl;
	std::vector<TH1D*> btiVector;

	btiVector.push_back(muGunAnalyse.plotBtiTriggers());
	btiVector.push_back(des17Analyse.plotBtiTriggers());

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

	//Des 17 sample
	std::vector<TH1D*> btiPerStationDes17;
	for( int i = 0 ; i < 4 ; i++){
		btiPerStationDes17.push_back(des17Analyse.plotBtiTriggersPerStation( i+1 ));
	}
	TCanvas* cBtiPerStDes17 = analyseBtiTriggersPerStation(btiPerStationDes17,"des17");

	//#######################
	//# TRACO Triggers
	//#######################

	std::cout << "Making TRACO trigger plots" << std::endl;
	std::vector<TH1D*> tracoVector;

	tracoVector.push_back(muGunAnalyse.plotTracoTriggers());
	tracoVector.push_back(des17Analyse.plotTracoTriggers());

	TCanvas* cTracoTriggers = analyseTracoTriggers(tracoVector);

	//All done. Save canvases and run root app

	gSystem->MakeDirectory("./plots");
	gSystem->MakeDirectory("./plots/png");
	gSystem->MakeDirectory("./plots/pdf");

	//Make png files
	cTracoTriggers->SaveAs("plots/png/tracoTriggers.png");
	cBtiPerStDes17->SaveAs("plots/png/btiTriggersPerStationDes17.png");
	cBtiPerStMuGun->SaveAs("plots/png/btiTriggersPerStationMuGun.png");
	cBtiTriggers->SaveAs("plots/png/btiTriggers.png");
	cGenMuons->SaveAs("plots/png/genMuons.png");
	cGenParticles->SaveAs("plots/png/genParticles.png");

	//Make pdf files
	cTracoTriggers->SaveAs("plots/pdf/tracoTriggers.pdf");
	cBtiPerStDes17->SaveAs("plots/pdf/btiTriggersPerStationDes17.pdf");
	cBtiPerStMuGun->SaveAs("plots/pdf/btiTriggersPerStationMuGun.pdf");
	cBtiTriggers->SaveAs("plots/pdf/btiTriggers.pdf");
	cGenMuons->SaveAs("plots/pdf/genMuons.pdf");
	cGenParticles->SaveAs("plots/pdf/genParticles.pdf");


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
