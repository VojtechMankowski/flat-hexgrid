#include "Game.h"
#include <stdio.h>
#include <SDL_image.h>


const bool Game::running(void)
{ 
	return isRunning;
}

int Game::init(const char* title, int width, int height)
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

int Game::loadResources(void)
{
	SDL_Texture* tmp = NULL;
	
	tmp = loadTexture(renderer, "assets//map-tile-v1-tile-map.png");
	background = new Entity(tmp, 2*568, 2*329);
	background->sourceSize(568, 329);

	tmp = loadTexture(renderer, "assets//grass_path.png");
	tile = new Entity(tmp, 64, 64);

	tmp = loadTexture(renderer, "assets//player.png");
	player = new Player(tmp, 64, 64);

	return 0;
}

int Game::unloadResources(void)
{
	SDL_DestroyTexture(background->getTexture());
	SDL_DestroyTexture(tile->getTexture());
	SDL_DestroyTexture(player->getTexture());

	delete background;
	delete player;
	delete tile;

	return 0;
}

void Game::prepareScene(void)
{
	// set green background
	SDL_SetRenderDrawColor(renderer, 0, 128, 0, 0);
	SDL_RenderClear(renderer);
}

void Game::handleInput(void)
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

void Game::update(void)
{
	player->update();
}

void Game::draw(void)
{
	background->draw(renderer);
	tile->setPos(100, 200);
	tile->draw(renderer);
	player->draw(renderer);

	// SDL_SetRenderDrawColor(renderer, 64, 64, 0, 0);
	// SDL_RenderFillRect(renderer, &rects[i]);

	SDL_RenderPresent(renderer);
}

void Game::quit(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

SDL_Texture* Game::loadTexture(SDL_Renderer* renderer, const char* file)
{
	SDL_Surface* tempSurf = IMG_Load(file);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurf);
	SDL_FreeSurface(tempSurf);
	return tex;
}
