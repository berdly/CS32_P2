#include "renderer.h"
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//s
Renderer::Renderer(const float* vertices, size_t size, ShaderProg& prog) : VAO{}, transform_addr{ prog.get_uniform_addr("transform") }, shader{ prog } {
    //creates a VBO and saves the interpretation info in a VAO for later use
    unsigned VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
}
void Renderer::draw(const Entity& sprite) const{
    //creates transformation matrix then sends it as a uniform to the vertex shader, then draws
    glm::mat4 transform{ glm::translate(glm::mat4{1.0f}, glm::vec3{sprite.x_pos(), sprite.y_pos(), 0.0f}) };
    //glm::vec3 rot_axis{ glm::normalize(glm::vec3(sprite.x_pos() + (sprite.length() / 2.0f), (sprite.y_pos() - (sprite.height()/2.0f)), 1.0f)) };
    
    transform = glm::rotate(transform, sprite.rotation(), glm::vec3(0.0f, 0.0f, 1.0f));
    
    shader.setMatrix(transform_addr, glm::value_ptr(transform));
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
void Renderer::draw(const Entity* sprite) const{
    if(sprite){
        this->draw(*sprite);
    } else{
        throw std::runtime_error("Attempted to draw nullptr >:(");
    }
}