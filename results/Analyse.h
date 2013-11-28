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

#include "TH1.h"

class Analyse : TrigTestTreeData {
	public:
		Analyse(TTree*,bool debug = false);
		TH1D* analyseBtiTriggers();
		TH1D* plotNGenMuons();
	private:
		bool debug;
};

#endif
