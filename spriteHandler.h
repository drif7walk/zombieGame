#ifndef SPRITEHANDLER_H
#define SPRITEHANDLER_H

#include <map>
#include <vector>
#include <time.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>

#include "sprite.h"
#include "player.h"
#include "cursor.h"
#include "bullet.h"
#include "zombie.h"
#include "tile.h"
#include "UI.h"
#include "zombiespawner.h"
#include "magazine.h"

class SpriteHandler
{
private:
	boost::shared_ptr<SDL_Renderer> renderer;

	bool playerIsAlive = true;

	void LoadSpritesFromList(boost::shared_ptr<SDL_Renderer> ren,
		boost::shared_ptr<std::map<std::string, boost::shared_ptr< Sprite > > > sprmap);

	void spawn();

public:

	boost::shared_ptr< std::map< std::string, boost::shared_ptr<Sprite> > > sprites;
	boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > entities;
	boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > spawnList;



	void Initialize(boost::shared_ptr<UI> ui);

	void Update(boost::shared_ptr<UI> ui, double frameTime);

	SpriteHandler(boost::shared_ptr<SDL_Renderer> renderer);
	~SpriteHandler();

};


#endif
