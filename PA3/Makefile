CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET = pa3_bench

SRC = main.cpp
HEADERS = avl_map.h USCity.h csv_loader.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
