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