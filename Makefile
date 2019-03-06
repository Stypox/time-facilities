SRC = src/
INC = include/

CXX = g++
CXXFLAGS := -Wall -std=c++17

time_facilities.o: $(INC)stypox/frequency.hpp $(SRC)frequency.cpp $(INC)stypox/clock.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC)frequency.cpp -o time_facilities.o

clean:
	rm time_facilities.o	