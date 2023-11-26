#ifndef HANDLER_H
#define HANDLER_H

#include "entity.h"
#include "renderer.h"
#include "shaderprog.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

//For enemies and bullets,
//many objects with same shape, move in same way
//can become inactive, enemy when killed or bullet when off screen

struct ExpendableObject {
    bool active;
    //must use the Entity interface
    std::unique_ptr<Entity> pos;
};
//handles groups of expendable objects

class ExpendableObjectHandler {
    std::vector<ExpendableObject> entities;
    Renderer renderer;
public:
    //depends on OpenGL being already initialized
    ExpendableObjectHandler(const float vertices[], size_t size_verts, ShaderProg& prog); //: vertices{verts}, num_vertices{size_verts}
    std::vector<glm::vec3> update(float dt); //returns coords and angle to 
    void draw() const;
    virtual void spawn() = 0;
    //void prune(); //removes inactive objects
    //void collide(const ExpendableObjectHandler& hitboxes); //for bullets to hit enemies
    const std::vector<ExpendableObject>& get_objects() const;
};

class PlayerHandler {
    static constexpr float vertices[] = {
            -0.025f, -0.05f, 0.05f,
            0.0f, 0.05f, 0.0f,
            0.025f, -0.05f, 0.0f
    };
    PlayerPos player;
    unsigned health;
    Renderer renderer;
public:
    PlayerHandler(ShaderProg& prog);
    bool update(GLFWwindow* window, float dt);
    void draw() const;
    bool checkCollisions(const ExpendableObjectHandler&);
};
#endif



