#include <stdio.h>
#include <SDL2/SDL.h>
#include "Game.h"
#undef main


const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[]) {
    // std::ios_base::sync_with_stdio(0);
    // std::cin.tie(0);
 
    Game game(WIDTH, HEIGHT);
    game.init("Tell Your Tale", WIDTH, HEIGHT);

    game.loadResources(); // initStage

    while (game.running()) {  // Input, Update, Draw
        // Input
        game.prepareScene();
        game.handleInput();
        game.update();
        game.draw();

        SDL_Delay(16);
    }

    game.quit();

    return EXIT_SUCCESS;
}