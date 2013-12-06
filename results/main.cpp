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

//Function declarations for plotting all histograms togther.
//Definitions are below the main function
TCanvas* analyseBtiTriggers(std::vector<TH1D*>);
TCanvas* analyseTracoTriggers(std::vector<TH1D*>);
TCanvas* analyseBtiTriggersPerStation(std::vector<TH1D*>,std::string);
TCanvas* analyseBtiTriggersPerEta(std::vector<TH1D*> input);
TCanvas* plotDividedCanvas(std::vector<TH1D*> input, int nY = 0);
TCanvas* getDividedCanvas(int nX, int nY = 0);
void storePlots(TCanvas*,std::string);

int main(int argc, char** argv){
	std::cout << "Starting application" << std::endl;
	TApplication* app = new TApplication("Analyse",&argc,argv);

	//Set plot style for own root design
	PlotStyle* s = new PlotStyle();

	CanvasManager cManager;

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
	TTree* des17Tree = (TTree*)(new TFile("UPG2017-v2_studies/DTTrigTest_Pt10.root"))->Get("h1");
	if(!des17Tree){
		std::cout << "Error! Des 17 14 TeV tree is null pointer!" << std::endl;
		return -1;
	}
	std::cout << "Creating Analyse object with Des 17 14TeV" << std::endl;
	Analyse des17Analyse(des17Tree,"des17",true);

	AnalysisWrapper muGunPt10Wrapper(muGunTree,"muGun",10.,true);
	muGunPt10Wrapper.analyseBti();
	muGunPt10Wrapper.savePlots();

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
	cGenParticles->SetLogy();
	TLegend* leg2 = new TLegend(0.1,0.7,0.48,0.9);
	leg2->AddEntry(genParticlesDes17,"Des 17","l");
	leg2->AddEntry(genParticlesMuGun,"Mu Gun","l");
	leg2->Draw();

	//#######################
	//# Gen particle eta with no bti trigger in event
	//#######################
//	TCanvas* cGenParticlesEta = new TCanvas( "genParticlesEta" , "Gen particle #eta distribution" , 1600 , 1200 );
//	TH1D* genParticlesEta = des17Analyse.plotEtaNoBtiTriggers();
//	genParticlesEta->Draw();

	//#######################
	//# BTI triggers over BX ID
	//#######################
/*	TCanvas* cBtiVsBx = new TCanvas( "cBtiVsBx" , "BX ID distribution" , 1600 , 1200 );
	des17Analyse.plotBtiTrgVsBx()->Draw();*/

	//#######################
	//# BTI triggers with no Theta information
	//#######################
/*
	TCanvas* cBtiNoTheta = getDividedCanvas(2,3);
	cBtiNoTheta->SetName("cBtiNoTheta");
	cBtiNoTheta->SetTitle("Distribution of BTI triggers with no theta info");
	for( int i = 0 ; i < 3 ; i++ ){
		cBtiNoTheta->cd( 2*i + 1 );
		TH2D* h = des17Analyse.plotNoBtiTheta( i+1 );
		h->Draw("Colz");
		h->SetStats(false);
		cBtiNoTheta->cd(2*(i+1));
		TH2D* h2 = muGunAnalyse.plotNoBtiTheta( i+1 );
		h2->Draw("Colz");
		h2->SetStats(false);

	}
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

	std::cout << "Making BTI triggers per station plots" << std::endl;
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
	//# BTI Triggers per eta
	//#######################

	std::cout << "Making BTI triggers per eta plots" << std::endl;

	std::vector<TH1D*> btiPerEta;

	btiPerEta.push_back(muGunAnalyse.plotBtiTriggersPerEta(31));
	btiPerEta.push_back(des17Analyse.plotBtiTriggersPerEta(31));

	TCanvas* cBtiPerEta = cManager.plotDividedCanvas(btiPerEta,"btiTriggersPerEta");
	cBtiPerEta->SetName("btiTriggersCanvas");
	cBtiPerEta->SetTitle("BTI Triggers");
*/

	//#######################
	//# TRACO Triggers
	//#######################

	std::cout << "Making TRACO trigger plots" << std::endl;
	std::vector<TH1D*> tracoVector;

	tracoVector.push_back(muGunAnalyse.plotTracoTriggers());
	tracoVector.push_back(des17Analyse.plotTracoTriggers());

	TCanvas* cTracoTriggers = analyseTracoTriggers(tracoVector);
/*

	//All done. Save canvases and run root app
	storePlots(cTracoTriggers,"tracoTriggers");
	storePlots(cBtiPerStDes17,"btiTriggersPerStationDes17");
	storePlots(cBtiPerStMuGun,"btiTriggersPerStationMuGun");
	storePlots(cBtiTriggers,"btiTriggers");
	storePlots(cGenMuons,"genMuons");
	storePlots(cGenParticles,"genParticles");
	storePlots(cBtiVsBx,"btiVsBx");
	storePlots(cBtiNoTheta,"btiNoTheta");
	storePlots(cGenParticlesEta,"genParticlesEtaNoBti");

	cManager.storePlots();
*/

	std::cout << "All done!\nExit via ctrl+c..." << std::endl;
//	app->Run();
}

