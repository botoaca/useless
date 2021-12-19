CXX = g++
CXXFLAGS = -Wall -std=c++20

all: output

output: main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
