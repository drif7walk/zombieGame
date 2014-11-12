#include "zombie.h"

void Zombie::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
	std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites)
{
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
				+ pow(this->locationVec.y - (*it)->locationVec.x, 2)) < 200)
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
}

Zombie::Zombie(std::string filename, SDL_Renderer* ren) : Sprite(filename, ren) {
	maxVelocity = 1.2f;
	healthPoints = 1;
	playerFound = false;
}

void Zombie::setDirection(Vector direction)
{
	float angle = direction.angle();

	if (angle >= 45 && angle < 135)
	{
		this->direction = 0;
		return;
	}
	if (angle >= 135 && angle < 225)
	{
		this->direction = 3;
		return;
	}
	if (angle >= 225 && angle < 315)
	{
		this->direction = 2;
		return;
	}
	if ((angle >= 315 && angle <= 360) || (angle >= 0 && angle < 45))
	{
		this->direction = 1;
		return;
	}
}