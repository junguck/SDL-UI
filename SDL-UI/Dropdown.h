/**
 * @file Dropdown.h
 * @brief Widget UI représentant une liste déroulante (ComboBox).
 *
 * La classe Dropdown permet de sélectionner une valeur parmi
 * une liste d’options textuelles.
 *
 * Elle est particulièrement adaptée aux interfaces de type :
 *  - Inspector
 *  - Paramètres
 *  - Choix de modes, types, options
 *
 * Cette classe hérite de Widget et utilise des Label
 * pour l’affichage du texte.
 *
 * Fonctionnalités :
 *  - Affichage de la valeur sélectionnée
 *  - Ouverture / fermeture de la liste
 *  - Sélection par clic souris
 *  - Callback lors du changement de sélection
 *
 * Utilisation typique :
 * @code
 * std::vector<std::string> gateTypes = {
 *     "AND", "OR", "NOT", "XOR", "NAND", "NOR"
 * };
 *
 * Dropdown* gateSelector = new Dropdown(
 *     20, 80, 160, 28,
 *     maxW, maxH, minW, minH,
 *     true,
 *     gateTypes,
 *     font,
 *     0,
 *     [](int index) {
 *         SDL_Log("Gate sélectionnée : %d", index);
 *     }
 * );
 * @endcode
 *
 * Notes :
 *  - Un seul élément est sélectionné à la fois
 *  - Le dropdown se ferme automatiquement après sélection
 *  - La gestion du survol et des clics est entièrement manuelle
 *
 * Limitations actuelles :
 *  - Pas de scrollbar pour grandes listes
 *  - Navigation clavier non implémentée
 *
 * Extensions possibles :
 *  - Animation d’ouverture
 *  - Scroll vertical
 *  - Recherche dans la liste
 *
 * @author
 * Yin
 */

#pragma once
#include <vector>
#include <string>
#include <functional>
#include "GUI.h"
#include "Label.h"

class Dropdown : public Widget {
public:
    std::vector<std::string> items;
    int selectedIndex;
    bool opened;

    Label* mainLabel;
    std::vector<Label*> itemLabels;

    std::function<void(int)> onSelect;

    Dropdown(float x, float y, float w, float h,
             const float& mxw, const float& mxh,
             const float& miw, const float& mih,
             const bool& fix,
             const std::vector<std::string>& options,
             TTF_Font* font,
             int defaultIndex = 0,
             std::function<void(int)> callback = nullptr)
        : Widget(x, y, w, h, mxw, mxh, miw, mih, fix, true, {90, 90, 90, 255}),
          items(options),
          selectedIndex(defaultIndex),
          opened(false),
          onSelect(callback)
    {
        mainLabel = new Label(
            x - w / 2 + 10,
            y - h / 2 + 5,
            x, y, x, y,
            items[selectedIndex],
            font,
            {255, 255, 255, 255}
        );

        for (const auto& item : items) {
            itemLabels.push_back(
                new Label(
                    x - w / 2 + 10,
                    y + h / 2,
                    x, y, x, y,
                    item,
                    font,
                    {255, 255, 255, 255}
                )
            );
        }
    }

    void draw(SDL_Renderer* renderer) override
    {
        // Bouton principal
        SDL_SetRenderDrawColor(renderer, isOver ? 120 : 80, 80, 80, 255);
        RenderFillRect(renderer, rect, max_width, max_height, min_width, min_height);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        RenderRect(renderer, rect, max_width, max_height, min_width, min_height);

        mainLabel->draw(renderer);

        // Liste déroulante
        if (opened)
        {
            for (size_t i = 0; i < items.size(); i++)
            {
                SDL_FRect itemRect = {
                    rect.x,
                    rect.y + rect.h * (i + 1),
                    rect.w,
                    rect.h
                };

                SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
                RenderFillRect(renderer, itemRect, max_width, max_height, min_width, min_height);
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
                RenderRect(renderer, itemRect, max_width, max_height, min_width, min_height);

                itemLabels[i]->rect.x = itemRect.x - itemRect.w / 2;
                itemLabels[i]->rect.y = itemRect.y - itemRect.h / 2;
                itemLabels[i]->draw(renderer);
            }
        }
    }

    void handleEvent(SDL_Event* event) override
    {
        Widget::handleEvent(event);

        if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (isOver)
            {
                opened = !opened;
                return;
            }

            if (opened)
            {
                for (size_t i = 0; i < items.size(); i++)
                {
                    SDL_FRect itemRect = {
                        rect.x,
                        rect.y + rect.h * (i + 1),
                        rect.w,
                        rect.h
                    };

                    if (isOver)
                    {
                        selectedIndex = (int)i;
                        mainLabel->setText(items[i]);
                        opened = false;

                        if (onSelect)
                            onSelect(selectedIndex);
                        break;
                    }
                }
            }
            else
                opened = false;
        }
    }
};
