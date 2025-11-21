# compiler flags

CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

TARGET = project4

SOURCES = main.cpp student.cpp bst.cpp menu.cpp

OBJECTS = $(SOURCES:.cpp=.o)

HEADERS = student.h bst.h menu.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp

student.o: student.cpp student.h
	$(CXX) $(CXXFLAGS) -c student.cpp

bst.o: bst.cpp bst.h student.h
	$(CXX) $(CXXFLAGS) -c bst.cpp

menu.o: menu.cpp menu.h bst.h student.h
	$(CXX) $(CXXFLAGS) -c menu.cpp

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run
