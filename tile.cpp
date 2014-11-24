#include "tile.h"

void Tile::Update(double deltaTime, boost::shared_ptr<UI> ui,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > entlist,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > spawnlist,
		boost::shared_ptr< std::map < std::string, boost::shared_ptr< Sprite > > > sprites)
{
	FreezeStep(0);
}

Tile::Tile(boost::shared_ptr< Sprite > templatesprite) : Sprite(templatesprite)
{
	this->plane = 0;
}

Tile::Tile(std::string filename, boost::shared_ptr< SDL_Renderer > ren): Sprite(filename, ren)
{
	this->plane = 0;
}
