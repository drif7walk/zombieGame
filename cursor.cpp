#include "cursor.h"

void Cursor::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime)
{
Sprite::Update(ui, entlist, deltaTime);

	int x, y;
	SDL_GetMouseState(&x, &y);
	this->locationVec.x = x;
	this->locationVec.y = y;
}

Cursor::Cursor(Sprite* templatesprite): Sprite(templatesprite)  {}
Cursor::Cursor(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{
	SDL_ShowCursor(false);
}

