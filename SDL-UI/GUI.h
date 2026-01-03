#ifndef __GUI_H__
#define __GUI_H__

#include<iostream>
#include<SDL3/SDL.h>
#include<string>
#include<vector>
#include<array>

#include "math.h"

namespace GUI
{
    class WindowElement
    {
        public:
            WindowElement(SDL_Renderer * render,const int& Length,const int& Width,const math::vector2D& Position,const SDL_Color& color,const bool& filled, const bool& bordered,const SDL_Color& border = {255,255,255,255}, const int& border_thickness = 0) 
            : Render(render) ,length(Length), width(Width), position(Position), Element_color(color) ,IsFilled(filled) ,IsBordered(bordered) ,Border_color(border), Border_Thickness(border_thickness) {}
        
        protected:
            int length;
            int width;
            int  Border_Thickness;
            bool IsFilled;
            bool IsBordered;
            math::vector2D position;
            SDL_Color Element_color;
            SDL_Color Border_color;
            SDL_Renderer * Render;
     
        protected:
            void Draw();
            bool Event(SDL_Event * event);
            void virtual nothing() = 0;
    };

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

    
};




#endif