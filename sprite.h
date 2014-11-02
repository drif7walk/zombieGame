#ifndef SPRITE_H
#define SPRITE_H

#ifdef OS_WINDOWS
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL.h>
#include <SDL_ttf.h>
#endif

#include <string>
#include <vector>

#include "vector.h"

class Sprite {

private:

public:
	SDL_Texture* texture;
	Vector locationVec;
	double w = 1;
	double h = 1;
	double velocity;

	Vector velocityVec;
	Vector accelerationVec;
	Vector directionVec;
	float maxVelocity;

	std::string name;

	int rows = 1;
	int cols = 1;
	int scale = 2;
	int framewidth;
	int frameheight;
	double framecount = 0;
	unsigned char direction = 0;
	SDL_Rect src;

	void AnimateStep(int direction, double deltaTime);
	void FreezeStep(int direction);

	virtual void Render(SDL_Renderer* ren);

	virtual void Update(std::vector<Sprite*>* entlist, double deltaTime);

	Sprite(Sprite* templatesprite) ;
	Sprite(std::string filename, SDL_Renderer* ren);

};

#endif

