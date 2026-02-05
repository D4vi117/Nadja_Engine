#include "application.hpp"

bool Application::init() {
    return true;
}

void Application::handleEvent(const SDL_Event& e) {
    (void)e;
}

void Application::update(float dt) {
    (void)dt;
}

void Application::render(SDL_Renderer* r) {
    (void)r;
}

void Application::shutdown() {
}
