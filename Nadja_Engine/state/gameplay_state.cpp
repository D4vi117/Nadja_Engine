#include "gameplay_state.hpp"
#include "gameplay/player.hpp"
#include "engine/sprite.hpp"
#include <SDL3/SDL.h>
#include <iostream>
#include "core/config.hpp"
#include "engine/asset_manager.hpp"
#include "engine/entity_factory.hpp"
#include "save/save_system.hpp"
#include "input/input.hpp"
#include "engine/context.hpp"

#include "gameplay/floor.hpp"

GameplayState::GameplayState(World& w, SDL_Renderer* r, StateManager& s)
    : world(w), renderer(r), states(s) {
}


GameplayState::~GameplayState() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void GameplayState::enter() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // ===== Pause Menu Initialization =====
    pauseMenu.onResume = [this]() {
        std::cout << "Resuming game from PauseState\n";
        setPaused(false);
        };

    pauseMenu.onSave = [this]() {
        SaveSystem::saveWorld(world, "saves/save1.json");
        };

    pauseMenu.onLoad = [this]() {
        loadSave("saves/save1.json");
		setPaused(false);
        };

    pauseMenu.start();



	// ===== Input Bindings =====
    Input::clearBindings();

    Input::bindKey("move_up", SDLK_W);
    Input::bindKey("move_up", SDLK_UP);

    Input::bindKey("move_down", SDLK_S);
    Input::bindKey("move_down", SDLK_DOWN);

    Input::bindKey("move_left", SDLK_A);
    Input::bindKey("move_left", SDLK_LEFT);

    Input::bindKey("move_right", SDLK_D);
    Input::bindKey("move_right", SDLK_RIGHT);

    Input::bindKey("interact", SDLK_E);
    Input::bindKey("attack", SDLK_SPACE);
    Input::bindKey("cancel", SDLK_ESCAPE);

    Input::bindMouseButton("attack", SDL_BUTTON_LEFT);


    // ===== CARREGA TEXTURA =====
    SDL_Surface* surface = SDL_LoadBMP("assets/sprites/test.bmp");
    if (!surface) {
        SDL_Log("Erro ao carregar BMP: %s", SDL_GetError());
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!texture) {
        SDL_Log("Erro ao criar textura: %s", SDL_GetError());
        return;
    }
    // ===== PLAYER =====
    // assets
    AudioManager::loadSound("interact", "assets/sounds/Ouch-6.wav");
    AudioManager::loadSound("footstep", "assets/sounds/1980s-Casio-Piano-C5.wav");
    AssetManager::loadTexture("player", "assets/sprites/player/player_IDLE.png");
    AssetManager::loadTexture("test", "assets/sprites/test.png");
    AssetManager::loadTexture("grass", "assets/sprites/sand_grass.png");
    AssetManager::loadTexture("dirt", "assets/sprites/dirt.png");
    AssetManager::loadTexture("slope", "assets/sprites/slope.png");
    if (!SaveSystem::loadWorld(world, "saves/save1.json")){
        std::cerr << "[GameplayState] Failed to load save, loading default level\n";
        world.loadLevel("level.json");
	}

    //world.loadLevel("level.json");

    world.update(0.f);

    const auto& entities = world.getEntities();

    for (const auto& e : entities) {
        if (e->name == "Player") {
            if (auto* player = dynamic_cast<Player*>(e.get())) {
                hud = std::make_unique<GameplayHUD>(player);
                break;
            }
        }
    }

}

void GameplayState::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_EVENT_KEY_DOWN &&
        e.key.key == SDLK_ESCAPE) {
		togglePause();

    }
}


void GameplayState::loadSave(const std::string& path) {
    if (!SaveSystem::loadWorld(world, path)) {
        std::cerr << "[GameplayState] Failed to load save\n";
        return;
    }

    // FORÇA SPAWN IMEDIATO
    world.update(0.f);

    hud.reset();
    const auto& entities = world.getEntities();
    for (const auto& e : entities) {
        if (e->name == "Player") {
            if (auto* player = dynamic_cast<Player*>(e.get())) {
                hud = std::make_unique<GameplayHUD>(player);
                break;
            }
        }
    }
}


void GameplayState::update(float dt) {

    if (isPaused)
    {
        pauseMenu.update();

    }
    else
    {
        world.update(dt);
        if (hud)
            hud->update(dt);
    }

}

void GameplayState::render(SDL_Renderer* r) {

    // ===== MUNDO =====
    BeginWorldRender(r);
    world.render(r);

    // ===== UI =====
    BeginUIRender(r, Engine::window);

    if (isPaused)
		pauseMenu.render(r);
    if (hud && !isPaused)
        hud->render(r);
    BeginWorldRender(r);
}