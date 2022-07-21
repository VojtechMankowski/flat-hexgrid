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
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 300;
    rect.h = 400;

    while (true) {
        SDL_RenderClear(renderer);

        SDL_PollEvent(&event);
        if (SDL_QUIT == event.type)
            break;

        


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return EXIT_SUCCESS;
}