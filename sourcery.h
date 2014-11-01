#ifndef SOURCERY_H
#define SOURCERY_H

#ifdef OS_WINDOWS
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL.h>
#include <SDL_ttf.h>
#endif

#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "spriteHandler.h"


class Sourcery {

private:

public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SpriteHandler* spriteHandler;

	int Update(double frameTime);

	int RenderText (SDL_Renderer* ren, std::string text, int x, int y);


	Sourcery();
	~Sourcery();
};

#endif

