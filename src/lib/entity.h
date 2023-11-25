
/*
Abstract base class to represent any object which needs to move and be drawn.
The update function will be called every frame with dt being the time since the last frame
which is useful for accelerating. Usually this method will update the velocity and angle while changing the
position based on the current velocity. Position represents the upper left corner of a rectangle
containing the object and size represents the bottom left which is needed for collision and rotation.
Angle determines the orientation with respect to the x-axis in radians.
*/
#ifndef ENTITY_H
#define ENTITY_H
#include <glm/glm.hpp>
#include <glfw/glfw3.h>
class Entity {
protected:
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 size;
    float angle;
public:
    Entity(const glm::vec2 pos, const glm::vec2 vel, glm::vec2 dim, float rot) : position{pos}, velocity{vel}, size{dim}, angle{rot} {}
    Entity(const glm::vec2 pos, const glm::vec2 dim) : Entity { pos, glm::vec2{ 0.0f, 0.0f }, dim, 0.0f } {}
    virtual void update(float dt) = 0;
    float rotation() const { return angle; }
    float x_pos() const { return position.x; }
    float y_pos() const { return position.y; }
    float length() const { return size.x; }
    float height() const { return size.y; }
    const glm::vec2& get_pos() const { return position; }
    const glm::vec2& get_dim() const { return size; }
};
//just for testing
class StaticEntity : public Entity {
public:
    StaticEntity(const glm::vec2 pos, const glm::vec2 size) : Entity{ pos, size } {}
    void update(float dt) override {} //never moves
};
//testing update
class Spinner : public Entity {
public:
    Spinner(const glm::vec2 pos, const glm::vec2 size) : Entity{ pos, size } {}
    void update(float dt) override {
        static float direction{1.0f};
        this->angle += dt;
        if((this->x_pos() > 0.75) || (this->x_pos() < -0.75)){
            direction *= -1.0;
        }
        this->position.x += direction * dt;
    }
};

class Player : public Entity {
    bool wasd[4];
public:
    Player(const glm::vec2 pos, const glm::vec2 size) : Entity{ pos, size },  wasd{ false, false, false, false } {}
    void process_input(GLFWwindow* window){
        wasd[0] = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
        wasd[1] = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
        wasd[2] = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
        wasd[3] = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    }
    void update(float dt) override {
        if(wasd[0]){
            position.y += dt;
        }
        if(wasd[1]){
            position.x -= dt;
        }
        if(wasd[2]){
            position.y -= dt;
        }
        if(wasd[3]){
            position.x += dt;
        }
    }
};
#endif
