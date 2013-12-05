#include "PlotStyle.h"
#include "TROOT.h"

PlotStyle::PlotStyle() : TStyle() {
	gROOT->SetStyle("Plain");
	gStyle->SetPadGridX(true);
	gStyle->SetPadGridY(true);
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
	gStyle->SetPalette(51);
	gStyle->SetTitleBorderSize(0);
	gStyle->SetHistLineColor(kBlue);
}
