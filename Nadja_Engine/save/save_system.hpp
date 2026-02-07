/*
 * @file save_system.hpp
 * @brief World save/load system for Nadja Engine.
 *
 * This header defines the SaveSystem class, responsible for
 * saving and loading the state of the game world.
 *
 * Responsibilities:
 * - Saving the current state of a World instance to a file
 * - Loading a World instance from a file
 * - Providing a static, centralized API for world persistence
 *
 * Dependencies:
 * - World (for accessing game world data)
 * - STL (string for file paths)
 *
 * Notes:
 * - All methods are static; no instance of SaveSystem is needed
 * - Save/load format should be consistent and versioned for future updates
 * - Intended for use at checkpoints, game exit, or level transitions
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include <string>

class World;

class SaveSystem {
public:
    static bool saveWorld(const World& world, const std::string& path);
    static bool loadWorld(World& world, const std::string& path);
};
