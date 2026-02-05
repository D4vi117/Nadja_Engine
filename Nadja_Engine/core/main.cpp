/*
 * @file main.cpp
 * @brief Application entry point and main loop implementation for Nadja Engine.
 *
 * This file defines the SDL3 application lifecycle using the
 * SDL_MAIN_USE_CALLBACKS model. It is responsible for:
 *
 * - Initializing core subsystems
 * - Creating and configuring the main window and renderer
 * - Managing the main game loop (events, update, render)
 * - Handling global shutdown and cleanup
 *
 * The engine uses a state-based architecture, where the StateManager
 * controls the active game states (e.g., GameplayState).
 *
 * Rendering is performed using a logical resolution with nearest-neighbor
 * scaling to ensure pixel-perfect visuals.
 *
 * Dependencies:
 * - SDL3
 * - SDL3_ttf
 * - Nadja Engine core modules (input, time, graphics, UI, state system)
 *
 * Notes:
 * - This file should remain lightweight and orchestration-focused.
 * - Game logic should live inside states, not here.
 *
 * @author Davi Barbosa
 * @date 2026
*/

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

#include "config.hpp"
#include "input/input.hpp"
#include "time.hpp"
#include "graphics/camera.hpp"
#include "ui/ui.hpp"
#include "state/statemanager.hpp"
#include "state/gameplay_state.hpp"
#include "engine/asset_manager.hpp"
#include "engine/context.hpp"

static StateManager states;
static World world;

/* INIT */
using namespace Engine;

static SDL_AppResult SDL_AppInit(void**, int, char**) {
    SDL_SetAppMetadata("Nadja Engine", "0.1", "nadja.engine");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL init failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(
        "Nadja Engine",
        640, 480,
        SDL_WINDOW_RESIZABLE,
        &window, &renderer)) {
        SDL_Log("Window/Renderer failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!TTF_Init()) {
        SDL_Log("TTF init failed");
        return SDL_APP_FAILURE;
    }

    AssetManager::init(renderer);
    AudioManager::init();

    AssetManager::loadFont("default", "assets/fonts/font.ttf", 18);
    UI::Font::init("default");

    SDL_SetDefaultTextureScaleMode(renderer, SDL_SCALEMODE_NEAREST);

    SDL_SetRenderLogicalPresentation(
        renderer,
        Config::Render::LOGICAL_WIDTH,
        Config::Render::LOGICAL_HEIGHT,
        SDL_LOGICAL_PRESENTATION_OVERSCAN
    );
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    extern Camera g_camera;
    g_camera.viewportW = Config::Render::LOGICAL_WIDTH;
    g_camera.viewportH = Config::Render::LOGICAL_HEIGHT;

    states.push(std::make_unique<GameplayState>(world, renderer, states));
    return SDL_APP_CONTINUE;

}

/* EVENT */
SDL_AppResult SDL_AppEvent(void*, SDL_Event* e) {

    if (e->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;

    if (e->type == SDL_EVENT_WINDOW_RESIZED) {
        SDL_SetRenderLogicalPresentation(
            renderer,
            Config::Render::LOGICAL_WIDTH,
            Config::Render::LOGICAL_HEIGHT,
            SDL_LOGICAL_PRESENTATION_OVERSCAN
        );

    }
    Input::handleEvent(*e);

    states.handleEvent(*e);

    return SDL_APP_CONTINUE;
}

/* LOOP */
SDL_AppResult SDL_AppIterate(void*) {
    Time::update();

    states.update(Time::delta);
    states.render(renderer);

    SDL_RenderPresent(renderer);
    Input::update();

    return SDL_APP_CONTINUE;
}

/* QUIT */
void SDL_AppQuit(void*, SDL_AppResult) {
    states.pop();
    TTF_Quit();
    AudioManager::shutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
