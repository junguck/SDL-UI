// texte simple (label)
#pragma once
#include "Widget.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class Label : public Widget {
public:
    std::string text;
    TTF_Font* font;

    //position + texte + police + couleur : heriter de la position et de la couleur de widget
    Label(float x, float y, std::string t, TTF_Font* f, SDL_Color c)
        : Widget(x, y, 0, 0, c), text(t), font(f) {}

        //definition de draw
    void draw(SDL_Renderer* renderer) override {
        if (text.empty()) return;
        //utilisqtion de mode de sld ttf
        SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), 0, color);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
        
        rect.w = (float)surf->w;
        rect.h = (float)surf->h;

        SDL_RenderTexture(renderer, tex, nullptr, &rect);
        SDL_DestroySurface(surf);
        SDL_DestroyTexture(tex);
    }
};