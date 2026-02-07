/*
 * @file actor.hpp
 * @brief Actor class for Nadja Engine.
 *
 * This header defines the Actor class, a specialized subclass of Sprite,
 * representing game characters or interactive objects that may need
 * state serialization.
 *
 * Responsibilities:
 * - Inherits all rendering, movement, and collision functionality from Sprite
 * - Provides interfaces for saving and loading state via JSON
 * - Serves as a base for player characters, NPCs, or other interactive entities
 *
 * Dependencies:
 * - Sprite.hpp (base class)
 * - SDL3 (via Sprite for rendering)
 * - nlohmann::json for serialization
 *
 * Notes:
 * - serializeState() and deserializeState() are virtual and can be
 *   overridden by derived classes for custom behavior.
 * - Actor adds minimal overhead on top of Sprite, focusing on state management.
 *
 * @author Davi Barbosa
 * @date 2026
 */

#include "sprite.hpp"

class Actor : public Sprite {
public:
    Actor(SDL_Texture* texture, float w, float h);
    virtual void serializeState(nlohmann::json& out) const {}
    virtual void deserializeState(const nlohmann::json& in) {}

};
