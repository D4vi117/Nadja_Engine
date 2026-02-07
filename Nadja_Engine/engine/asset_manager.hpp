/*
 * @file assetManager.hpp
 * @brief Centralized resource manager for Nadja Engine.
 *
 * This header defines the AssetManager class, responsible for
 * loading, storing, and providing access to game assets such as
 * textures and fonts.
 *
 * Responsibilities:
 * - Initializing and shutting down asset management
 * - Loading textures and caching them for reuse
 * - Loading fonts and caching them for reuse
 * - Providing getter functions for textures and fonts
 *
 * Dependencies:
 * - SDL3 (for rendering and textures)
 * - SDL3_ttf (for font loading and management)
 * - STL containers (unordered_map, string)
 *
 * Notes:
 * - All methods are static; no instance of AssetManager is needed.
 * - Assets are stored in maps for fast lookup by string identifiers.
 * - Keep this class focused on resource management; rendering or game logic
 *   should be handled elsewhere.
 *
 * @author Davi Barbosa
 * @date 2026
 */

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
