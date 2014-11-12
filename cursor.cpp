#include "cursor.h"

#include <SDL.h>

void Cursor::Render(SDL_Renderer* ren)
{
	SDL_Rect r = { (int)this->locationVec.x - (int)this->w / 2,
		(int)this->locationVec.y - (int)this->h / 2,
		(int)this->framewidth * (int)this->scale,
		(int)this->frameheight * (int)this->scale };
	SDL_RenderCopy(ren, this->texture, &src, &r);
}

void Cursor::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites)
{
	Sprite::Update(ui, entlist, deltaTime, spawnList, sprites);
	int x, y;
	SDL_GetMouseState(&x, &y);
	this->locationVec.x = (float)x;
	this->locationVec.y = (float)y;
}



Cursor::Cursor(Sprite* templatesprite): Sprite(templatesprite)  {}
Cursor::Cursor(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{
	SDL_ShowCursor(false);
	this->plane = 2;
}

