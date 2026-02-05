#include "asset_manager.hpp"
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>
// ================= INIT =================
bool AssetManager::init(SDL_Renderer* renderer) {
    s_renderer = renderer;
    return s_renderer != nullptr;
}

// ================= SHUTDOWN =================
void AssetManager::shutdown() {
    for (auto& [id, tex] : s_textures) {
        SDL_DestroyTexture(tex);
    }
    s_textures.clear();

    for (auto& [id, font] : s_fonts) {
        TTF_CloseFont(font);
    }
    s_fonts.clear();

    s_renderer = nullptr;
}

// ================= TEXTURES =================
bool AssetManager::loadTexture(const std::string& id, const std::string& path) {
    if (s_textures.find(id) != s_textures.end())
        return true;

    SDL_Surface* surface = SDL_LoadPNG(path.c_str());
    if (!surface) {
        SDL_Log("Failed to load PNG %s: %s", path.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(s_renderer, surface);
    SDL_DestroySurface(surface);

    if (!tex) {
        SDL_Log("Failed to create texture %s: %s", id.c_str(), SDL_GetError());
        return false;
    }
    s_textures[id] = tex;
    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
    return true;
}

SDL_Texture* AssetManager::getTexture(const std::string& id) {
    auto it = s_textures.find(id);
    if (it == s_textures.end()) {
        SDL_Log("Texture not found: %s", id.c_str());
        return nullptr;
    }
    return it->second;
}

// ================= FONTS =================
bool AssetManager::loadFont(const std::string& id, const std::string& path, float size) {
    if (s_fonts.find(id) != s_fonts.end())
        return true;

    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        SDL_Log("Failed to load font %s: %s", path.c_str(), SDL_GetError());
        return false;
    }

    s_fonts[id] = font;
    return true;
}

TTF_Font* AssetManager::getFont(const std::string& id) {
    auto it = s_fonts.find(id);
    if (it == s_fonts.end()) {
        SDL_Log("Font not found: %s", id.c_str());
        return nullptr;
    }
    return it->second;
}
