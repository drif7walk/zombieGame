#include "bullet.h"

void Bullet::Update(std::vector<Sprite*>* entlist, double deltaTime)
{
Sprite::Update(entlist, deltaTime);
	this->FreezeStep(direction);
}

Bullet::Bullet(Sprite* templatesprite, SDL_Point location, int direction): Sprite(templatesprite)  
{
	this->x = location.x;
	this->y = location.y;
	this->direction = direction;
}

Bullet::Bullet(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{
	
}
