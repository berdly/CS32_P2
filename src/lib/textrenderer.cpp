#include "textrenderer.h"

TextRenderer::TextRenderer(ShaderProg& shader) : text_shader{shader}{
    
}
void TextRenderer::draw_char(char c, float x, float y) const {}
void TextRenderer::draw_str(const std::string& str, float x, float y) const {}