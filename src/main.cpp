//class to handle dynamic shader loading
//#include "shaderprog.h"
//class which represents game objects
//#include "entity.h"
//class which handles rendering of entities
//#include "renderer.h"
//#include "handler.h"
//OpenGL function loading
//window and input handling
#include <GL/glut.h> //i think it goes like this
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// Standard Headers
//#include <iostream>
//#include <vector>
//#include <utility>

/*
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
*/



int window2 = 0, window = 0, width = 400, height = 400;

void display(void)
{
    glClearColor(0.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    printf("display1\n");
    glFlush();
}

void display2(void)
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    printf("display2\n");
    glFlush();
}

void reshape (int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    // Initialization stuff
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(width, height);

    // Create  window main
    window = glutCreateWindow("Window 1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutInitWindowPosition(100,100);

    // Create second window
    window2 = glutCreateWindow("Window 2");
    glutDisplayFunc(display2);
    glutReshapeFunc(reshape);

    // Enter Glut Main Loop and wait for events
    glutMainLoop();
return 0;
}
