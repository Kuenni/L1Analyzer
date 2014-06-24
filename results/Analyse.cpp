#include "Analyse.h"
#include "TString.h"
#include "TH1.h"
#include "TTree.h"
#include <vector>

Analyse::Analyse(std::string treeName,std::string sampleName, double ptCut, bool debug) :
	TrigTestTreeData((TTree*)(new TFile(treeName.c_str()))->Get("h1"))
	, sampleName(sampleName)
	, ptCut(ptCut)
	, debug(debug){
	std::cout << "[Analyse " << sampleName << "] Loading Tree: " << ( LoadTree(0) ? "ERROR" : "OK" ) << std::endl;
}
