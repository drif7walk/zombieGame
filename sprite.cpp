#include "sprite.h"

void Sprite::setDirection(Vector direction)
{
	float angle = direction.angle();

	if (angle > 22.5f && angle <202.5f)
	{
		if (angle > 112.5f)
		{
			if (angle > 157.5f)
			{
				this->direction = 3;
				return;
			}
			else
			{
				this->direction = 5;
				return;
			}
		}
		else
		{
			if (angle < 67.5f)
			{
				this->direction = 4;
				return;
			}
			else
			{
				this->direction = 0;
				return;
			}
		}
	}
	else
	{
		if (angle > 202.5f && angle < 292.5f)
		{
			if (angle > 247.5f)
			{
				this->direction = 2;
				return;
			}
			else
			{
				this->direction = 6;
				return;
			}
		}
		else
		{
			if (angle > 292.5f && angle < 337.5f)
			{
				this->direction = 7;
				return;
			}
			else
			{
				this->direction = 1;
				return;
			}
		}
	}
}

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

void Sprite::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites)
{
		this->FreezeStep(direction);
}

Sprite::Sprite(Sprite* templatesprite)
{

	this->destroyed = templatesprite->destroyed;

	this->texture = templatesprite->texture;
	this->name=templatesprite->name;
	/* if null then */
	this->w = templatesprite->w;
	this->h = templatesprite->h;
	this->framewidth = templatesprite->framewidth;
	this->frameheight = templatesprite->frameheight;

	this->rows = templatesprite->rows;
	this->cols = templatesprite->cols;

	this->plane = templatesprite->plane;
}

Sprite::Sprite(std::string filename, SDL_Renderer* ren)
{
	this->texture = NULL;

	this->destroyed = false;

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

	this->plane = 1;
		
}

