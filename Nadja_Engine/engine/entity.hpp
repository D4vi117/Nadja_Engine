#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include <optional>
#include "physics/collider.hpp"
#include "physics/phisycs_body.hpp"
#include "audio/audio_manager.hpp"
#include "libs/json.hpp"


class Entity {
public:
    float x = 0;
    float y = 0;
    float z = 0;

    float rotation = 0.0f; //redians
    
    float w = 0;
    float h = 0;

    std::string name;
    std::string prefabPath;

    BodyType bodyType = BodyType::STATIC;

    std::vector<CollisionInfo> collisions;

    std::optional<PhysicsBody> physics;

    uint32_t persistentId = 0;

    bool persistent = false;

    virtual ~Entity() = default;

    virtual void start() {}
    virtual void update(float delta) {}
    virtual void render(SDL_Renderer* r) {}

    virtual void move(float dx, float dy) = 0;

    // agora retorna TODOS os colliders
    virtual std::vector<Collider> getColliders() const = 0;

    void clearCollisions() {
        collisions.clear();
    }

    virtual void interact(Entity* other) {}


};
