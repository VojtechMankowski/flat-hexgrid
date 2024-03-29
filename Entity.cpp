#include "Entity.h"

Entity::Entity(SDL_Texture* tex, int w, int h)
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

void Entity::setPos(int x, int y)
{
	dstRect.x = x;
	dstRect.y = y;
}

void Entity::setSize(int w, int h)
{
	dstRect.w = w;
	dstRect.h = h;
}

void Entity::sourcePos(int x, int y)
{
	srcRect.x = x;
	srcRect.y = y;
}

void Entity::sourceSize(int w, int h)
{
	srcRect.w = w;
	srcRect.h = h;
}

void Entity::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, tex, &srcRect, &dstRect);
}

SDL_Texture* Entity::getTexture(void)
{
	return tex;
}

Player::Player(SDL_Texture* tex, int w, int h)
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

void Player::setSpeed(float s)
{
	speed = s;
}

void Player::update(void)
{
	dstRect.x += static_cast<int>(vx * speed);
	dstRect.y += static_cast<int>(vy * speed);
}
