#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

class AssetManager {
public:
    // ===== INIT / SHUTDOWN =====
    static bool init(SDL_Renderer* renderer);
    static void shutdown();

    // ===== TEXTURES =====
    static SDL_Texture* getTexture(const std::string& id);
    static bool loadTexture(const std::string& id, const std::string& path);

    // ===== FONTS =====
    static TTF_Font* getFont(const std::string& id);
    static bool loadFont(const std::string& id, const std::string& path, float size);

private:
    static inline SDL_Renderer* s_renderer = nullptr;

    static inline std::unordered_map<std::string, SDL_Texture*> s_textures;
    static inline std::unordered_map<std::string, TTF_Font*> s_fonts;
};
