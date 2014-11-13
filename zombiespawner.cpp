#include "zombiespawner.h"
#include "zombie.h"

void Zombiespawner::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnlist, std::map<std::string, Sprite*>*sprites)
{
	/* spawn zombies */
	if (maxzombies > 0)
	{
		this->spawntimer++;
		if (this->spawntimer >= this->interval)
		{
			this->spawntimer = 0;

			spawnlist->push_back(new Zombie( sprites->operator[]("zombie") ));
			spawnlist->back()->locationVec.x = this->locationVec.x + rand() % 50 - 25;
			spawnlist->back()->locationVec.y = this->locationVec.y + rand() % 50 - 25;
			maxzombies--;

		}
	}
	FreezeStep(0);
}



Zombiespawner::Zombiespawner(Sprite* templatesprite): Sprite(templatesprite) 
{
	this->scale = 2;

}
Zombiespawner::Zombiespawner(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{

}

