#ifndef CANVAS_MANAGER_H
#define CANVAS_MANAGER_H

#include "TCanvas.h"
#include "TH1.h"

#include <vector>
#include <string>
#include <map>

class CanvasManager{
public:
	CanvasManager(std::string sampleName) : sampleName(sampleName),verbose(false){};
	/*
	 * Destructor, that automatically calls the store plots function
	 */
	~CanvasManager(){
	}

	TCanvas* plotDividedCanvas(std::vector<TH1*> input,std::string name ,int nY = 0, bool fillColumns = false);
	TCanvas* getDividedCanvas(int nX, int nY = 0);
	void addCanvas(std::string,TCanvas*);
	TCanvas* showCanvas(std::string);
	void storePlots();

	/**
	 * This function closes all canvases stored in the cavas map
	 */
	inline void closeCanvases(){
		for (std::map<std::string,TCanvas*>::iterator mapIterator = canvasContainer.begin();
				mapIterator != canvasContainer.end();
				mapIterator++ ){
			mapIterator->second->Close();

		}
	}
	/**
	 * Getter and setter vor verbosity
	 */
	inline void setVerbose(bool verbose){
		this->verbose = verbose;
	}
	inline bool getVerbose(){
		return verbose;
	}
private:
	bool verbose;
	std::string sampleName;
	std::map<std::string,TCanvas*> canvasContainer;
};

#endif
