CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

TARGET = controller/periguard

SOURCES = controller/main.cpp controller/access_manager.cpp

all: 
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean: 
	rm -f $(TARGET)
