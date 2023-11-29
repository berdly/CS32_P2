#include "handler.h"
#include <algorithm>
/*
class PlayerHandler {
    static constexpr float* vertices{
            -0.025f, -0.05f, 0.05f,
            0.0f, 0.05f, 0.0f,
            0.025f, -0.05f, 0.0f
        }
    };
    Player player;
    unsigned health;
    Renderer renderer;
    public:
    PlayerHandler(ShaderProg& prog);
    bool update(GLFWwindow* window, float dt);
    void draw();
    void checkCollisions(const ExpendableObjectHandler&);
};
*/
PlayerHandler::PlayerHandler(ShaderProg& prog) : player{ glm::vec2{0.0f, 0.0f} }, health{ 3 }, renderer{ vertices, sizeof(vertices), prog } {}
bool PlayerHandler::update(GLFWwindow* window, float dt) {
    this->player.process_input(window);
    return this->player.update(dt);
}
void PlayerHandler::draw() const{
    this->renderer.draw(player);
}
bool PlayerHandler::checkCollisions(const ExpendableObjectHandler& handler) {
    for(const auto& obj : handler.get_objects()){
        if(obj.pos->in(this->player.get_pos())){
            this->health--;
            return health == 0;
        }
    }
    return false;
}
glm::vec3 PlayerHandler::get_coord(){
    return glm::vec3(player.get_pos(), player.rotation());
}
/*
class ExpendableObjectHandler {
    std::vector<ExpendableObject> entities;
    Renderer renderer;
public:
    //depends on OpenGL being already initialized
    ExpendableObjectHandler(const float[] verts, size_t size_verts, ShaderProg& prog); //: vertices{verts}, num_vertices{size_verts}
    std::vector<glm::vec3> update(float dt); //returns coords and angle to 
    void draw() const;
    virtual void spawn() = 0;
    void prune(); //removes inactive objects
    void collide(const ExpendableObjectHandler& hitboxes); //for bullets to hit enemies
    const std::vector<ExpendableObject>& get_objects() const;
};
*/
bool out_bounds(const glm::vec2& pos){
    return ((pos.x)*(pos.x) > 1.0f) || ((pos.y)*(pos.y) > 1.0f);
}
ExpendableObjectHandler::ExpendableObjectHandler(const float verts[], size_t size_verts, ShaderProg& prog)
    : renderer{verts, size_verts, prog}, cleanup{}, entities{} {}
std::vector<glm::vec3> ExpendableObjectHandler::update(float dt){
    std::vector<glm::vec3> spawn_points;
    for(auto& obj : entities){
        if(obj.active && obj.pos->update(dt)){
            spawn_points.emplace_back(obj.pos->get_pos(), obj.pos->rotation());
        }
        if(out_bounds(obj.pos->get_pos())){
            obj.active = false;
        }
    }
    cleanup += dt;
    if(cleanup > 3.0f){
        this->prune();
        cleanup = 0.0f;
    }
    return spawn_points;
}

void ExpendableObjectHandler::draw() const{
    for(const auto& obj : entities){
        if(obj.active){
            this->renderer.draw(obj.pos.get());
        }
    }
}
void ExpendableObjectHandler::prune(){
    auto itr{std::remove_if(entities.begin(), entities.end(), [](const auto& obj){return !obj.active;})};
    std::cout << "pruned\n";
    entities.erase(itr, entities.end());
}
const std::vector<ExpendableObject>& ExpendableObjectHandler::get_objects() const { return entities; }

PlayerBulletHandler::PlayerBulletHandler(ShaderProg& prog) : ExpendableObjectHandler{vertices, sizeof(vertices), prog} {}

void PlayerBulletHandler::spawn(const glm::vec3& coord) {
    this->entities.emplace_back(true, new PlayerBullet{ glm::vec2{coord.x, coord.y}, coord.z });
}