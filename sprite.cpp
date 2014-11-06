#include "sprite.h"

SDL_Rect Sprite::GetRect()
{
	return { (int)this->locationVec.x, (int)this->locationVec.y, (int)(this->framewidth*this->scale), (int)(this->framewidth*this->scale) };
}

void Sprite::AnimateStep(int direction, double deltaTime)
{
	framecount += (double)0.6*deltaTime;
	int row = (int)framecount % cols;
	this->src = { row*framewidth, direction*frameheight, this->framewidth, this->frameheight };
}

void Sprite::FreezeStep(int direction)
{
	this->src = { 0, direction*frameheight, this->framewidth, this->frameheight };
}

void Sprite::Render(SDL_Renderer* ren)
{
	SDL_Rect r = { (int)this->locationVec.x, (int)this->locationVec.y, (int)this->framewidth*this->scale, (int)this->frameheight*this->scale };
	SDL_RenderCopy(ren, this->texture, &src, &r);
}

void Sprite::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime)
{
		this->FreezeStep(direction);
}

Sprite::Sprite(Sprite* templatesprite)
{
	this->texture = templatesprite->texture;
	this->name=templatesprite->name;
	/* if null then */
	this->w = templatesprite->w;
	this->h = templatesprite->h;
	this->framewidth = templatesprite->framewidth;
	this->frameheight = templatesprite->frameheight;

	this->rows = templatesprite->rows;
	this->cols = templatesprite->cols;
}

Sprite::Sprite(std::string filename, SDL_Renderer* ren)
{
	this->texture = NULL;
	SDL_Surface* ls = SDL_LoadBMP(filename.c_str());
	/* if null then [...] */

	SDL_SetColorKey(ls, 1, 0xFF00FF);

	this->texture = SDL_CreateTextureFromSurface(ren, ls);
	/* if null then */

	SDL_FreeSurface(ls);

	int w, h;
	SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);
	this->w = (double)w;
	this->h = (double)h;

	this->framewidth = this->rows;
	this->frameheight = this->cols;
		
}

