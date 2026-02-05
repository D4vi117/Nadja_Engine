#include "ui.hpp"
#include "input/input.hpp"
#include <iostream>
#include <typeinfo>
#include <unordered_set>
#include "core/config.hpp"
#include "engine/context.hpp"

namespace UI {

    static Element* captured = nullptr;
    static std::unordered_set<const Element*> spawned;

    // ================= GLOBAL POS =================
    float Element::globalX() const {
        float px = parent ? parent->globalX() : 0.0f;
        float pw = parent ? parent->rect.w : rect.w;

        return px + rect.x + (pw - rect.w) * anchor.x + offset.x;
    }
    

    float Element::globalY() const {
        float py = parent ? parent->globalY() : 0.0f;
        float ph = parent ? parent->rect.h : rect.h;
        return py + rect.y + (ph - rect.h) * anchor.y + offset.y;
    }

    // ================= DEBUG =================
    static void dumpElement(const Element* e, const char* tag) {
        if (Config::Debug::HUD_DUMP)
        std::cout
            << "[UI][" << tag << "] "
            << typeid(*e).name()
            << " @" << e
            << " local("
            << e->rect.x << ","
            << e->rect.y << " "
            << e->rect.w << "x"
            << e->rect.h << ")"
            << " global("
            << e->globalX() << ","
            << e->globalY() << ")"
            << " anchor("
            << e->anchor.x << ","
            << e->anchor.y << ")"
            << " parent=" << e->parent
            << std::endl;
    }

    // ================= CONTAINER =================
    void Container::layout() {
        for (auto& c : children)
            c->layout();
    }

    void Container::update() {
        for (auto& c : children)
            if (c->visible && c->enabled)
                c->update();
    }

    void Container::render(SDL_Renderer* r) {
        SDL_Rect clip{
            static_cast<int>(globalX()),
            static_cast<int>(globalY()),
            static_cast<int>(rect.w),
            static_cast<int>(rect.h)
        };

        if (rect.w > 0 && rect.h > 0)
            SDL_SetRenderClipRect(r, &clip);
        else
            SDL_SetRenderClipRect(r, nullptr);
        for (auto& c : children) {
            if (!c->visible) continue;

            if (spawned.find(c.get()) == spawned.end()) {
                spawned.insert(c.get());
                dumpElement(c.get(), "SPAWN");
            }

            c->render(r);
            c->debugRender(r);
        }

        SDL_SetRenderClipRect(r, nullptr);
    }

    // ================= CANVAS =================
    void Canvas::layout() {
        int w, h;
        SDL_GetWindowSize(Engine::window, &w, &h);

        rect.x = 0;
        rect.y = 0;
        rect.w = (float)w;
        rect.h = (float)h;

        for (auto& c : children)
            c->layout();
    }

    void Canvas::update() {
        captured = nullptr;
        Container::update();
    }

    void Canvas::render(SDL_Renderer* r) {
        for (auto& c : children) {
            if (!c->visible) continue;

            if (spawned.find(c.get()) == spawned.end()) {
                spawned.insert(c.get());
                dumpElement(c.get(), "SPAWN");
            }

            c->render(r);
            c->debugRender(r);
        }
    }

    // ================= TEXT =================
    void Text::setText(const std::string& t) {
        if (value != t) {
            value = t;
            dirty = true;
        }
    }

    void Text::rebuild(SDL_Renderer* r) {
        TTF_Font* font = AssetManager::getFont(Font::defaultFontId);
        if (!font || value.empty()) return;

        if (texture) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }

        SDL_Surface* s = TTF_RenderText_Blended(font, value.c_str(), value.size(), color);
        if (!s) return;

        texture = SDL_CreateTextureFromSurface(r, s);
        rect.w = static_cast<float>(s->w);
        rect.h = static_cast<float>(s->h);

        SDL_DestroySurface(s);

        if (parent)
            parent->layout();

