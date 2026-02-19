#include "entity_factory.hpp"

#include <fstream>
#include <iostream>

#include "sprite.hpp"
#include "terrain/slope.hpp"
#include "terrain/terrain.hpp"
#include "gameplay/pipe.hpp"
#include "gameplay/player.hpp"
#include "asset_manager.hpp"

using json = nlohmann::json;

std::unique_ptr<Entity> EntityFactory::createFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[EntityFactory] Failed to open " << path << "\n";
        return nullptr;
    }

    json data;
    file >> data;
    return create(data);
}

std::unique_ptr<Entity> EntityFactory::create(const json& data) {
    if (!data.contains("type")) {
        std::cerr << "[EntityFactory] Entity has no type\n";
        return nullptr;
    }

    std::string type = data["type"];

    std::unique_ptr<Entity> entity = nullptr;

    // ===== FACTORY =====
    if (type == "Player") {
        std::string tex = data["components"]["Sprite"]["texture"];
        entity = std::make_unique<Player>(AssetManager::getTexture(tex));
    }
    else if (type == "Sprite") {
        std::string tex = data["components"]["Sprite"]["texture"];
        entity = std::make_unique<Sprite>(
            AssetManager::getTexture(tex),
            0.f, 0.f
        );
    }
    else if (type == "Terrain"){
        std::string tex = data["components"]["Sprite"]["texture"];
        entity = std::make_unique<Terrain>(
            AssetManager::getTexture(tex),
            0.f, 0.f
        );

    }
    else if(type == "Slope")
    {
        std::string tex = data["components"]["Sprite"]["texture"];
        entity = std::make_unique<Slope>(
            AssetManager::getTexture(tex),
            0.f, 0.f
        );
    }
    else if (type == "Pipe")
    {
        entity = std::make_unique<Pipe>(
            AssetManager::getTexture(data["components"]["Sprite"]["top"]),
            AssetManager::getTexture(data["components"]["Sprite"]["bottom"]),
            26.f,
            320.f
        );

    }
    else {
        std::cerr << "[EntityFactory] Unknown type: " << type << "\n";
        return nullptr;
    }

    // ===== COMMON DATA =====
    if (data.contains("name"))
        entity->name = data["name"];

    if (data.contains("transform")) {
        auto& t = data["transform"];
        entity->x = t.value("x", 0.f);
        entity->y = t.value("y", 0.f);
        entity->w = t.value("w", entity->w);
        entity->h = t.value("h", entity->h);
    }

    if (data.contains("bodyType")) {
        std::string bt = data["bodyType"];
        if (bt == "STATIC") entity->bodyType = BodyType::STATIC;
        else if (bt == "KINEMATIC") entity->bodyType = BodyType::KINEMATIC;
        else if (bt == "DYNAMIC") entity->bodyType = BodyType::DYNAMIC;
    }

    return entity;
}