/**
 * Plot BTI triggers per eta
 */
TCanvas* analyseBtiTriggersPerEta(std::vector<TH1D*> input){
	if( !( &input ) ){
		std::cout << "[main] Null pointer for BTI trigger per eta hist vector.\nReturning." << std::endl;
		return NULL;
	} else if ( input.size() == 0 ){
		std::cout << "[main] Empty BTI trigger per eta hist vector.\nReturning." << std::endl;
		return NULL;
	}
	TString name("btiTriggersPerEta");

	TString title("BTI Triggers per eta ");

	TCanvas* canvas = plotDividedCanvas(input);
	canvas->SetName( name.Data() );
	canvas->SetTitle( title.Data() );
	return canvas;
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
	name += sampleInfo;	new TCanvas( "" , "Distribution of BTI triggers with no theta info" , 1600 , 1200 );


	TString title("BTI Triggers per Station ");
	title += sampleInfo;

	TCanvas* canvas = plotDividedCanvas(input);
	canvas->SetName( name.Data() );
	canvas->SetTitle( title.Data() );
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
	TCanvas* canvas = plotDividedCanvas(input);
	canvas->SetName("btiTriggersCanvas");
	canvas->SetTitle("BTI Triggers");
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
	TCanvas* canvas = plotDividedCanvas(input);
	canvas->SetTitle("TRACO Triggers");
	canvas->SetName("tracoTriggersCanvas");
	return canvas;

}

/**
 * Helper function to create divided canvases
 * If nY is 0, a canvas with n^2 pads is created, otherwise the canvas is
 * divided as nX times nY pads
 * The function automatically plots the TH1D given in the input vector
 */
TCanvas* plotDividedCanvas(std::vector<TH1D*> input, int nY){
	int nX = ceil( sqrt( input.size() ) );
	TCanvas* canvas = getDividedCanvas( nX , nY );
	/*
			new TCanvas("c","",1600,1200);

	if( nY <= 0 ){
		if(nY < 0)
			std::cout << "[main] Warning! Ignoring invalid canvas row count " << nY << std::endl;
		canvas->Divide(nX,nX);
	} else {
		canvas->Divide(nX,nY);
	}
	std::cout << "[main] Created canvas with " << nX << " pads." << std::endl;
	*/
	canvas->cd(1);
	input[0]->Draw();
	for( int i = 1 ; i < input.size() ; i++ ){
		canvas->cd(i+1);
		input[i]->SetLineColor( TColor::GetColorBright(i) );
		input[i]->Draw();
	}
	return canvas;
}

TCanvas* getDividedCanvas(int nX , int nY){
	TCanvas* canvas = new TCanvas("c","",1600,1200);
	if( nY <= 0 ){
		if(nY < 0)
			std::cout << "[main] Warning! Ignoring invalid canvas row count " << nY << std::endl;
		canvas->Divide(nX,nX);
	}else {
		canvas->Divide(nX,nY);
	}
	std::cout << "[main] Created canvas with " << nX << " pads." << std::endl;
	return canvas;
}
/**
 * Helper function plotting the given canvases with the given file name
 * both as pdf and png
 */
void storePlots(TCanvas* canvas, std::string nameTrunk){
	gSystem->MakeDirectory("./plots");
	gSystem->MakeDirectory("./plots/png");
	gSystem->MakeDirectory("./plots/pdf");

	canvas->SaveAs(("plots/pdf/" + nameTrunk + ".pdf").c_str());
	canvas->SaveAs(("plots/png/" + nameTrunk + ".png").c_str());


}
