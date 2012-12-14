export CXX=clang++
export CXXFLAGS= -W -Wall -O2 -pedantic -g -pipe

SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)
EXEC=cmdparser

$(EXEC): main.o $(OBJ)
	$(CXX) -o $(EXEC) $(CXXFLAGS) $^ 

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean: 
	rm -f *.o $(OBJ) $(EXEC)

format:

