#include "ui/HUD/Gameplay_HUD.hpp"
#include "ui/ui.hpp"
#include "core/config.hpp"
#include "gameplay/player.hpp"
#include "core/time.hpp"
#include "state/gameplay_state.hpp"
#include <sstream>
#include <iomanip>

GameplayHUD::GameplayHUD(Player* p, GameplayState* s)
	: player(p), state(s)
{
    canvas.rect = { 0, 0, 0, 0 };
    canvas.padding = { 10,10,10,10 };
	fpsText = canvas.add(std::make_unique<UI::Text>("FPS: 0"));
	fpsText->anchor = { 0.f, 0.f };
	pointsText = canvas.add(std::make_unique<UI::Text>("Points: 0"));
	pointsText->anchor = { 0.5f, 0.f };

    canvas.layout();
}
void GameplayHUD::update(float dt) {
    if (!player) return;

    std::ostringstream ss;
    ss << std::fixed << std::setprecision(1) << Time::fps;

    fpsText->setText("FPS: " + ss.str());
	pointsText->setText("Points: " + std::to_string(state->Points));
    if (!player->alive)
    {
        state->setPaused(true);
    }
    canvas.update();
}

void GameplayHUD::render(SDL_Renderer* r) {
	canvas.render(r);
}