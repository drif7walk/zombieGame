#include "Tile.h"

#include <SDL.h>

void Tile::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites)
{
	FreezeStep(0);
}

void Tile::Render(SDL_Renderer* ren)
{
	SDL_Rect r = { (int)this->locationVec.x, (int)this->locationVec.y, (int)this->framewidth*this->scale, (int)this->frameheight*this->scale };
	SDL_RenderCopy(ren, this->texture, &src, &r);
}

SDL_Rect Tile::GetRect()
{
	return  { (int)this->locationVec.x, (int)this->locationVec.y, (int)this->framewidth*this->scale, (int)this->frameheight*this->scale };
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

