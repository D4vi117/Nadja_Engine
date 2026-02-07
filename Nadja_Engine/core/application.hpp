/*
 * @file application.hpp
 * @brief High-level application interface for Nadja Engine.
 *
 * The Application class represents the top-level owner of the engine
 * runtime. It is responsible for:
 *
 * - Initializing core systems and the main window/renderer
 * - Receiving and dispatching SDL events
 * - Driving the update and render steps
 * - Managing orderly shutdown of resources
 *
 * This class acts as a bridge between the platform layer (SDL)
 * and the engine subsystems. It should not contain game logic;
 * such logic must live in engine systems or state objects.
 *
 * Typically, only one Application instance should exist at a time.
 *
 * @author Davi
 * @date 2026
 */

#pragma once
#include <SDL3/SDL.h>

class Application {
public:
    bool init();
    void handleEvent(const SDL_Event& e);
    void update(float dt);
    void render(SDL_Renderer* renderer);
    void shutdown();

    SDL_Renderer* getRenderer() const { return renderer; }

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
