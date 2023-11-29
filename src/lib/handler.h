#ifndef HANDLER_H
#define HANDLER_H

#include "entity.h"
#include "renderer.h"
#include "shaderprog.h"
#include <GL/glut.h>
#include <vector>
#include <memory>

//For enemies and bullets,
//many objects with same shape, move in same way
//can become inactive, enemy when killed or bullet when off screen

struct ExpendableObject {
    bool active;
    //must use the Entity interface
    std::unique_ptr<Entity> pos;
    ExpendableObject(bool state, Entity* type) : active{ state }, pos{ type } {};
};
//handles groups of expendable objects

class ExpendableObjectHandler {
    Renderer renderer;
    float cleanup;
protected:
    std::vector<ExpendableObject> entities;
public:
    //depends on OpenGL being already initialized
    ExpendableObjectHandler(const float vertices[], size_t size_verts, ShaderProg& prog); //: vertices{verts}, num_vertices{size_verts}
    std::vector<glm::vec3> update(float dt); //returns coords and angle to 
    void draw() const;
    void prune(); //removes inactive objects
    //void collide(const ExpendableObjectHandler& hitboxes); //for bullets to hit enemies
    const std::vector<ExpendableObject>& get_objects() const;
};

class PlayerHandler {
    PlayerPos player;
    unsigned health;
    Renderer renderer;
public:
    PlayerHandler(ShaderProg& prog);
    bool update(bool* input, float dt);
    void draw() const;
    void prune();
    bool checkCollisions(const ExpendableObjectHandler&);
    glm::vec3 get_coord();
};

class PlayerBulletHandler : public ExpendableObjectHandler {
public:
    PlayerBulletHandler(ShaderProg & prog);
    void spawn(const glm::vec3& coord);
};
#endif



