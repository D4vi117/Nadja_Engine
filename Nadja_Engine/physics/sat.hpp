/*
 * @file sat.hpp
 * @brief Separating Axis Theorem (SAT) collision detection for Nadja Engine.
 *
 * This header defines the SATResult struct and the SAT function for
 * performing collision checks between convex polygons.
 *
 * Responsibilities:
 * - Detecting collisions between two sets of points (polygons)
 * - Returning collision information including hit status, penetration depth, and collision normal
 * - Serving as part of the engine's physics and collision system
 *
 * Dependencies:
 * - Vec2.hpp (for vector math)
 * - STL containers (vector)
 *
 * Notes:
 * - SAT only supports convex polygons
 * - The SATResult struct contains all data needed for collision response
 * - Typically called by higher-level physics or collision systems
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include <vector>
#include "math/vec2.hpp"

struct SATResult {
    bool hit = false;
    Vec2 normal;
    float depth = 0.0f;
};

SATResult SAT(const std::vector<Vec2>& A, const std::vector<Vec2>& B);
