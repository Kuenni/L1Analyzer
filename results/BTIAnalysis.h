/*
 * BTIAnalysis.h
 *
 *  Created on: 06.12.2013
 *      Author: kuensken
 */

#ifndef BTIANALYSIS_H_
#define BTIANALYSIS_H_

#include "Analyse.h"

#include "TH2.h"

class BTIAnalysis : public Analyse{
public:
	BTIAnalysis(std::string treeName, std::string sampleName , double ptCut, bool debug) : Analyse(treeName , sampleName , ptCut , debug){};
	TH1D* plotBtiTriggers();
	TH1D* plotBtiTriggersPerStation(int);
	TH1D* plotBtiTriggersPerStationAndSL(int,int,int,bool);
	TH1D* plotBtiTriggersPerEta();
	TH1D* plotEtaNoBtiTriggers();
	TH1D* plotBtiTrgVsBx();
	TH2D* plotNoBtiTheta(int station);
	TH1D* plotNoBtiThetaPerWheel(TH2D*,int);
	TH1D* plotBtiTrgVsBxPerStationPhi(int,int);
	TH1D* plotBtiTrgVsBxPerStationTheta(int);
	TH2D* plotBtiTrigPerStatAndSectAndSL(int station,int sl);
	inline int getNBti(){
		return Nbti;
	}
};


#endif /* BTIANALYSIS_H_ */
