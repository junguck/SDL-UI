// deffinition du bouton
#pragma once
#include "Widget.hpp"
#include "Label.hpp"
#include <functional>

class Button : public Widget {
public:
    Label* label;
    std::function<void()> onClick;

    Button(float x, float y, float w, float h, std::string t, TTF_Font* f, std::function<void()> callback)
        : Widget(x, y, w, h, {100, 100, 100, 255}), onClick(callback) {
        label = new Label(x + 10, y + 5, t, f, {255, 255, 255, 255});
    }

    void draw(SDL_Renderer* renderer) override {
        // Changement de couleur au survol
        SDL_SetRenderDrawColor(renderer, isOver ? 150 : 80, 80, 80, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderRect(renderer, &rect);
        label->draw(renderer);
    }

    void handleEvent(SDL_Event* event) override {
        Widget::handleEvent(event);
        if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && isOver && onClick) {
            onClick();
        }
    }
};