/*
 * PlotTitle.h
 *
 *  Created on: Mar 13, 2014
 *      Author: kuensken
 */

#ifndef PLOTTITLE_H_
#define PLOTTITLE_H_

#include <TPaveText.h>

class PlotTitle: public TPaveText {
public:
	PlotTitle();
	PlotTitle(std::string);
	virtual ~PlotTitle();
	void initPlotBox();
};

#endif /* PLOTTITLE_H_ */
