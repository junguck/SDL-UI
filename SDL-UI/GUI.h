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

    class widget
    {
        public:
        widget(){}

        SDL_Color Color;

        bool IsOver = false;
        bool Clicked = false;

        void Draw_widget(SDL_Renderer * render);
        bool Event(SDL_Event * event);
    };

    class window
    {

    };

    
};




#endif