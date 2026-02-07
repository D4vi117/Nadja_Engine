#include "physics.hpp"
#include "engine/entity.hpp"
#include "physics/sat.hpp"
#include <algorithm>
#include <cmath>

constexpr float GROUND_EPSILON = 1.5f;

static bool intersect(const SDL_FRect& a, const SDL_FRect& b) {
    return SDL_HasRectIntersectionFloat(&a, &b);
}

std::vector<Vec2> getWorldPoints(const Entity* e, const Collider& c) {
    std::vector<Vec2> out;
    float cosr = std::cos(e->rotation_rad);
    float sinr = std::sin(e->rotation_rad);

    for (auto& p : c.points) {
        Vec2 r;
        r.x = p.x * cosr - p.y * sinr;
        r.y = p.x * sinr + p.y * cosr;
        out.push_back({ r.x + e->x, r.y + e->y });
    }
    return out;
}

void Physics::solve(const std::vector<std::unique_ptr<Entity>>& entities) {

    for (auto& e : entities) {
        e->clearCollisions();

    }
    for (size_t i = 0; i < entities.size(); i++) {
        for (size_t j = i + 1; j < entities.size(); j++) {

            Entity* a = entities[i].get();
            Entity* b = entities[j].get();

            auto colsA = a->getColliders();
            auto colsB = b->getColliders();

            for (auto& ca : colsA) {
                for (auto& cb : colsB) {

                    bool hit = false;
                    Vec2 normal;
                    float depth = 0;

                    // AABB vs AABB
                    if (ca.shape == ShapeType::AABB &&
                        cb.shape == ShapeType::AABB) {

                        if (!intersect(ca.rect, cb.rect))
                            continue;

                        hit = true;
                        float dx = (ca.rect.x + ca.rect.w * 0.5f) -
                            (cb.rect.x + cb.rect.w * 0.5f);
                        float dy = (ca.rect.y + ca.rect.h * 0.5f) -
                            (cb.rect.y + cb.rect.h * 0.5f);

                        float px = (ca.rect.w + cb.rect.w) * 0.5f - std::abs(dx);
                        float py = (ca.rect.h + cb.rect.h) * 0.5f - std::abs(dy);

                        if (px < py) {
                            normal = { dx < 0 ? -1.f : 1.f, 0 };
                            depth = px;
                        }
                        else {
                            normal = { 0, dy < 0 ? -1.f : 1.f };
                            depth = py;
                        }

                    }
                    else {
                        auto A = (ca.shape == ShapeType::AABB)
                            ? std::vector<Vec2>{
                                {ca.rect.x, ca.rect.y},
                                { ca.rect.x + ca.rect.w, ca.rect.y },
                                { ca.rect.x + ca.rect.w, ca.rect.y + ca.rect.h },
                                { ca.rect.x, ca.rect.y + ca.rect.h }
                        }
                        : getWorldPoints(a, ca);

                        auto B = (cb.shape == ShapeType::AABB)
                            ? std::vector<Vec2>{
                                {cb.rect.x, cb.rect.y},
                                { cb.rect.x + cb.rect.w, cb.rect.y },
                                { cb.rect.x + cb.rect.w, cb.rect.y + cb.rect.h },
                                { cb.rect.x, cb.rect.y + cb.rect.h }
                        }
                        : getWorldPoints(b, cb);

                        auto sat = SAT(A, B);
                        if (!sat.hit) continue;

                        hit = true;
                        normal = sat.normal;
                        depth = sat.depth;
                    }

                    if (!hit) continue;

                    a->collisions.push_back({ b, ca.type,  normal, depth });
                    b->collisions.push_back({ a, cb.type, -normal, depth });

                    if (ca.type == ColliderType::OVERLAP ||
                        cb.type == ColliderType::OVERLAP)
                        continue;

                    if (a->bodyType == BodyType::DYNAMIC) {
                        Vec2 mtv = normal * depth;
                        a->move(-mtv.x, -mtv.y);
                        if (normal.y > 0.5f && a->physics->velocity.y > 0) {
                            a->physics->velocity.y = 0;
                        }
                    }
                    if (a->bodyType == BodyType::DYNAMIC &&
                        b->bodyType == BodyType::DYNAMIC) {

                        Vec2 mtv = normal * (depth * 0.5f);
                        a->move(-mtv.x, -mtv.y);
                        b->move(mtv.x, mtv.y);
                    }
                    else if (a->bodyType == BodyType::DYNAMIC) {
                        Vec2 mtv = normal * depth;
                        a->move(-mtv.x, -mtv.y);
                    }
                    else if (b->bodyType == BodyType::DYNAMIC) {
                        Vec2 mtv = normal * depth;
                        b->move(mtv.x, mtv.y);
                    }
                }
            }
        }
    }
}
