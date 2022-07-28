#include <stdio.h>
#include <SDL2/SDL.h>
#undef main

SDL_Rect createRect(int x, int y, int w, int h) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    return rect;
}

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
    SDL_Rect rect = {0, 0, 50, 50};

    const int N = 5;
    SDL_Rect rects[N];
    for (int i = 0; i < N; i++) {
        rects[i] = createRect(0, 0, 100, 50);
    }

    int rect_count = 0, rect_curr = 0;
    bool clicked = false;

    while (true) {  // Input, Update, Draw
        // Input
        SDL_GetMouseState(&(rect.x), &(rect.y));

        SDL_PollEvent(&event);
        if (SDL_QUIT == event.type)
            break;
        if (SDL_MOUSEBUTTONUP == event.type) {
            if (clicked) {
                SDL_GetMouseState(&(rects[rect_curr].x), &(rects[rect_curr].y));
                rect_curr++;
                if (rect_curr > rect_count) rect_count = rect_curr;
                if (rect_curr == N) {
                    rect_curr = 0;
                    rect_count = N;
                }
                printf("curr: %d, count: %d\n", rect_curr, rect_count);
            }
            clicked = false;
        }
        if (SDL_MOUSEBUTTONDOWN == event.type)
            clicked = true;
        
        // Update 
        SDL_SetRenderDrawColor(renderer, 0, 128, 0, 0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 128, 0, 64, 0);
        SDL_RenderDrawLine(renderer, 0, 0, rect.x, rect.y);
        SDL_RenderDrawLine(renderer, WIDTH, 0, rect.x, rect.y);
        SDL_RenderDrawLine(renderer, 0, HEIGHT, rect.x, rect.y);
        SDL_RenderDrawLine(renderer, WIDTH, HEIGHT, rect.x, rect.y);

        SDL_SetRenderDrawColor(renderer, 128, 64, 0, 0);
        SDL_RenderDrawRect(renderer, &rect);
        
        for (int i=0; i < rect_count; i++) {
            SDL_SetRenderDrawColor(renderer, 64, 64, 0, 0);
            SDL_RenderFillRect(renderer, &rects[i]);
        }

        // Draw
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return EXIT_SUCCESS;
}