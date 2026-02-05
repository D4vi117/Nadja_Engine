
#include "save_system.hpp"

#include <fstream>
#include <iostream>
#include "libs/json.hpp"
#include "engine/actor.hpp"
#include "engine/entity_factory.hpp"
#include <cmath>

#include "engine/world.hpp"

using json = nlohmann::json;

bool SaveSystem::saveWorld(const World& world, const std::string& path)
{
    json root;
    root["level"] = "level.json"; // depois você puxa isso do World
    root["entities"] = json::object();
    root["spawned"] = json::array();

    for (const auto& e : world.getEntities()) {
        if (!e) continue;

        // ENTIDADE DO LEVEL salva só estado
        if (e->persistent) {
            json state;

            state["transform"] = {
                { "x", std::floor(e->x) },
                { "y", std::floor(e->y) },
                { "w", e->w },
                { "h", e->h }
            };

            if (auto* actor = dynamic_cast<Actor*>(e.get())) {
                actor->serializeState(state);
            }

            root["entities"][std::to_string(e->persistentId)] = state;
        }
        // ENTIDADE DINÂMICA salva inteira
        else {
            json ent;
            ent["prefab"] = e->prefabPath;

            ent["state"]["transform"] = {
                { "x", std::floor(e->x) },
                { "y", std::floor(e->y) },
                { "w", e->w },
                { "h", e->h }
            };

            if (auto* actor = dynamic_cast<Actor*>(e.get())) {
                actor->serializeState(ent["state"]);
            }

            root["spawned"].push_back(ent);
        }
    }

    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "[SaveSystem] Failed to write save file\n";
        return false;
    }

    file << root.dump(4);
    return true;
}


bool SaveSystem::loadWorld(World& world, const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[SaveSystem] Failed to open save file\n";
        return false;
    }

    json root;
    file >> root;

    // carrega level base
    world.loadLevel(root.value("level", "level.json"));

    // aplica estado nas entidades persistentes
    if (root.contains("entities")) {
        for (auto& [idStr, state] : root["entities"].items()) {
            uint32_t id = std::stoul(idStr);
            Entity* e = world.findByPersistentId(id);
            if (!e) continue;

            if (state.contains("transform")) {
                auto& t = state["transform"];
                e->x = t.value("x", e->x);
                e->y = t.value("y", e->y);
                e->w = t.value("w", e->w);
                e->h = t.value("h", e->h);
            }

            if (auto* actor = dynamic_cast<Actor*>(e)) {
                actor->deserializeState(state);
            }
        }
    }

    //  recria entidades dinâmicas
    if (root.contains("spawned")) {
        for (auto& ent : root["spawned"]) {
            std::string prefab = ent["prefab"];

            auto entity = EntityFactory::createFromFile(prefab);
            if (!entity) continue;

            entity->prefabPath = prefab;
            entity->persistent = false;

            auto& state = ent["state"];
            if (state.contains("transform")) {
                auto& t = state["transform"];
                entity->x = t.value("x", entity->x);
                entity->y = t.value("y", entity->y);
                entity->w = t.value("w", entity->w);
                entity->h = t.value("h", entity->h);
            }

            if (auto* actor = dynamic_cast<Actor*>(entity.get())) {
                actor->deserializeState(state);
            }

            world.spawnNow(std::move(entity));
        }
    }

    return true;
}
