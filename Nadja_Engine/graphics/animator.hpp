/*
 * @file animator.hpp
 * @brief Sprite animation system for Nadja Engine.
 *
 * This header defines the Animator class, responsible for managing
 * frame-based animations of sprites, including playback, looping,
 * and rendering.
 *
 * Responsibilities:
 * - Defining animations as sequences of frame indices
 * - Managing frame timing and looping behavior
 * - Switching between different animations
 * - Rendering the correct frame of the animation using SDL3
 *
 * Dependencies:
 * - SDL3 (for rendering)
 * - STL containers (unordered_map, vector)
 *
 * Notes:
 * - Animations are identified by integer IDs
 * - update() must be called every frame with delta time
 * - render() requires an SDL_Texture and draws the current frame
 * - Supports scaling during rendering
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include <unordered_map>
#include <vector>
#include <SDL3/SDL.h>

    struct Animation {
        std::vector<int> frames;
        float frameTime;         
        bool loop;
    };

    class Animator {
    public:
        Animator(float w, float h, int c, int r);

        void addAnimation(int id, const std::vector<int>& frames, float frameTime, bool loop = true);
        void play(int id);
        void update(float dt);
        void render(SDL_Renderer* r, SDL_Texture* tex, float x, float y, float scale = 1.f);

		float rotation_cos = 0;
    private:
        SDL_FRect src;
        float spriteW, spriteH;
        int cols, rows;
        std::unordered_map<int, Animation> animations;
        int currentAnim = -1;
        size_t frameIndex = 0;
        float timer = 0.f;
    };

