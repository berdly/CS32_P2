// Local Headers
#include "shaderprog.h"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <iostream>
#include <cstdlib>
class Entity {
    double x_pos;
    double y_pos;
    Entity() = default;
    virtual void update() = 0;
};

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
        std::exit(1);
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
    float ver1[]{
        -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    };
    float ver2[]{
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.4f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    };
    auto window{ init_window() };
    unsigned VAO[2];
    unsigned VBO[2];
    glGenBuffers(2, VBO);
    glGenVertexArrays(2, VAO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ver1), ver1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ver2), ver2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));
    glEnableVertexAttribArray(1);

#ifdef _WIN32
    ShaderProg shaderProg1{ "..\\shaders\\vertex.vert", "..\\shaders\\fragment.frag" };
    ShaderProg shaderProg2{ "..\\shaders\\vertex.vert", "..\\shaders\\fragment.frag" };
#else
    ShaderProg shaderProg1{ "../shaders/vertex.vert", "../shaders/fragment.frag" };
    ShaderProg shaderProg2{ "../shaders/vertex.vert", "../shaders/fragment.frag" };
#endif

    unsigned offset{ shaderProg1.get_uniform_addr("offset") };
    float val{};
    float last{ static_cast<float>(glfwGetTime()) };
    float deltaTime{};
    while (!glfwWindowShouldClose(window)) {
        float now{ static_cast<float>(glfwGetTime()) };
        deltaTime = now - last;
        last = now;
        if (val > 0.5) {
            val -= deltaTime/5.0;
        }
        else {
            val += deltaTime/5.0;
        }
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProg1.use();
        shaderProg1.setFloat(offset, val);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        shaderProg2.use();
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
