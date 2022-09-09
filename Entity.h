#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>


class Entity {

int x = 0, y = 0, w = 64, h = 64;
SDL_Rect srcRect, dstRect;
SDL_Texture* tex = NULL;

public:
Entity(SDL_Texture* tex, int w, int h)
{
    this->tex = tex;
    this->w = w;
    this->h = h;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = w;
    srcRect.h = h;

    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = w;
    dstRect.h = h;
}

void setPos(int x, int y)
{
    dstRect.x = x;
    dstRect.y = y;
}

void readPos(int x, int y)
{
    srcRect.x = x;
    srcRect.y = y;
}

void draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, tex, &srcRect, &dstRect);
}

};

#endif  // ENTITY_H