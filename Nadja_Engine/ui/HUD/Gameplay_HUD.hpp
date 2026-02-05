#pragma once

#include "ui/ui.hpp"
#include "gameplay/player.hpp"


class GameplayHUD {
public:
	GameplayHUD(Player* player);
	void start();
	void update(float dt);
	void render(SDL_Renderer* r);
	Player* player = nullptr;

private:
	UI::Canvas canvas;
	UI::Panel* healthFill = nullptr;       // verde
	UI::Panel* healthDecreaser = nullptr;  // amarelo

	UI::Text* healthText = nullptr;
	UI::Text* fpsText = nullptr;

	float delayedHealth = 100.f; // amarelo
	float smoothHealth = 100.f; // verde
};