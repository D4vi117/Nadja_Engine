/*
 * @file entity.hpp
 * @brief Base class for all entities in Nadja Engine.
 *
 * This header defines the Entity class, which serves as the base
 * for all in-game objects with position, rotation, physics, and
 * collision behavior.
 *
 * Responsibilities:
 * - Storing core entity properties (position, size, rotation)
 * - Managing optional physics body integration
 * - Tracking collisions per frame
 * - Providing a common interface for update, render, and interaction
 * - Defining pure virtual methods for movement and collider retrieval
 *
 * Dependencies:
 * - SDL3 (for rendering)
 * - Physics system headers (Collider, PhysicsBody)
 * - AudioManager (for potential audio interactions)
 * - JSON library for prefab/data serialization
 *
 * Notes:
 * - This is an abstract base class; derived classes should implement
 *   move() and getColliders() methods.
 * - Physics integration is optional and uses PhysicsBody when available.
 * - Collisions are tracked per-frame and cleared using clearCollisions().
 *
 * @author Davi Barbosa
 * @date 2026
 */

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

    float rotation_rad = 0.0f;
    
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

    virtual std::vector<Collider> getColliders() const = 0;

    void clearCollisions() {
        collisions.clear();
    }

    virtual void interact(Entity* other) {}


};
