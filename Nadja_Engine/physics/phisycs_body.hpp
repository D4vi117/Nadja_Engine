/*
 * @file physics_body.hpp
 * @brief Physics body structure for Nadja Engine.
 *
 * This header defines the PhysicsBody struct, which stores
 * physics-related properties for entities, such as velocity,
 * acceleration, and gravity handling.
 *
 * Responsibilities:
 * - Storing current velocity and acceleration of an entity
 * - Tracking grounded state and ground timer
 * - Controlling gravity usage and scaling
 * - Serving as the physics component for integration with
 *   movement and collision systems
 *
 * Dependencies:
 * - Vec2.hpp (for 2D vector math)
 *
 * Notes:
 * - Designed to be used as a member of Entity or attached physics components
 * - Delta-time integration and physics updates occur elsewhere in the engine
 * - Provides a lightweight, per-entity physics state
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include "math/vec2.hpp"

struct PhysicsBody {
    Vec2 velocity{ 0, 0 };
    Vec2 acceleration{ 0, 0 };

    bool useGravity = true;
    float groundTimer = 0.0f;
    bool grounded = false;

    float gravityScale = 1.0f;
};
