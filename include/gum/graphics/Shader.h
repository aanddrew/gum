#pragma once

#include <string>
#include <GL/glew.h>

/*
 * This is a simple file used to load shaders into openGL
 */

GLuint LoadShadersByPath(const char * vertex_file_path,const char * fragment_file_path);

GLuint LoadShadersByCode(std::string& VertexShaderCode, std::string& FragmentShaderCode);

