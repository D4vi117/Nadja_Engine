#pragma once

#include "engine/sprite.hpp"

class Pipe : public Entity {
public:
    Pipe(SDL_Texture* top, SDL_Texture* bottom, float w, float h);

    void update(float delta) override;
    void render(SDL_Renderer* r) override;

    void move(float dx, float dy) override;
    std::vector<Collider> getColliders() const override;
    
    std::function<void()> onScore;

private:
    SDL_Texture* t_top = nullptr;
    SDL_Texture* t_bottom = nullptr;
    float gap = 80.f;
	bool scored = false;
};
