LDFLAGS=$(shell root-config --libs --glibs)
CFLAGS=$(shell root-config --cflags)
OBJECTS = Analyse.o TrigTestTreeData.o PlotStyle.o CanvasManager.o AnalysisWrapper.o BTIAnalysis.o TracoAnalysis.o GenAnalysis.o
EXE = main.o
NO_PH_EXE = noPhMain.o
#       BTIAnalysis.cpp
#       BTIAnalysis.h
#       CanvasManager.cpp
#       CanvasManager.h

all: $(EXE) $(OBJECTS)
	@echo Linking Analyse
	c++ $(LDFLAGS) $(EXE) $(OBJECTS) -o Analyse

noPh: $(NO_PH_EXE) $(OBJECTS)
	@echo Linking AnalyseNoPh
	c++ $(LDFLAGS) $(NO_PH_EXE) $(OBJECTS) -o AnalyseNoPh

%.o: %.cpp
	@echo Compiling $<
	c++ -g -c $< $(CFLAGS) -o $@

%.o: %.C
	@echo Compiling $<
	c++ -c $< $(CFLAGS) -o $@
clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)
	@echo All clean!
