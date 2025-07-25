CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET = inventory_app
OBJS = main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp HashTable.h LinkedList.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o $(TARGET)
