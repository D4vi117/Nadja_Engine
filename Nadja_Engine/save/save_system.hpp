#pragma once
#include <string>

class World;

class SaveSystem {
public:
    static bool saveWorld(const World& world, const std::string& path);
    static bool loadWorld(World& world, const std::string& path);
};
