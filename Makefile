CXX=g++
CFLAGS=-Wall -Werror -Wextra -g
LFLAGS=-lGLEW -lglfw -lGL
#LFLAGS=-lglfw3 -pthread -ldl -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11

all: 
	$(CXX) *.cpp math/*.cpp $(CFLAGS) $(LFLAGS)
