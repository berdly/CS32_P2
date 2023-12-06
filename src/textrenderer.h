/*
#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H
#include "shaderprog.h"
#include "entity.h"
#include <glm/glm.hpp>

This class handles drawing a vertex buffer. Vertex buffers send sets of points to the GPU
which represent the vertices of the shapes we are drawing. This means we should instantiate 
one Renderer for each differently shaped entity we create so it can handle drawing that shape. 
It uses the individual entities position and angle member variables to determine where on 
the screen to draw each vertex allowing for the same shape to be drawn many times in different places and orientations

typedef int Texture;
class TextRenderer {
    std::map<char, Texture> characters;
    unsigned VAO;
    unsigned transform_addr;
    ShaderProg& text_shader;

public:
    Renderer(const float* vertices, size_t size, ShaderProg& shader);
    void draw_char(char c, float x, float y) const;
    void draw_str(const std::string& str, float x, float y) const;
};
#endif

*/

