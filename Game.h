#ifndef GAME_H
#define GAME_H

#include "Entity.h"


#define ERR_SDL_INIT 1
#define ERR_CREATE_WIN 2
#define ERR_CREATE_REND 3
#define ERR_LOAD_RES 4
#define ERR_UNLOAD_RES 5


class Game
{
	int WIDTH = 0, HEIGHT = 0;
	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;
	SDL_Event event;
	bool isRunning = false;

	SDL_Rect rect{ 0,0,0,0 };
	bool clicked = false;

	Player* player = nullptr;
	Entity* tile = nullptr;
	Entity* background = nullptr;

public:
	Game() = default;

	const bool running(void);
	int init(const char* title, int width, int height);
	int loadResources(void);
	int unloadResources(void);
	void prepareScene(void);
	void handleInput(void);
	void update(void);
	void draw(void);
	void quit(void);
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file);
};

#endif  // GAME_H