/*
 * @file entityFactory.hpp
 * @brief Factory class for creating Entity instances in Nadja Engine.
 *
 * This header defines the EntityFactory class, responsible for
 * creating game entities from JSON data or external files.
 *
 * Responsibilities:
 * - Creating entities from already parsed JSON objects
 * - Creating entities directly from JSON files
 * - Encapsulating the construction logic of various Entity types
 *
 * Dependencies:
 * - Entity.hpp (base class for all entities)
 * - nlohmann::json (for JSON parsing and serialization)
 * - STL (memory, string)
 *
 * Notes:
 * - Returns std::unique_ptr<Entity> to manage ownership automatically.
 * - Supports future expansion for new entity types without modifying
 *   the engine core.
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once

#include <memory>
#include <string>
#include "entity.hpp"
#include "libs/json.hpp"

class EntityFactory {

public:
    
    static std::unique_ptr<Entity> create(const nlohmann::json& data);

    static std::unique_ptr<Entity> createFromFile(const std::string& path);
};
