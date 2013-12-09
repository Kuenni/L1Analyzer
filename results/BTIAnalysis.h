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
	TH1D* plotBtiTriggersPerEta();
	TH1D* plotEtaNoBtiTriggers();
	TH1D* plotBtiTrgVsBx();
	TH2D* plotNoBtiTheta(int station);
	TH1D* plotNoBtiThetaPerWheel(TH2D*,int);
};


#endif /* BTIANALYSIS_H_ */
