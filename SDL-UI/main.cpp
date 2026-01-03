//main de teste des objects 
//ce main gere deja la fenetre et aussi la gestion des UI mais on prevoit
//faire un classe pour la gestion des UI
//on va afficher un cercle ou un carre avec un bouttons
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include "Colors.hpp"
#include "Button.hpp"

enum Shape { RECTANGLE, CIRCLE };
Shape currentShape = RECTANGLE;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Ma Bibliothèque UI SDL3", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    TTF_Font* font = TTF_OpenFont("arial.ttf", 18);

    std::vector<Widget*> uiElements;

    // --- Tableau de bord (Panel gauche) ---
    auto btnRect = new Button(20, 50, 150, 40, "Rectangle", font, []() {
        currentShape = RECTANGLE;
    });
    
    auto btnCircle = new Button(20, 110, 150, 40, "Cercle", font, []() {
        currentShape = CIRCLE;
    });

    uiElements.push_back(btnRect);
    uiElements.push_back(btnCircle);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            for (auto w : uiElements) w->handleEvent(&event);
        }

        // Rendu
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // Fond sombre
        SDL_RenderClear(renderer);

        // Dessiner le panneau latéral
        SDL_FRect panel = {0, 0, 200, 600};
        SDL_SetRenderDrawColor(renderer, 45, 45, 45, 255);
        SDL_RenderFillRect(renderer, &panel);

        // Dessiner la Scène (Zone de droite)
        SDL_SetRenderDrawColor(renderer, Colors.SkyBlue.r, Colors.SkyBlue.g, Colors.SkyBlue.b, 255);
        if (currentShape == RECTANGLE) {
            SDL_FRect r = {400, 200, 200, 200};
            SDL_RenderFillRect(renderer, &r);
        } else {
            // SDL3 a des fonctions de dessin de points pour les cercles ou utiliser une texture
            SDL_FRect r = {400, 200, 200, 200}; // Simulé par un carré pour l'exemple
            SDL_RenderRect(renderer, &r); 
        }

        // Dessiner l'UI
        for (auto w : uiElements) w->draw(renderer);

        SDL_RenderPresent(renderer);
    }

    // Nettoyage
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}