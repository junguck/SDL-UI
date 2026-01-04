#ifndef __GUI_H__
#define __GUI_H__

#include<iostream>
#include<SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include<string>
#include<vector>
#include<array>

#include "math.h"


//push de jun (remodification de la classe)

class Widget {
public:
    //zone du wigdet
    SDL_FRect rect;
    //couleur 
    SDL_Color color;
    //gestionaire des event
    bool isOver = false;
    bool isPressed = false;

    Widget(float x, float y, float w, float h, SDL_Color c) 
        : rect({x, y, w, h}), color(c) {}

    virtual ~Widget() = default;
    
    // Méthodes virtuelles pures pour forcer l'implémentation
    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void handleEvent(SDL_Event* event) {
        if (event->type == SDL_EVENT_MOUSE_MOTION) {
            float mx = event->motion.x;
            float my = event->motion.y;
            isOver = (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h);
        }
        if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && isOver) {
            isPressed = true;
        }
        if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
            isPressed = false;
        }
    }
};

    
class SubWindow : public Widget
{
    public:
        SubWindow(const float& x,const float& y,const float& w,const float& h,const SDL_Color& c) : Widget(x,y,w,h,c), header({x,y,w,15}), cross ({x +(w-14),y+1,13,13}) {}

    private:
        SDL_FRect header;
        SDL_FRect cross;
        bool isOverheader = false;
        bool isOvercross = false;
        bool isPressedheader = false;
        bool isPressedcross = false;
        bool isMoved = false;
        std::vector<Widget *> Widget_List;
        bool isOpend = true;
        
    public:
        void add_widget(Widget * newVal)
        {
            newVal->rect.x += rect.w;
            newVal->rect.y += rect.h;
            Widget_List.push_back(newVal);
        }
        void draw(SDL_Renderer* renderer) override
        {
            if(isOpend)
            {
                SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
                SDL_RenderFillRect(renderer,&rect);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer,Colors::Black.r,Colors::Black.g,Colors::Black.b,Colors::Black.a);
                SDL_RenderFillRect(renderer,&header);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderRect(renderer, &header);
                SDL_SetRenderDrawColor(renderer,Colors::LightGray.r,Colors::LightGray.g,Colors::LightGray.b,Colors::LightGray.a);
                SDL_RenderFillRect(renderer,&cross);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderRect(renderer, &cross);
                SDL_SetRenderDrawColor(renderer,Colors::Black.r,Colors::Black.g,Colors::Black.b,Colors::Black.a);
                for(int i = cross.x; i < cross.x + cross.w; i++)
                {
                    for(int j = cross.y; i < cross.y + cross.h; j++)
                    {
                        SDL_RenderPoint(renderer,i,j);
                    }
                }
                for(auto widget : Widget_List) widget->draw(renderer);
                }
        }

        void handleEvent(SDL_Event* event) override
        {
            if(event->type == SDL_EVENT_MOUSE_MOTION)
            {
                float mx = event->motion.x;
                float my = event->motion.y;
                isOverheader = ((mx >= header.x && mx < cross.x) && (my >= header.y && my < header.y + header.h)) ? true : false;
                isOvercross = ((mx >= cross.x && mx < cross.x) )
            }

        }

    };




#endif