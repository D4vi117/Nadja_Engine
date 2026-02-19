/*
 * @file world.hpp
 * @brief World simulation container for Nadja Engine.
 *
 * The World class represents a game world instance responsible for:
 *
 * - Owning and managing all active entities
 * - Controlling entity lifecycle (spawn, update, destroy)
 * - Driving physics simulation and gravity
 * - Rendering entities and world geometry (terrain)
 * - Managing pause state
 *
 * Entity addition and removal are deferred to ensure safe iteration
 * during update and render phases.
 *
 * The World does not contain game-specific logic; it acts as a
 * simulation and orchestration layer between engine systems and
 * gameplay code.
 *
 * Typically, a single World instance exists per gameplay state.
 *
 * @author Davi
 * Date 2026
 */

#pragma once
#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include "entity.hpp"
#include "terrain/terrain.hpp"

class World {
public:
    World();
    void add(std::unique_ptr<Entity> e);
    void destroy(Entity* e);
    void spawnNow(std::unique_ptr<Entity> e);
    void update(float dt);
    void loadLevel(const std::string& levelPath);
    Entity* findByPersistentId(uint32_t id);
    void render(SDL_Renderer* r);

    void clear();

    void setPaused(bool value);
    void togglePause();
    bool isPaused() const;

    const std::vector<std::unique_ptr<Entity>>& getEntities() const;

    float width = 2000;
    float height = 2000;

    SDL_Texture* background = nullptr;


private:
	float accumulator = 0.0f;
    std::vector<std::unique_ptr<Entity>> toAdd;
    std::vector<Entity*> toRemove;

    bool paused = false;
    
    std::vector<std::unique_ptr<Entity>> entities;
    std::unordered_map<uint32_t, Entity*> persistentMap;
};