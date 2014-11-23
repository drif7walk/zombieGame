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

class SpriteHandler
{
private:
	std::shared_ptr<SDL_Renderer> renderer;





	void LoadSpritesFromList(std::shared_ptr<SDL_Renderer> ren,	
		std::shared_ptr<std::map<std::string, std::shared_ptr< Sprite > > > sprmap);

	void spawn();

public:

	std::shared_ptr< std::map< std::string, std::shared_ptr<Sprite> > > sprites;
	std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entities;
	std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnList;



	void Initialize(std::shared_ptr<UI> ui);

	void Update(std::shared_ptr<UI> ui, double frameTime);

	SpriteHandler(std::shared_ptr<SDL_Renderer> renderer);
	~SpriteHandler();

};


#endif
