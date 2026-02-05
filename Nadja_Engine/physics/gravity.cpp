#include "gravity.hpp"

static constexpr float GRAVITY = 250.f; // pixels/s² (ajusta no feeling)

void Physics::applyGravity(
    const std::vector<std::unique_ptr<Entity>>& entities,
    float delta
) {
    for (auto& e : entities) {
        if (!e->physics.has_value()) continue;
        if (e->bodyType != BodyType::DYNAMIC) continue;

        auto& body = e->physics.value();

        if (body.useGravity && !body.grounded) {
            body.acceleration.y = GRAVITY * body.gravityScale;
        }
        else {
            body.acceleration.y = 0;
        }

        // integração básica (oldschool e funciona)
        body.velocity += body.acceleration * delta;

        e->move(
            body.velocity.x * delta,
            body.velocity.y * delta
        );
    }
}
