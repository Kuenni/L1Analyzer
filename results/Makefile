LDFLAGS=$(shell root-config --libs --glibs)
CFLAGS=$(shell root-config --cflags)
OBJECTS = main.o Analyse.o TrigTestTreeData.o PlotStyle.o
EXECUTABLE=Analyse

all: $(OBJECTS)
	c++ $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cpp
	c++ -c $< $(CFLAGS) -o $@

%.o: %.C
	c++ -c $< $(CFLAGS) -o $@
clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)
