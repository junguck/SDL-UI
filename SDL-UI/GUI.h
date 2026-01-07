#ifndef __GUI_H__
#define __GUI_H__

#include<iostream>
#include<SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include<vector>
#include<array>


void RenderFillRect(SDL_Renderer * render,const SDL_FRect& rect, const float& max_width, const float& max_height,const float& min_width, const float& min_height)
{
    for(int i = rect.x - (rect.w/2); i <= rect.x + (rect.w/2); i++)
    {
        for(int j = rect.y - (rect.h/2); j <= rect.y + (rect.h/2); j++)
        {
            if(i < max_width && j < max_height && i >= min_width && j >= min_height) SDL_RenderPoint(render,i,j);
        }
    }
}

void RenderRect(SDL_Renderer * render,const SDL_FRect& rect, const float& max_width, const float& max_height, const float& min_width, const float& min_height)
{
    for(int i = rect.x - (rect.w/2),j = rect.y - (rect.h/2); i <= rect.x + (rect.w/2); i++)
    { if(i < max_width && j < max_height && i >= min_width && j >= min_height) SDL_RenderPoint(render,i,j); }

    for(int i = rect.x - (rect.w/2),j = rect.y+(rect.h/2); i <= rect.x + (rect.w/2); i++)
    { if(i < max_width && j < max_height && i >= min_width && j >= min_height) SDL_RenderPoint(render,i,j); }

    for(int i = rect.x - (rect.w/2),j = rect.y - (rect.h/2); j <= rect.y + (rect.h/2); j++)
    { if(i < max_width && j < max_height && i >= min_width && j >= min_height) SDL_RenderPoint(render,i,j); }

    for(int i = rect.x +(rect.w/2),j = rect.y - (rect.h/2); j <= rect.y + (rect.h/2); j++)
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
    bool CanResize;

    float InitX;
    float InitY;
    float max_width;
    float max_height;
    float min_width;
    float min_height;

    Widget(float x, float y, float w, float h, const float& mxw,const float& mxh,const float& miw,const float& mih,const bool& fix,const bool& resize,SDL_Color c) 
        : rect({x, y, w, h}) ,InitX(x),InitY(y),max_width(mxw) ,max_height(mxh),min_width(miw), min_height(mih) , fixed(fix),CanResize(resize), color(c) { check_visibility(); }

    virtual ~Widget() = default;

    void check_visibility()
    { 
      isVisible = (((rect.x+(rect.w/2)) >= min_width && (rect.x+(rect.w/2)) < max_width ) || ((rect.x-(rect.w/2)) >= min_width &&  (rect.x-(rect.w/2)) < max_width) 
      && ((rect.y+(rect.h/2)) >= min_height && (rect.y+(rect.h/2)) < max_height) || ((rect.y-(rect.h/2)) >= min_height && (rect.y-(rect.h/2)) < max_height)); 
    }
    
    // Méthodes virtuelles pures pour forcer l'implémentation
    // virtual void Resize(const float& size);```
    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void handleEvent(SDL_Event* event) {
        if (event->type == SDL_EVENT_MOUSE_MOTION) {
            float mx = event->motion.x;
            float my = event->motion.y;
            isOver = (mx >= rect.x - (rect.w/2) && mx <= rect.x + (rect.w/2) && my >= rect.y - (rect.h/2) && my <= rect.y + (rect.h/2));
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