#ifndef IMAGE_RENDERER_H
#define IMAGE_RENDERER_H

#include "shaderprog.h"

class ImageRenderer{
    unsigned game_over_tex;
    unsigned heart_tex;
    unsigned win_tex;
    unsigned VAO;
    ShaderProg image_prog;
    unsigned transform_addr;
public:
    ImageRenderer(const fs::path&, const fs::path&);
    void draw_game_over(float x, float y);
    void draw_heart(float x, float y);
    void draw_win(float x, float y);
    void use_shader();
};
#endif