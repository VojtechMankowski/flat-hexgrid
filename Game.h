#ifndef GAME_H
#define GAME_H

#define ERR_SDL_INIT 1
#define ERR_CREATE_WIN 2
#define ERR_CREATE_REND 3

class Game {
public:
    Game(int WIDTH, int HEIGHT) : WIDTH(WIDTH), HEIGHT(HEIGHT) {};
    SDL_Renderer* renderer = NULL;

private:
    int WIDTH = 0, HEIGHT = 0;
    SDL_Window* window = NULL;
    SDL_Event event;
    bool isRunning = false;

    SDL_Rect rect;
    SDL_Rect* rects = nullptr;
    bool clicked = false;
    int rect_count = 0, rect_curr = 0;
    const int N = 5;

public:
    const bool running(void) { return isRunning; }

    int init(const char* title, int width, int height)
    {
        int ret = SDL_Init(SDL_INIT_EVERYTHING);
        if (ret != 0) 
        {
            printf("Couldn't initialize SDL: %s.\n", SDL_GetError());
            return ERR_SDL_INIT;
        }
        
        window = SDL_CreateWindow("Flat Hexagon Grid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
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
        rect = createRect(0, 0, 50, 50);

        rects = new SDL_Rect[N];
        for (int i = 0; i < N; i++)
        {
            rects[i] = createRect(0, 0, 100, 50);
        }
        rect_count = 0;
        rect_curr = 0;
        clicked = false;

        return 0;
    }

    void prepareScene(void)
    {
        SDL_SetRenderDrawColor(renderer, 0, 128, 0, 0);
        SDL_RenderClear(renderer);
    }

    void handleInput(void)
    {
        SDL_GetMouseState(&(rect.x), &(rect.y));

        while (SDL_PollEvent(&event))
        {
            if (SDL_QUIT == event.type)
                isRunning = false;

            if (SDL_MOUSEBUTTONUP == event.type)
            {
                if (clicked)
                {
                    SDL_GetMouseState(&(rects[rect_curr].x), &(rects[rect_curr].y));
                    rect_curr++;
                    if (rect_curr > rect_count)
                        rect_count = rect_curr;
                    if (rect_curr == N)
                    {
                        rect_curr = 0;
                        rect_count = N;
                    }
                    printf("curr: %d, count: %d\n", rect_curr, rect_count);
                }
                clicked = false;
            }

            if (SDL_MOUSEBUTTONDOWN == event.type)
                clicked = true;
        }
    }

    void update(void) {}

    void draw(void)
    {
        SDL_SetRenderDrawColor(renderer, 128, 0, 64, 0);
        SDL_RenderDrawLine(renderer, 0, 0, rect.x, rect.y);
        SDL_RenderDrawLine(renderer, WIDTH, 0, rect.x, rect.y);
        SDL_RenderDrawLine(renderer, 0, HEIGHT, rect.x, rect.y);
        SDL_RenderDrawLine(renderer, WIDTH, HEIGHT, rect.x, rect.y);

        SDL_SetRenderDrawColor(renderer, 128, 64, 0, 0);
        SDL_RenderDrawRect(renderer, &rect);

        for (int i = 0; i < rect_count; i++)
        {
            SDL_SetRenderDrawColor(renderer, 64, 64, 0, 0);
            SDL_RenderFillRect(renderer, &rects[i]);
        }

        // Draw
        SDL_RenderPresent(renderer);
    }

    void quit(void) {
        delete[] rects;

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    static SDL_Rect createRect(int x, int y, int w, int h)  //change to static void setRect(Rect&)
    {
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        return rect;
    }
};

#endif  // GAME_H