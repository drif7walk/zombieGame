#ifndef SOURCERY_H
#define SOURCERY_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "spriteHandler.h"
#include "vector.h"
#include "UI.h"


class Sourcery {

private:

public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SpriteHandler* spriteHandler;
	UI* ui;

	int Update(double frameTime);

	Sourcery();
	~Sourcery();
};

#endif


