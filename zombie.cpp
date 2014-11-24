#include "zombie.h"

#include "magazine.h"

void Zombie::Update(double deltaTime, boost::shared_ptr<UI> ui,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > entlist,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > spawnlist,
		boost::shared_ptr< std::map < std::string, boost::shared_ptr< Sprite > > > sprites)
{
	/* Do not update if destroyed */
	if (this->destroyed)
	{
		return;
	}

	/* Play spawning animation */
	if (this->state == 0)
	{
		if (this->framecount >= 3)
		{
			this->state = 1;
			this->framecount = 0;
			return;
		}
		this->AnimateStep(8, deltaTime);
		return;
	}

	if (this->state == 2)
	{
		this->animSpeed = 1.2;
		/* XXX: Death animation repeats first frame if 3 - why? */
		if (this->framecount > 2)
		{
			ui->AddKill();
			this->destroyed = true;

			if (rand() % 50 == 0)
			{
				spawnlist->push_back(boost::make_shared< Magazine >(sprites->operator[]("magazine")));
				spawnlist->back()->locationVec = this->locationVec;
			}

			return;
		}
		this->AnimateStep(9, deltaTime);
		return;
	}

	/* Check health */
	if (this->healthPoints <= 0)
	{
		this->state = 2;
		this->framecount = 0;
		return;
	}

	/* Stalk player */

	auto playerIsAlive = false;
	for (auto it = entlist->begin(); it != entlist->end(); it++)
	{
		if (strcmp((*it)->name.c_str(), "player") == 0 && playerFound == true)
		{
			auto playerVec((*it)->locationVec);
			directionVec = playerVec - locationVec;
			directionVec.normalize();
			directionVec = directionVec * 0.025f;
			accelerationVec = directionVec;

			velocityVec = velocityVec + accelerationVec;
			velocityVec.limit(maxVelocity);
			locationVec = locationVec + velocityVec * deltaTime;
			playerIsAlive = true;
			break;
		}
		if (strcmp((*it)->name.c_str(), "player") == 0)
		{
			if (sqrt(pow(this->locationVec.x - (*it)->locationVec.x, 2)
				+ pow(this->locationVec.y - (*it)->locationVec.x, 2)) < this->aggrodist)
			{
				playerFound = true;
			}
			playerIsAlive = true;
			break;
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

Zombie::Zombie(boost::shared_ptr< Sprite > templatesprite) : Sprite(templatesprite)  {
	maxVelocity = 2.2f;
	healthPoints = 1;
	playerFound = false;
	scale = 3;
}

Zombie::Zombie(std::string filename, boost::shared_ptr< SDL_Renderer > ren) : Sprite(filename, ren) {
	maxVelocity = 2.2f;
	healthPoints = 3;
	playerFound = false;
}
