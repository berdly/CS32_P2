
#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H
#include "shaderprog.h"
#include "entity.h"
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <map>

typedef int Texture;

class TextRenderer {
    std::map<char, Texture> characters;
    unsigned VAO;
    unsigned transform_addr;
    ShaderProg& text_shader;
public:
    TextRenderer(ShaderProg& shader);
    void draw_char(char c, float x, float y) const;
    void draw_str(const std::string& str, float x, float y) const;
};
#endif



