/*
 * @file config.hpp
 * @brief Engine configuration constants for Nadja Engine.
 *
 * This header defines compile-time constants for engine settings,
 * including rendering and debug options.
 *
 * Responsibilities:
 * - Providing logical screen resolution and target FPS
 * - Enabling or disabling debug features (FPS display, collision, HUD)
 * - Centralizing configuration for easy adjustment
 *
 * Dependencies:
 * - None (pure compile-time constants)
 *
 * Notes:
 * - All values are constexpr and should not change at runtime
 * - Use the Config namespace to access these settings across the engine
 *
 * @author Davi Barbosa
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
