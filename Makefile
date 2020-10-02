CXX=g++
CFLAGS= -std=c++11 -Wall -Werror -Wextra -g
LFLAGS=-lGLEW -lglfw -lGL -lfreetype
IDIRS=-I/usr/include/freetype2

SONAME=libgum.so

all: 
	$(CXX) -c src/*/*.cpp $(CFLAGS) $(LFLAGS) $(IDIRS) -fpic && mkdir -p build && mv *.o build && gcc -shared -o libgum.so build/*.o

install:
	cp -r include/* /usr/include/
	cp libgum.so /usr/lib/
