#include "zombie.h"

<<<<<<< HEAD
#include "magazine.h"

void Zombie::Update(double deltaTime, std::shared_ptr<UI> ui,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
		std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites) 
=======
void Zombie::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
	std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites)
>>>>>>> parent of 7bd50a5... magazine update for rapid fire mode
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

<<<<<<< HEAD
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
				spawnlist->push_back(std::make_shared< Magazine >(sprites->operator[]("magazine")));
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
=======
	/* Stalk player */
	double stepx = 0;
	double stepy = 0;
	bool playerIsAlive = false;
	for (std::vector<Sprite*>::iterator it = entlist->begin(); it != entlist->end(); it++)
>>>>>>> parent of 7bd50a5... magazine update for rapid fire mode
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

<<<<<<< HEAD
Zombie::Zombie(std::shared_ptr< Sprite > templatesprite) : Sprite(templatesprite)  {
	maxVelocity = 2.2f;
=======
Zombie::Zombie(Sprite* templatesprite) : Sprite(templatesprite)  {
	maxVelocity = 1.2f;
>>>>>>> parent of 7bd50a5... magazine update for rapid fire mode
	healthPoints = 1;
	playerFound = false;
	scale = 2;
}

<<<<<<< HEAD
Zombie::Zombie(std::string filename, std::shared_ptr< SDL_Renderer > ren) : Sprite(filename, ren) {
	maxVelocity = 2.2f;
	healthPoints = 3;
=======
Zombie::Zombie(std::string filename, SDL_Renderer* ren) : Sprite(filename, ren) {
	maxVelocity = 1.2f;
	healthPoints = 1;
>>>>>>> parent of 7bd50a5... magazine update for rapid fire mode
	playerFound = false;
}
