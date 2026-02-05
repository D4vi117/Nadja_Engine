#pragma once
#include <memory>
#include <vector>
#include "gamestate.hpp"

class StateManager {
public:
    void push(std::unique_ptr<GameState> state);
    void pop();

    void handleEvent(const SDL_Event& e);
    void update(float dt);
    void render(SDL_Renderer* r);

private:
    std::vector<std::unique_ptr<GameState>> stack;
};
