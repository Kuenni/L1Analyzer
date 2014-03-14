/*
 * PlotTitle.cpp
 *
 *  Created on: Mar 13, 2014
 *      Author: kuensken
 */

#include "PlotTitle.h"

PlotTitle::PlotTitle():TPaveText(0.25,0.92,0.75,0.99,"NDC"){
	initPlotBox();
}

PlotTitle::~PlotTitle() {
}

PlotTitle::PlotTitle(std::string text) : TPaveText(0.25,0.92,0.75,0.99,"NDC"){
	initPlotBox();
	this->AddText(text.c_str());
}

void PlotTitle::initPlotBox(){
	this->SetBorderSize(0);
	this->SetFillColor(kWhite);
	this->SetTextFont(42);
}
