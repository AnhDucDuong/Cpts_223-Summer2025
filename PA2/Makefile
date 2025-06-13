# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -std=c++11

# Object files
OBJS = Destination.o ListMyJosephus.o VectorMyJosephus.o

# Targets
all: TestListMyJosephus TestVectorMyJosephus

TestListMyJosephus: TestListMyJosephus.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o TestListMyJosephus TestListMyJosephus.cpp $(OBJS)

TestVectorMyJosephus: TestVectorMyJosephus.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o TestVectorMyJosephus TestVectorMyJosephus.cpp $(OBJS)

Destination.o: Destination.cpp Destination.h
	$(CXX) $(CXXFLAGS) -c Destination.cpp

ListMyJosephus.o: ListMyJosephus.cpp ListMyJosephus.h
	$(CXX) $(CXXFLAGS) -c ListMyJosephus.cpp

VectorMyJosephus.o: VectorMyJosephus.cpp VectorMyJosephus.h
	$(CXX) $(CXXFLAGS) -c VectorMyJosephus.cpp

clean:
	rm -f *.o TestListMyJosephus TestVectorMyJosephus *.log
