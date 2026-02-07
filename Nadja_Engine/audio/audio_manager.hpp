/*
 * @file AudioManager.hpp
 * @brief Audio management system for Nadja Engine.
 *
 * This header defines the AudioManager class, responsible for loading,
 * playing, and managing sound assets within the engine.
 *
 * Current Implementation:
 * - Uses miniaudio library for audio playback and management.
 *
 * Planned Change:
 * - The system is intended to migrate to SDL_mixer in the future
 *   for better SDL integration and more robust audio features.
 *
 * Responsibilities:
 * - Initializing the audio engine
 * - Loading sound files and caching them
 * - Playing sounds with optional looping
 * - Adjusting volume per sound
 * - Cleaning up all audio resources on shutdown
 *
 * Dependencies:
 * - miniaudio
 * - STL containers (unordered_map, string, memory)
 *
 * Notes:
 * - This is a static manager class; all methods are class-level.
 * - Keep this header focused on interface; implementation details
 *   reside in the corresponding .cpp file.
 *
 * @author Davi Barbosa
 * @date 2026
 */

#pragma once
#include "miniaudio.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <memory>
class AudioManager {
public:
    static void init() {
        if (ma_engine_init(nullptr, &engine) != MA_SUCCESS) {
            std::cerr << "Failed to initialize audio engine\n";
        }
    }



    static bool loadSound(const std::string& id, const std::string& path) {

        if (sounds.find(id) != sounds.end()) {
            return true;
        }

        auto sound = std::make_unique<ma_sound>();

        if (ma_sound_init_from_file(
            &engine,
            path.c_str(),
            0,
            nullptr,
            nullptr,
            sound.get()
        ) != MA_SUCCESS) {
            std::cerr << "Failed to load sound: " << path << "\n";
            return false;
        }

        sounds[id] = std::move(sound);
        return true;
    }





    static void playSound(const std::string& id, bool loop = false) {
        auto it = sounds.find(id);
        if (it != sounds.end()) {
            ma_sound_set_looping(it->second.get(), loop);
            ma_sound_start(it->second.get());
        }
    }
    static void shutdown() {
        for (auto& [id, sound] : sounds) {
            ma_sound_uninit(sound.get());
        }
        sounds.clear();
        ma_engine_uninit(&engine);
    }

    static void setVolume(const std::string& id, float volume) {
        auto it = sounds.find(id);
        if (it != sounds.end()) {
            ma_sound_set_volume(it->second.get(), volume);

        }
    }

private:
    static inline ma_engine engine;

    static inline std::unordered_map<std::string, std::unique_ptr<ma_sound>> sounds;
};
