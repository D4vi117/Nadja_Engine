#include "input.hpp"
#include "engine/context.hpp"
namespace Input {

    MouseState mouse;
    
    static std::unordered_map<std::string, ActionState> actions;
    static std::unordered_map<std::string, std::vector<Binding>> bindings;

    // =========================
    // INTERNAL HELPERS
    // =========================

    static void updateAction(ActionState& a, bool isDown) {
        if (isDown && !a.down)
            a.pressed = true;

        if (!isDown && a.down)
            a.released = true;

        a.down = isDown;
    }

    // =========================
    // PUBLIC API
    // =========================

    void clearBindings() {
        bindings.clear();
        actions.clear();
    }

    void bindKey(const std::string& action, SDL_Keycode key) {
        bindings[action].push_back(Binding{ Binding::Type::KEY, key });
        actions[action]; // garante que exista
    }

    void bindMouseButton(const std::string& action, Uint32 button) {
        bindings[action].push_back(Binding{ Binding::Type::MOUSE_BUTTON, button });
        actions[action];
    }

    void handleEvent(const SDL_Event& e) {


        // ===== MOUSE MOVE =====
        if (e.type == SDL_EVENT_MOUSE_MOTION) {
            mouse.dx = e.motion.xrel;
            mouse.dy = e.motion.yrel;
            mouse.x = e.motion.x;
            mouse.y = e.motion.y;
            return;
        }

        // ===== MOUSE BUTTON =====
        if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN ||
            e.type == SDL_EVENT_MOUSE_BUTTON_UP) {

            bool isDown = (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN);

            if (e.button.button == SDL_BUTTON_LEFT) {
                if (isDown && !mouse.leftDown)
                    mouse.leftPressed = true;

                if (!isDown && mouse.leftDown)
                    mouse.leftReleased = true;

                mouse.leftDown = isDown;
            }
        }
        
		// ===== KEYBOARD / MOUSE BUTTON =====
        bool isDownEvent =
            e.type == SDL_EVENT_KEY_DOWN ||
            e.type == SDL_EVENT_MOUSE_BUTTON_DOWN;

        bool isUpEvent =
            e.type == SDL_EVENT_KEY_UP ||
            e.type == SDL_EVENT_MOUSE_BUTTON_UP;

        if (!isDownEvent && !isUpEvent)
            return;

        for (auto& [actionName, binds] : bindings) {
            for (auto& b : binds) {

                if (b.type == Binding::Type::KEY &&
                    (e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_KEY_UP)) {

                    if (e.key.key == b.code) {
                        updateAction(actions[actionName], isDownEvent);
                    }
                }

                if (b.type == Binding::Type::MOUSE_BUTTON &&
                    (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN || e.type == SDL_EVENT_MOUSE_BUTTON_UP)) {

                    if (e.button.button == b.code) {
                        updateAction(actions[actionName], isDownEvent);
                    }
                }
            }
        }
    }

    void update() {
        mouse.leftPressed = false;
        mouse.leftReleased = false;

        for (auto& [_, a] : actions) {
            a.pressed = false;
            a.released = false;
        }
    }

    // =========================
    // QUERY
    // =========================

    bool down(const std::string& action) {
        return actions[action].down;
    }

    bool pressed(const std::string& action) {
        return actions[action].pressed;
    }

    bool released(const std::string& action) {
        return actions[action].released;
    }

}
