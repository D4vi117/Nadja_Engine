/*
 * @file collider.hpp
 * @brief Collision system definitions for Nadja Engine.
 *
 * This header defines the core structures and enums used in the
 * engine's collision system, including colliders, collision info,
 * and body types.
 *
 * Responsibilities:
 * - Defining different collider shapes (AABB, polygon)
 * - Defining collider types (BLOCK, OVERLAP)
 * - Defining physics body types (STATIC, KINEMATIC, DYNAMIC)
 * - Storing collision information between entities
 * - Providing structures for use in collision detection and response
 *
 * Dependencies:
 * - SDL3 (for SDL_FRect)
 * - Vec2.hpp (for vector math in collision normals and polygons)
 * - STL containers (vector)
 *
 * Notes:
 * - Collider points for polygons are in local space
 * - CollisionInfo stores data needed for collision resolution
 * - Designed to integrate with Entity and PhysicsBody systems
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include <SDL3/SDL.h>
#include "math/vec2.hpp"

enum class ColliderType {
    BLOCK,
    OVERLAP
};

enum class BodyType {
    STATIC,
    KINEMATIC,
    DYNAMIC
};

class Entity;

struct CollisionInfo {
    Entity* other;
    ColliderType type;
    Vec2 normal;
    float depth;
};

enum class ShapeType {
    AABB,
    POLYGON
};

struct Collider {
    ShapeType shape = ShapeType::AABB;
    ColliderType type = ColliderType::BLOCK;

    // AABB
    SDL_FRect rect = { 0,0,0,0 };

    // SAT polygon (local space)
    std::vector<Vec2> points;
};