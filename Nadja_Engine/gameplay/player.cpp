#include "player.hpp"
#include "input/input.hpp"
#include "engine/world.hpp"
#include <iostream>
static float maxSpeed = 200.f;



Player::Player(SDL_Texture* texture)
    : Actor(texture, 16, 32), animator(16, 32, 4, 4)
{
    bodyType = BodyType::DYNAMIC;
}
void Player::start() {
    bodyType = BodyType::DYNAMIC;
    name = "Player";


    physics.emplace();
    physics->useGravity = true;
    physics->gravityScale = 1.0f;
    physics->velocity = { 0, 0 };

    animator.addAnimation(
        IDLE,
        { 0,0,0,0,0,0,0,0,0,0,0,0, 1, 2, 3 },
        0.2f
    );

    animator.addAnimation(
        WALK,
        { 2, 2, 2, 2 },
        0.1f
    );

    animator.play(IDLE);

}



void Player::update(float delta) {

    float dx = 0;
    float dy = 0;

    if (!physics) return;

    if (!physics->useGravity)
		physics->velocity.y = 0;

    bool onGround = false;

    for (auto& c : collisions) {
        if (c.type == ColliderType::BLOCK &&
            c.normal.y > 0.5f &&
            physics->velocity.y >= 0) {
            onGround = true;
            break;
        }
    }

    if (onGround) {
        physics->grounded = true;
        physics->groundTimer = 0.1f;
    }
    else if (physics->groundTimer > 0) {
        physics->groundTimer -= delta;
        physics->grounded = true;
    }
    else {
        physics->grounded = false;
    }

    auto& body = physics.value();


    body.velocity.x = 0;

    if (Input::down("move_left"))
        body.velocity.x = -maxSpeed;
    if (Input::down("move_right"))
        body.velocity.x = maxSpeed;

    if (Input::down("move_up")) {
        if (!physics->useGravity)
		    body.velocity.y = -maxSpeed;
    }
    if (Input::down("move_down"))
    {
        if (!physics->useGravity) 
			body.velocity.y = maxSpeed;

    }
    if (Input::pressed("move_up")) {
        if (physics->useGravity){
            if (body.grounded){
                body.velocity.y = -150.0f;
            }
        }
    }

    if (Input::pressed("interact")) {
        for (auto& c : collisions) {
            if (c.type == ColliderType::OVERLAP) {
                c.other->interact(this);
				
                AudioManager::playSound("interact");
                
				health -= 10;
                
                break;
            }
        }
    }

    animator.play(IDLE);

    animator.update(delta);

	g_camera.follow(x, y, w, h);
}


void Player::render(SDL_Renderer * r)
{
    float rx = x - g_camera.x;
    float ry = y - g_camera.y;

    animator.render(r, texture, rx, ry, 1);
}
void Player::serializeState(nlohmann::json& out) const {
    out["Health"]["current"] = health;
}

void Player::deserializeState(const nlohmann::json& in) {
    if (in.contains("Health"))
        health = in["Health"].value("current", health);
}