/*
 * @file input.hpp
 * @brief Input handling system for Nadja Engine.
 *
 * This header defines the Input namespace, which manages keyboard
 * and mouse input, action bindings, and input state tracking.
 *
 * Responsibilities:
 * - Tracking the state of actions (down, pressed, released)
 * - Handling SDL3 events and updating internal state
 * - Managing mouse position, delta movement, and button states
 * - Supporting data-driven bindings for keys and mouse buttons
 *
 * Dependencies:
 * - SDL3 (for event handling and key/button codes)
 * - STL containers (unordered_map, vector, string)
 *
 * Notes:
 * - Input state is updated per frame via update()
 * - MouseState and ActionState provide detailed input information
 * - Supports both direct queries and action-based input mapping
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>
namespace Input {

    struct ActionState {
        bool down = false;
        bool pressed = false;
        bool released = false;
    };

    struct Binding {
        enum class Type {
            KEY,
            MOUSE_BUTTON
        };

        Type type;
        Uint32 code; // SDL_Keycode or SDL_BUTTON_*
    };

    struct MouseState {
        float x;
        float y;
        float dx;
        float dy;
        bool leftDown = false;
        bool leftPressed = false;
        bool leftReleased = false;
    };


    extern MouseState mouse;

    // ===== PUBLIC API =====
    void handleEvent(const SDL_Event& e);
    void update();

    bool down(const std::string& action);
    bool pressed(const std::string& action);
    bool released(const std::string& action);

    // ===== DATA-DRIVEN =====
    void clearBindings();
    void bindKey(const std::string& action, SDL_Keycode key);
    void bindMouseButton(const std::string& action, Uint32 button);

}
