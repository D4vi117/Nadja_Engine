#pragma once

#include "engine/actor.hpp"
#include "graphics/animator.hpp"
#include "graphics/camera.hpp"
#include "libs/json.hpp"

class Player : public Actor {
public:
    Player(SDL_Texture* texture);

    void start() override;
    void update(float delta) override;
    void render(SDL_Renderer* r) override;


	void serializeState(nlohmann::json& out) const override;
    void deserializeState(const nlohmann::json& in) override;
    
    float health = 100;

private:
    Animator animator;

    enum AnimID {
        IDLE = 0,
        WALK,
        RUN,
        ATTACK
    };
};
