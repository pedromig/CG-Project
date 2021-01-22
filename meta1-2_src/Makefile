.PHONY: all clean
all:
	mkdir -p bin
	g++ RgbImage.cpp RgbImage.h main.cpp door.cpp utils.cpp cgproject.h -o bin/door -lglut -lGLU -lGL -lm

clean:
	rm -rf bin/door