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