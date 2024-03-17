CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O3 -Wall 


SOURCES = main.cpp gradient.cpp
OBJECTS = $(SOURCES: .cpp=.o)
HEADERS = gradient.hpp
EXEC = main

all: $(EXEC)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(EXEC) : $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)
	


clean:
	@rm *.o *.a