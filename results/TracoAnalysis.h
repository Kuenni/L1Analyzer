/*
 * TracoAnalysis.h
 *
 *  Created on: 06.12.2013
 *      Author: kuensken
 */

#ifndef TRACOANALYSIS_H_
#define TRACOANALYSIS_H_

#include "Analyse.h"

class TracoAnalysis : public Analyse {
public:
	TracoAnalysis(TTree* tree, std::string sampleName,double ptCut, bool debug) : Analyse(tree,sampleName,ptCut,debug){};
	TH1D* plotTracoTriggers();
};


#endif /* TRACOANALYSIS_H_ */
