/*
 * @file physics_solver.hpp
 * @brief Physics solver functions for Nadja Engine.
 *
 * This header defines functions responsible for resolving physics
 * interactions between entities, such as collision response and
 * motion adjustment.
 *
 * Responsibilities:
 * - Processing a collection of entities each frame
 * - Applying collision resolution and positional corrections
 * - Serving as part of the engine's physics pipeline
 *
 * Dependencies:
 * - Entity.hpp (to access entity positions, colliders, and physics bodies)
 * - STL containers (vector, memory for unique_ptr)
 *
 * Notes:
 * - Entities are passed as std::unique_ptr references to maintain ownership
 * - Intended to be called once per frame after applying forces (e.g., gravity)
 * - Integration with Animator, Collider, and PhysicsBody is expected
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include <vector>
#include "engine/entity.hpp"
#include <memory>

namespace Physics {
    void solve(const std::vector<std::unique_ptr<Entity>>& entities);
}
