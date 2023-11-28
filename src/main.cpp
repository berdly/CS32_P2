//class to handle dynamic shader loading
#include "shaderprog.h"
//class which represents game objects
#include "entity.h"
//class which handles rendering of entities
#include "renderer.h"
#include "handler.h"
//OpenGL function loading
#include <glad/glad.h>
//window and input handling
#include <GLFW/glfw3.h>
// Standard Headers
#include <iostream>
#include <vector>
#include <utility>

void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* init_window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* mwindow{ glfwCreateWindow(800, 600, "CS32 Project 2", nullptr, nullptr) };
    if (!mwindow) {
        std::cout << "Couldn't open window.";
    }
    glfwMakeContextCurrent(mwindow);
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    glViewport(0, 0, 600, 800);
    glfwSetFramebufferSizeCallback(mwindow, frame_buffer_size_callback);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    glEnable(GL_CULL_FACE); // cull face
    glCullFace(GL_BACK); // cull back face
    glFrontFace(GL_CW);
    
    return mwindow;
}
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, char * argv[]) {
    GLFWwindow* window{ init_window() };
    ShaderProg shaderProg{ "../shaders/vertex.vert", "../shaders/fragment.frag" };
    shaderProg.use();
    
    PlayerHandler player{shaderProg};
    PlayerBulletHandler bullets{shaderProg};

    float last = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        float now = glfwGetTime();
        float dt{now - last};
        last = now;

        processInput(window);
        if(player.update(window, dt)){
            bullets.spawn(player.get_coord());
        }
        bullets.update(dt);
        glClear(GL_COLOR_BUFFER_BIT);
        player.draw();
        bullets.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
