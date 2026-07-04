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
 */

#pragma once
#include <functional>
#include "GUI.h"


class Checkbox : public Widget {
public:
    bool checked;
    std::function<void(bool)> onChange;

    Checkbox(float x, float y, float size,
             const float& mxw, const float& mxh,
             const float& miw, const float& mih,
             const bool& fix,
             bool defaultValue = false,
             std::function<void(bool)> callback = nullptr)
        : Widget(x, y, size, size, mxw, mxh, miw, mih, fix, true, {80, 80, 80, 255}),
          checked(defaultValue),
          onChange(callback)
    {
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
            SDL_FRect inner = {
                (rect.x - rect.w / 2 + 4),
                (rect.y - rect.h / 2 + 4),
                (rect.w - 8),
                (rect.h - 8)
            };
            SDL_SetRenderDrawColor(renderer, 0, 180, 0, 255);
            SDL_RenderFillRect(renderer, &inner);
        }
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
