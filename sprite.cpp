#include "sprite.h"

void Sprite::setDirection(Vector direction)
{
	auto angle = direction.angle();

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
	return { (int)this->locationVec.x, (int)this->locationVec.y, (int)(this->framewidth*this->scale), (int)(this->frameheight*this->scale) };
}

void Sprite::AnimateStep(int direction, double deltaTime)
{
<<<<<<< HEAD
	framecount += (double)animSpeed * deltaTime;
	auto row = (int)framecount % cols;
=======
	framecount += (double)0.6*deltaTime;
	int row = (int)framecount % cols;
>>>>>>> parent of 7bd50a5... magazine update for rapid fire mode
	this->src = { row*framewidth, direction*frameheight, this->framewidth, this->frameheight };
}

void Sprite::FreezeStep(int direction)
{
	this->src = { 0, direction*frameheight, this->framewidth, this->frameheight };
}

void Sprite::Render(std::shared_ptr< SDL_Renderer > ren)
{
	auto r = SDL_Rect{ (int)this->locationVec.x, (int)this->locationVec.y, (int)this->framewidth*this->scale, (int)this->frameheight*this->scale };
	SDL_RenderCopy(ren.get(), this->texture, &src, &r);
}

void Sprite::Render(std::shared_ptr< SDL_Renderer > ren, Vector offset)
{
	auto r = SDL_Rect{ (int)(this->locationVec.x + offset.x), (int)(this->locationVec.y + offset.y), (int)this->framewidth*this->scale, (int)this->frameheight*this->scale };
	SDL_RenderCopy(ren.get(), this->texture, &src, &r);
}

void Sprite::Update(double deltaTime, std::shared_ptr<UI> ui,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
		std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites)
{
	this->FreezeStep(direction);
}

Sprite::Sprite(std::shared_ptr< Sprite > templatesprite)
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

Sprite::Sprite(std::string filename, std::shared_ptr< SDL_Renderer > ren)
{
	this->texture = NULL;

	this->destroyed = false;

	SDL_Surface* ls = SDL_LoadBMP(filename.c_str());
	if (ls == NULL) 
	{
		SDL_Log("Could not load %s", filename.c_str());
	}

	SDL_SetColorKey(ls, 1, 0xFF00FF);

	this->texture = SDL_CreateTextureFromSurface(ren.get(), ls);
	/* if null then */

	SDL_FreeSurface(ls);

	auto w = 0;
	auto h = 0;
	SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);
	this->w = (double)w;
	this->h = (double)h;

	this->framewidth = this->rows;
	this->frameheight = this->cols;

	this->plane = 1;
		
}

