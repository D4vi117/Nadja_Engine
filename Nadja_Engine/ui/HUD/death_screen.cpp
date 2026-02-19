#include "death_screen.hpp"
#include <iostream>
#include "core/config.hpp"
#include "input/input.hpp"
void DeathScreen::start() {

    canvas.rect = { 0, 0, Config::Render::LOGICAL_WIDTH, Config::Render::LOGICAL_HEIGHT };
	canvas.padding = { 20,20,20,20 };

    auto* btnBegin = canvas.add(std::make_unique<UI::Button>());
    btnBegin->rect = { 0, 0, 120, 40 };
	btnBegin->anchor = { 0.5f, 0.5f };
    auto txtResume = std::make_unique<UI::Text>("Resume");
    btnBegin->child = std::move(txtResume);

	btnBegin->onClick = [this]() {
        if (onBegin) onBegin();
		};
       
    canvas.layout();
}


void DeathScreen::update() {
    canvas.update();
    
}
void DeathScreen::render(SDL_Renderer* r) {
    canvas.render(r);

}
