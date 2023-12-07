/*
#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H
#include "shaderprog.h"

#include <glm/glm.hpp>
#include <ft2build.h>
#include <freetype/freetype.h>

#include <map>

typedef int Texture;

class TextRenderer {
    struct CharInfo {
        unsigned int id;  // ID handle of the glyph texture
        glm::ivec2   size;       // Size of glyph
        glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
        unsigned int advance;    // Offset to advance to next glyph
    };
    std::map<char, CharInfo> chars;
    unsigned VAO;
    unsigned transform_addr;
    ShaderProg& text_shader;
public:
    TextRenderer(ShaderProg& shader, const fs::path& font_path);
    void draw_char(char c, float x, float y) const;
    void draw_str(const std::string& str, float x, float y) const;
};
#endif
*/
