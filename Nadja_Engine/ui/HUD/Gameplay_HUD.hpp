/*
 * @file Gameplay_HUD.hpp
 * @brief Player HUD UI for Nadja Engine gameplay.
 *
 * This header defines the GameplayHUD class, which provides a heads-up
 * display (HUD) for the player, showing health, FPS, and other gameplay
 * information.
 *
 * Responsibilities:
 * - Displaying health bars and textual information
 * - Smoothly updating health visuals with delayed and smoothed values
 * - Showing FPS and other debug/game info if needed
 * - Integrating with the engine's UI system
 *
 * Dependencies:
 * - ui/ui.hpp (core UI system and elements)
 * - Player.hpp (to access player state and stats)
 * - SDL3 (for rendering)
 *
 * Notes:
 * - HUD elements are rendered via internal Canvas and Panels
 * - Designed to be attached to GameplayState for active gameplay
 * - Health updates are smoothed to enhance visual feedback
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once

#include "ui/ui.hpp"
#include "gameplay/player.hpp"

class GameplayState;

class GameplayHUD {
public:
	GameplayHUD(Player* player, GameplayState* state);
	void start();
	void update(float dt);
	void render(SDL_Renderer* r);
	void forceLayout() { canvas.layout(); }
	Player* player = nullptr;
	GameplayState* state = nullptr;

private:
	UI::Canvas canvas;
	UI::Text* fpsText = nullptr;
	UI::Text* pointsText = nullptr;
};