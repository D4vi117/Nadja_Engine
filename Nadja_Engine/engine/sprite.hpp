#pragma once
#include <SDL3/SDL.h>
#include "entity.hpp"

class Sprite : public Entity {
public:
    SDL_Texture* texture = nullptr;

    Sprite(SDL_Texture* tex, float width, float height);
    ~Sprite();

    void render(SDL_Renderer* renderer) override;
    void move(float dx, float dy) override;

    std::vector<Collider> getColliders() const override;

    virtual void interact(Entity* other) override;

    const void debug_collider(SDL_Renderer* renderer);
};
