CXX=g++
CFLAGS= -std=c++11 -Wall -Werror -Wextra -g
LFLAGS=-lGLEW -lglfw -lGL

SONAME=libgum.so

all: 
	$(CXX) -c src/*.cpp src/math/*.cpp $(CFLAGS) $(LFLAGS) -fpic && mkdir -p build && mv *.o build

install:
	mkdir -p /usr/include/gum/
	cp -r include/* /usr/include/gum/
	cp libgum.so /usr/lib/
