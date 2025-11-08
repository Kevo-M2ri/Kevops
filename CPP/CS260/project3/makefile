#makefile for project3.cpp

CXX = g++
CXXFLAGS = -std=c++17 -Wall

TARGET = proj3

SOURCES = main.cpp menu.cpp table.cpp

OBJECTS = main.o menu.o table.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "*** Still going maaahhhn! ***"
	@echo "Key in ./$(TARGET) to run the program"

main.o: main.cpp menu.h
	$(CXX) $(CXXFLAGS) -c main.cpp

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)
