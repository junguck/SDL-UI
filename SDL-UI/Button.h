// deffinition du bouton
#pragma once
#include <functional>
#include "GUI.h"
#include "Label.h"


    class Button : public Widget {
        public:
        Label* label;
        std::function<void()> onClick;
        
        Button(float x, float y, float w, float h, const float& mxw,const float& mxh,const float& miw,const float& mih,const bool& fix,std::string t, TTF_Font* f, std::function<void()> callback)
            : Widget(x, y, w, h,mxw,mxh,miw,mih,fix,false,{100, 100, 100, 255}), onClick(callback) {
            label = new Label((x-(w/2)) + 10, (y - (h/2)) + 5, rect.x+(rect.w/2), rect.y+(rect.h/2), rect.x-(rect.w/2),rect.y-(rect.h/2),t, f, {255, 255, 255, 255});
        }

        void draw(SDL_Renderer* renderer) override {
            label->rect.x = (rect.x - (rect.w/2));
            label->rect.y = (rect.y - (rect.h/2));
            
            // Changement de couleur au survol
            SDL_SetRenderDrawColor(renderer, isOver ? 150 : 80, 80, 80, 255);
            RenderFillRect(renderer, rect,max_width,max_height,min_width,min_height);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            RenderRect(renderer, rect,max_width,max_height,min_width,min_height);
            if(isVisible) label->draw(renderer);
            else std::cout << "woko" << std::endl;
        }

        void handleEvent(SDL_Event* event) override {
            Widget::handleEvent(event);
            if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && isOver && onClick) {
                onClick();
            }
        }
    };
