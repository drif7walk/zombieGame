#ifndef SOURCERY_H
#define SOURCERY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

	int state = 0;// 0 - mainmenu, 1 - game

public:

	boost::shared_ptr< SDL_Window > window;
	boost::shared_ptr< SDL_Renderer > renderer;
	boost::shared_ptr< SpriteHandler > spriteHandler;
	boost::shared_ptr< UI > ui;


	int UpdateGame(double frameTime);


	Sourcery();
	~Sourcery();
};

#endif


