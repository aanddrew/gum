#include <iostream>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gum/gum.h>

//screen resolution
#define WIDTH 1920
#define HEIGHT 1080

//this is all stuff for the keyboard input handling, view callback function at the bottom
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
void myKeyCallbackFunc(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
    /* Begin boilerplate! */
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
    /* End boilerplate! */

    //handles input for player control
    glfwSetKeyCallback(window, myKeyCallbackFunc);

    //load shader programs using regular old opengl
    GLuint programID = LoadShadersByPath("shaders/vertex.glsl", "shaders/fragment.glsl");
    glUseProgram(programID);

    //create mesh
    gum::Mesh mesh("res/starter.obj");
    mesh.name = "Mesh";
    //create player and camera
    gum::Object3D player;
    player.name = "Player";
    gum::Camera camera((float)WIDTH/ (float)HEIGHT);
    camera.name = "Camera";

    //create lights
    gum::Light light(gum::Vec3(5,12,10));
    light.name = "light";
    gum::Light light2;
    light2.name ="light2";

    //create sun
    gum::Object3D sun;
    sun.name = "Sun";
    sun.set_transform(gum::Mat4::translate(gum::Vec3(0,5000,-250)));

    gum::Object3D root;
    root.name = "root";
    root.shader_program = programID;
    
    //build the tree now
    root.add_child(&sun);
    root.add_child(&light);
    root.add_child(&mesh);
    root.add_child(&player);
    player.add_child(&camera);
    player.add_child(&light2);

    std::cout << "Tree looks like this currently: " << std::endl;
    root.print();

    //window stuff
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    float pitch = 0.0f;
    float yaw = 0.0f;

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //reset the cameras transform
        camera.set_transform(gum::Mat4::identity());
        float speed = 0.2;

        if (moving[LOOK_UP]) {
            pitch += 0.01;
        }
        if (moving[LOOK_DOWN]) {
            pitch -= 0.01;
        }
        if (moving[LOOK_LEFT]) {
            yaw += 0.01;
        }
        if (moving[LOOK_RIGHT]) {
            yaw -= 0.01;
        }

        //then yaw it, then pitch it
        camera.set_transform(gum::Mat4::rotate(camera.local_transform().basis()[1], yaw) * camera.local_transform());
        camera.set_transform(gum::Mat4::rotate(camera.local_transform().basis()[0], pitch) * camera.local_transform());

        //translate the player
        if (moving[MOVE_LEFT]) {
            player.set_transform(gum::Mat4::translate(camera.local_transform().basis()[0] * -speed) * player.local_transform());
        }
        if (moving[MOVE_RIGHT]) {
            player.set_transform(gum::Mat4::translate(camera.local_transform().basis()[0] * speed) * player.local_transform());
        }
        if (moving[MOVE_FORWARD]) {
            player.set_transform(gum::Mat4::translate(camera.local_transform().basis()[2] * -speed) * player.local_transform());
        }
        if (moving[MOVE_BACKWARD]) {
            player.set_transform(gum::Mat4::translate(camera.local_transform().basis()[2] * speed) * player.local_transform());
        }
        
        //drawing takes place here
        root.render();

        //have to swap the buffers after drawing
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window) == 0);
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

//callback function for glfw, handles keyboard input
void myKeyCallbackFunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
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