        dirty = false;
    }


    void Text::render(SDL_Renderer* r) {
        if (dirty || !texture)
            rebuild(r);

        SDL_FRect fr{ globalX(), globalY(), rect.w, rect.h };
        SDL_RenderTexture(r, texture, nullptr, &fr);
    }
    void Text::layout() {
        if (!Font::defaultFontId.empty() && (rect.w == 0 || rect.h == 0))
            dirty = true;
    }

    // ================= IMAGE =================
    void Image::render(SDL_Renderer* r) {
        if (!texture && !path.empty()) {
            SDL_Surface* s = SDL_LoadBMP(path.c_str());
            if (s) {
                texture = SDL_CreateTextureFromSurface(r, s);
                rect.w = static_cast<float>(s->w);
                rect.h = static_cast<float>(s->h);
                SDL_DestroySurface(s);
            }
        }

        if (!texture) return;

        SDL_FRect fr{ globalX(), globalY(), rect.w, rect.h };
        SDL_RenderTexture(r, texture, nullptr, &fr);
    }

    // ================= PANEL =================
    void Panel::render(SDL_Renderer* r) {
        SDL_FRect fr{ globalX(), globalY(), rect.w, rect.h };
        SDL_SetRenderDrawColor(r, bg.r, bg.g, bg.b, bg.a);
        SDL_RenderFillRect(r, &fr);
        Container::render(r);
    }

    // ================= BUTTON =================
    void Button::layout() {
        if (child) {
            child->anchor = { 0, 0 }; // ESSENCIAL

            child->rect.x = (rect.w - child->rect.w) * 0.5f;
            child->rect.y = (rect.h - child->rect.h) * 0.5f;

            child->layout();
        }
    }

    void Button::update() {
        if (!enabled) return;

        static bool lastHover = false;

        float x = globalX();
        float y = globalY();

        Vec2 m{
           Input::mouse.x,
           Input::mouse.y
        };

        bool nowHover =
            m.x >= x &&
            m.x <= x + rect.w &&
            m.y >= y &&
            m.y <= y + rect.h;

        lastHover = nowHover;

        if (nowHover && Input::mouse.leftPressed) {
            captured = this;
            pressed = true;
            dumpElement(this, "PRESS");
            if (onClick) onClick();
        }

        if (captured == this && Input::mouse.leftReleased) {
            pressed = false;
            captured = nullptr;

            dumpElement(this, nowHover ? "CLICK" : "RELEASE");

            if (nowHover && onClick)
                onClick();
        }
    }

    void Button::render(SDL_Renderer* r) {
        SDL_Color c = !enabled ? style.disabled :
            pressed ? style.pressed :
            hovered ? style.hover : style.normal;

        SDL_FRect fr{ globalX(), globalY(), rect.w, rect.h };
        SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(r, &fr);

        if (child) {
            const UI::Element* ptr = child.get();
            child->parent = this;
            if (spawned.find(ptr) == spawned.end()) {
                spawned.insert(ptr);
                dumpElement(ptr, "SPAWN");
            }

            child->render(r);
            child->debugRender(r);
        }

    }

    // ================= LAYOUTS =================
    void VBox::layout() {
        if (children.empty()) return;

        float contentH = 0;
        for (auto& c : children)
            contentH += c->rect.h;

        float totalSpacing = spacing * (children.size() - 1);
        float freeH = rect.h - padding.t - padding.b - contentH - totalSpacing;

        float y = padding.t;

        if (justify == Justify::Center)
            y += freeH * 0.5f;
        else if (justify == Justify::End)
            y += freeH;
        else if (justify == Justify::SpaceAround)
            y += freeH / children.size() * 0.5f;
        else if (justify == Justify::SpaceEvenly)
            y += freeH / (children.size() + 1);

        float dynSpacing = spacing;
        if (justify == Justify::SpaceBetween && children.size() > 1)
            dynSpacing += freeH / (children.size() - 1);
        else if (justify == Justify::SpaceAround)
            dynSpacing += freeH / children.size();
        else if (justify == Justify::SpaceEvenly)
            dynSpacing += freeH / (children.size() + 1);

        for (auto& c : children) {
            float x = padding.l;

            if (alignX == Align::Center)
                x += (rect.w - padding.l - padding.r - c->rect.w) * 0.5f;
            else if (alignX == Align::End)
                x += (rect.w - padding.l - padding.r - c->rect.w);
            else if (alignX == Align::Stretch)
                c->rect.w = rect.w - padding.l - padding.r;

            c->rect.x = x;
            c->rect.y = y;
            c->anchor = { 0,0 };

            c->layout();
            y += c->rect.h + dynSpacing;
        }
    }



    void HBox::layout() {
        if (children.empty()) return;

        float contentW = 0;
        for (auto& c : children)
            contentW += c->rect.w;

        float totalSpacing = spacing * (children.size() - 1);
        float freeW = rect.w - padding.l - padding.r - contentW - totalSpacing;

        float x = padding.l;

        if (justify == Justify::Center)
            x += freeW * 0.5f;
        else if (justify == Justify::End)
            x += freeW;
        else if (justify == Justify::SpaceAround)
            x += freeW / children.size() * 0.5f;
        else if (justify == Justify::SpaceEvenly)
            x += freeW / (children.size() + 1);

        float dynSpacing = spacing;
        if (justify == Justify::SpaceBetween && children.size() > 1)
            dynSpacing += freeW / (children.size() - 1);
        else if (justify == Justify::SpaceAround)
            dynSpacing += freeW / children.size();
        else if (justify == Justify::SpaceEvenly)
            dynSpacing += freeW / (children.size() + 1);

        for (auto& c : children) {
            float y = padding.t;

            if (alignY == Align::Center)
                y += (rect.h - padding.t - padding.b - c->rect.h) * 0.5f;
            else if (alignY == Align::End)
                y += (rect.h - padding.t - padding.b - c->rect.h);
            else if (alignY == Align::Stretch)
                c->rect.h = rect.h - padding.t - padding.b;

            c->rect.x = x;
            c->rect.y = y;
            c->anchor = { 0,0 };

            c->layout();
            x += c->rect.w + dynSpacing;
        }
    }



    void GridPanel::layout() {
        for (size_t i = 0; i < children.size(); ++i) {
            size_t col = i % static_cast<size_t>(columns);
            size_t row = i / static_cast<size_t>(columns);

            float cellX = padding.l + col * (cellW + spacing);
            float cellY = padding.t + row * (cellH + spacing);

            auto& c = children[i];

            float x = cellX;
            float y = cellY;

            if (cellAlignX == Align::Center)
                x += (cellW - c->rect.w) * 0.5f;
            else if (cellAlignX == Align::End)
                x += (cellW - c->rect.w);

            if (cellAlignY == Align::Center)
                y += (cellH - c->rect.h) * 0.5f;
            else if (cellAlignY == Align::End)
                y += (cellH - c->rect.h);

            c->rect.x = x;
            c->rect.y = y;
            c->anchor = { 0,0 };

            c->layout();
        }
    }


}
