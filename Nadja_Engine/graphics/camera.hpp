/*
 * @file camera.hpp
 * @brief Camera system for Nadja Engine.
 *
 * This header defines the Camera struct, which handles the viewport
 * and following of targets within the game world.
 *
 * Responsibilities:
 * - Storing the camera's position and viewport dimensions
 * - Following a target entity or object by centering it in the viewport
 * - Providing a global camera instance for engine-wide access
 *
 * Dependencies:
 * - core/config.hpp (for logical viewport dimensions)
 *
 * Notes:
 * - g_camera is declared as an extern global instance for convenience
 *   across the engine.
 * - Camera coordinates are float-based for smooth movement and sub-pixel rendering.
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include "core/config.hpp"

struct Camera {
    float x = 0;
    float y = 0;

    float viewportW = Config::Render::LOGICAL_WIDTH;
    float viewportH = Config::Render::LOGICAL_HEIGHT;

    void follow(float targetX, float targetY, float targetW, float targetH)
    { 
        x = targetX + targetW * 0.5f - viewportW * 0.5f;
        y = targetY + targetH * 0.5f - viewportH * 0.5f;
    }

};

extern Camera g_camera;