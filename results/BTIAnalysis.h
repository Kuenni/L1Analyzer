/*
 * BTIAnalysis.h
 *
 *  Created on: 06.12.2013
 *      Author: kuensken
 */

#ifndef BTIANALYSIS_H_
#define BTIANALYSIS_H_

#include "Analyse.h"

class BTIAnalysis : public Analyse{
public:
	BTIAnalysis(TTree* tree, std::string sampleName,double ptCut, bool debug) : Analyse(tree,sampleName,ptCut,debug){};
	TH1D* plotBtiTriggers();
	TH1D* plotBtiTriggersPerStation(int);
	TH1D* plotBtiTriggersPerEta(int);
	TH1D* plotEtaNoBtiTriggers();
	TH1D* plotBtiTrgVsBx();
	TH2D* plotNoBtiTheta(int station);
};


#endif /* BTIANALYSIS_H_ */
