
#include "entity.h"
#include "renderer.h"
#include <memory>
class PlayerHandler{
    static constexpr float[] vertices;
    Player player;
    Renderer renderer;
    void spawn();
    bool update(GLFWwindow* window, float dt);
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
    size_t num_vertices;
    std::vector<ExpendableObject> entities;
    Renderer renderer;
public:
    //depends on OpenGL being already initialized
    ExpendableObjectHandler(const float[] verts, size_t size_verts); //: vertices{verts}, num_vertices{size_verts}
    std::vector<glm::vec3> update(float dt); //returns coords and angle to 
    virtual void spawn() = 0;
    void prune(); //removes inactive objects
    void collide(const ExpendableObjectHandler& hitboxes); //for bullets to hit enemies
}



