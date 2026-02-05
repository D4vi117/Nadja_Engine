#include "sat.hpp"
#include <algorithm>
#include <cmath>

struct Projection {
    float min;
    float max;
};

static Projection project(const std::vector<Vec2>& pts, const Vec2& axis) {
    float min = pts[0].dot(axis);
    float max = min;

    for (const auto& p : pts) {
        float d = p.dot(axis);
        if (d < min) min = d;
        if (d > max) max = d;
    }
    return { min, max };
}

static float overlap(const Projection& a, const Projection& b) {
    return std::min(a.max, b.max) - std::max(a.min, b.min);
}

static std::vector<Vec2> getAxes(const std::vector<Vec2>& pts) {
    std::vector<Vec2> axes;
    for (size_t i = 0; i < pts.size(); i++) {
        Vec2 p1 = pts[i];
        Vec2 p2 = pts[(i + 1) % pts.size()];
        Vec2 edge = p2 - p1;
        axes.push_back(edge.perpendicular().normalized());
    }
    return axes;
}

SATResult SAT(const std::vector<Vec2>& A, const std::vector<Vec2>& B) {
    SATResult res;
    res.depth = INFINITY;

    auto axesA = getAxes(A);
    auto axesB = getAxes(B);

    for (auto& axis : axesA) {
        auto pA = project(A, axis);
        auto pB = project(B, axis);
        float o = overlap(pA, pB);
        if (o <= 0) return {};
        if (o < res.depth) {
            res.depth = o;
            res.normal = axis;
        }
    }

    for (auto& axis : axesB) {
        auto pA = project(A, axis);
        auto pB = project(B, axis);
        float o = overlap(pA, pB);
        if (o <= 0) return {};
        if (o < res.depth) {
            res.depth = o;
            res.normal = axis;
        }
    }

    res.hit = true;
    return res;
}
