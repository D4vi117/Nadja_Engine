/*
 * @file terrain.hpp
 * @brief Terrain entity for Nadja Engine.
 *
 * This header defines the Terrain class, a subclass of Sprite, representing
 * static terrain blocks in the game world.
 *
 * Responsibilities:
 * - Storing texture, size, and base entity properties from Sprite
 * - Setting static body type for physics interactions
 * - Defining AABB colliders representing solid terrain
 *
 * Dependencies:
 * - Sprite.hpp (base class)
 * - Collider system (for collision detection)
 *
 * Notes:
 * - getColliders() returns an AABB collider covering the terrain block
 * - Intended for level geometry, ground, and platforms
 * - Inherits rendering, movement, and other base functionality from Sprite
 *
 * @author Davi Barbosa
 * @date 2026
 */

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
