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
