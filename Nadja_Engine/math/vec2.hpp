#pragma once
#include <cmath>

struct Vec2 {
    float x = 0;
    float y = 0;

    // soma
    Vec2 operator+(const Vec2& other) const {
        return { x + other.x, y + other.y };
    }

    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // subtração
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

    // multiplicação por escalar
    Vec2 operator*(float scalar) const {
        return { x * scalar, y * scalar };
    }

    Vec2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // utilidades que tu já usa
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
