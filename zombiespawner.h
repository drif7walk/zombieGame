#ifndef ZOMBIESPAWNER_H
#define ZOMBIESPAWNER_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "sprite.h"
#include "UI.h"

class Zombiespawner: public Sprite {

private:

public:
	int interval = 60;
	int spawntimer = 0;
	int maxzombies = 50;

	void Update(double deltaTime, std::shared_ptr<UI> ui,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
		std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites) override;

	Zombiespawner(std::shared_ptr< Sprite > templatesprite) ;
	Zombiespawner(std::string filename, std::shared_ptr< SDL_Renderer > ren);

};

#endif


