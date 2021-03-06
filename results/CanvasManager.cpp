#include "CanvasManager.h"
#include <cmath>
#include "TColor.h"
#include <iostream>
#include "TSystem.h"
#include "TFile.h"

/**
 * Searches for the canvas in the container and if found, shows it and returns a pointer to it
 */
TCanvas* CanvasManager::showCanvas(std::string canvasName){
	TCanvas* c = canvasContainer[canvasName];
	if(!c){
		if(getVerbose())
			std::cout << "[CanvasManager] Show canvas error! Didn't find canvas with name " << canvasName << "." << std::endl;
	} else {
		c->Show();
	}
	return c;
}

/**
 * Helper function to create divided canvases
 * If nY is 0, a canvas with n^2 pads is created, otherwise the canvas is
 * divided as nX times nY pads
 * The function automatically plots the TH1D given in the input vector
 * fillColumns can be used to decide wether the plots are filled in rows or columns
 */
TCanvas* CanvasManager::plotDividedCanvas(std::vector<TH1*> input, std::string name, int nY, bool fillColumns){
	int nX = 1;
	if( nY <= 0 )
		nX = ceil( sqrt( (float) input.size() ) );
	else
		nX = input.size()/nY;
	TCanvas* canvas = getDividedCanvas( nX , nY );
	canvas->cd(1);
	input[0]->Draw();
	for( int i = 1 ; i < input.size() ; i++ ){
		if(fillColumns){
			canvas->cd( i*nX%(nX*nY) + i/nY + 1);
		} else{
			canvas->cd( i+1 );
		}
		input[i]->SetLineColor( TColor::GetColorBright(i) );
		input[i]->Draw();
	}
	canvas->SetName(name.c_str());
	canvasContainer[name] = canvas;
	return canvas;
}

/**
 * Creates a TCanvas divided by nX times nY
 */
TCanvas* CanvasManager::getDividedCanvas(int nX , int nY){
	TCanvas* canvas = new TCanvas("c","",1600,1200);
	if( nY <= 0 ){
		if(nY < 0)
			std::cout << "[CanvasManager] Warning! Ignoring invalid canvas row count " << nY << std::endl;
		canvas->Divide(nX,nX);
	}else {
		canvas->Divide(nX,nY);
	}
	if(getVerbose())
		std::cout << "[CanvasManager] Created canvas with " << nX << " pads." << std::endl;
	return canvas;
}

/**
 * Adds a canvas to the list of canvases, the manager maintains
 */
void CanvasManager::addCanvas(std::string name, TCanvas* canvas){
	if(!canvas){
		if(getVerbose())
			std::cout << "[CanvasManager] Given canvas is a null pointer!" << std::endl;
		return;
	}
	TCanvas* c = canvasContainer[name];
	if(c){
		std::cout << "[CanvasManager] Warning! overwriting existing canvas with name " << name << "!" << std::endl;
	}
	canvas->SetName(name.c_str());
	canvasContainer[name] = canvas;
}

/**
 * Helper function plotting the given canvases with the given file name
 * both as pdf and png
 */
void CanvasManager::storePlots(){
	TString directory("./plots/");
	gSystem->MakeDirectory(directory);
	directory += sampleName;
	gSystem->MakeDirectory(directory);
	gSystem->MakeDirectory(directory + "/png");
	gSystem->MakeDirectory(directory + "/pdf");

	gSystem->MakeDirectory("./plots/rootfiles");
	TString fileName("./plots/rootfiles/" + sampleName);
	fileName += ".root";
	std::cout << "Creating root file " << fileName.Data() << "... ";
	TFile* rootfile = new TFile(fileName,"RECREATE");
	std::cout << (rootfile ? "Success!" : "Failed!") << std::endl;

	for (std::map<std::string,TCanvas*>::iterator mapIterator = canvasContainer.begin();
			mapIterator != canvasContainer.end();
			mapIterator++ ){
		mapIterator->second->SaveAs((directory + "/pdf/" + mapIterator->first + ".pdf"));
		mapIterator->second->SaveAs((directory + "/png/" + mapIterator->first + ".png"));
		rootfile->Cd(0);
		mapIterator->second->Write();
	}
	rootfile->Write();
	rootfile->Close();
	delete rootfile;
}
