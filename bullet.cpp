#include "bullet.h"

void Bullet::Update(std::vector<Sprite*>* entlist, double deltaTime)
{
Sprite::Update(entlist, deltaTime);
	this->FreezeStep(direction);

	if (direction == 0)
	{
		locationVec.y += velocity * deltaTime;
	}
		else if (direction == 1)
		{
			locationVec.x += velocity * deltaTime;
		}	
			else if (direction == 2)
			{
				locationVec.y += -velocity * deltaTime;
			}	
				else if (direction == 3)
				{
					locationVec.x += -velocity * deltaTime;
				}
}

Bullet::Bullet(Sprite* templatesprite, SDL_Point location, int direction): Sprite(templatesprite)  
{
	this->locationVec.x = location.x;
	this->locationVec.y = location.y;
	this->direction = direction;
	velocity = 30;
}

Bullet::Bullet(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{
	
}
