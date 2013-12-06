#ifndef CANVAS_MANAGER_H
#define CANVAS_MANAGER_H

#include "TCanvas.h"
#include "TH1.h"

#include <vector>
#include <string>

class CanvasManager{
public:
	TCanvas* plotDividedCanvas(std::vector<TH1*> input,std::string name ,int nY = 0);
	TCanvas* getDividedCanvas(int nX, int nY = 0);
	void storePlots();
private:
	std::vector< std::pair<TCanvas*,std::string> > canvasContainer;
};

#endif
