#include "player.hpp"
#include "input/input.hpp"
#include "engine/world.hpp"
#include <iostream>
static float maxSpeed = 200.f;



Player::Player(SDL_Texture* texture)
    : Actor(texture, 17, 12), animator(17, 12, 3, 1)
{
    bodyType = BodyType::DYNAMIC;
 
}
void Player::start() {
    bodyType = BodyType::DYNAMIC;
    name = "Player";


    physics.emplace();
    physics->useGravity = true;
    physics->gravityScale = 2.5f;
    physics->velocity = { 0, 0 };

    animator.addAnimation(
        IDLE,
        {0, 1, 2 },
        0.2f
    );


    animator.play(IDLE);

}

void Player::update(float delta) {

    float dx = 0;
    float dy = 0;

    if (!physics) return;

    if (!physics->useGravity)
		physics->velocity.y = 0;

    auto& body = physics.value();


    if (Input::pressed("move_up")) {
        if (physics->useGravity){
                body.velocity.y = -250.0f;
        }
    }
    float maxTilt = 45.f;
    float normalized = body.velocity.y / 300.f;

    if (normalized > 1.f) normalized = 1.f;
    if (normalized < -1.f) normalized = -1.f;

    float targetRotation = normalized * maxTilt;

    animator.rotation_cos +=
        (targetRotation - animator.rotation_cos) * 8.f * delta;

    animator.play(IDLE);

    animator.update(delta);

	g_camera.follow(x + 150, 0, w, h);
    for (auto& c : collisions)
    {   
        if (c.other->name == "Pipe")
        {
            body.velocity.y = 0.0f;
            alive = false;
        }
    }
}

void Player::render(SDL_Renderer * r)
{

    float rx = x - g_camera.x;
    float ry = y - g_camera.y;

    animator.render(r, texture, rx, ry, 1);
    
}

std::vector<Collider> Player::getColliders() const
{
    std::vector<Collider> cols;

    Collider body;
    body.shape = ShapeType::AABB;
    body.type = ColliderType::OVERLAP;
    body.rect = { x, y, w, h };
    cols.push_back(body);

    cols.push_back(body);

    return cols;
}
