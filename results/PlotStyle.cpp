#include "PlotStyle.h"
#include "TROOT.h"

PlotStyle::PlotStyle() : TStyle() {
	gROOT->SetStyle("Pub");
	gStyle->SetPadGridX(true);
	gStyle->SetPadGridY(true);
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
	gStyle->SetPalette(51);
	gStyle->SetTitleBorderSize(0);
	gStyle->SetHistLineColor(kBlue);
	gStyle->SetOptStat("emr");
	gStyle->SetHistLineWidth(3);
	gStyle->SetLegendBorderSize(1);
	gStyle->SetLegendFillColor(kWhite);
}
