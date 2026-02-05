/**
 * @file time.hpp
 * @brief Frame timing and time-related utilities for Nadja Engine.
 *
 * This module provides global timing information used by the engine,
 * including frame delta time and frames-per-second (FPS) tracking.
 *
 * The Time::update() function must be called once per frame, typically
 * at the beginning of the main loop, to update all timing values.
 *
 * Exposed values:
 * - Time::delta : Time elapsed since the previous frame, in seconds.
 * - Time::fps   : Smoothed frames-per-second value, updated periodically.
 *
 * Notes:
 * - Timing is based on SDL_GetTicks().
 * - This module is stateful and frame-dependent.
 * - No game or simulation logic should live here.
 *
 * @author Davi
 * date 2026
 */


#pragma once
#include <SDL3/SDL.h>

namespace Time {

    extern float delta;
    extern float fps;

    void update();
}
