#include "statemanager.hpp"

void StateManager::push(std::unique_ptr<GameState> state) {
    if (!stack.empty())
        stack.back()->pause();

    stack.push_back(std::move(state));
    stack.back()->enter();
}

void StateManager::pop() {
    if (stack.empty())
        return;

    stack.back()->exit();
    stack.pop_back();

    if (!stack.empty())
        stack.back()->resume();
}


void StateManager::handleEvent(const SDL_Event& e) {
    if (!stack.empty())
        stack.back()->handleEvent(e);
}

void StateManager::update(float dt) {
    if (!stack.empty())
        stack.back()->update(dt);

}

void StateManager::render(SDL_Renderer* r) {
    for (auto& s : stack)
        s->render(r);
}