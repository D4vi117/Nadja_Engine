# Nadja Engine

Nadja Engine is a **2D game engine written in C++**, built from scratch on top of **SDL3**.  
It focuses on explicit systems, clean architecture, and full control over the game loop, rendering, and simulation.

This is an engine in the traditional sense: minimal magic, no editor dependency, and no hidden behavior.  
Everything is code, and everything is intentional.

---

# Trailer
[![Watch the demo](https://img.youtube.com/vi/aUU6aMnkapA/0.jpg)](https://youtu.be/aUU6aMnkapA)
---
## Features

- **State-based architecture**
  - Stack-based state management (menus, gameplay, pause, etc.)
  - Clear lifecycle: enter, exit, pause, resume
  - Centralized orchestration via `StateManager`

- **World and Entity system**
  - `World` owns and updates all entities
  - Deferred entity creation and destruction for safe iteration
  - Clear inheritance chain: `Entity → Sprite → Actor → Player`
  - Separation between simulation, rendering, and gameplay logic

- **2D Physics System**
  - Per-entity `PhysicsBody` with velocity, acceleration, gravity, and grounded state
  - Static, kinematic, and dynamic body types
  - AABB and convex polygon colliders
  - Collision detection using **Separating Axis Theorem (SAT)**
  - Dedicated physics solver for collision resolution

- **Pixel-perfect rendering**
  - Fixed logical resolution
  - Nearest-neighbor scaling
  - Clear separation between world rendering and UI rendering

- **Camera system**
  - Global camera with float-based coordinates
  - Target-following support for smooth movement

- **Sprite animation system**
  - Frame-based animations via `Animator`
  - Time-based updates with looping support
  - Dynamic animation switching

- **Input system**
  - Action-based input mapping
  - Keyboard and mouse support
  - Per-frame input state tracking (pressed / released / held)

- **Audio system**
  - Centralized `AudioManager`
  - Audio playback via **miniaudio**
  - Sound caching and per-sound volume control
  - Planned migration to SDL_mixer

- **Asset management**
  - Centralized texture and font loading
  - Asset caching for reuse
  - SDL3 and SDL3_ttf integration

- **Save and load system**
  - World-level persistence
  - JSON-based serialization
  - Actors and player state support save/load

- **Custom UI system**
  - Immediate-mode–inspired retained UI
  - Panels, containers, and layout helpers
  - Buttons, text, and images
  - Gameplay HUD and pause menu implemented using the same UI layer

---

## Engine Flow

1. **Application startup**
   - SDL subsystems are initialized
   - Core systems are created (window, renderer, input, time)

2. **Main loop**
   - SDL events are processed
   - Input and time systems are updated
   - The active game state is updated and rendered

3. **State management**
   - `StateManager` forwards events, update, and render calls
   - States can be pushed and popped dynamically

4. **Gameplay**
   - `GameplayState` owns the `World`
   - The world updates entities, physics, and collisions
   - Rendering is split between world space and UI space

---

## Design Philosophy

- No game logic in `main`
- No hidden side effects
- No engine-wide god objects
- Explicit ownership using `std::unique_ptr`
- Systems are decoupled and purpose-driven
- Engine code stays engine code; gameplay lives elsewhere

The goal is clarity, control, and long-term maintainability.

---

## Build Requirements

- C++17 or later
- SDL3
- SDL3_ttf
- miniaudio
- nlohmann/json

---

## Project Status

- Core systems implemented and stable
- Physics and collision system functional
- State management complete
- UI system in active use
- Audio system functional, pending future refactor
- Ongoing refinements and feature expansion

---

## License

This project is licensed under the MIT License.  
See the LICENSE file for details.

---

## Author

**Davi Barbosa**  
2026
