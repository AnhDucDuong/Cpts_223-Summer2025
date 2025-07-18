CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET = inventory_app
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
