#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <SDL3/SDL_render.h >
#include "engine/asset_manager.hpp"
#include "math/vec2.hpp"
#include "core/config.hpp"

namespace UI {


    static void drawRect(SDL_Renderer* r, float x, float y, float w, float h, SDL_Color c) {
        SDL_FRect fr{ x, y, w, h };
        SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
        SDL_RenderRect(r, &fr);
    }

    static void drawCross(SDL_Renderer* r, float x, float y, float size = 4.f) {
        SDL_RenderLine(r, x - size, y, x + size, y);
        SDL_RenderLine(r, x, y - size, x, y + size);
    }

    struct Rect { float x = 0, y = 0, w = 0, h = 0; };

    struct Padding {
        float l = 0, r = 0, t = 0, b = 0;
    };

    enum class Align {
        Start,
        Center,
        End,
        Stretch
    };
    enum class Justify {
        Start,
        Center,
        End,
        SpaceBetween,
        SpaceAround,
        SpaceEvenly
    };
    class Element {
    public:
        virtual ~Element() = default;

        virtual void layout() {}
        virtual void update() {}
        virtual void render(SDL_Renderer*) = 0;

        

        Vec2 anchor{ 0.5f, 0.5f };
        Vec2 offset{ 0, 0 };
        Rect rect{ 0, 0, 0, 0 };
        Padding padding{};
        bool visible = true;
        bool enabled = true;

        Element* parent = nullptr;

        float globalX() const;
        float globalY() const;
        virtual void debugRender(SDL_Renderer* r) {
            if (!Config::Debug::HUD_VISUAL) return;

            float gx = globalX();
            float gy = globalY();

            // bounding box
            UI::drawRect(r, gx, gy, rect.w, rect.h, { 255, 0, 0, 180 });

            // anchor point
            float ax = gx + rect.w * anchor.x;
            float ay = gy + rect.h * anchor.y;

            SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
            UI::drawCross(r, ax, ay);
        }
    };

    // ================= FONT =================
    struct Font {
        static inline std::string defaultFontId;

        static bool init(const std::string& id) {
            defaultFontId = id;
            return true;
        }

    };

    // ================= CONTAINER =================
    class Container : public Element {
    public:
        std::vector<std::unique_ptr<Element>> children;

        template<typename T>
        T* add(std::unique_ptr<T> e) {
            e->parent = this;
            T* raw = e.get();
            children.push_back(std::move(e));
            return raw;
        }

        void layout() override;
        void update() override;
        void render(SDL_Renderer*) override;
    };

    // ================= CANVAS =================
    class Canvas : public Container {
    public:
        void layout() override;
        void update() override;
        void render(SDL_Renderer*) override;
    };

    // ================= TEXT =================
    class Text : public Element {
    public:
        std::string value;
        SDL_Color color{ 255,255,255,255 };
        TTF_Text* ttfText = nullptr;

        Text(const std::string& t = "") : value(t) {}
        ~Text() {
            if (texture) {
                SDL_DestroyTexture(texture);
                texture = nullptr;
            }
        }
        void setText(const std::string&);

        void layout() override;
        void render(SDL_Renderer*) override;

    private:
        SDL_Texture* texture = nullptr;
        bool dirty = true;
        void rebuild(SDL_Renderer*);
    };

    // ================= IMAGE =================
    class Image : public Element {
    public:
        std::string path;

        void render(SDL_Renderer*) override;

    private:
        SDL_Texture* texture = nullptr;
    };

    // ================= PANEL =================
    class Panel : public Container {
    public:
        SDL_Color bg{ 60,60,60,200 };
        void render(SDL_Renderer*) override;
    };

    // ================= BUTTON =================
    struct ButtonStyle {
        SDL_Color normal{ 140,140,140,255 };
        SDL_Color hover{ 180,180,180,255 };
        SDL_Color pressed{ 120,120,120,255 };
        SDL_Color disabled{ 80,80,80,255 };
    };

    class Button : public Element {
    public:
        std::unique_ptr<Element> child;
        ButtonStyle style;

        std::function<void()> onClick;

        void layout() override;
        void update() override;
        void render(SDL_Renderer*) override;

    private:
        bool hovered = false;
        bool pressed = false;
    };

    // ================= LAYOUTS =================
    class VBox : public Container {
    public:
        float spacing = 10;
        Align alignX = Align::Start;        // alinhamento horizontal
        Justify justify = Justify::Start;   // distribuição vertical
        void layout() override;
    };

    class HBox : public Container {
    public:
        float spacing = 10;
        Align alignY = Align::Start;         // alinhamento vertical
        Justify justify = Justify::Start;    // distribuição horizontal
        void layout() override;
    };

    class GridPanel : public Container {
    public:
        int columns = 2;
        float cellW = 64, cellH = 64, spacing = 8;
        Align cellAlignX = Align::Center;
        Align cellAlignY = Align::Center;
        void layout() override;
    };


}
