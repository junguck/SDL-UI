//Cette classe utilise SDL_StartTextInput() pour capturer les caractères et gère la touche "Backspace" pour effacer.
#pragma once
#include "Widget.hpp"
#include <SDL3/SDL.h>
#include <string>

class TextBox : public Widget {
public:
    std::string text;
    TTF_Font* font;
    bool hasFocus = false;
    int cursorTimer = 0; // Pour le clignotement du curseur
    //constructeur de la classe
    TextBox(float x, float y, float w, float h, TTF_Font* f)
        : Widget(x, y, w, h, {255, 255, 255, 255}), font(f), text("") {}

    void handleEvent(SDL_Event* event) override {
        Widget::handleEvent(event);

        // Gestion du Focus
        if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            hasFocus = isOver;
            if (hasFocus) SDL_StartTextInput(SDL_GetKeyboardFocus());
            else SDL_StopTextInput(SDL_GetKeyboardFocus());
        }

        if (hasFocus) {
            // Saisie de texte
            if (event->type == SDL_EVENT_TEXT_INPUT) {
                text += event->text.text;
            }
            // Suppression (Backspace)
            if (event->type == SDL_EVENT_KEY_DOWN) {
                if (event->key.key == SDLK_BACKSPACE && !text.empty()) {
                    text.pop_back();
                }
            }
        }
    }

    void draw(SDL_Renderer* renderer) override {
        // Fond de la zone
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        
        // Bordure (plus épaisse si focus)
        SDL_SetRenderDrawColor(renderer, hasFocus ? 0 : 150, 120, 255, 255);
        SDL_RenderRect(renderer, &rect);

        // Rendu du texte
        if (!text.empty()) {
            SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), 0, {0, 0, 0, 255});
            if (surf) {
                SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
                SDL_FRect textRect = {rect.x + 5, rect.y + (rect.h - surf->h) / 2, (float)surf->w, (float)surf->h};
                
                // Empêcher le texte de dépasser de la zone
                if (textRect.w > rect.w - 10) textRect.w = rect.w - 10;

                SDL_RenderTexture(renderer, tex, nullptr, &textRect);
                SDL_DestroySurface(surf);
                SDL_DestroyTexture(tex);
            }
        }

        // Curseur clignotant
        if (hasFocus) {
            cursorTimer++;
            if ((cursorTimer / 30) % 2 == 0) { // Clignote toutes les ~30 frames
                float textW = 0;
                if (!text.empty()) {
                    int w;
                    TTF_SizeText(font, text.c_str(), &w, nullptr);
                    textW = (float)w;
                }
                SDL_FRect cursor = {rect.x + 5 + textW, rect.y + 5, 2, rect.h - 10};
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &cursor);
            }
        }
    }
};