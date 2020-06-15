#include <iostream>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "math/Math.h"

#include "Mesh.h"
#include "Camera.h"

#include "Shader.h"

#define WIDTH 1024
#define HEIGHT 768

int main() {
    glewExperimental = true;
    if ( !glfwInit() ) {
        std::cerr << "Failed to initialize GLFW\n" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow( WIDTH, HEIGHT, "gum", NULL, NULL );
    if ( window == NULL ) {
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        return -1;
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    GLuint programID = LoadShaders("shaders/vertex.glsl", "shaders/fragment.glsl");
    glUseProgram(programID);

    gum::Mesh mesh("");
    mesh.name = "Mesh";
    gum::Camera camera((float)WIDTH/ (float)HEIGHT);
    camera.name = "Camera";

    camera.set_transform(gum::Mat4::translate(gum::Vec3(0,0,10)));
    mesh.set_transform(gum::Mat4::rotate(gum::Vec3(1,1,0).normalize(), M_PI/2));

    gum::Object3D root;
    root.add_child(&mesh);
    root.add_child(&camera);

    //window stuff
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mesh.set_transform(gum::Mat4::rotate(gum::Vec3(-0,1,0).normalize(), 0.01) * mesh.get_transform());
        //camera.set_transform(gum::Mat4::translate(gum::Vec3(0.1,0,0)) * camera.get_transform());

        //actual drawing
        root.render(programID);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window) == 0);

}

