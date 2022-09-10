#ifndef GAME_H
#define GAME_H

#include "Entity.h"


#define ERR_SDL_INIT 1
#define ERR_CREATE_WIN 2
#define ERR_CREATE_REND 3
#define ERR_LOAD_RES 4
#define ERR_UNLOAD_RES 5


class Game {
private:
    int WIDTH = 0, HEIGHT = 0;
    SDL_Window* window = NULL;
    SDL_Event event;
    bool isRunning = false;

    SDL_Rect rect;
    bool clicked = false;

public:
    SDL_Renderer* renderer = NULL;
    SDL_Texture* backgroundTex = NULL;
    SDL_Texture* playerTex = NULL;
    Player* player;
    Entity* background;

    Game(int WIDTH, int HEIGHT) : WIDTH(WIDTH), HEIGHT(HEIGHT) {};

    const bool running(void) { return isRunning; }

    int init(const char* title, int width, int height)
    {
        int ret = SDL_Init(SDL_INIT_EVERYTHING);
        if (ret != 0)
        {
            printf("Couldn't initialize SDL: %s.\n", SDL_GetError());
            return ERR_SDL_INIT;
        }

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
        if (window == NULL)
        {
            printf("Couldn't create a window: %s.\n", SDL_GetError());
            return ERR_CREATE_WIN;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer == NULL)
        {
            printf("Couldn't create a renderer: %s.\n", SDL_GetError());
            return ERR_CREATE_REND;
        }

        isRunning = true;
        return 0;
    }

    int loadResources(void)
    {
        backgroundTex = loadTexture(renderer, "assets//grass_path.png");
        playerTex = loadTexture(renderer, "assets//player.png");

        background = new Entity(backgroundTex, 64, 64);
        player = new Player(playerTex, 64, 64);

        return 0;
    }

    int unloadResources(void)
    {
        delete background;
        delete player;

        SDL_DestroyTexture(backgroundTex);
        SDL_DestroyTexture(playerTex);

        return 0;
    }

    void prepareScene(void)
    {
        SDL_SetRenderDrawColor(renderer, 0, 128, 0, 0);
        SDL_RenderClear(renderer);

        background->setPos(100, 200);
        background->draw(renderer);
        player->draw(renderer);

        SDL_RenderPresent(renderer);
    }

    void handleInput(void)
    {
        // SDL_GetMouseState(&(rect.x), &(rect.y));

        while (SDL_PollEvent(&event))
        {
            // const Uint8* state = SDL_GetKeyboardState(NULL);

            if (SDL_QUIT == event.type)
                isRunning = false;

            if (SDL_KEYDOWN == event.type && event.key.repeat == 0)
            {

                if (SDLK_UP == event.key.keysym.sym)
                    player->vy += -1.0f;

                if (SDLK_DOWN == event.key.keysym.sym)
                    player->vy += 1.0f;

                if (SDLK_LEFT == event.key.keysym.sym)
                    player->vx += -1.0f;

                if (SDLK_RIGHT == event.key.keysym.sym)
                    player->vx += 1.0f;
            }

            if (SDL_KEYUP == event.type)
            {
                if (SDLK_UP == event.key.keysym.sym)
                    player->vy = 0.0f;

                if (SDLK_DOWN == event.key.keysym.sym)
                    player->vy = 0.0f;

                if (SDLK_LEFT == event.key.keysym.sym)
                    player->vx = 0.0f;

                if (SDLK_RIGHT == event.key.keysym.sym)
                    player->vx = 0.0f;
            }
        }
    }


    void update(void)
    {
        player->update();
    }

    void draw(void)
    {
        SDL_SetRenderDrawColor(renderer, 128, 0, 64, 0);

        // SDL_SetRenderDrawColor(renderer, 64, 64, 0, 0);
        // SDL_RenderFillRect(renderer, &rects[i]);

        SDL_RenderPresent(renderer);
    }

    void quit(void)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    static SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file)
    {
        SDL_Surface* tempSurf = IMG_Load(file);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurf);
        SDL_FreeSurface(tempSurf);
        return tex;
    }

};

#endif  // GAME_H