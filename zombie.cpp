#include "zombie.h"

void Zombie::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
	std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites)
{
	
	/* Play spawning animation */
	if (state == 0) 
	{
		if (framecount >= 3) 
		{
			state = 1;
			framecount = 0;
			return;
		}
		this->AnimateStep(8, deltaTime);
		return;
	}

	/* Stalk player */
	double stepx = 0;
	double stepy = 0;
	bool playerIsAlive = false;
	for (std::vector<Sprite*>::iterator it = entlist->begin(); it != entlist->end(); it++)
	{
		if (strcmp((*it)->name.c_str(), "player") == 0 && playerFound == true)
		{
			Vector playerVec((*it)->locationVec);
			directionVec = playerVec - locationVec;
			directionVec.normalize();
			directionVec = directionVec * 0.025f;
			accelerationVec = directionVec;

			velocityVec = velocityVec + accelerationVec;
			velocityVec.limit(maxVelocity);
			locationVec = locationVec + velocityVec * deltaTime;
			playerIsAlive = true;
		}
		if (strcmp((*it)->name.c_str(), "player") == 0)
		{
			if (sqrt(pow(this->locationVec.x - (*it)->locationVec.x, 2)
				+ pow(this->locationVec.y - (*it)->locationVec.x, 2)) < this->aggrodist)
			{
				playerFound = true;
			}
			playerIsAlive = true;
		}
	}
	if (playerFound == false || playerIsAlive == false)
	{
		directionVec.random();
		directionVec.normalize();
		directionVec = directionVec * 0.025f;
		accelerationVec = directionVec;

		velocityVec = velocityVec + accelerationVec;
		velocityVec.limit(maxVelocity);
		locationVec = locationVec + velocityVec * deltaTime;
	}

	setDirection(velocityVec);

	this->AnimateStep(direction, deltaTime);
}

Zombie::Zombie(Sprite* templatesprite) : Sprite(templatesprite)  {
	maxVelocity = 1.2f;
	healthPoints = 1;
	playerFound = false;
	scale = 2;
}

Zombie::Zombie(std::string filename, SDL_Renderer* ren) : Sprite(filename, ren) {
	maxVelocity = 1.2f;
	healthPoints = 1;
	playerFound = false;
}
