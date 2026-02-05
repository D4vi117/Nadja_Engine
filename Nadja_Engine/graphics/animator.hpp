#pragma once
#include <unordered_map>
#include <vector>
#include <SDL3/SDL.h>

    struct Animation {
        std::vector<int> frames; // IDs dos frames
        float frameTime;         // tempo por frame (segundos)
        bool loop;
    };

    class Animator {
    public:
        Animator(float w, float h, int c, int r);

        void addAnimation(int id, const std::vector<int>& frames, float frameTime, bool loop = true);
        void play(int id);
        void update(float dt);
        void render(SDL_Renderer* r, SDL_Texture* tex, float x, float y, float scale = 1.f);

    private:
        SDL_FRect src;
        float spriteW, spriteH;
        int cols, rows;

        std::unordered_map<int, Animation> animations;
        int currentAnim = -1;
        size_t frameIndex = 0;
        float timer = 0.f;
    };

