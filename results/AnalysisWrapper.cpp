#include "AnalysisWrapper.h"

#include "TLegend.h"

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

std::vector<TH1*> AnalysisWrapper::analyseBtiBxPerStationPhi(int sl){
	std::vector<TH1*> vect;
	for (int var = 0; var < 4; ++var) {
		vect.push_back(btiAna->plotBtiTrgVsBxPerStationPhi( var + 1 , sl ));
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

std::vector<TH1*> AnalysisWrapper::analyseBtiTrigPerStatAndSectAndSL(){
	std::vector<TH1*> vect;
	for (int var = 0; var < 4; ++var) {
		for (int k = 0 ; k < 3 ; k++){
			vect.push_back(btiAna->plotBtiTrigPerStatAndSectAndSL( var+1 , k+1 ) );
		}
	}
	return vect;
}

std::vector<TH1*> AnalysisWrapper::analyseBtiTrigPerStatAndSL(){
	std::vector<TH1*> vect;
	//create the histograms
	for (int i = 0; i < 4; ++i) {
		for (int j = 1; j < 4; j+=2) {
			vect.push_back(btiAna->plotBtiTriggersPerStationAndSL(i+1,j));
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
	tempCanvas = cManager->plotDividedCanvas(analyseBtiBxPerStationPhi(1),"btiBxPerStationPhiSL1");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiBxPerStationPhi(3),"btiBxPerStationPhiSL3");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiBxPerStationTheta(),"btiBxPerStationTheta");
	tempCanvas = cManager->plotDividedCanvas(analyseBtiTrigPerStatAndSectAndSL(),"btiTrigPerStatAndSectAndSL",3,/*fill columns*/true);

	//Calls the ana function which does more complex stuff for plotting
	std::vector<TH1*> vect = analyseBtiTrigPerStatAndSL();
	tempCanvas = cManager->getDividedCanvas(2,2);
	//Draw the super layers for the same station together
	for (int i = 0; i < 4; ++i) {
		//change to canvas and set log y
		tempCanvas->cd(i+1)->SetLogy();
		vect[2*i]->Draw();
		vect[2*i+1]->SetLineColor(kRed);
		vect[2*i+1]->Draw("same");
		TLegend* l = new TLegend(0.75,.55,0.95,0.75);
		l->AddEntry(vect[2*i],"SL 1");
		l->AddEntry(vect[2*i+1],"SL 3");
		l->Draw();
	}
	cManager->addCanvas("btiTrigPerStatAndSL",tempCanvas);
	tempCanvas = 0;
}

//#######################################
// Analyse Traco stuff
//#######################################
std::vector<TH1*> AnalysisWrapper::analyseTracoTriggers(){
	std::vector<TH1*> vect;
	vect.push_back(tracoAna->plotTracoTriggers());
	return vect;
}

std::vector<TH1*> AnalysisWrapper::analyseTracoBx(){
	std::vector<TH1*> vect;
	vect.push_back(tracoAna->plotTracoBx());
	return vect;
}

void AnalysisWrapper::analyseTraco(){
	TCanvas* tempCanvas = cManager->plotDividedCanvas(analyseTracoTriggers(),"tracoTriggers");
	tempCanvas = cManager->plotDividedCanvas(analyseTracoBx(),"tracoBx");
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
