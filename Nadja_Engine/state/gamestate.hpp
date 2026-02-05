#pragma once
#include <SDL3/SDL.h>
#include "core/config.hpp"

class GameState {
public:
    virtual ~GameState() = default;

    virtual void enter() {}
    virtual void exit() {}
    virtual void pause() {}
    virtual void resume() {}
    virtual void handleEvent(const SDL_Event&) = 0;
    virtual void update(float) = 0;
    virtual void render(SDL_Renderer*) = 0;

    void BeginWorldRender(SDL_Renderer* r) {
        SDL_SetRenderLogicalPresentation(
            r,
            Config::Render::LOGICAL_WIDTH,
            Config::Render::LOGICAL_HEIGHT,
            SDL_LOGICAL_PRESENTATION_OVERSCAN
        );
        SDL_SetRenderViewport(r, nullptr);
    }

    void BeginUIRender(SDL_Renderer* r, SDL_Window* w) {
        SDL_SetRenderLogicalPresentation(
            r,
            0, 0,
            SDL_LOGICAL_PRESENTATION_DISABLED
        );

        int ww, wh;
        SDL_GetWindowSize(w, &ww, &wh);

        SDL_Rect vp{ 0, 0, ww, wh };
        SDL_SetRenderViewport(r, &vp);
    }

};
