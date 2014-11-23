#ifndef SOURCERY_H
#define SOURCERY_H

<<<<<<< HEAD
#include <memory>

#include "sdl.hpp"
=======
#include <SDL.h>
#include <SDL_ttf.h>

>>>>>>> parent of 7bd50a5... magazine update for rapid fire mode

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

	std::shared_ptr< SDL_Window > window;
	std::shared_ptr< SDL_Renderer > renderer;
	std::shared_ptr< SpriteHandler > spriteHandler;
	std::shared_ptr< UI > ui;


	int UpdateGame(double frameTime);


	Sourcery();
	~Sourcery();
};

#endif


