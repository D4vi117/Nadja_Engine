#pragma once
#include <vector>
#include "engine/entity.hpp"
#include <memory>
namespace Physics {
    void solve(const std::vector<std::unique_ptr<Entity>>& entities);
}
