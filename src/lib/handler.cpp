#include "handler.h"
#include <algorithm>

PlayerHandler::PlayerHandler(ShaderProg& prog) : player{ glm::vec2{0.0f, -0.5f} }, health{ 5}, active{true},renderer{ vertices, sizeof(vertices),objColor, prog } {}
bool PlayerHandler::update(GLFWwindow* window, float dt) {
    this->player.process_input(window);
    return this->player.update(dt);
}
void PlayerHandler::draw() const{
    if(this->active){
        this->renderer.draw(player);
    }
}

bool PlayerHandler::checkCollisions(const ExpendableObjectHandler& handler) {
    
    for(const auto& obj : handler.get_objects()){
        if(obj.pos->in(this->player.get_pos())){
            this->health--;
            if(health == 0){
                this->active = false;
            }
            return true;
        }
    }
    return false;
}
glm::vec3 PlayerHandler::get_coord(){
    return glm::vec3(player.get_pos(), player.rotation());
}
unsigned PlayerHandler::get_health(){
    return health;
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
ExpendableObjectHandler::ExpendableObjectHandler(const float verts[], size_t size_verts, const glm::vec3& color, ShaderProg& prog)
    : renderer{verts, size_verts, color, prog}, cleanup{}, entities{} {}


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
    entities.erase(itr, entities.end());
}
const std::vector<ExpendableObject>& ExpendableObjectHandler::get_objects() const { return entities; }

PlayerBulletHandler::PlayerBulletHandler(ShaderProg& prog) : ExpendableObjectHandler{vertices, sizeof(vertices), objColor, prog}  {}

void PlayerBulletHandler::spawn(const glm::vec3& coord) {
    this->entities.emplace_back(true, new PlayerBullet{ glm::vec2{coord.x, coord.y}, coord.z });
}


EnemyHandler::EnemyHandler(ShaderProg& prog) : ExpendableObjectHandler{vertices, sizeof(vertices), objColor, prog}, levels{lev}, numEn{enMap}, level{0} {}
ChaserEnemyHandler::ChaserEnemyHandler(ShaderProg& prog) : ExpendableObjectHandler{vertices, sizeof(vertices), objColor, prog} {}

void EnemyHandler::spawn(const glm::vec3& coord, float * pl) {
    this->entities.emplace_back(true, new Enemy{ glm::vec2{coord.x, coord.y}, levels[level], pl});//add random coords at top of screen
}

void ChaserEnemyHandler::spawn(const glm::vec3& coord, float * pl) {
    this->entities.emplace_back(true, new ChaserEnemy{glm::vec2{coord.x, coord.y}, pl});//add random coords at top of screen
}



unsigned EnemyHandler::checkCollisions(const ExpendableObjectHandler& handler) {
    unsigned killed{};
    for( ExpendableObject& enem: this->entities){

    for(const ExpendableObject& obj : handler.get_objects()){
        if(obj.pos->in(enem.pos->get_pos())){
            enem.health--;
            if(enem.health == 0){
                enem.active = false;
                killed++;
            }
        }
    }

    }
    return killed;
}

EnemyBulletHandler::EnemyBulletHandler(ShaderProg& prog) : ExpendableObjectHandler{vertices, sizeof(vertices), objColor, prog}, timeAccum{0.0f}, bulletRate{1.0f}{}

void EnemyBulletHandler::spawn(const glm::vec3& coord, float dt) {
    /* timeAccum+=dt;
    if(timeAccum > bulletRate){
    timeAccum = 0; */
    this->entities.emplace_back(true, new EnemyBullet{ glm::vec2{coord.x, coord.y}, coord.z });
    //}
}

