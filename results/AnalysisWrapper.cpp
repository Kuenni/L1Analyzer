#include "AnalysisWrapper.h"

TCanvas* AnalysisWrapper::showPlot(std::string plotName){
	return cManager->showCanvas(plotName);
}

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

std::vector<TH1*> AnalysisWrapper::analyseBtiBxPerStationPhi(){
	std::vector<TH1*> vect;
	for (int var = 0; var < 4; ++var) {
		vect.push_back(btiAna->plotBtiTrgVsBxPerStationPhi( var + 1 ));
	}
	return vect;
}

std::vector<TH1*> AnalysisWrapper::analyseBtiBxPerStationTheta(){
	std::vector<TH1*> vect;
	for (int var = 0; var < 3; ++var) {
		vect.push_back(btiAna->plotBtiTrgVsBxPerStationTheta( var + 1 ));
	}
	return vect;
}

std::vector<TH1*> AnalysisWrapper::analyseBtiNoThetaPerWheel(){
	std::vector<TH1*> vect;
	for (int var = 0; var < 3; ++var) {
		vect.push_back( btiAna->plotNoBtiThetaPerWheel( btiAna->plotNoBtiTheta( var+1 ) , var+1 ) );
	}
	return vect;
}

std::vector<TH1*> AnalysisWrapper::analyseBtiTrigPerStatAndSL(){
	std::vector<TH1*> vect;
	for (int var = 0; var < 4; ++var) {
		for (int k = 0 ; k < 3 ; k++){
			vect.push_back(btiAna->plotBtiTrigPerStatAndSL( var+1 , k+1 ) );
		}
	}
	return vect;
}

//Call all the subanalyzer functions
void AnalysisWrapper::analyseBti(){
	TCanvas* tempCanvas = cManager->plotDividedCanvas(analyseBtiBx(),"btiBx");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiTriggers(),"btiTriggers");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiTriggersPerStation(),"btiTrgPerStation");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiTriggersPerEta(),"btiTrgPerEta");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiNoTheta(),"btiNoThetaTrg");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiNoThetaPerWheel(),"btiNoThetaTrgPerWheel");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiBxPerStationPhi(),"btiBxPerStationPhi");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiBxPerStationTheta(),"btiBxPerStationTheta");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiTrigPerStatAndSL(),"btiTrigPerStatAndSL",3,true);
}

//#######################################
// Analyse Traco stuff
//#######################################
std::vector<TH1*> AnalysisWrapper::analyseTracoTriggers(){
	std::vector<TH1*> vect;
	vect.push_back(tracoAna->plotTracoTriggers());
	return vect;
}

void AnalysisWrapper::analyseTraco(){
	TCanvas* tempCanvas = cManager->plotDividedCanvas(analyseTracoTriggers(),"tracoTriggers");
}

//#######################################
// Analyse Gen particle stuff
//#######################################

std::vector<TH1*> AnalysisWrapper::analyseNGenMuons(){
	std::vector<TH1*> vect;
	vect.push_back(genAna->plotNGenMuons());
	return vect;
}

std::vector<TH1*> AnalysisWrapper::analyseGenParticleIds(){
	std::vector<TH1*> vect;
	vect.push_back(genAna->plotGenParticleIds());
	return vect;
}

std::vector<TH1*> AnalysisWrapper::analyseGenParticleEta(){
	std::vector<TH1*> vect;
	vect.push_back(genAna->plotGenParticleEta());
	return vect;
}

std::vector<TH1*> AnalysisWrapper::analyseGenParticlePhi(){
	std::vector<TH1*> vect;
	vect.push_back(genAna->plotGenParticlePhi());
	return vect;
}

void AnalysisWrapper::analyseGenParticles(){
	TCanvas* tempCanvas = cManager->plotDividedCanvas(analyseGenParticleIds(),"getPartIds");
	tempCanvas->SetLogy(1);
	tempCanvas = cManager->plotDividedCanvas(analyseNGenMuons(),"nGenMuons");
	tempCanvas = cManager->plotDividedCanvas(analyseGenParticleEta(),"genPartEta");
	tempCanvas = cManager->plotDividedCanvas(analyseGenParticlePhi(),"genPartPhi");
}
