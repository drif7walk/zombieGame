#include "cursor.h"

void Cursor::Update(std::vector<Sprite*>* entlist, double deltaTime)
{
Sprite::Update(entlist, deltaTime);

	int x, y;
	SDL_GetMouseState(&x, &y);
	this->x = x;
	this->y = y;

}

Cursor::Cursor(Sprite* templatesprite): Sprite(templatesprite)  {}
Cursor::Cursor(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{
	SDL_ShowCursor(false);
}
