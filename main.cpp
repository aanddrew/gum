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

enum {
    MOVE_FORWARD,
    MOVE_BACKWARD,
    MOVE_LEFT,
    MOVE_RIGHT,

    LOOK_UP,
    LOOK_DOWN,
    LOOK_LEFT,
    LOOK_RIGHT,

    NUM_MOVES,
};

bool moving[NUM_MOVES] = {};

void myKeyCallbackFunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)(scancode);
    (void)(action);
    (void)(mods);
    (void)(window);
    switch (action) {
        case GLFW_PRESS: {
            switch (key) {
                case 'W': moving[MOVE_FORWARD] = true; break;
                case 'A': moving[MOVE_LEFT] = true; break;
                case 'S': moving[MOVE_BACKWARD] = true; break;
                case 'D': moving[MOVE_RIGHT] = true; break;

                case 'I': moving[LOOK_UP] = true; break;
                case 'J': moving[LOOK_LEFT] = true; break;
                case 'K': moving[LOOK_DOWN] = true; break;
                case 'L': moving[LOOK_RIGHT] = true; break;
                default: break;
            }
        } break;
        case GLFW_RELEASE: {
             switch (key) {
                case 'W': moving[MOVE_FORWARD] = false; break;
                case 'A': moving[MOVE_LEFT] = false; break;
                case 'S': moving[MOVE_BACKWARD] = false; break;
                case 'D': moving[MOVE_RIGHT] = false; break;

                case 'I': moving[LOOK_UP] = false; break;
                case 'J': moving[LOOK_LEFT] = false; break;
                case 'K': moving[LOOK_DOWN] = false; break;
                case 'L': moving[LOOK_RIGHT] = false; break;
                default: break;
            }
        } break;
    }
}

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

    glfwSetKeyCallback(window, myKeyCallbackFunc);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    GLuint programID = LoadShaders("shaders/vertex.glsl", "shaders/fragment.glsl");
    glUseProgram(programID);

    gum::Mesh mesh("res/cube.obj");
    mesh.name = "Mesh";
    gum::Object3D player;
    player.name = "Player";
    gum::Camera camera((float)WIDTH/ (float)HEIGHT);
    camera.name = "Camera";

    //camera.set_transform(gum::Mat4::translate(gum::Vec3(0,0,5)));
    mesh.set_transform(gum::Mat4::rotate(gum::Vec3(1,1,0).normalize(), M_PI/3));

    gum::Object3D root;
    root.name = "root";
    root.add_child(&mesh);
    root.add_child(&player);
    player.add_child(&camera);
    
    player.set_transform(gum::Mat4::translate(gum::Vec3(0, 0, 5)) * player.world_transform());
    std::cout << camera.world_transform() << std::endl;

    root.print();

    //window stuff
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //float rand1 = (float) (rand() % 256) / 256.0;
        //float rand2 = (float) (rand() % 256) / 256.0;
        //float rand3 = (float) (rand() % 256) / 256.0;
        mesh.set_transform(gum::Mat4::rotate(gum::Vec3(1, 1, 1).normalize(), 0.003) * mesh.world_transform());
        //player.set_transform(gum::Mat4::translate(gum::Vec3(0.1,0,0)) * player.world_transform());
        //camera.set_transform(gum::Mat4::rotate(gum::Vec3(1, 1, 1).normalize(), 0.003) * camera.world_transform());
        //camera.set_transform(gum::Mat4::rotate(gum::Vec3(1, 1, 1).normalize(), 0.003) * camera.local_transform());
        //std::cout << camera.local_transform() << std::endl;
        //

        gum::Mat4 camera_local = camera.local_transform();

        if (moving[MOVE_LEFT]) {
            player.set_transform(gum::Mat4::translate(camera_local.basis()[0] * -0.01) * player.local_transform());
        }
        if (moving[MOVE_RIGHT]) {
            player.set_transform(gum::Mat4::translate(camera_local.basis()[0] * 0.01) * player.local_transform());
        }
        if (moving[MOVE_FORWARD]) {
            player.set_transform(gum::Mat4::translate(camera_local.basis()[2] * -0.01) * player.local_transform());
        }
        if (moving[MOVE_BACKWARD]) {
            player.set_transform(gum::Mat4::translate(camera_local.basis()[2] * 0.01) * player.local_transform());
        }

        if (moving[LOOK_UP]) {
            camera.set_transform(gum::Mat4::rotate(camera_local.basis()[0], 0.01) * camera_local);
        }
        if (moving[LOOK_DOWN]) {
            camera.set_transform(gum::Mat4::rotate(camera_local.basis()[0], -0.01) * camera_local);
        }
        if (moving[LOOK_LEFT]) {
            camera.set_transform(gum::Mat4::rotate(camera_local.basis()[1], 0.01) * camera_local);
        }
        if (moving[LOOK_RIGHT]) {
            camera.set_transform(gum::Mat4::rotate(camera_local.basis()[1], -0.01) * camera_local);
        }
        
        //actual drawing
        root.render(programID);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window) == 0);

}

