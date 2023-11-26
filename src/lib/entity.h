
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

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <algorithm>
#include <stdexcept>
class Entity {
protected:
    glm::vec2 position;
    glm::vec2 size;
    float speed;
    float angle;
public:
    Entity(const glm::vec2& pos, const glm::vec2& dim, float mag, float rot) : position{pos}, speed{mag}, size{dim}, angle{rot} {}
    Entity(const glm::vec2& pos, const glm::vec2& dim) : Entity { pos, dim, 0.0f, 0.0f } {}
    //true indicates some change in state we'd like to check, such as if the player shoots a bullet
    virtual bool update(float dt) = 0;
    float rotation() const { return angle; }
    float x_pos() const { return position.x; }
    float y_pos() const { return position.y; }
    float length() const { return size.x; }
    float height() const { return size.y; }
    const glm::vec2& get_pos() const { return position; }
    const glm::vec2& get_dim() const { return size; }
    bool in(const glm::vec2& point){
        float left_bound{position.x};
        float right_bound{position.x + size.x};
        float top_bound{position.y};
        float bottom_bound{position.y - size.y};
        return (point.y < top_bound) && (point.y > bottom_bound) && (point.x > left_bound) && (point.x < right_bound);
    }
};

//testing update
class PlayerPos : public Entity {
    bool wasdj[5];
public:
    PlayerPos(const glm::vec2 pos) : Entity{ pos, glm::vec2{0.05f, 0.1f } }, wasdj{ false, false, false, false, false } {}
    void process_input(GLFWwindow* window){
        wasdj[0] = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
        wasdj[1] = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
        wasdj[2] = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
        wasdj[3] = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
        wasdj[4] = glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS;
    }
    bool update(float dt) override {
        if(wasdj[0]){
            speed += dt/1000.0f;
        }
        if(wasdj[1]){
            angle -= dt*3;
        }
        if(wasdj[2]){
            speed -= dt/1000.0f;;
        }
        if(wasdj[3]){
             angle += dt*3;
        }
        speed = std::clamp(speed, 0.0f, 1.0f);

        position -= speed * glm::vec2{2.0f*glm::sin(angle)/3.0f, -glm::cos(angle)};
    
        position.x = std::clamp(position.x, -1.0f, 1.0f);
        position.y = std::clamp(position.y, -1.0f, 1.0f);

        speed -= dt / 2000.0f;
        return wasdj[4];
    }
};

class PlayerBullet : public Entity {
public:
    PlayerBullet(const glm::vec2& pos, float rot) : Entity{ pos, glm::vec2{0.05f, 0.05f}, 1.0f, rot } {}
    bool update(float dt) override {
        position -= speed * glm::vec2{ 4.0f * glm::sin(angle)/3.0f, -glm::cos(angle) };
    }
};
#endif
