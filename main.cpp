#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#undef main


const int WIDTH = 800, HEIGHT = 600;
const int FPS = 60;
const int frameDelay = 1000 / FPS;  // [ms]

int main(int argc, char* argv[]) {
    // std::ios_base::sync_with_stdio(0);
    // std::cin.tie(0);

    unsigned int frameStart = 0;
    int frameTicks = 0;

    Game game(WIDTH, HEIGHT);
    game.init("Tell Your Tale", WIDTH, HEIGHT);

    game.loadResources(); // initStage

    while (game.running()) {  // Input, Update, Draw

        frameStart = SDL_GetTicks();

        // Input
        game.prepareScene();
        game.handleInput();
        game.update();
        game.draw();

        // Limit FPS
        frameTicks = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTicks) {
            SDL_Delay(frameDelay - frameTicks);
        }
        
        frameTicks = SDL_GetTicks() - frameStart;
        printf("%d ms, ( %.2f FPS)\n", frameTicks, 1000.0f/frameTicks );
    }

    game.quit();

    return EXIT_SUCCESS;
}