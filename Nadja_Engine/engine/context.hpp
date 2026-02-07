/*
 * @file context.hpp
 * @brief Global engine context for Nadja Engine.
 *
 * This header provides global access to core SDL3 objects such as
 * the main window and renderer. It allows different systems and
 * modules to reference the central rendering context.
 *
 * Responsibilities:
 * - Declaring global SDL_Window* and SDL_Renderer* pointers
 * - Ensuring a single point of access to the engine's main SDL context
 *
 * Dependencies:
 * - SDL3 (for window and renderer types)
 * - core/config.hpp for engine configuration
 *
 * Notes:
 * - This file only declares extern pointers; actual initialization
 *   occurs elsewhere in the engine startup code.
 * - Use these globals cautiously to avoid tight coupling between systems.
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include <SDL3/SDL.h>
#include "core/config.hpp"

namespace Engine {

    extern SDL_Window* window;
    extern SDL_Renderer* renderer;

}
