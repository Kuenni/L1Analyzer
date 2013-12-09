/*
 * GenAnalysis.h
 *
 *  Created on: 09.12.2013
 *      Author: kuensken
 */

#ifndef GENANALYSIS_H_
#define GENANALYSIS_H_

#include "Analyse.h"

class GenAnalysis : public Analyse {
public:
	GenAnalysis(std::string treeName, std::string sampleName,double ptCut, bool debug) : Analyse(treeName,sampleName,ptCut,debug){};
	TH1D* plotNGenMuons();
	TH1D* plotGenParticleIds();
};


#endif /* GENANALYSIS_H_ */
