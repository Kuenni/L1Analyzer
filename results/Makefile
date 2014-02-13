LDFLAGS=$(shell root-config --libs --glibs)
CFLAGS=$(shell root-config --cflags)
OBJECTS = main.o Analyse.o TrigTestTreeData.o PlotStyle.o CanvasManager.o AnalysisWrapper.o BTIAnalysis.o TracoAnalysis.o GenAnalysis.o
EXECUTABLE=Analyse
#       AnalysisWrapper.cpp
#       AnalysisWrapper.h
#       BTIAnalysis.cpp
#       BTIAnalysis.h
#       CanvasManager.cpp
#       CanvasManager.h

all: $(OBJECTS)
	c++ $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cpp
	c++ -g -c $< $(CFLAGS) -o $@

%.o: %.C
	c++ -c $< $(CFLAGS) -o $@
clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)
