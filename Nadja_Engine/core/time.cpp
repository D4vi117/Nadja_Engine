#include "time.hpp"


namespace Time {

    float delta = 0.0f;
    float fps = 0.0f;

    static Uint64 last_ticks = 0;
    static float fps_timer = 0.0f;
    static int fps_frames = 0;

    void update() {
        Uint64 now = SDL_GetTicks();

        if (last_ticks == 0) {
            delta = 0.0f;
        }
        else {
            delta = (now - last_ticks) / 1000.0f;
        }

        last_ticks = now;

        fps_timer += delta;
        fps_frames++;

        if (fps_timer >= 1.0f) {
            fps = fps_frames / fps_timer;
            fps_frames = 0;
            fps_timer = 0.0f;
        }
    }
}
