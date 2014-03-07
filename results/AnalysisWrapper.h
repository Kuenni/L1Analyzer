#ifndef ANALYSISWRAPPER_H
#define ANALYSISWRAPPER_H

#include "TTree.h"
#include <string>

#include "BTIAnalysis.h"
#include "TracoAnalysis.h"
#include "GenAnalysis.h"
#include "CanvasManager.h"

class AnalysisWrapper{
public:
	AnalysisWrapper(std::string treeName, std::string sampleName,double ptCut, bool debug):treeName(treeName),sampleName(sampleName),ptCut(ptCut),debug(debug){
		btiAna = new BTIAnalysis(treeName,sampleName,ptCut,debug);
		tracoAna = new TracoAnalysis(treeName,sampleName,ptCut,debug);
		genAna = new GenAnalysis(treeName,sampleName,ptCut,debug);
		cManager = new CanvasManager(sampleName);
	};

	~AnalysisWrapper(){
		delete cManager;
		delete btiAna;
		delete tracoAna;
		delete genAna;
	}

	//GenMuon analyzer functions
	std::vector<TH1*> analyseNGenMuons();
	std::vector<TH1*> analyseGenParticleIds();
	std::vector<TH1*> analyseGenParticleEta();
	std::vector<TH1*> analyseGenParticlePhi();

	//BTI Analyzer functions
	std::vector<TH1*> analyseBtiBx();
	std::vector<TH1*> analyseBtiTriggers();
	std::vector<TH1*> analyseBtiTriggersPerStation();
	std::vector<TH1*> analyseBtiTriggersPerEta();
	std::vector<TH1*> analyseBtiNoTheta();
	std::vector<TH1*> analyseBtiNoThetaPerWheel();
	std::vector<TH1*> analyseBtiBxPerStationPhi(int);
	std::vector<TH1*> analyseBtiBxPerStationTheta();
	std::vector<TH1*> analyseBtiTrigPerStatAndSectAndSL();
	std::vector<TH1*> analyseBtiTrigPerStatAndSL();

	//Traco Analyzer functions
	std::vector<TH1*> analyseTracoTriggers();
	std::vector<TH1*> analyseTracoBx();
	std::vector<TH1*> analyseTracoTrigPerStaion();
	std::vector<TH1*> analyseTracoTrigPerStationHtrig();

	//Calls all bti analyzer functions
	void analyseBti();

	//Calls all the TRACO analyzer functions
	void analyseTraco();

	//Calls all the gen analyzer functions
	void analyseGenParticles();

	//Save the plots in the canvas manager
	void savePlots(){ cManager->storePlots();};

	//Calls the close canvases function of the underlying canvas manager
	void closeCanvases(){
		cManager->closeCanvases();
	};

	//Show a certain plot from the canvas manager with the given name
	TCanvas* showPlot(std::string);

	inline int getNbti(){
		return btiAna->getNBti();
	}


private:
	bool debug;
	std::string treeName;
	std::string sampleName;
	double ptCut;
	BTIAnalysis* btiAna;
	TracoAnalysis* tracoAna;
	GenAnalysis* genAna;
	CanvasManager* cManager;
};

#endif
