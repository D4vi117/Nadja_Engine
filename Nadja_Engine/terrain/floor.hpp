#pragma once
#include "engine/actor.hpp"

class Floor : public Actor {
public:
    Floor(SDL_Texture* texture);

    void start() override;
};
