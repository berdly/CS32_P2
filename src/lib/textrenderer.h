
#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H
#include "shaderprog.h"


#include <ft2build.h>
#include FT_FREE_TYPE_H

#include <map>

typedef int Texture;

class TextRenderer {
    struct CharTexture {
        unsigned int id;  // ID handle of the glyph texture
        glm::ivec2   size;       // Size of glyph
        glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
        unsigned int advance;    // Offset to advance to next glyph
    };
    std::map<char, CharTexture> chars;
    unsigned VAO;
    unsigned transform_addr;
    ShaderProg& text_shader;
public:
    TextRenderer(ShaderProg& shader);
    void draw_char(char c, float x, float y) const;
    void draw_str(const std::string& str, float x, float y) const;
};
#endif



