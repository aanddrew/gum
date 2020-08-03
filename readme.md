# GUM

Gum is an extension of GLFW and OpenGL using c++ which brings useful abstractions for 3d Graphics or Game development. Right now it includes a math library and a scene graph framework for building 3d scenes. This scene graph framework is heavily inspired by the [Godot Engine](https://godotengine.org/)'s Node system. It is recommended to have a strong understand of Linear algebra to use this engine.

This engine is fairly barebones and requires the programmer to write their own shaders and create their own glfw windows etc. These are features that may come in the future though.

[I have made a short video explaining some of the functionality here.](https://youtu.be/KkaePsm76J0)

# Dependencies

This project depends on libGLEW, libGL, and libGLFW (or another windowing library theoretically)

# Installation

First clone this repository and navigate to its directory. Then do 

    make
    
and  *(please read the makefile before using sudo)*
 
    sudo make install
    
# Usage
 
Simply
 
    #include <gum/gum.h>
 
and

    gcc your_file.cpp -lgum -lGL -lglfw -lGLEW -lm

to link it together

For a more helpful example, see the test directory for a sample program built using this engine. More detailed documentation is on the way. 
