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

        // pontos LOCAIS (origem = x, y da entidade)
        // slope subindo da esquerda pra direita
        slope.points = {
            { 0.0f, h },   // canto inferior esquerdo
            { w,    0.0f },// canto superior direito
            { w,    h }    // canto inferior direito
        };

        cols.push_back(slope);
        return cols;
    }
};
