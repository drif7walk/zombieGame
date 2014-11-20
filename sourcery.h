#ifndef SOURCERY_H
#define SOURCERY_H

#include <memory>

#include "sdl.hpp"

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


