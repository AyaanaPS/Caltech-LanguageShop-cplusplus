CXX = g++
CXXFLAGS = -std=c++14 -Wall

all : genmaze

genmaze : maze.o genmaze.o
	$(CXX) $(CXXFLAGS) maze.o genmaze.o -o genmaze

genmaze.o : maze.cc genmaze.cc
	$(CXX) $(CXXFLAGS) -c genmaze.cc

maze.o : maze.hh maze.cc
	$(CXX) $(CXXFLAGS) -c maze.cc

clean :
	rm -f genmaze *.o *~

.PHONY : all clean
