#include "world.hpp"
#include "physics/physics.hpp"
#include "sprite.hpp"
#include <algorithm>
#include "physics/gravity.hpp"
#include <cmath>
#include <fstream>
#include "entity_factory.hpp"
#include "core/config.hpp"

World::World() = default;


void World::add(std::unique_ptr<Entity> e) {
    if (!e) {
        std::cerr << "[World] Tried to add nullptr entity\n";
        return;
    }
    toAdd.push_back(std::move(e));
}

void World::destroy(Entity* e) {
    toRemove.push_back(e);
}

void World::setPaused(bool value) {
    paused = value;
}

void World::togglePause() {
    paused = !paused;
}

bool World::isPaused() const {
    return paused;
}

const std::vector<std::unique_ptr<Entity>>& World::getEntities() const {
    return entities;
}
void World::spawnNow(std::unique_ptr<Entity> e) {
    e->start();
    entities.push_back(std::move(e));
}
void World::update(float dt) {

    for (auto& e : toAdd) {
        e->start();
        entities.push_back(std::move(e));
    }
    toAdd.clear();

    if (!paused) {
        for (auto& e : entities){
            e->update(dt);
            
    }
        const float step = 1.0f / 120.0f;
        float accumulator = dt;

        while (accumulator > 0.0f) {
            float dt_step = (std::min)(step, accumulator);

            Physics::applyGravity(entities, dt_step);
            Physics::solve(entities);


            accumulator -= dt_step;
        }
    }

    for (Entity* dead : toRemove) {
        auto it = std::remove_if(
            entities.begin(),
            entities.end(),
            [&](const std::unique_ptr<Entity>& ptr) {
                return ptr.get() == dead;
            }
        );
        entities.erase(it, entities.end());
    }
    toRemove.clear();
}


void World::loadLevel(const std::string& levelPath)
{
    clear();

    std::ifstream file(levelPath);
    if (!file.is_open()) {
        std::cerr << "[World] Failed to open level: " << levelPath << "\n";
        return;
    }
    else
    {
		std::cout << "[World] Loading level: " << levelPath << "\n";
    }

    nlohmann::json root;
    file >> root;

    for (auto& ent : root["entities"]) {
        std::string prefab = ent["prefab"];
        uint32_t id = ent["id"];

        auto entity = EntityFactory::createFromFile(prefab);
        if (!entity) {
            std::cerr << "[World] Failed to create prefab: " << prefab << "\n";
            continue;
        }

        entity->prefabPath = prefab;
        entity->persistentId = id;
        entity->persistent = true;

        entity->x = ent.value("x", entity->x);
        entity->y = ent.value("y", entity->y);

        spawnNow(std::move(entity));

        persistentMap[id] = entities.back().get();
    }
}

Entity* World::findByPersistentId(uint32_t id)
{
    auto it = persistentMap.find(id);
    if (it == persistentMap.end())
        return nullptr;
    return it->second;
}


void World::render(SDL_Renderer* r) {
    SDL_SetRenderDrawColor(r, 170, 200, 220, 255);
    SDL_RenderClear(r);

    SDL_FRect dest;
    dest.x = 0.f;
    dest.y = 0.f;
    dest.w = Config::Render::LOGICAL_WIDTH;
    dest.h = Config::Render::LOGICAL_HEIGHT;

    SDL_RenderTexture(r, background, nullptr, &dest);

    std::sort(
        entities.begin(),
        entities.end(),
        [](const std::unique_ptr<Entity>& a,
            const std::unique_ptr<Entity>& b) {
                return (a->y + a->h) < (b->y + b->h);
        }
    );

    for (auto& e : entities) {
        e->render(r);

        if (auto* s = dynamic_cast<Sprite*>(e.get())) {
            s->debug_collider(r);
        }
    }
}

void World::clear()
{
    entities.clear();
    toAdd.clear();
    toRemove.clear();
    persistentMap.clear();

}
