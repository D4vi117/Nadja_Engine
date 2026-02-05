/*
 * Engine compile-time configuration.
 *
 * Contains constants that define core engine behavior and are not meant
 * to be modified at runtime.
 * 
 * @author Davi
 * @date 2026
 */

#pragma once

namespace Config {
    namespace Render {
        constexpr int LOGICAL_WIDTH = 640;
        constexpr int LOGICAL_HEIGHT = 360;
        constexpr int TARGET_FPS = 60;
    }
    namespace Debug {
        constexpr bool SHOW_FPS = false;
        constexpr bool COLLISION = false;
        constexpr bool HUD_DUMP = false;
        constexpr bool HUD_VISUAL = false;

    }
}
