#ifndef ZOMBIESPAWNER_H
#define ZOMBIESPAWNER_H

#include <SDL2/SDL.h>

#include "sprite.h"
#include "UI.h"

class Zombiespawner: public Sprite {

private:

public:
	int interval = 60;
	int spawntimer = 0;
	int maxzombies = 50;

	void Update(double deltaTime, boost::shared_ptr<UI> ui,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > entlist,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > spawnlist,
		boost::shared_ptr< std::map < std::string, boost::shared_ptr< Sprite > > > sprites) override;

	Zombiespawner(boost::shared_ptr< Sprite > templatesprite) ;
	Zombiespawner(std::string filename, boost::shared_ptr< SDL_Renderer > ren);

};

#endif


