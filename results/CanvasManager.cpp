#include "CanvasManager.h"
#include <cmath>
#include "TColor.h"
#include <iostream>
#include "TSystem.h"

/**
 * Searches for the canvas in the container and if found, shows it and returns a pointer to it
 */
TCanvas* CanvasManager::showCanvas(std::string canvasName){
	TCanvas* c = canvasContainer[canvasName];
	if(!c){
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
		nX = ceil( sqrt( input.size() ) );
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
void CanvasManager::storePlots(){
	TString directory("./plots/");
	gSystem->MakeDirectory(directory);
	directory += sampleName;
	gSystem->MakeDirectory(directory);
	gSystem->MakeDirectory(directory + "/png");
	gSystem->MakeDirectory(directory + "/pdf");

	for (std::map<std::string,TCanvas*>::iterator mapIterator = canvasContainer.begin();
			mapIterator != canvasContainer.end();
			mapIterator++ ){
		mapIterator->second->SaveAs((directory + "/pdf/" + mapIterator->first + ".pdf"));
		mapIterator->second->SaveAs((directory + "/png/" + mapIterator->first + ".png"));

	}
}
