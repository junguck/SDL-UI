// gestion des couleur defini une fois dans le fichier .h
#pragma once
#include <SDL3/SDL.h>

struct Colors {
    static inline SDL_Color White = {255, 255, 255, 255};
    static inline SDL_Color Black = {0, 0, 0, 255};
    static inline SDL_Color Gray = {100, 100, 100, 255};
    static inline SDL_Color LightGray = {200, 200, 200, 255};
    static inline SDL_Color DarkGray = {50, 50, 50, 255};
    static inline SDL_Color Red = {255, 0, 0, 255};
    static inline SDL_Color Green = {0, 255, 0, 255};
    static inline SDL_Color Blue = {0, 0, 255, 255};
    static inline SDL_Color Yellow = {255, 255, 0, 255};
    static inline SDL_Color Cyan = {0, 255, 255, 255};
    static inline SDL_Color Magenta = {255, 0, 255, 255};
    static inline SDL_Color Orange = {255, 165, 0, 255};
    static inline SDL_Color Purple = {128, 0, 128, 255};
    static inline SDL_Color Navy = {0, 0, 128, 255};
    static inline SDL_Color Olive = {128, 128, 0, 255};
    static inline SDL_Color Maroon = {128, 0, 0, 255};
    static inline SDL_Color Silver = {192, 192, 192, 255};
    static inline SDL_Color Gold = {255, 215, 0, 255};
    static inline SDL_Color SkyBlue = {135, 206, 235, 255};
    static inline SDL_Color ForestGreen = {34, 139, 34, 255};
};