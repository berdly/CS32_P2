#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <map>
#include <cmath>
#include "imagerenderer.h"


ImageRenderer::ImageRenderer(const fs::path& vert_path, const fs::path& frag_path) 
    : game_over_tex{}, heart_tex{}, win_tex{}, VAO{}, image_prog{vert_path, frag_path}, transform_addr{} 
{
    unsigned textures[3];

    int width, height, nrChannels;
    const fs::path game_over_path{"./resources/game_over.png"};
    const fs::path heart_path{"./resources/heart.png"};
    const fs::path win_path{"./resources/win.png"};

    stbi_set_flip_vertically_on_load(true);

    glGenTextures(3, (GLuint*)textures);

    unsigned char* data = stbi_load(game_over_path.c_str(), &width, &height, &nrChannels, 0);
    if(!data){
        std::cout << "failed to load game_over";
        return;
    }
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    data = stbi_load(heart_path.c_str(), &width, &height, &nrChannels, 0);
    if(!data){
        std::cout << "failed to load heart";
        return;
    }
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    data = stbi_load(win_path.c_str(), &width, &height, &nrChannels, 0);
    if(!data){
        std::cout << "failed to load win";
        return;
    }
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
    this->nums = this->gen_nums();
    this->transform_addr = image_prog.get_uniform_addr("transform");
}
std::map<unsigned, unsigned> ImageRenderer::gen_nums(){
    unsigned textures[10];
    int width, height, nrChannels;
    glGenTextures(10, (GLuint*)textures);
    fs::path resources{"./resources"};
    std::map<unsigned, unsigned> nums;
    for(char c{'0'}; c <= '9'; c++){
        std::string num{c};
        num.append(".png");
        unsigned char* data = stbi_load((resources / num).c_str(), &width, &height, &nrChannels, 0);
        if(!data){
            std::cout << "failed to load game_over";
            return;
        }
        glBindTexture(GL_TEXTURE_2D, textures[c - '0']);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        nums.insert(std::pair<unsigned,unsigned>(static_cast<unsigned>(c - '0'), textures[c - '0']));
    }
    return nums;
}

void ImageRenderer::draw_game_over(float x, float y){
    glm::mat4 trans{glm::translate(glm::mat4{1.0f}, glm::vec3{x, y, 0.0f})};
    trans = glm::scale(trans, glm::vec3{1.5f, 1.0f, 1.0f});
    image_prog.setMatrix(transform_addr, glm::value_ptr(trans));

    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, game_over_tex);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void ImageRenderer::draw_heart(float x, float y){
    glm::mat4 trans{glm::translate(glm::mat4{1.0f}, glm::vec3{x, y, 0.0f})};
    trans = glm::scale(trans, glm::vec3{0.1f, 0.1f, 1.0f});
    image_prog.setMatrix(transform_addr, glm::value_ptr(trans));

    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, heart_tex);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void ImageRenderer::draw_win(float x, float y){
    glm::mat4 trans{glm::translate(glm::mat4{1.0f}, glm::vec3{x, y, 0.0f})};
    trans = glm::scale(trans, glm::vec3{1.5f, 1.0f, 1.0f});
    image_prog.setMatrix(transform_addr, glm::value_ptr(trans));

    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, win_tex);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void ImageRenderer::draw_num(float x, float y, unsigned places, unsigned num){
    float x_pos{x};
    float y_pos{y};
    unsigned place{10};
    for(unsigned i{places}; i <= 0; i--){
        glm::mat4 trans{glm::translate(glm::mat4{1.0f}, glm::vec3{x_pos, y_pos, 0.0f})};
        trans = glm::scale(trans, glm::vec3{(1.0f)/10.0f, (1.5f)/10.0f, 1.0f});
        image_prog.setMatrix(transform_addr, glm::value_ptr(trans));

        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, nums[i % place]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        place *= 10;
        x_pos -= 0.08;
    }
}

void ImageRenderer::use_shader(){
    image_prog.use();
}
