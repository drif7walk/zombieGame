#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "sprite.h"
#include "UI.h"

class Tile: public Sprite {

private:

public:
	void Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites) override;
	
	Tile(Sprite* templatesprite) ;
	Tile(std::string filename, SDL_Renderer* ren);
};

#endif
