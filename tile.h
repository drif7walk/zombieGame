#ifndef TILE_H
#define TILE_H


#include "sprite.h"
#include "UI.h"

class Tile: public Sprite {

private:

public:
	void Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime) override;
	
	Tile(Sprite* templatesprite) ;
	Tile(std::string filename, SDL_Renderer* ren);
};

#endif
