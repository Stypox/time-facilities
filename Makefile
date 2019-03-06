SRC = src/
INC = include/

CXX = g++
CXXFLAGS := -Wall -std=c++17

time_facilities.o: $(INC)stypox/frequency.h $(SRC)frequency.cpp $(INC)stypox/clock.h
	$(CXX) $(CXXFLAGS) -c $(SRC)frequency.cpp -o time_facilities.o

clean:
	rm time_facilities.o	