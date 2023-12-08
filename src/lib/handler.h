#ifndef HANDLER_H
#define HANDLER_H

#include "entity.h"
#include "renderer.h"
#include "shaderprog.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include <map>

//For enemies and bullets,
//many objects with same shape, move in same way
//can become inactive, enemy when killed or bullet when off screen

struct ExpendableObject {
    bool active;
    float health; //for enemies
    //must use the Entity interface
    //glm::vec2 pl; //player location

    std::unique_ptr<Entity> pos;
    ExpendableObject(bool state, Entity* type) : active{ state }, pos{ type }, health{1.0f} {};
   
};
//handles groups of expendable objects

class ExpendableObjectHandler {
    Renderer renderer;
    
protected:
    std::vector<ExpendableObject> entities;
    float cleanup;
public:
    
    //depends on OpenGL being already initialized
    ExpendableObjectHandler(const float vertices[], size_t size_verts, const glm::vec3& color, ShaderProg& prog); //: vertices{verts}, num_vertices{size_verts}
    std::vector<glm::vec3> update(float dt); //returns coords and angle to 
    void draw() const;
    void prune(); //removes inactive objects
    size_t getActive(){ return entities.size();};
   
        //void collide(const ExpendableObjectHandler& hitboxes); //for bullets to hit enemies
    const std::vector<ExpendableObject>& get_objects() const;
};

class PlayerHandler {
    public:
    static constexpr float vertices[] = {
            -0.025f, -0.05f, 0.0f,
            0.0f, 0.05f, 0.0f,
            0.025f, -0.05f, 0.0f
    };
    static constexpr glm::vec3 objColor{0.5, 0.5, 0.25};
    private:
    PlayerPos player;
    unsigned health;
    bool active;
    Renderer renderer;
public:
    PlayerHandler(ShaderProg& prog);
    bool update(GLFWwindow* window, float dt);
    void draw() const;
    void prune();
    bool checkCollisions(const ExpendableObjectHandler&);
    unsigned get_health();
    bool get_active(){return active;}
    glm::vec3 get_coord();
};

class PlayerBulletHandler : public ExpendableObjectHandler {
    static constexpr float vertices[] = {
        -0.0125f, -0.0125f, 0.0f,
        -0.0125f, 0.0125f, 0.0f,
        0.0125f, 0.0125f, 0.0f,
        0.0125f, -0.0125f, 0.0f,
    };
    static constexpr glm::vec3 objColor{0.8f, 0.8f, 0.1f};
public:
    PlayerBulletHandler(ShaderProg & prog);
    void spawn(const glm::vec3& coord);
};

class EnemyHandler : public ExpendableObjectHandler {

    static constexpr float vertices[] = {
            -0.025f, 0.05f, 0.0f,
            0.025f, 0.05f, 0.0f,
            0.0f, -0.05f, 0.0f,
    };

    static constexpr glm::vec3 objColor{1.0f, 0.0f, 0.0f};
    
    const std::map<int,float> lev{{1,3.0f}, {2, 2.0f}, {3, 1.00f}}; //each level and corresponding bullet rate;
    const std::map<int,int> enMap{{1,2}, {2, 3}, {3, 5}};
    public:
        EnemyHandler(ShaderProg & prog);
        void spawn(const glm::vec3& coord, float * pl);
        bool checkCollisions(const ExpendableObjectHandler& handler);
        std::map<int,float> getLevels(){
            return levels;
        }
        std::map<int,int> getnumEn(){return numEn;};

        void setLev(int l){
            level = l;
        }
        int getLev(){return level;}
        void deactivate(){
            entities.clear();
        }
    private:

        int level;
        std::map<int,float> levels;
        std::map<int, int> numEn;


};

class ChaserEnemyHandler : public ExpendableObjectHandler {

    static constexpr float vertices[] = {
            -0.0125f, 0.05f, 0.0f,
            0.0125f, 0.05f, 0.0f,
            0.0f, -0.05f, 0.0f,
    };
    static constexpr glm::vec3 objColor{0.0f, 1.0f, 0.0f};
    public:
    ChaserEnemyHandler(ShaderProg & prog);
    void spawn(const glm::vec3& coord, float * pl);
    
};


class EnemyBulletHandler : public ExpendableObjectHandler {
    static constexpr float vertices[] = {
        -0.0125f, -0.0125f, 0.0f,
        -0.0125f, 0.0125f, 0.0f,
        0.0125f, 0.0125f, 0.0f,
        0.0125f, -0.0125f, 0.0f,
    };
    static constexpr glm::vec3 objColor{1.0f, 0.0f,0.0f};
public:

    EnemyBulletHandler(ShaderProg & prog);
    void spawn(const glm::vec3& coord,float dt);
    
private:
    float timeAccum;
    float bulletRate;
};

#endif



