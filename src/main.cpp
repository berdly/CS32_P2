//class to handle dynamic shader loading
#include "shaderprog.h"
//class which represents game objects
#include "entity.h"
//class which handles rendering of entities
#include "renderer.h"
#include "handler.h"
//OpenGL function loading
//window and input handling
#include <GL/glut.h> //i think it goes like this
#include <stdlib.h>
#include <stdio.h>
#include <string>
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

int last;
PlayerHandler player;
PlayerBulletHandler bullets;
ShaderProg shaderProg;
bool wasdj[5];

int window2 = 0, window = 0, width = 400, height = 400;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    player.draw();
    bullets.draw();

    glutSwapBuffers(window);
}

void init(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    glEnable(GL_CULL_FACE); // cull face
    glCullFace(GL_BACK); // cull back face
    glFrontFace(GL_CW);
    last = glutGet(GLUT_ELAPSED_TIME);
    float dt;
    shaderProg = ShaderProg{ "../shaders/vertex.vert", "../shaders/fragment.frag" };
    shaderProg.use();
    
    player = PlayerHandler{shaderProg};
    bullets = PlayerBulletHandler{shaderProg};
}

void idle(){
    int now = glutGet(GLUT_ELAPSE_TIME);
    float dt = (last - now) / 1000.0f;
    last = now;
    if(player.update(dt, wasdj)){
            bullets.spawn(player.get_coord());
    }
    bullets.update(dt);
    glutPostRedisplay();
}
void reshape (int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glutPostRedisplay();
}

void keyboard_func(unsigned char key, int x, int y) 
{
     switch (key) 
    {    
       case 'w' : wasdj[0] = true;   break;
       case 'a':  wasdj[1] = true;  ;  break;
       case 's' : wasdj[2] = true;  ;  break;
       case 'd' : wasdj[3] = true;  ;  break;
        case 'j' : wasdj[4] = true; ; break;
        default:
            break;
    }
}

void keyboard_up_func(unsigned char key, int x, int y) 
{
     switch (key) 
    {    
       case 'w' : wasdj[0] = false;   break;
       case 'a':  wasdj[1] = false;  ;  break;
       case 's' : wasdj[2] = false;  ;  break;
       case 'd' : wasdj[3] = false;  ;  break;
        case 'j' : wasdj[4] = false; ; break;
        default:
            break;
    }

}

int main(int argc, char **argv)
{
    // Initialization stuff
    glutInit(&argc, argv);
    glutInitContextVersion( 3, 3 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    
    glutInitDisplayMode(GLUT_DOUBLE, GLUT_RGB);
    glutInitWindowSize(width, height);

    // Create  window main
    window = glutCreateWindow("Window 1");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard_func);
    glutReshapeFunc(keyboard_up_func);
    glutInitWindowPosition(100,100);


    // Enter Glut Main Loop and wait for events
    glutMainLoop();
return 0;
}
