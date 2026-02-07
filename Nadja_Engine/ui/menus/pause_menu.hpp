/*
 * @file pause_menu.hpp
 * @brief Pause menu UI for Nadja Engine gameplay.
 *
 * This header defines the PauseMenu class, which provides an in-game
 * pause menu interface with buttons for resuming, saving, and loading
 * the game.
 *
 * Responsibilities:
 * - Displaying a pause menu canvas and UI elements
 * - Handling user interactions via callbacks (onResume, onSave, onLoad)
 * - Integrating with the engine's UI system
 *
 * Dependencies:
 * - ui/ui.hpp (core UI system and elements)
 * - SDL3 (for rendering)
 * - Functional (for callback functions)
 *
 * Notes:
 * - Canvas and UI elements are managed internally
 * - Callbacks allow gameplay logic to respond to menu actions
 * - Designed for quick integration into GameplayState
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include "ui/ui.hpp"

class PauseMenu {
public:
    void start();
    void update();
    void render(SDL_Renderer* r);

    std::function<void()> onResume;
    std::function<void()> onSave;
    std::function<void()> onLoad;

private:
    UI::Canvas canvas;

};