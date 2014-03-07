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
	TracoAnalysis(std::string treeName, std::string sampleName,double ptCut, bool debug) : Analyse(treeName,sampleName,ptCut,debug){};
	TH1D* plotTracoTriggers();
	TH1D* plotTracoBx();
	TH1D* plotTracoTriggersPerStation(int,bool);
};


#endif /* TRACOANALYSIS_H_ */
