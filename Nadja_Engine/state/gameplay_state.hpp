/*
 * @file GameplayState.hpp
 * @brief Gameplay state for Nadja Engine.
 *
 * This header defines the GameplayState class, a subclass of GameState,
 * responsible for managing active gameplay, including player interactions,
 * HUD, pause menu, and save/load functionality.
 *
 * Responsibilities:
 * - Managing the game world during active gameplay
 * - Handling player input and SDL events
 * - Updating game logic each frame
 * - Rendering the world, HUD, and pause menu
 * - Supporting save/load operations and pause state toggling
 *
 * Dependencies:
 * - GameState (base class)
 * - World (game world management)
 * - StateManager (state transitions)
 * - HUD and PauseMenu UI components
 * - SDL3 (for rendering and events)
 * - STL (string, unique_ptr)
 *
 * Notes:
 * - Tracks internal pause state and pending load requests
 * - HUD and pause menu are managed as part of the state
 * - Designed to keep orchestration focused; game logic lives in World and entities
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include "game_state.hpp"
#include "engine/world.hpp"
#include "state_manager.hpp"
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
