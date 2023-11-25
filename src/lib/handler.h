
#include "entity.h"
#include "renderer.h"
#include <memory>
#include 
class PlayerHandler{
    static constexpr float[] vertices;
    Player player;
    Renderer renderer;
    void spawn();
    void update(GLFWwindow* window, float dt);
}

//For enemies and bullets,
//many objects with same shape, move in same way
//can become inactive, enemy when killed or bullet when off screen
struct ExpendableObject{
    bool active;
    std::unique_ptr<Entity> pos;
}
//handles groups of expendable objects
class ExpendableObjectHandler{
    const float[] vertices;
    std::vector<ExpendableObject> entities;
    Renderer renderer;
    void prune();
public:
//spawns new instance of ExpendableObject
    void spawn();
    void update();
    void collide(const ExpendableObjectHandler& hitboxes); //for bullets to hit enemies
}

