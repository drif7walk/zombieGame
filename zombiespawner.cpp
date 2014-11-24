#include "zombiespawner.h"
#include "zombie.h"

void Zombiespawner::Update(double deltaTime, boost::shared_ptr<UI> ui,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > entlist,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > spawnlist,
		boost::shared_ptr< std::map < std::string, boost::shared_ptr< Sprite > > > sprites)
{
	/* spawn zombies */
	if (maxzombies > 0)
	{
		this->spawntimer++;
		if (this->spawntimer >= this->interval)
		{
			this->spawntimer = 0;

			spawnlist->push_back(boost::make_shared< Zombie >(sprites->operator[]("zombie") ));
			spawnlist->back()->locationVec.x = this->locationVec.x + rand() % 50 - 25;
			spawnlist->back()->locationVec.y = this->locationVec.y + rand() % 50 - 25;
			maxzombies--;

		}
	}
	FreezeStep(0);
}



Zombiespawner::Zombiespawner(boost::shared_ptr< Sprite > templatesprite): Sprite(templatesprite)
{
	this->scale = 2;

}
Zombiespawner::Zombiespawner(std::string filename, boost::shared_ptr< SDL_Renderer > ren): Sprite(filename, ren)
{

}

