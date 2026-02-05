#pragma once
#include "gamestate.hpp"
#include "engine/world.hpp"
#include "statemanager.hpp"
#include "ui/HUD/Gameplay_HUD.hpp"
#include "ui/menus/pause_menu.hpp"

class GameplayState : public GameState {
public:
    GameplayState(World& world, SDL_Renderer* r, StateManager& states);
    ~GameplayState() override;
    void enter() override;
    void handleEvent(const SDL_Event& e) override;
    void update(float dt) override;
    void render(SDL_Renderer* r) override;
    void loadSave(const std::string& path);
	void togglePause() { isPaused = !isPaused;
    }
    void setPaused(bool value) { isPaused = value; }
    void requestLoadSave(const std::string& path) {
        saveToLoad = path;
        loadRequested = true;
    }
private:
    // GameplayState.hpp
    bool loadRequested = false;
	bool isPaused = false;
    std::string saveToLoad;
    World& world;
    SDL_Renderer* renderer;
    StateManager& states;
    SDL_Texture* texture = nullptr;
    std::unique_ptr<GameplayHUD> hud;
    PauseMenu pauseMenu;

};
