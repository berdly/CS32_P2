
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <filesystem>

#include "shaderprog.h"
namespace std::filesystem = fs;

class ImageRenderer{
    unsigned game_over_tex;
    unsigned heart_tex;
    unsigned win_tex;
    unsigned VAO;
    ShaderProg image_prog;
    unsigned transform_addr;
public:
    ImageRenderer();
    void draw_game_over(float x, float y);
    void draw_heart(float x, float y);
    void draw_win(float x, float y);
};
ImageRenderer::ImageRenderer() 
    : game_over_tex{}, heart_tex{}, win_tex{}, VAO{}, image_prog{"./shaders/text.vert", "./shaders/text.frag"}, transform_addr{} 
{
    unsigned textures[3];

    int width, height, nrChannels;
    const fs::path game_over_path{"./resources/game_over.png"};
    const fs::path heart_path{"./resources/heart.png"};
    const fs::path win_path{"./resources/win.png"};

    stbi_set_flip_vertically_on_load(true);

    glGenTextures(3, &textures);

    unsigned char* data = stbi_load(game_over_path.c_str(), &width, &height, &nrChannels);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    data = stbi_load(heart_path.c_str(), &width, &height, &nrChannels)
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    data = stbi_load(win_path.c_str(), &width, &height, &nrChannels)
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    float vertices[] = {
        // positions         // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    this->VAO = VAO;
    this->game_over_tex = textures[0];
    this->heart_tex = textures[1];
    this->win_tex = textures[2];
    this->transform_addr = image_prog.get_uniform_addr("transform");
}

