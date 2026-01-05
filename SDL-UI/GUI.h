#ifndef __GUI_H__
#define __GUI_H__

#include<iostream>
#include<SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include<string>
#include<vector>
#include<array>


void RenderFillRect(SDL_Renderer * render,const SDL_FRect& rect, const float& max_width, const float& max_height,const float& min_width, const float& min_height)
{
    for(int i = rect.x; (i < rect.x + rect.w); i++)
    {
        for(int j = rect.y; (j < rect.y + rect.h); j++)
        {
            if(i < max_width && j < max_height && i >= min_width && j >= min_height) SDL_RenderPoint(render,i,j);
        }
    }
}

void RenderRect(SDL_Renderer * render,const SDL_FRect& rect, const float& max_width, const float& max_height, const float& min_width, const float& min_height)
{
    for(int i = rect.x,j = rect.y; (i < rect.x + rect.w); i++)
    { if(i < max_width && j < max_height && i >= min_width && j >= min_height) SDL_RenderPoint(render,i,j); }

    for(int i = rect.x,j = (rect.y+rect.h)-1; (i < rect.x + rect.w); i++)
    { if(i < max_width && j < max_height && i >= min_width && j >= min_height) SDL_RenderPoint(render,i,j); }

    for(int i = rect.x,j = rect.y; (j < rect.y + rect.h); j++)
    { if(i < max_width && j < max_height && i >= min_width && j >= min_height) SDL_RenderPoint(render,i,j); }

    for(int i = (rect.x+rect.w)-1,j = rect.y; (j < rect.y + rect.h); j++)
    { if(i < max_width && j < max_height && i >= min_width && j >= min_height) SDL_RenderPoint(render,i,j); }
}


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
    bool fixed;
    bool isVisible;
    bool isRightPressed = false;

    float InitX;
    float InitY;
    float max_width;
    float max_height;
    float min_width;
    float min_height;

    Widget(float x, float y, float w, float h, const float& mxw,const float& mxh,const float& miw,const float& mih,const bool& fix,SDL_Color c) 
        : rect({x, y, w, h}) ,InitX(x),InitY(y),max_width(mxw) ,max_height(mxh),min_width(miw), min_height(mih) , fixed(fix),color(c) { check_visibility(); }

    virtual ~Widget() = default;

    void check_visibility()
    { isVisible = rect.x < max_width || rect.y < max_height || rect.x >= min_width || rect.y>= min_height  ||  (rect.x+rect.w)-1 < max_width || (rect.y+rect.h)-1 < max_height || (rect.x+rect.w)-1 >= min_width || (rect.y+rect.h)-1 >= min_height; }
    
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


#endif