#include "GUI.h"
#include "TextBox.h"
#include "Label.h"
#include "Button.h"
#include "Color.h"

class SubWindow : public Widget
{
    public:
        SubWindow(const float& x,const float& y,const float& w,const float& h, const float& mxw,const float& mxh,const float& miw,const float& mih,const bool& fix,const bool& isheader,const bool& scroll,const bool& move,const SDL_Color& c) 
        : Widget(x,y,w,h,mxw,mxh,miw,mih,fix,c), header({x,y,w,15}), isHeaderVisible(isheader),canScroll(scroll) , canMove(move),cross ({x +(w-14),y+1,13,13}) {}

    private:
        SDL_FRect header;
        SDL_FRect cross;
        bool isOverheader = false;
        bool isOvercross = false;
        bool isPressedheader = false;
        bool isPressedcross = false;
        bool isMoved = false;
        bool isOpend = true;
        bool isMiddlePressed = false;
        bool Ctrl = false;
        bool isHeaderVisible;
        bool canScroll;
        bool canMove;
        bool canZoom;
        float mx,my;
        std::vector<Widget *> Widget_List;
        std::string Windows_Name;
        
        
    public:
        void add_widget(Widget * newVal)
        {
            //temporal
            newVal->rect.x += rect.x;
            newVal->rect.y += rect.y;
            newVal->InitX = newVal->rect.x;
            newVal->InitX = newVal->rect.y;
            if(isHeaderVisible) newVal->min_height = rect.y+15;
            else newVal->min_height = rect.y;
            newVal->min_width = rect.x;
            newVal->max_width = rect.x+rect.w;
            newVal->max_height = rect.y+rect.h;
            newVal->check_visibility();
            //------------------
            Widget_List.push_back(newVal);
        }
        void Update_Size(const float& add)
        {
            for (auto widgets : Widget_List) 
            {
                widgets->rect.w += add;
                widgets->rect.h += add;
                widgets->max_width = rect.x+rect.w;
                widgets->max_height = rect.y+rect.h;
            }
        }
        void Update_Position(const float& addx, const float& addy)
        {
            rect.x += addx;
            rect.y += addy;
            header.x += addx;
            header.y += addy;
            cross.x += addx;
            cross.y += addy;
            this->check_visibility();
            for (auto widgets : Widget_List) 
            {
                widgets->rect.x += addx;
                widgets->rect.y += addy;
                widgets->InitX = widgets->rect.x;
                widgets->InitY = widgets->rect.y;
                widgets->max_width = rect.x+rect.w;
                widgets->max_height = rect.y+rect.h;
                widgets->min_width = rect.x;
                if(isHeaderVisible) widgets->min_height = rect.y+15;
                else widgets->min_height = rect.y;
                widgets->check_visibility();
            }
        }
        void Update_Element_PositionY(const float& add)
        {
            for(auto widgets : Widget_List) 
            {
                if(!widgets->fixed)
                {
                    // if(widgets->rect.y + add < widgets->InitY) widgets->rect.y = InitY;
                    // else 
                    widgets->rect.y += add;
                    widgets->check_visibility();
                }
            }
        }
        void Update_Element_Position(const float& addx,const float& addy)
        {
            for(auto widgets : Widget_List) 
            {
                if(!widgets->fixed)
                {
                    widgets->rect.x += addx;
                    widgets->rect.y += addy;
                    widgets->check_visibility();
                }
            }
        }
        void draw(SDL_Renderer* renderer) override
        {
            if(isPressed && isOvercross) isOpend = false;
            if(isOpend)
            {
                SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
                RenderFillRect(renderer,rect,max_width,max_height,min_width,min_height);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                RenderRect(renderer, rect,max_width,max_height,min_width,min_height);
                if(isHeaderVisible)
                {
                    if(!isOverheader) SDL_SetRenderDrawColor(renderer,Colors::Black.r,Colors::Black.g,Colors::Black.b,Colors::Black.a);
                    else SDL_SetRenderDrawColor(renderer,Colors::Cyan.r,Colors::Cyan.g,Colors::Cyan.b,Colors::Cyan.a);
                    RenderFillRect(renderer,header,max_width,max_height,min_width,min_height);
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    RenderRect(renderer, header,max_width,max_height,min_width,min_height);
                }
                
                SDL_SetRenderDrawColor(renderer,Colors::LightGray.r,Colors::LightGray.g,Colors::LightGray.b,Colors::LightGray.a);
                RenderFillRect(renderer,cross,max_width,max_height,min_width,min_height);
                if(!isOvercross) SDL_SetRenderDrawColor(renderer,Colors::Black.r,Colors::Black.g,Colors::Black.b,Colors::Black.a);
                else SDL_SetRenderDrawColor(renderer,Colors::White.r,Colors::White.g,Colors::White.b,Colors::White.a);
                for(int i = cross.x,j = cross.y; i < cross.x + cross.w && j < cross.y + cross.h; i++,j++)
                { SDL_RenderPoint(renderer,i,j); }
                for(int i = (cross.x + cross.w)-1,j = cross.y; i >= cross.x && j < cross.y+ cross.h; i--,j++)
                { SDL_RenderPoint(renderer,i,j); }
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                RenderRect(renderer, cross,max_width,max_height,min_width,min_height);
                for(auto widget : Widget_List) widget->draw(renderer);
            }
        }

        void handleEvent(SDL_Event* event) override
        {
            if(isOpend)
            { 
                if(isPressed && event->type == SDL_EVENT_MOUSE_MOTION && isOverheader && !fixed && isVisible)
                { Update_Position(event->motion.x - mx,event->motion.y - my); }

                if(event->type == SDL_EVENT_MOUSE_MOTION && isMiddlePressed && isOver && isVisible && canMove)
                {
                    Update_Element_Position(event->motion.x-mx,event->motion.y-my);
                    mx = event->motion.x;
                    my = event->motion.y;
                }

                if(event->type == SDL_EVENT_MOUSE_MOTION && isVisible)
                {
                    mx = event->motion.x;
                    my = event->motion.y;
                    isOverheader = ((mx >= header.x && mx < cross.x) && (my >= header.y && my < header.y + header.h)) ? true : false;
                    isOvercross = ((mx >= cross.x && mx < cross.x+cross.w) && (my >= cross.y && my < cross.y+cross.h) );
                    isOver = (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h);
                }

                if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && (isOverheader || isOvercross || isOver) && isVisible) 
                { 
                    if(event->button.button == SDL_BUTTON_LEFT) isPressed = true; 
                    else if(event->button.button == SDL_BUTTON_RIGHT) isRightPressed = true;
                    else if(event->button.button == SDL_BUTTON_MIDDLE) isMiddlePressed = true;
                }

                if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) 
                { 
                    isPressed = false; 
                    isRightPressed = false;
                    isMiddlePressed = false;
                }

                if(event->type == SDL_EVENT_MOUSE_WHEEL && isOver && isVisible && canScroll)
                { 
                    if(!Ctrl) Update_Element_PositionY(event->wheel.y*10); 
                    else Update_Size(event->wheel.y*10);
                }

                if(event->type == SDL_EVENT_KEY_DOWN && (event->key.key == SDLK_LCTRL || event->key.key == SDLK_RCTRL))
                { Ctrl = true; }

                if(event->type == SDL_EVENT_KEY_UP) Ctrl = false;

                for(auto widgets : Widget_List) widgets->handleEvent(event);
            }
        }

    };