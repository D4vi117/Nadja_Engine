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
        Uint32 code; // SDL_Keycode ou SDL_BUTTON_*
    };

	// Mouse state
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

    // ===== API PÚBLICA =====
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
