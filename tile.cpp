#include "tile.h"

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
	this->plane = 0;
}
