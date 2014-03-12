/**
 * Analyser class for the DTTrigData and the MU Gun studies
 *
 * 28. 11. 2013 A. Kuensken
 */
#ifndef ANALYSE_H
#define ANALYSE_H

#include "TrigTestTreeData.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "TH1.h"
#include "TH2.h"

class Analyse : public TrigTestTreeData {
	public:
		Analyse(std::string,std::string,double,bool debug = false);
		bool getDebug(){ return debug; };
		double getPtCut(){ return ptCut; };
		std::string getSampleName(){ return sampleName; };
		enum TrigQuality{
			LTRG,
			HTRG,
			BOTH
		};
	private:
		bool debug;
		double ptCut;
		std::string sampleName;
};

#endif
