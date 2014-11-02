#include "zombie.h"

void Zombie::Update(std::vector<Sprite*>* entlist, double deltaTime)
{
Sprite::Update(entlist, deltaTime);

	double stepx = 0;
	double stepy = 0;
	for (std::vector<Sprite*>::iterator it = entlist->begin(); it != entlist->end(); it++)
	{
		
		if (strcmp((*it)->name.c_str(), "player") == 0)
		{
			Vector playerVec((*it)->locationVec);
			directionVec = playerVec - locationVec;
			directionVec.normalize();
			directionVec = directionVec * 0.025f;//0.5f magic number do not touch
			accelerationVec = directionVec;

			velocityVec = velocityVec + accelerationVec;
			velocityVec = velocityVec;
			velocityVec.limit(maxVelocity);
			locationVec = locationVec + velocityVec * deltaTime;

			bool y_x = this->locationVec.y - (*it)->locationVec.y - frameheight / 2 < this->locationVec.x - (*it)->locationVec.x + framewidth / 2;
			bool yx = this->locationVec.y - (*it)->locationVec.y - frameheight / 2 > -1 * (this->locationVec.x - (*it)->locationVec.x + framewidth / 2);
				/* change break to continue for multiple follow */
			if (y_x && yx)
			{
				this->direction = 3;
				break;
			}
			if (!y_x && yx)
			{
				this->direction = 2;
				break;
			}
			if (y_x && !yx)
			{
				this->direction = 0;
				break;
			}
			else
			{
				this->direction = 1;
				break;
			}
		}
	}
	this->AnimateStep(direction, deltaTime);
	this->locationVec.x += stepx * deltaTime;
	this->locationVec.y += stepy * deltaTime;
}

Zombie::Zombie(Sprite* templatesprite) : Sprite(templatesprite)  {
	maxVelocity = 1.2f;
}

Zombie::Zombie(std::string filename, SDL_Renderer* ren) : Sprite(filename, ren) {
	maxVelocity = 1.2f;
}
