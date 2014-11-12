#include "tile.h"

#include <SDL.h>

void Tile::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites)
{
	FreezeStep(0);
}

Tile::Tile(Sprite* templatesprite) : Sprite(templatesprite)  
{
	this->plane = 0; 
}

Tile::Tile(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{
	SDL_ShowCursor(false);
	this->plane = 0;
}

