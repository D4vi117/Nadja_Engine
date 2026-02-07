/*
 * @file state_manager.hpp
 * @brief State manager for Nadja Engine.
 *
 * This header defines the StateManager class, responsible for managing
 * the stack of GameState instances and orchestrating their lifecycle,
 * event handling, updates, and rendering.
 *
 * Responsibilities:
 * - Managing a stack of active game states
 * - Pushing and popping states with proper ownership
 * - Forwarding SDL events, update calls, and render calls to the active state(s)
 *
 * Dependencies:
 * - GameState.hpp (base class for states)
 * - STL containers (vector, memory for unique_ptr)
 * - SDL3 (for event handling and rendering)
 *
 * Notes:
 * - The top of the stack is considered the currently active state
 * - Useful for implementing menus, gameplay, pause screens, and modal states
 * - Ensures ownership of states via std::unique_ptr
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include <memory>
#include <vector>
#include "game_state.hpp"

class StateManager {
public:
    void push(std::unique_ptr<GameState> state);
    void pop();

    void handleEvent(const SDL_Event& e);
    void update(float dt);
    void render(SDL_Renderer* r);

private:
    std::vector<std::unique_ptr<GameState>> stack;
};
