/*
 * @file sprite.hpp
 * @brief Sprite entity class for Nadja Engine.
 *
 * This header defines the Sprite class, a subclass of Entity,
 * representing visual game objects with an SDL_Texture.
 *
 * Responsibilities:
 * - Storing and managing the SDL_Texture associated with the entity
 * - Rendering the sprite using SDL3
 * - Implementing movement and collision retrieval from base Entity
 * - Providing interaction and optional debug rendering for colliders
 *
 * Dependencies:
 * - SDL3 (for texture management and rendering)
 * - Entity.hpp (base class)
 * - Collider system (from Entity/Physics integration)
 *
 * Notes:
 * - Inherits position, rotation, physics, and collision management
 *   from Entity.
 * - Debugging helpers like debug_collider() are included for development.
 * - All graphical logic is separated from core entity logic.
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include <SDL3/SDL.h>
#include "entity.hpp"

class Sprite : public Entity {
public:
    SDL_Texture* texture = nullptr;

    Sprite(SDL_Texture* tex, float width, float height);
    ~Sprite();

    void render(SDL_Renderer* renderer) override;
    void move(float dx, float dy) override;

    std::vector<Collider> getColliders() const override;

    virtual void interact(Entity* other) override;

    const void debug_collider(SDL_Renderer* renderer);
};
