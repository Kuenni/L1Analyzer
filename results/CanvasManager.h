#ifndef CANVAS_MANAGER_H
#define CANVAS_MANAGER_H

#include "TCanvas.h"
#include "TH1.h"

#include <vector>
#include <string>
#include <map>

class CanvasManager{
public:
	CanvasManager(std::string sampleName) : sampleName(sampleName){};
	/*
	 * Destructor, that automatically calls the store plots function
	 */
	~CanvasManager(){
		storePlots();
	}
	TCanvas* plotDividedCanvas(std::vector<TH1*> input,std::string name ,int nY = 0, bool fillColumns = false);
	TCanvas* getDividedCanvas(int nX, int nY = 0);
	void addCanvas(std::string,TCanvas*);
	TCanvas* showCanvas(std::string);
	void storePlots();
private:
	std::string sampleName;
	std::map<std::string,TCanvas*> canvasContainer;
};

#endif
