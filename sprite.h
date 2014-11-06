#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
#include <vector>

#include "vector.h"
#include "UI.h"

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

	bool destroyed;

	int healthPoints;

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

	SDL_Rect GetRect();

	virtual void Render(SDL_Renderer* ren);

	virtual void Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime);

	Sprite(Sprite* templatesprite) ;
	Sprite(std::string filename, SDL_Renderer* ren);

};

#endif


