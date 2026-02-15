#include "sprite.hpp"
#include "graphics/camera.hpp"
#include <iostream>
#include "math/vec2.hpp"
#include "core/config.hpp"
extern Camera g_camera;

Sprite::Sprite(SDL_Texture* tex, float width, float height) {
    texture = tex;
    w = width;
    h = height;
}

Sprite::~Sprite() {}

void Sprite::render(SDL_Renderer* renderer) {
    SDL_FRect dst;
    dst.x = x - g_camera.x;
    dst.y = y - g_camera.y;
    dst.w = w;
    dst.h = h;

    SDL_RenderTexture(renderer, texture, nullptr, &dst);
}

void Sprite::move(float dx, float dy) {
    x += dx;
    y += dy;
}

std::vector<Collider> Sprite::getColliders() const {
    std::vector<Collider> cols;

    // ===============================
    // OVERLAP — Body-Overlap inteiro (AABB)
    // ===============================
    Collider overlap;
    overlap.shape = ShapeType::AABB;
    overlap.type = ColliderType::OVERLAP;
    overlap.rect = { x, y, w, h };
    cols.push_back(overlap);

    // ===============================
    // BLOCK — Foot (SAT / POLYGON)
    // ===============================
    Collider foot;
    foot.shape = ShapeType::POLYGON;
    foot.type = ColliderType::BLOCK;

    float footHeight = 4.0f;

    // pontos locais (origem = Entity)
    foot.points = {
        { 0, h - footHeight},
        { w -1, h  - footHeight },
        { w -1, h - 1},
        { 0, h -1}
    };

    cols.push_back(foot);

    return cols;
}

const void Sprite::debug_collider(SDL_Renderer* r) {
    if (!Config::Debug::COLLISION)
		return;
    for (auto& c : getColliders()) {

        if (c.type == ColliderType::BLOCK)
            SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
        else
            SDL_SetRenderDrawColor(r, 0, 255, 0, 0);

        if (c.shape == ShapeType::AABB) {
            SDL_FRect rect = c.rect;
            rect.x -= g_camera.x;
            rect.y -= g_camera.y;
            SDL_RenderRect(r, &rect);
        }
        else {
            float cosr = std::cos(rotation_rad);
            float sinr = std::sin(rotation_rad);

            for (size_t i = 0; i < c.points.size(); i++) {
                Vec2 p1 = c.points[i];
                Vec2 p2 = c.points[(i + 1) % c.points.size()];

                Vec2 w1{
                    p1.x * cosr - p1.y * sinr + x - g_camera.x,
                    p1.x * sinr + p1.y * cosr + y - g_camera.y
                };

                Vec2 w2{
                    p2.x * cosr - p2.y * sinr + x - g_camera.x,
                    p2.x * sinr + p2.y * cosr + y - g_camera.y
                };

                SDL_RenderLine(r, w1.x, w1.y, w2.x, w2.y);
            }
        }
    }
}

void Sprite::interact(Entity* other) {
    std::cout << "interact " << name << "\n";
}
