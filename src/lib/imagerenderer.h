#ifndef IMAGE_RENDERER_H
#define IMAGE_RENDERER_H

#include "shaderprog.h"

class ImageRenderer{
    unsigned game_over_tex;
    unsigned heart_tex;
    unsigned win_tex;
    unsigned VAO;
    std::map<unsigned, unsigned> nums;
    ShaderProg image_prog;
    unsigned transform_addr;
    std::map<unsigned, unsigned> gen_nums();
public:
    ImageRenderer(const fs::path&, const fs::path&);
    void draw_num(float x, float y, unsigned places, unsigned num);
    void draw_game_over(float x, float y);
    void draw_heart(float x, float y);
    void draw_win(float x, float y);
    void use_shader();
};
#endif