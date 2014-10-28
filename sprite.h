#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <string>
using namespace std;

class Sprite {

private:

public:
	SDL_Texture* texture;

	double x = 0;
	double y = 0;
	double w = 1;
	double h = 1;

	string name;

	/* move to private */
	int rows = 1;
	int cols = 1;
	int scale = 2;
	int framewidth;
	int frameheight;
	double framecount = 0;
	SDL_Rect src;

	void AnimateStep(int direction, double deltaTime)
	{
		framecount += (double)0.6*deltaTime;
		int row = (int)framecount % cols;
		this->src = { row*framewidth, direction*frameheight, this->framewidth, this->frameheight };
	}

	void Render(SDL_Renderer* ren)
	{

		SDL_Rect r = { (int)this->x, (int)this->y, (int)this->w, (int)this->h };

		SDL_RenderCopy(ren, this->texture, &src, &r);

	}

	virtual void Update(double deltaTime)
	{
		this->AnimateStep(0, deltaTime);
	}

	Sprite(string filename, SDL_Renderer* ren)
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

		this->framewidth = this->w;
		this->frameheight = this->h;
	}

	~Sprite()
	{
		SDL_DestroyTexture(this->texture);
	}

};
#endif