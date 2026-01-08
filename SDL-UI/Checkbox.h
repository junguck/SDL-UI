/**
 * @file Checkbox.h
 * @brief Widget UI représentant une case à cocher (booléen).
 *
 * La classe Checkbox permet de gérer un état ON/OFF (true / false)
 * avec affichage graphique et interaction souris.
 *
 * Elle est conçue pour être utilisée dans le module UI du moteur,
 * et hérite de la classe Widget afin de bénéficier :
 *  - de la gestion de position
 *  - de la détection de survol (hover)
 *  - de la gestion des événements SDL
 *
 * Fonctionnalités :
 *  - Affichage d’une case cliquable
 *  - Gestion d’un état booléen
 *  - Label textuel associé
 *  - Callback lors du changement d’état
 *
 * Utilisation typique :
 * @code
 * Checkbox* gridCheck = new Checkbox(
 *     20, 40, 18,
 *     maxW, maxH, minW, minH,
 *     true,
 *     "Afficher la grille",
 *     font,
 *     false,
 *     [](bool value) {
 *         SDL_Log("Checkbox: %s", value ? "ON" : "OFF");
 *     }
 * );
 * @endcode
 *
 * Notes :
 *  - L’état est inversé automatiquement lors d’un clic souris
 *  - Le callback est appelé après chaque changement
 *  - Le rendu est géré via SDL_Renderer
 *
 * @author
 * Yin
 */

#pragma once
#include <functional>
#include "GUI.h"
#include "Label.h"

class Checkbox : public Widget {
public:
    bool checked;
    Label* label;
    std::function<void(bool)> onChange;

    Checkbox(float x, float y, float size,
             const float& mxw, const float& mxh,
             const float& miw, const float& mih,
             const bool& fix,
             const std::string& text,
             TTF_Font* font,
             bool defaultValue = false,
             std::function<void(bool)> callback = nullptr)
        : Widget(x, y, size, size, mxw, mxh, miw, mih, fix, false, {80, 80, 80, 255}),
          checked(defaultValue),
          onChange(callback)
    {
        label = new Label(
            x + size + 10,
            y - size / 2,
            x + size + 10, y,
            x, y,
            text,
            font,
            {255, 255, 255, 255}
        );
    }

    void draw(SDL_Renderer* renderer) override
    {
        // Fond
        SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
        RenderFillRect(renderer, rect, max_width, max_height, min_width, min_height);

        // Contour
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        RenderRect(renderer, rect, max_width, max_height, min_width, min_height);

        // Check
        if (checked) {
            SDL_Rect inner = {
                (int)(rect.x - rect.w / 2 + 4),
                (int)(rect.y - rect.h / 2 + 4),
                (int)(rect.w - 8),
                (int)(rect.h - 8)
            };
            SDL_SetRenderDrawColor(renderer, 0, 180, 0, 255);
            SDL_RenderFillRect(renderer, &inner);
        }

        if (isVisible)
            label->draw(renderer);
    }

    void handleEvent(SDL_Event* event) override
    {
        Widget::handleEvent(event);

        if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && isOver)
        {
            checked = !checked;
            if (onChange)
                onChange(checked);
        }
    }
};
