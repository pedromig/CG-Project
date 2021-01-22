CXX=g++
CXX_FLAGS=-std=c++17 -O3 -DNDEBUG
CXX_WARN_FLAGS=-Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion -Wno-unused-parameter
CXX_LINK_FLAGS=-lglut -lGLEW -lGLU -lGL -lm

SOURCEDIR=.
SOURCES=$(shell find $(SOURCEDIR) -type f -name "*.cpp")
HEADERS=$(shell find $(SOURCEDIR) -type f -name "*.hpp")

.PHONY: all
all: bin/shaders

bin/%: $(SOURCES) $(HEADERS)
	mkdir -p bin
	$(CXX) $(CXX_FLAGS) $(CXX_WARN_FLAGS) -o $@ $(SOURCES) $(CXX_LINK_FLAGS)

.PHONY: clean
clean:
	rm -rf shaders