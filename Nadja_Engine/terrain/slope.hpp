/*
 * @file slope.hpp
 * @brief Slope entity for Nadja Engine.
 *
 * This header defines the Slope class, a subclass of Sprite, representing
 * ramp-like geometry in the game world.
 *
 * Responsibilities:
 * - Storing texture, size, and base entity properties from Sprite
 * - Setting static body type for physics interactions
 * - Defining polygon colliders representing the slope surface
 *
 * Dependencies:
 * - Sprite.hpp (base class)
 * - Collider system (for collision detection)
 *
 * Notes:
 * - getColliders() returns a polygon-shaped collider representing the slope
 * - Designed for use in terrain and level design with proper physics response
 * - Inherits rendering, movement, and other base functionality from Sprite
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include "engine/sprite.hpp"

class Slope : public Sprite {
public:
    Slope(SDL_Texture* tex, float width, float height)
        : Sprite(tex, width, height)
    {
        bodyType = BodyType::STATIC;
        name = "Slope";
    }

    std::vector<Collider> getColliders() const override {
        std::vector<Collider> cols;

        Collider slope;
        slope.shape = ShapeType::POLYGON;
        slope.type = ColliderType::BLOCK;

        slope.points = {
            { 0.0f, h },
            { w,    0.0f },
            { w,    h }    
        };

        cols.push_back(slope);
        return cols;
    }
};
