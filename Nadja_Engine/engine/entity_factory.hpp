#pragma once

#include <memory>
#include <string>
#include "entity.hpp"
#include "libs/json.hpp"

class EntityFactory {
public:
    // cria a partir de um objeto json já parseado
    static std::unique_ptr<Entity> create(const nlohmann::json& data);

    // cria direto de arquivo
    static std::unique_ptr<Entity> createFromFile(const std::string& path);
};
