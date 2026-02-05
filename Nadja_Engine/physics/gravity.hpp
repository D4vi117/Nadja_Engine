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
