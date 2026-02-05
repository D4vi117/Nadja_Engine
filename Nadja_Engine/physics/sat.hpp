#pragma once
#include <vector>
#include "math/vec2.hpp"

struct SATResult {
    bool hit = false;
    Vec2 normal;
    float depth = 0.0f;
};

SATResult SAT(const std::vector<Vec2>& A, const std::vector<Vec2>& B);
