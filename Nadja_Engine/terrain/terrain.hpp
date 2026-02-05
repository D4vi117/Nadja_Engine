#pragma once
#include "engine/sprite.hpp"

class Terrain : public Sprite {
public:
    Terrain(SDL_Texture* tex, float width, float height)
        : Sprite(tex, width, height)
    {
        bodyType = BodyType::STATIC;
    }

    std::vector<Collider> getColliders() const override {
        std::vector<Collider> cols;

        Collider fullBlock;
        fullBlock.shape = ShapeType::AABB;
        fullBlock.type = ColliderType::BLOCK;
        fullBlock.rect = { x, y-1, w, h };

        cols.push_back(fullBlock);
        return cols;
    }

};
