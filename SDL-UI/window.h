#include "GUI.h"
#include "TextBox.h"
#include "Label.h"
#include "Button.h"
#include "Color.h"
#include "Checkbox.h"
#include "Dropdown.h"

class SubWindow : public Widget
{
    public:
        SubWindow(const float& x,const float& y,const float& w,const float& h, const float& mxw,const float& mxh,const float& miw,const float& mih,const bool& fix,const bool& resize,const bool& isheader,const bool& scroll,const bool& move,const SDL_Color& c) 
        : Widget(x,y,w,h,mxw,mxh,miw,mih,fix,resize,c), header({x,y-(h/2)+(15/2),w,15}), isHeaderVisible(isheader),canScroll(scroll) , canMove(move),cross ({x-(w/2) + (w-7),y-(h/2)+(15/2),10,10}) {}

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
        bool CursorOnLeft;
        bool CursorOnRight;
        bool CursorOnUp;
        bool CursorOnDown;
        float mx,my;
        std::vector<Widget *> Widget_List;
        std::string Windows_Name;
        
        
    public:
        void add_widget(Widget * newVal)
        {
            //temporal
            newVal->rect.x += (rect.x - (rect.x/2));
            newVal->rect.y += (rect.y - (rect.h/2));
            newVal->InitX = newVal->rect.x;
            newVal->InitY = newVal->rect.y;
            if(isHeaderVisible) newVal->min_height = (rect.y - (rect.h/2)) +15;
            else newVal->min_height = (rect.y - (rect.h/2));
            newVal->min_width = rect.x - (rect.w/2);
            newVal->max_width = rect.x + (rect.w/2);
            newVal->max_height = rect.y +(rect.h/2);
            newVal->check_visibility();
            //------------------
            Widget_List.push_back(newVal);
        }
        void Update_Size(const float& add)
        {
            for (auto widgets : Widget_List) 
            {
                if(widgets->CanResize == true)
                {
                    widgets->rect.w += add;
                    widgets->rect.h += add;
                }
            }
        }
        void Resize(const float& add)
        {
            if(CursorOnDown) 
            {
                rect.h += add;
                Update_Windows_Position(0,add/2);
                // Update_Position(0,add/2);
                header.y = rect.y-(rect.h/2)+(15/2);
                cross.y = rect.y-(rect.h/2)+(15/2);
            }
            else if(CursorOnUp)
            {
                rect.h -= add;
                Update_Windows_Position(0,add/2);
                // Update_Position(0,add/2);
                header.y = rect.y-(rect.h/2)+(15/2);
                cross.y = rect.y-(rect.h/2)+(15/2);
            }
            else if(CursorOnRight)
            {
                rect.w += add;
                Update_Windows_Position(add/2,0);
                // Update_Position(add/2,0);
                header.x = rect.x;
                cross.x = rect.x-(rect.w/2) + (rect.w-7);
                header.w += add;
            }
            else
            {
                rect.w -= add;
                Update_Windows_Position(add/2,0);
                // Update_Position(add/2,0);
                header.x = rect.x;
                cross.x = rect.x-(rect.w/2) + (rect.w-7);
                header.w -= add;
            }
        }
        void Update_Windows_Position(const float& addx, const float& addy)
        {
            float XY_dif [Widget_List.size()][2];
            for(int i = 0; i < Widget_List.size(); i++)
            {
                XY_dif[i][0] =  Widget_List[i]->rect.x - (rect.x-(rect.w/2));
                XY_dif[i][1] =  Widget_List[i]->rect.y - (rect.y-(rect.h/2));
                // XY_dif[i][0] = (rect.x-(rect.w/2)) - Widget_List[i]->rect.x;
                // XY_dif[i][1] = (rect.y-(rect.h/2)) - Widget_List[i]->rect.y;
            }

            rect.x += addx;
            rect.y += addy;
            header.x += addx;
            header.y += addy;
            cross.x += addx;
            cross.y += addy;
            this->check_visibility();

            for(int i = 0; i < Widget_List.size(); i++)
            {
                Widget_List[i]->rect.x = (rect.x-(rect.w/2)) + XY_dif[i][0];
                Widget_List[i]->rect.y = (rect.y-(rect.h/2)) + XY_dif[i][1];
                Widget_List[i]->max_width = (rect.x + (rect.w/2));
                Widget_List[i]->max_height = (rect.y+ (rect.h/2));
                Widget_List[i]->min_width = (rect.x - (rect.w/2));
                if(isHeaderVisible) Widget_List[i]->min_height = (rect.y - (rect.h/2)) +15;
                else Widget_List[i]->min_height = (rect.y - (rect.h/2));
                Widget_List[i]->check_visibility();
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
                widgets->max_width = (rect.x + (rect.w/2));
                widgets->max_height = (rect.y+ (rect.h/2));
                widgets->min_width = (rect.x - (rect.w/2));
                if(isHeaderVisible) widgets->min_height = (rect.y - (rect.h/2)) +15;
                else widgets->min_height = (rect.y - (rect.h/2));
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
        
        void DrawResizeArrow(const int& side,SDL_Renderer * render)
        {
            float size = 30;
            float ArrowSize = 4;

            if(side == 1 || side == 3)
            {
                for(int i = mx - (size/2) + ArrowSize; i <=  mx + (size/2) - ArrowSize; i++)
                {
                    for(int j = my-1; j <= my+1; j++)
                    {
                        SDL_RenderPoint(render,i,j);
                    }
                }

                for(int i = mx - (size/2), add = 0; i < mx - (size/2) + ArrowSize; i++, add++)
                {
                    for(int j = my-add; j <= my+add; j++)
                    {
                        SDL_RenderPoint(render,i,j);
                    }
                }

                for(int i = mx + (size/2), add = 0; i > mx + (size/2) - ArrowSize; i--, add++)
                {
                    for(int j = my-add; j <= my+add; j++)
                    {
                        SDL_RenderPoint(render,i,j);
                    }
                }
            }
            else if(side == 2 || side == 4)
            {
                for(int i = mx-1; i <= mx+1; i++)
                {
                    for(int j = my - (size/2) + ArrowSize; j <= my + (size/2) - ArrowSize; j++)
                    {
                        SDL_RenderPoint(render,i,j);
                    }
                }

                for(int j = my - (size/2), add = 0; j < my - (size/2) + ArrowSize; j++, add++)
                {
                    for(int i = mx-add; i <= mx+add; i++)
                    {
                        SDL_RenderPoint(render,i,j);
                    }
                }

                for(int j = my + (size/2), add = 0; j > my + (size/2) - ArrowSize; j--, add++)
                {
                    for(int i = mx-add; i <= mx+add; i++)
                    {
                        SDL_RenderPoint(render,i,j);
                    }
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
                for(int i = cross.x - (cross.w/2),j = cross.y - (cross.h/2); i <= cross.x + (cross.w/2) && j <= cross.y + (cross.h/2); i++,j++)
                { SDL_RenderPoint(renderer,i,j); }
                for(int i = cross.x + (cross.w/2),j = cross.y-(cross.h/2); i >= cross.x - (cross.w/2) && j <= cross.y+ (cross.h/2); i--,j++)
                { SDL_RenderPoint(renderer,i,j); }
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                RenderRect(renderer, cross,max_width,max_height,min_width,min_height);
                for(auto widget : Widget_List) widget->draw(renderer);
                if(CursorOnDown || CursorOnLeft || CursorOnRight || CursorOnUp)
                {
                    auto side = [this] ()
                    {
                        if(CursorOnDown) return 4;
                        else if(CursorOnLeft)  return 1;
                        else if(CursorOnRight) return 3;
                        else return 2;
                    };

                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    DrawResizeArrow(side(),renderer);
                }
            }
        }

        void handleEvent(SDL_Event* event) override
        {
            if(isOpend)
            { 
                if(isPressed && event->type == SDL_EVENT_MOUSE_MOTION && isOverheader && !CursorOnUp && !fixed && isVisible)
                { Update_Position(event->motion.x - mx,event->motion.y - my); }

                if(event->type == SDL_EVENT_MOUSE_MOTION && isMiddlePressed && isOver && !isOverheader && isVisible && canMove)
                { Update_Element_Position(event->motion.x-mx,event->motion.y-my); }

                if(event->type == SDL_EVENT_MOUSE_MOTION && isVisible && isPressed && (CursorOnDown || CursorOnLeft || CursorOnRight || CursorOnUp))
                { Resize( (CursorOnDown || CursorOnUp) ? event->motion.y - my : event->motion.x - mx); }

                if(event->type == SDL_EVENT_MOUSE_MOTION && isVisible)
                {
                    mx = event->motion.x;
                    my = event->motion.y;

                    isOvercross = ((mx >= cross.x- (cross.w/2) && mx <= cross.x+(cross.w/2)) && (my >= cross.y - (cross.h/2) && my <= cross.y+(cross.h/2)));
                    isOver = (mx >= rect.x - (rect.w/2) && mx <= rect.x + (rect.w/2) && my >= rect.y - (rect.h/2) && my <= rect.y + (rect.h/2));

                    CursorOnDown = isOver && ((my >= (rect.y + (rect.h/2)-2)) && my <= (rect.y + (rect.h/2)+2));
                    CursorOnLeft = isOver && ((mx >= (rect.x-(rect.w/2)-2)) && (mx <= (rect.x-(rect.w/2)+2)));
                    CursorOnRight = isOver && (mx >= (rect.x + (rect.w/2)-2)) && mx <= (rect.x + (rect.w/2)+2);
                    CursorOnUp = isOver && !isOvercross && ((my >= (rect.y-(rect.h/2)-2)) && (my <= (rect.y-(rect.h/2)+5)));
    
                    if(isHeaderVisible) isOverheader = !CursorOnUp && ((mx >= header.x-(header.w/2) && mx <= cross.x - (cross.w/2)) && (my >= header.y - (header.h/2)+5 && my <= header.y + (header.h/2))) ? true : false;
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

                if(event->type == SDL_EVENT_MOUSE_WHEEL && isOver && !isOverheader && isVisible && canScroll)
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