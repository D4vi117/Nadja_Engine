/*
 * @file Vec2.hpp
 * @brief 2D vector math structure for Nadja Engine.
 *
 * This header defines the Vec2 struct, representing a 2-dimensional
 * vector with common vector operations for game development.
 *
 * Responsibilities:
 * - Storing 2D coordinates (x, y)
 * - Supporting basic arithmetic operations (+, -, *, +=, -=, *=)
 * - Providing vector utility functions such as dot product, normalization,
 *   and perpendicular vector calculation
 *
 * Dependencies:
 * - <cmath> for square root calculations
 *
 * Notes:
 * - All operations are float-based for smooth movement and physics calculations
 * - Designed for use in physics, movement, and collision systems
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include <cmath>

struct Vec2 {
    float x = 0;
    float y = 0;


    Vec2 operator+(const Vec2& other) const {
        return { x + other.x, y + other.y };
    }

    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }


    Vec2 operator-(const Vec2& other) const {
        return { x - other.x, y - other.y };
    }
    Vec2 operator-() const {
        return { -x, -y };
    }
    Vec2& operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }


    Vec2 operator*(float scalar) const {
        return { x * scalar, y * scalar };
    }

    Vec2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }


    float dot(const Vec2& o) const {
        return x * o.x + y * o.y;
    }

    Vec2 perpendicular() const {
        return { -y, x };
    }

    Vec2 normalized() const {
        float len = std::sqrt(x * x + y * y);
        if (len == 0) return { 0,0 };
        return { x / len, y / len };
    }


};
