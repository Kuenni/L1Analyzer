#ifndef ANALYSISWRAPPER_H
#define ANALYSISWRAPPER_H

#include "TTree.h"
#include <string>

#include "BTIAnalysis.h"
#include "TracoAnalysis.h"
#include "CanvasManager.h"

class AnalysisWrapper{
public:
	AnalysisWrapper(TTree* tree, std::string sampleName,double ptCut, bool debug):tree(tree),sampleName(sampleName),ptCut(ptCut),debug(debug){
		btiAna = new BTIAnalysis(tree,sampleName,ptCut,debug);
	//	tracoAna = new TracoAnalysis(tree,sampleName,ptCut,debug);
		cManager = new CanvasManager(sampleName);
	};

	//GenMuon analyzer functions
	std::vector<TH1*> analyseNGenMuons();

	//BTI Analyser functions
	std::vector<TH1*> analyseBtiBx();
	std::vector<TH1*> analyseBtiTriggers();
	std::vector<TH1*> analyseBtiTriggersPerStation();
	std::vector<TH1*> analyseBtiTriggersPerEta();
	std::vector<TH1*> analyseBtiNoTheta();
	std::vector<TH1*> analyseBtiNoThetaPerWheel();

	//Traco Analyzer functions
	std::vector<TH1*> analyseTracoTriggers();

	//Calls all bti analyzer functions
	void analyseBti();

	//Save the plots in the canvas manager
	void savePlots(){ cManager->storePlots();};


private:
	bool debug;
	TTree* tree;
	std::string sampleName;
	double ptCut;
	BTIAnalysis* btiAna;
	TracoAnalysis* tracoAna;
	CanvasManager* cManager;
};

#endif
