//class to handle dynamic shader loading
#include "shaderprog.h"

//OpenGL function loading
#include <glad/glad.h>
//window and input handling
#include <GLFW/glfw3.h>

//matrix math for vertex shader
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Standard Headers
#include <iostream>


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
    float ver[]{
        -0.5f, -0.5f, 0.0f, 
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    /*
    float textCord[]{
        0.0f, 0.0f,
        0.5f, 1.0f,
        1.0f, 0.0f
    };
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    */
    auto window{ init_window() };
    unsigned VAO;
    unsigned VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ver), ver, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    ShaderProg shaderProg1{ "../shaders/vertex.vert", "../shaders/fragment.frag" };
    shaderProg1.use();
    glm::mat4 m{ 1.0f };
    glm::mat4 s{ 1.0f };
    unsigned unif_addr{shaderProg1.get_uniform_addr("transform")};

    while (!glfwWindowShouldClose(window)) {
        m = glm::rotate(m, 0.0002f, glm::vec3{0.0f, 0.0f, 1.0f});
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shaderProg1.setMatrix(unif_addr, glm::value_ptr(m));
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        s = glm::scale(s, glm::vec3(1.0005f, 1.0005f, 1.0005f));
        shaderProg1.setMatrix(unif_addr, glm::value_ptr(s));
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
