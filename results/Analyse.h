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

class Analyse : TrigTestTreeData {
	public:
		Analyse(TTree*,std::string,bool debug = false);
		TH1D* plotBtiTriggers();
		TH1D* plotNGenMuons();
		TH1D* plotTracoTriggers();
		TH1D* plotBtiTriggersPerStation(int);
		TH1D* plotGenParticles();
		TH1D* plotBtiTriggersPerEta(int);
		TH1D* plotEtaNoBtiTriggers();
		TH1D* plotBtiTrgVsBx();
		TH2D* plotNoBtiTheta(int station);
	private:
		bool debug;
		std::string sampleName;
};

#endif
