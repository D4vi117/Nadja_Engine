/*
 * @file player.hpp
 * @brief Player-controlled actor implementation.
 *
 * This file defines the Player class, which represents the main
 * player-controlled entity in the game world.
 *
 * The Player extends the Actor base class and is responsible for:
 *
 * - Handling player-specific behavior and state updates
 * - Managing animations via the Animator system
 * - Rendering the player sprite
 * - Serializing and deserializing persistent player state (save/load)
 *
 * The Player integrates with the engine's physics, animation,
 * and world systems, and serves as a reference implementation
 * for controllable actors.
 *
 * Dependencies:
 * - Actor system
 * - Animator (sprite-based animation controller)
 * - Camera system
 * - nlohmann::json (serialization)
 *
 * Notes:
 * - Input handling is expected to be abstracted by the Actor or input system.
 * - Gameplay logic specific to the player should live here, not in generic actors.
 * - Health and animation state are part of the persistent save data.
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once

#include "engine/actor.hpp"
#include "graphics/animator.hpp"
#include "graphics/camera.hpp"
#include "libs/json.hpp"

class Player : public Actor {
public:
    Player(SDL_Texture* texture);

    void start() override;
    void update(float delta) override;
    void render(SDL_Renderer* r) override;
    std::vector<Collider> getColliders() const override;

    bool alive = true;

private:
    Animator animator;

    enum AnimID {
        IDLE = 0
    };
};
