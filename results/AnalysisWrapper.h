#ifndef ANALYSISWRAPPER_H
#define ANALYSISWRAPPER_H

#include "TTree.h"
#include <string>

#include "BTIAnalysis.h"
#include "CanvasManager.h"

class AnalysisWrapper{
public:
	AnalysisWrapper(TTree* tree, std::string sampleName,double ptCut, bool debug):tree(tree),sampleName(sampleName),ptCut(ptCut),debug(debug){
		btiAna = new BTIAnalysis(tree,sampleName,ptCut,debug);
		cManager = new CanvasManager();
	};
	std::vector<TH1*> analyseNGenMuons();

	std::vector<TH1*> analyseBtiBx();

	std::vector<TH1*> analyseBtiTriggers();

	std::vector<TH1*> analyseBtiTriggersPerStation();

	std::vector<TH1*> analyseBtiTriggersPerEta();

	std::vector<TH1*> analyseBtiNoTheta();

	void analyseBti();

	void savePlots(){ cManager->storePlots();};


private:
	bool debug;
	TTree* tree;
	std::string sampleName;
	double ptCut;
	BTIAnalysis* btiAna;
//	TracoAnalysis tracoAna;
	CanvasManager* cManager;
};

#endif
