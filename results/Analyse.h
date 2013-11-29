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

#include "TH1.h"

class Analyse : TrigTestTreeData {
	public:
		Analyse(TTree*,std::string,bool debug = false);
		TH1D* plotBtiTriggers();
		TH1D* plotNGenMuons();
	private:
		bool debug;
		std::string sampleName;
};

#endif
