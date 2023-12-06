#include <iostream>
#include <vector>
#include <utility>
#include <random>
#ifdef _DEBUG
#  define DBG(x) do { std::cerr << x << '\n'; } while (false)
#else
#  define DBG(x) do {} while (false)
#endif

//class to handle dynamic shader loading
#include "../src/lib/shaderprog.h"
//class which represents game objects
#include "../src/lib/entity.h"
//class which handles rendering of entities
#include "../src/lib/renderer.h"
#include "../src/lib/handler.h"
//OpenGL function loading
#include <glad/glad.h>
//window and input handling
#include <GLFW/glfw3.h>
#include <ctime>
#include <random>
// Standard Headers
typedef std::mt19937 RNG;
//usage gen_range<-100, 100>(gen); produces random number between -100 and 100
template<int low, int up>
int gen_range(RNG& gen){
    static std::uniform_int_distribution< int > dist(low, up);
    return dist(gen);
}

glm::vec2 gen_coord(RNG& gen){
    static std::uniform_real_distribution<float> distx{-1.0f, 1.0f};
     static std::uniform_real_distribution<float> disty{0, 1.0f};
    return glm::vec2{distx(gen), disty(gen)};
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(height/3, 0, height, height);
}
/*
GLFWwindow* init_window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* mwindow{ glfwCreateWindow(800, 600, "CS32 Project 2", nullptr, nullptr) };
    if (!mwindow) {
        std::cout << "Couldn't open window.";
    }
    glfwMakeContextCurrent(mwindow);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, 600, 800);
    glfwSetFramebufferSizeCallback(mwindow, frame_buffer_size_callback);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    glEnable(GL_CULL_FACE); // cull facem
    glCullFace(GL_BACK); // cull back face
    glFrontFace(GL_CW);
    
    return mwindow;
}
*/
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}



int main(int argc, char * argv[]) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //opens full screen window in release mode, smaller window for debugging
#ifdef _DEBUG
    GLFWwindow* mwindow{ glfwCreateWindow(800, 600, "CS32 Project 2", glfwGetPrimaryMonitor(), nullptr) };
#else 
    GLFWwindow* mwindow{ glfwCreateWindow(800, 600, "CS32 Project 2", glfwGetPrimaryMonitor(), nullptr) };
#endif

    if (!mwindow) {
        std::cout << "Couldn't open window.";
    }
    glfwMakeContextCurrent(mwindow);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, 600, 800);
    glfwSetFramebufferSizeCallback(mwindow, frame_buffer_size_callback);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    glEnable(GL_CULL_FACE); // cull facem
    glCullFace(GL_BACK); // cull back face
    glFrontFace(GL_CW);
    
    ShaderProg shaderProg{ "./shaders/vertex.vert", "./shaders/fragment.frag" };
    shaderProg.use();
    DBG("test");
    DBG(mwindow);
    
    PlayerHandler player{shaderProg};
    PlayerBulletHandler bullets{shaderProg};

    EnemyHandler enemy{shaderProg};
    //ChaserEnemyHandler chaser{shaderProg};
    EnemyBulletHandler enemyBullets{shaderProg};


    float last = glfwGetTime();
    RNG rng{std::random_device{}()}; //seeds rng
    int num{gen_range<0,100>(rng)};
    DBG(num);
    int i = 0;
     float playerLoc[2] = {player.get_coord().x,player.get_coord().y};

    while (!glfwWindowShouldClose(mwindow)) {
        playerLoc[0] = player.get_coord().x;
        playerLoc[1] = player.get_coord().y;

        float now = glfwGetTime();
        float dt{now - last};
        last = now;

        
        
           
        if(enemy.getActive() == 0){
            enemy.setLev(enemy.getLev()+1);
            for(size_t i = 0; i < enemy.getnumEn()[enemy.getLev()];i++){
                enemy.spawn(glm::vec3(gen_coord(rng),0.0f), playerLoc);
            }
        }
            //chaser.spawn(glm::vec3{0,0.9f,0}, playerLoc);
            
        

        processInput(mwindow);
        if(player.update(mwindow, dt) && player.get_active()){
            bullets.spawn(player.get_coord());
        }
         
        
        bullets.update(dt);
        enemyBullets.update(dt);

        std::vector<glm::vec3> sp = enemy.update(dt);

        for(glm::vec3 v: sp){
            enemyBullets.spawn(glm::vec3(v.x,v.y,v.z+glm::radians(180.0f)),dt);
        }
        //chaser.update(dt);


        enemy.checkCollisions(bullets);
        player.checkCollisions(enemyBullets);

        glClear(GL_COLOR_BUFFER_BIT);
        
            player.draw();
            bullets.draw();
        
       
        //chaser.draw();
        enemy.draw();
        enemyBullets.draw();

        glfwSwapBuffers(mwindow);
        glfwPollEvents();
    }
    glfwTerminate();
}
