#include "cursor.h"

void Cursor::Render(std::shared_ptr< SDL_Renderer > ren)
{
	auto r = SDL_Rect{ (int)(this->locationVec.x - this->framewidth * this->scale / 2), (int)(this->locationVec.y -this->framewidth * this->scale / 2), (int)(this->frameheight*this->scale), (int)(this->frameheight*this->scale) };
	SDL_RenderCopy(ren.get(), this->texture, &src, &r);
}

void Cursor::Update(double deltaTime, std::shared_ptr<UI> ui,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
		std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites) 
{
	Sprite::Update(deltaTime, ui, entlist, spawnlist, sprites);

	auto x = int(), y = int();
	SDL_GetMouseState(&x, &y);
	this->locationVec.x = x;
	this->locationVec.y = y;
}

Cursor::Cursor(std::shared_ptr< Sprite > templatesprite): Sprite(templatesprite) 
{

}

Cursor::Cursor(std::string filename, std::shared_ptr< SDL_Renderer > ren): Sprite(filename, ren)
{
	SDL_ShowCursor(false);
	this->plane = 2;
}

