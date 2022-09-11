#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>


class Entity {
protected:
    SDL_Rect srcRect{ 0,0,0,0 };
    SDL_Rect dstRect{ 0,0,0,0 };
    SDL_Texture* tex = NULL;

public:
    int x = 0, y = 0, w = 64, h = 64;

public:
    Entity() = default;
    Entity(SDL_Texture* tex, int w, int h);
    void setPos(int x, int y);
    void setSize(int w, int h);
    void sourcePos(int x, int y);
    void sourceSize(int w, int h);
    void draw(SDL_Renderer* renderer);
    SDL_Texture* getTexture(void);
};


class Player : public Entity
{
public:
    float vx = 0.0f, vy = 0.0f, speed = 1.0f;

public:
    Player(SDL_Texture* tex, int w, int h);

    void setSpeed(float s);
    void update(void);
};

#endif  // ENTITY_H