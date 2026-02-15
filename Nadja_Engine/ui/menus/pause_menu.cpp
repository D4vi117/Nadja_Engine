#include "pause_menu.hpp"
#include <iostream>
#include "core/config.hpp"
#include "input/input.hpp"
void PauseMenu::start() {

    canvas.rect = { 0, 0, Config::Render::LOGICAL_WIDTH, Config::Render::LOGICAL_HEIGHT };
	canvas.padding = { 20,20,20,20 };

    auto panel = canvas.add(std::make_unique<UI::Panel>());
    panel->rect = {0, 0, 320, 300};
    
    auto rootVBox = panel->add(std::make_unique<UI::VBox>());
    rootVBox->rect = { 0, 0, 300, 280 };
    rootVBox->spacing = 15.f;
    rootVBox->padding = { 10,10,10,10 };

    rootVBox->add(std::make_unique<UI::Text>("UI TEST SCENE"));

    auto hbox = rootVBox->add(std::make_unique<UI::HBox>());
    hbox->anchor = { 0.f, 0.f };
    hbox->rect = { 0, 0, 280, 60 };
    hbox->spacing = 10.f;
    hbox->alignY = UI::Align::Center;
    hbox->justify = UI::Justify::Center;

    auto btnResume = hbox->add(std::make_unique<UI::Button>());
    btnResume->rect = { 0, 0, 80, 40 };
    auto txtResume = std::make_unique<UI::Text>("Resume");
    btnResume->child = std::move(txtResume);

	auto* btnSave = hbox->add(std::make_unique<UI::Button>());
	btnSave->rect = { 0, 0, 80, 40 };
	auto txtSave = std::make_unique<UI::Text>("Save");
	btnSave->child = std::move(txtSave);

	auto* btnLoad = hbox->add(std::make_unique<UI::Button>());
	btnLoad->rect = { 0, 0, 80, 40 };
	auto txtLoad = std::make_unique<UI::Text>("Load");
	btnLoad->child = std::move(txtLoad);


    btnResume->onClick = [this]() {
        if (onResume) onResume();
        };

    btnSave->onClick = [this]() {
		if (onSave) onSave();
        };

	btnLoad->onClick = [this]() {
        if (onLoad) onLoad();
		};
       
    canvas.layout();
}


void PauseMenu::update() {
    canvas.update();
    
}
void PauseMenu::render(SDL_Renderer* r) {
    canvas.render(r);
    UI::drawCross(r, Input::mouse.x, Input::mouse.y, 6.f);
}
