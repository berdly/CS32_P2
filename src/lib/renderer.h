#ifndef RENDERER_H
#define RENDERER_H
#include "shaderprog.h"
#include "entity.h"
#include <glm/glm.hpp>
/*
This class handles drawing a vertex buffer. Vertex buffers send sets of points to the GPU
which represent the vertices of the shapes we are drawing. This means we should instantiate 
one Renderer for each differently shaped entity we create so it can handle drawing that shape. 
It uses the individual entities position and angle member variables to determine where on 
the screen to draw each vertex allowing for the same shape to be drawn many times in different places and orientations
*/
class Renderer {
    unsigned VAO;
    unsigned transform_addr;
    unsigned color_addr;
    glm::vec3 color;
    ShaderProg& shader;
public:
    Renderer(const float* vertices, size_t size, const glm::vec3& color, ShaderProg& shader);
    void draw(const Entity& sprite) const;
    void draw(const Entity* sprite_ptr) const;
};
#endif
