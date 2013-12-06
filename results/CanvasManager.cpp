#include "CanvasManager.h"
#include <cmath>
#include "TColor.h"
#include <iostream>
#include "TSystem.h"
/**
 * Helper function to create divided canvases
 * If nY is 0, a canvas with n^2 pads is created, otherwise the canvas is
 * divided as nX times nY pads
 * The function automatically plots the TH1D given in the input vector
 */
TCanvas* CanvasManager::plotDividedCanvas(std::vector<TH1*> input, std::string name, int nY){
	int nX = ceil( sqrt( input.size() ) );
	TCanvas* canvas = getDividedCanvas( nX , nY );
	canvas->cd(1);
	input[0]->Draw();
	for( int i = 1 ; i < input.size() ; i++ ){
		canvas->cd(i+1);
		input[i]->SetLineColor( TColor::GetColorBright(i) );
		input[i]->Draw();
	}
	canvas->SetName(name.c_str());
	canvasContainer.push_back(std::make_pair(canvas,name));
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
	gSystem->MakeDirectory("./plots");
	gSystem->MakeDirectory("./plots/png");
	gSystem->MakeDirectory("./plots/pdf");

	for (std::vector<std::pair<TCanvas*,std::string> >::iterator pairIterator = canvasContainer.begin();
			pairIterator != canvasContainer.end();
			pairIterator++ ){

		pairIterator->first->SaveAs(("plots/pdf/" + pairIterator->second + ".pdf").c_str());
		pairIterator->first->SaveAs(("plots/png/" + pairIterator->second + ".png").c_str());

	}
}
