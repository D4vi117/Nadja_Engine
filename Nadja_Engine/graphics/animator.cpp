#include "animator.hpp"

Animator::Animator(float w, float h, int c, int r)
    : spriteW(w), spriteH(h), cols(c), rows(r) {
    src = { 0, 0, w, h };
}

void Animator::addAnimation(
    int id,
    const std::vector<int>& frames,
    float frameTime,
    bool loop
) {
    animations[id] = { frames, frameTime, loop };
}

void Animator::play(int id) {
    if (currentAnim == id) return;

    currentAnim = id;
    frameIndex = 0;
    timer = 0.0f;
}

void Animator::update(float dt) {
    if (currentAnim == -1) return;

    auto& anim = animations[currentAnim];
    timer += dt;

    if (timer >= anim.frameTime) {
        timer = 0.0f;
        frameIndex++;

        if (frameIndex >= anim.frames.size()) {
            if (anim.loop)
                frameIndex = 0;
            else
                frameIndex = anim.frames.size() - 1;
        }
    }

    int frameID = anim.frames[frameIndex];

    int fx = frameID % cols;
    int fy = frameID / cols;

    src.x = fx * spriteW;
    src.y = fy * spriteH;
}

void Animator::render(SDL_Renderer* r, SDL_Texture* tex, float x, float y, float scale) {
    SDL_FRect dst{
        x,
        y,
        spriteW * scale,
        spriteH * scale
    };
	SDL_RenderTextureRotated(r, tex, &src, &dst, rotation_cos, nullptr, SDL_FLIP_NONE);
   //SDL_RenderTexture(r, tex, &src, &dst);
}
