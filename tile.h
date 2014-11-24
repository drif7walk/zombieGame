#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

#include "sprite.h"
#include "UI.h"

class Tile: public Sprite {

private:

public:
	void Update(double deltaTime, boost::shared_ptr<UI> ui,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > entlist,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > spawnlist,
		boost::shared_ptr< std::map < std::string, boost::shared_ptr< Sprite > > > sprites) override;

	Tile(boost::shared_ptr< Sprite > templatesprite) ;
	Tile(std::string filename, boost::shared_ptr< SDL_Renderer > ren);
};

#endif
