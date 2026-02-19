#include "pipe.hpp"
#include "graphics/camera.hpp"
#include "engine/asset_manager.hpp"
#include <random>

Pipe::Pipe(SDL_Texture* top, SDL_Texture* bottom, float w, float h)

{
	bodyType = BodyType::DYNAMIC;
	t_top = AssetManager::getTexture("pipe_down");
    t_bottom = AssetManager::getTexture("pipe_up");

}

void Pipe::update(float delta)
{
    
	move(-100.f * delta, 0.f);
    if (x <= -20 && !scored){
		scored = true;
        if (onScore)
            onScore();
    }
    else if (x + w - 50 < g_camera.x){
		scored = false;
        std::random_device rd;  // Seed
        std::mt19937 gen(rd()); // Generator
        std::uniform_int_distribution<> dis(-50, 50);
		
        x = 500;
        y = dis(gen) * 1.0f;
    }
}
void Pipe::move(float dx, float dy)
{
    x += dx;
    y += dy;
}

std::vector<Collider> Pipe::getColliders() const
{
    std::vector<Collider> cols;

    // bottom pipe
    Collider bottom;
    bottom.shape = ShapeType::AABB;
    bottom.type = ColliderType::BLOCK;
    bottom.rect = { x, y, w, h };
    cols.push_back(bottom);

    // top pipe
    Collider top;
    top.shape = ShapeType::AABB;
    top.type = ColliderType::BLOCK;
    top.rect = { x, y - h - gap, w, h };
    cols.push_back(top);

    return cols;
}

void Pipe::render(SDL_Renderer* r)
{
    SDL_FRect bottom;
    bottom.x = x - g_camera.x;
    bottom.y = y - g_camera.y;
    bottom.w = w;
    bottom.h = h;

    SDL_FRect top;
    top.x = x - g_camera.x;
    top.y = y - g_camera.y - h - gap;
    top.w = w;
    top.h = h;

    SDL_RenderTexture(r, t_top, nullptr, &bottom);
    SDL_RenderTexture(r, t_bottom, nullptr, &top);

}

