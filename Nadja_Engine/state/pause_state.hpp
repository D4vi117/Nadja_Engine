#pragma once
#include "gamestate.hpp"
#include "engine/world.hpp"
#include "statemanager.hpp"
#include "ui/menus/pause_menu.hpp"
#include "gameplay_state.hpp"

class PauseState : public GameState {
public:
    PauseState(World& world, StateManager& states, GameplayState* gameplay);

    void enter() override;

    void handleEvent(const SDL_Event& e) override;
    void update(float dt) override;
    void render(SDL_Renderer* r) override;

private:
    World& world;
    StateManager& states;
    GameplayState* gameplay;
    PauseMenu pauseMenu;
};
