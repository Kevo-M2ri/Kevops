#makefile for project2.cpp

CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = proj2

SOURCES = main.cpp undoRedoManager.cpp deque.cpp command.cpp

OBJECTS = main.o undoRedoManager.o deque.o comman.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "*** I made it laslty ***"
	@echo "Key in ./$(TARGET) to run the program"

main.o: main.cpp undoRedoManager.h
	$(CXX) $(CXXFLAGS) -c main.cpp

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)
