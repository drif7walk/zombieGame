#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "sprite.h"
#include "UI.h"

class Tile: public Sprite {

private:

public:
	void Update(double deltaTime, std::shared_ptr<UI> ui,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
		std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites) override;
	
	Tile(std::shared_ptr< Sprite > templatesprite) ;
	Tile(std::string filename, std::shared_ptr< SDL_Renderer > ren);
};

#endif
