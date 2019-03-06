SRC = src/
INC = include/

CXX = g++
CXXFLAGS := -Wall -std=c++17

OBJECT_FILES = $(SRC)frequency.o $(SRC)clock.o

time_facilities.o: $(OBJECT_FILES)
	ld -r $(OBJECT_FILES) -o time_facilities.o

$(SRC)frequency.o: $(INC)stypox/frequency.hpp $(SRC)frequency.cpp $(INC)stypox/clock.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC)frequency.cpp -o $(SRC)frequency.o
$(SRC)clock.o: $(INC)stypox/clock.hpp $(SRC)clock.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)clock.cpp -o $(SRC)clock.o

clean:
	rm $(OBJECT_FILES) time_facilities.o