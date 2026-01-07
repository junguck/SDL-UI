#pragma once
#include "GUI.h"

// Texte simple (label avec retour à la ligne automatique)
class Label : public Widget
{
public:
    std::string text;
    TTF_Font* font;
    Uint32 wrapWidth; // largeur max avant retour à la ligne

    // position + dimensions + texte + police + couleur
    Label(float x, float y,
          const float& mxw, const float& mxh,
          const float& miw, const float& mih,
          std::string t,
          TTF_Font* f,
          SDL_Color c,
          Uint32 wrap = 300) // largeur par défaut
        : Widget(x, y, mxw, mxh, miw, mih, fixed, false, 0, 0, c),
          text(t),
          font(f),
          wrapWidth(wrap)
    {
    }

    void draw(SDL_Renderer* renderer) override
    {
        if (text.empty() || !font) return;

        // Rendu du texte avec retour à la ligne automatique
        SDL_Surface* surf = TTF_RenderText_Blended_Wrapped(
            font,
            text.c_str(),
            color,
            wrapWidth
        );

        if (!surf) return;

        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
        if (!tex)
        {
            SDL_DestroySurface(surf);
            return;
        }

        // Ajustement automatique de la taille du widget
        rect.w = static_cast<float>(surf->w);
        rect.h = static_cast<float>(surf->h);

        SDL_RenderTexture(renderer, tex, nullptr, &rect);

        SDL_DestroySurface(surf);
        SDL_DestroyTexture(tex);
    }
};
