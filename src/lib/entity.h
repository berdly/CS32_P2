#include <glm/glm.hpp>
class Entity {
    glm::vec2 position;
    glm::vec2 velocity;
    virtual void update() = 0;
    virtual void render() = 0;
};