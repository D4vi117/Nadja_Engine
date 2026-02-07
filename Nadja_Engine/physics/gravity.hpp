/*
 * @file gravity.hpp
 * @brief Physics system functions for Nadja Engine.
 *
 * This header defines physics-related operations on game entities,
 * such as applying forces like gravity.
 *
 * Responsibilities:
 * - Applying gravity to a list of entities each frame
 * - Serving as a base for future physics-related functions (collisions,
 *   forces, motion integration)
 *
 * Dependencies:
 * - Entity.hpp (for access to entity position, body type, and physics state)
 * - STL containers (vector, memory for unique_ptr)
 *
 * Notes:
 * - Functions operate on vectors of std::unique_ptr<Entity> to maintain ownership semantics
 * - Delta time (delta) is required to apply frame-rate-independent physics
 * - Designed to integrate with collision and movement systems
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include <vector>
#include <memory>
#include "engine/entity.hpp"

namespace Physics {
    void applyGravity(
        const std::vector<std::unique_ptr<Entity>>& entities,
        float delta
    );
}
