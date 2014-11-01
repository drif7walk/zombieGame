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
			bool y_x = this->y - (*it)->y - frameheight / 2 < this->x - (*it)->x + framewidth / 2;
			bool yx = this->y - (*it)->y - frameheight / 2 > -1 * (this->x - (*it)->x + framewidth / 2);
				/* change break to continue for multiple follow */
			if (y_x && yx)
			{
				this->direction = 3;
				stepx -= 1;
				break;
			}
			if (!y_x && yx)
			{
				this->direction = 2;
				stepy -= 1;
				break;
			}
			if (y_x && !yx)
			{
				this->direction = 0;
				stepy += 1;
				break;
			}
			else
			{
				this->direction = 1;
				stepx += 1;
				break;
			}
		}
	}
	this->AnimateStep(direction, deltaTime);
	this->x += stepx * deltaTime;
	this->y += stepy * deltaTime;
}

Zombie::Zombie(Sprite* templatesprite): Sprite(templatesprite)  {}
Zombie::Zombie(std::string filename, SDL_Renderer* ren): Sprite(filename, ren) {}
