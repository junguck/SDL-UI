// deffinition du bouton
#pragma once
#include <functional>
#include "GUI.h"
#include "Label.h"


    class Button : public Widget {
        public:
        Label* label;
        std::function<void()> onClick;
        int xc,yc;
        Button(float x, float y, float w, float h, const float& mxw,const float& mxh,const float& miw,const float& mih,const bool& fix,std::string t, TTF_Font* f, std::function<void()> callback)
            : Widget(x, y, w, h,mxw,mxh,miw,mih,fix,{100, 100, 100, 255}), onClick(callback) {
                xc = x;
                yc = y;
            label = new Label(x + 10, y + 5, rect.x+rect.x, rect.y+rect.h, rect.x,rect.h,t, f, {255, 255, 255, 255});
        }

        void draw(SDL_Renderer* renderer) override {
            xc = rect.x;
            yc = rect.y;
            label->rect.x = xc;
            label->rect.y = yc;
            
            // Changement de couleur au survol
            SDL_SetRenderDrawColor(renderer, isOver ? 150 : 80, 80, 80, 255);
            RenderFillRect(renderer, rect,max_width,max_height,min_width,min_height);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            RenderRect(renderer, rect,max_width,max_height,min_width,min_height);
            if(isVisible) label->draw(renderer);
        }

        void handleEvent(SDL_Event* event) override {
            Widget::handleEvent(event);
            if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && isOver && onClick) {
                onClick();
            }
        }
    };
