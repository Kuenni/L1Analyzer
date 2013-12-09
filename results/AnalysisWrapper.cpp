#include "AnalysisWrapper.h"

//#######################################
// Analyse BTI stuff
//#######################################
std::vector<TH1*> AnalysisWrapper::analyseBtiTriggers() {
	std::vector<TH1*> vect;
	vect.push_back(btiAna->plotBtiTriggers());
	return vect;
}

std::vector<TH1*> AnalysisWrapper::analyseBtiTriggersPerStation() {
	std::vector<TH1*> vect;
	for (int var = 0; var < 4; ++var) {
		vect.push_back(btiAna->plotBtiTriggersPerStation( var+1 ));
	}
	return vect;
}

std::vector<TH1*> AnalysisWrapper::analyseBtiTriggersPerEta() {
	std::vector<TH1*> vect;
	vect.push_back(btiAna->plotBtiTriggersPerEta());
	return vect;
}

std::vector<TH1*> AnalysisWrapper::analyseBtiNoTheta() {
	std::vector<TH1*> vect;
	for (int var = 0; var < 3; ++var) {
		vect.push_back(btiAna->plotNoBtiTheta( var + 1 ));
	}
	return vect;
}

std::vector<TH1*> AnalysisWrapper::analyseBtiBx(){
	std::vector<TH1*> vect;
	vect.push_back(btiAna->plotBtiTrgVsBx());
	return vect;
}

std::vector<TH1*> AnalysisWrapper::analyseBtiNoThetaPerWheel(){
	std::vector<TH1*> vect;
	for (int var = 0; var < 3; ++var) {
		vect.push_back( btiAna->plotNoBtiThetaPerWheel( btiAna->plotNoBtiTheta( var+1 ) , var+1 ) );
	}
	return vect;
}

void AnalysisWrapper::analyseBti(){
	std::vector<TCanvas*> vect;
	TCanvas* tempCanvas = cManager->plotDividedCanvas(analyseBtiBx(),"btiBx");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiTriggers(),"btiTriggers");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiTriggersPerStation(),"btiTrgPerStation");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiTriggersPerEta(),"btiTrgPerEta");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiNoTheta(),"btiNoThetaTrg");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiNoThetaPerWheel(),"btiNoThetaTrgPerWheel");
}

//#######################################
// Analyse Traco stuff
//#######################################
std::vector<TH1*> AnalysisWrapper::analyseTracoTriggers(){
	std::vector<TH1*> vect;
	vect.push_back(tracoAna->plotTracoTriggers());
	return vect;
}
