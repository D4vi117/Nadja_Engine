#include "gameplay_state.hpp"
#include "ui/HUD/Gameplay_HUD.hpp"
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
#include "gameplay/pipe.hpp"
#include <random>

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

    // ===== Death screen Initialization =====
    deathScreen.onBegin = [this]() {
		
        playerRef->alive = true;
        
		int index = 0;
        for (auto& c : world.getEntities())
        {
            if (c->name == "Pipe")
            {

				c->x = 300 + 200 * index *1.f;
                
            }
			index++;
        }
		playerRef->y = 0;
		playerRef->physics->velocity = { 0, 0 };
        
		Points = 0;

        playerRef->collisions.clear();
        setPaused(false);
        
        };

    deathScreen.start();

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

    // ===== ASSETS =====
    AudioManager::loadSound("interact", "assets/sounds/Ouch-6.wav");
    AssetManager::loadTexture("player", "assets/sprites/player/bird_y.png");
    AssetManager::loadTexture("pipe_down", "assets/sprites/pipe_down.png");
    AssetManager::loadTexture("pipe_up", "assets/sprites/pipe_up.png");
    AssetManager::loadTexture("background", "assets/sprites/background.png");

    world.background = AssetManager::getTexture("background");
	// ===== LOAD SAVE =====
    /* Disabled SaveGame
    if (!SaveSystem::loadWorld(world, "saves/save1.json")) {
        std::cerr << "[GameplayState] Failed to load save, loading default level\n";
	}
    */
    world.loadLevel("level.json");

    world.update(0.f);

    const auto& entities = world.getEntities();

    for (auto& c : world.getEntities())
    {
        if (c->name == "Pipe")
        {
            std::random_device rd;  // Seed
            std::mt19937 gen(rd()); // Generator
            std::uniform_int_distribution<> dis(-50, 50);

            c->y = dis(gen) * 1.f;

        }

    }
    for (const auto& e : entities) {
        if (e->name == "Player") {
            if (auto* player = dynamic_cast<Player*>(e.get())) {
				playerRef = player;
                hud = std::make_unique<GameplayHUD>(player, this);
            }
        } if (e->name == "Pipe") {
            if (auto* pipe = dynamic_cast<Pipe*>(e.get())) {
                pipe->onScore = [this]() {
                    Points++;
                };
			}
        }
    }

}

void GameplayState::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_EVENT_KEY_DOWN &&
        e.key.key == SDLK_ESCAPE) {
		togglePause();
		return;
    }
    if (e.type == SDL_EVENT_KEY_DOWN &&
        e.key.key == SDLK_F11) {

		SDL_SetWindowFullscreen(Engine::window, true);
        return;

    }
    if (e.type == SDL_EVENT_KEY_DOWN &&
        e.key.key == SDLK_F5) {
        SaveSystem::saveWorld(world, "saves/save1.json");
        return;

	}
    if (e.type == SDL_EVENT_KEY_DOWN &&
        e.key.key == SDLK_F6) {
        loadSave("saves/save1.json");
		std::cout << "Load requested\n";
        return;

    }
    if (e.type == SDL_EVENT_WINDOW_RESIZED ||
        e.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {

        if (hud)
            hud->forceLayout();

        deathScreen.forceLayout();
    }
}


void GameplayState::loadSave(const std::string& path) {
    if (!SaveSystem::loadWorld(world, path)) {
        std::cerr << "[GameplayState] Failed to load save\n";
        return;
    }

    world.update(0.f);

    hud.reset();
    const auto& entities = world.getEntities();
    for (const auto& e : entities) {
        if (e->name == "Player") {
            if (auto* player = dynamic_cast<Player*>(e.get())) {
                hud = std::make_unique<GameplayHUD>(player, this);
                break;
            }
        }
    }
}


void GameplayState::update(float dt) {

    if (isPaused)
    {
        deathScreen.update();

    }
    else
    {
        world.update(dt);
        if (hud)
            hud->update(dt);
    }

}

void GameplayState::render(SDL_Renderer* r) {

    // ===== WORLD =====

    BeginWorldRender(r);
    world.render(r);

    // ===== UI =====
    BeginUIRender(r, Engine::window);

    if (isPaused)
		deathScreen.render(r);
    if (hud && !isPaused)
        hud->render(r);
    BeginWorldRender(r);
}