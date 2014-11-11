#include "wall.h"

#include <SDL.h>

void Wall::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites)
{
	FreezeStep(0);
}

void Wall::Render(SDL_Renderer* ren)
{
	SDL_Rect r = { (int)this->locationVec.x, (int)this->locationVec.y, (int)this->framewidth*this->scale, (int)this->frameheight*this->scale };
	SDL_RenderCopy(ren, this->texture, &src, &r);
}

SDL_Rect Wall::GetRect()
{
	return  { (int)this->locationVec.x, (int)this->locationVec.y, (int)this->framewidth*this->scale, (int)this->frameheight*this->scale };
}

Wall::Wall(Sprite* templatesprite) : Sprite(templatesprite)  
{
	this->plane = this->plane;
	this->impassable = templatesprite->impassable;
}

Wall::Wall(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{
	SDL_ShowCursor(false);// im not touching this but i have no idea why it was there for tile anyway
	this->plane = 0;
	this->impassable = true;
}

