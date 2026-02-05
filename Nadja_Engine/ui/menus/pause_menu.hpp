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