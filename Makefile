CXX=g++
CFLAGS= -std=c++11 -Wall -Werror -Wextra -g
LFLAGS=-lGLEW -lglfw -lGL

SONAME=libgum.so

all: 
	$(CXX) -c src/*/*.cpp $(CFLAGS) $(LFLAGS) -fpic && mkdir -p build && mv *.o build && gcc -shared -o libgum.so build/*.o

install:
	cp -r include/* /usr/include/
	cp libgum.so /usr/lib/
