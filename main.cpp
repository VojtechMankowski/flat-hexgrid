#include <stdio.h>
#include <SDL2/SDL.h>
#undef main

const int WIDTH = 800, HEIGHT = 600;


int main(int argc, char* argv[]) {

    // std::ios_base::sync_with_stdio(0);
    // std::cin.tie(0);

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Flat Hexagon Grid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    if (NULL == window) {
        printf("Couldn't create a window: %s.\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;
    SDL_Rect rect, rect2;
    rect.x = 220;
    rect.y = 330;
    rect.w = 100;
    rect.h = 50;
    
    const int N = 10;
    SDL_Rect rects[N];

    for (int i = 0; i < N; i++) {
        rect2.x = 0;
        rect2.y = 0;
        rect2.w = 100;
        rect2.h = 50;
    }
    int rect_count = 0;
    bool clicked = false;

    while (true) {
        SDL_SetRenderDrawColor(renderer, 0, 128, 0, 0);
        SDL_RenderClear(renderer);

        SDL_GetMouseState(&(rect.x), &(rect.y));

        SDL_PollEvent(&event);
        if (SDL_QUIT == event.type)
            break;
        if (SDL_MOUSEBUTTONUP == event.type) {
            if (clicked) {
                SDL_GetMouseState(&(rect2.x), &(rect2.y));
                SDL_SetRenderDrawColor(renderer, 64, 64, 0, 0);
                SDL_RenderDrawRect(renderer, &rect2);
            }
            clicked = false;
        }
        if (SDL_MOUSEBUTTONDOWN == event.type)
            clicked = true;
        
        SDL_SetRenderDrawColor(renderer, 128, 0, 64, 0);
        SDL_RenderDrawLine(renderer, 0, 0, rect.x, rect.y);
        SDL_RenderDrawLine(renderer, WIDTH, 0, rect.x, rect.y);
        SDL_RenderDrawLine(renderer, 0, HEIGHT, rect.x, rect.y);
        SDL_RenderDrawLine(renderer, WIDTH, HEIGHT, rect.x, rect.y);

        SDL_SetRenderDrawColor(renderer, 128, 64, 0, 0);
        SDL_RenderDrawRect(renderer, &rect);
        
        SDL_SetRenderDrawColor(renderer, 64, 64, 0, 0);
        SDL_RenderFillRect(renderer, &rect2);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return EXIT_SUCCESS;
}