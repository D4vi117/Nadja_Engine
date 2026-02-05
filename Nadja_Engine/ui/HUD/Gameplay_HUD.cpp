#include "ui/HUD/Gameplay_HUD.hpp"
#include "ui/ui.hpp"
#include "core/config.hpp"
#include "gameplay/player.hpp"
#include "core/time.hpp"
#include <sstream>
#include <iomanip>

GameplayHUD::GameplayHUD(Player* p)
    : player(p)
{
    canvas.rect = { 0, 0, 0, 0 };
    canvas.padding = { 10,10,10,10 };

    auto* healthBar = canvas.add(std::make_unique<UI::Panel>());
    healthBar->bg = { 100,0,0,200 };
    healthBar->rect = { 0, 200, 200, 30 };
    healthBar->padding = { 4,4,4,4 };
   
    healthDecreaser = healthBar->add(std::make_unique<UI::Panel>());
    healthDecreaser->bg = { 255,255,0,255 };
    healthDecreaser->anchor = { 0, .5f };
    healthDecreaser->rect = { 4, 0, 192, 22 };

    healthFill = healthBar->add(std::make_unique<UI::Panel>());
    healthFill->bg = { 0,255,0,255 };
    healthFill->anchor = { 0, .5f };
    healthFill->rect = { 4, 0, 192, 22 };

	healthText = healthBar->add(std::make_unique<UI::Text>("100 / 100"));
	healthText->anchor = { 0.f, 0.f };
	healthText->rect = { 4, 0, 0, 0 };

	fpsText = canvas.add(std::make_unique<UI::Text>("FPS: 0"));
	fpsText->anchor = { 0.f, 0.f };

    canvas.layout();
}
void GameplayHUD::update(float dt) {
    if (!player) return;

    std::ostringstream ss;
    ss << std::fixed << std::setprecision(1) << Time::fps;

    fpsText->setText("FPS: " + ss.str());

    float realHealth = std::clamp(player->health, 0.f, 100.f);

    // =========================
    //  YELLOW
    // =========================
    delayedHealth = realHealth;

    // =========================
    //  GREEN
    // =========================
    if (smoothHealth > realHealth) {
        smoothHealth = realHealth;
    }
    else if (smoothHealth < realHealth) {
        float speed = 60.f;
        smoothHealth += speed * dt;

        if (smoothHealth > realHealth)
            smoothHealth = realHealth;
    }

    healthDecreaser->rect.w = (192 * (delayedHealth / 100.f));
    healthFill->rect.w = (192 * (smoothHealth / 100.f));

	healthText->setText(std::to_string(static_cast<int>(realHealth)) + " / 100");

    canvas.update();
}

void GameplayHUD::render(SDL_Renderer* r) {
	canvas.render(r);
}