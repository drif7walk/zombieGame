#include "tile.h"

void Tile::Update(double deltaTime, std::shared_ptr<UI> ui,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
		std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites)
{
	FreezeStep(0);
}

Tile::Tile(std::shared_ptr< Sprite > templatesprite) : Sprite(templatesprite)  
{
	this->plane = 0; 
}

Tile::Tile(std::string filename, std::shared_ptr< SDL_Renderer > ren): Sprite(filename, ren)
{
	this->plane = 0;
}
