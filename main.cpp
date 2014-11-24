#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include <SDL2/SDL.h>

#include "sourcery.h"

#include "vector.h"

//intellisense will help me

int main(int argc, char** argv)
{
	SDL_Event e;

	bool quit = false;

	double startTime = 1.0;
	double deltaTime = 1.0;
	double alpha = 0.2;
	uint64_t getticks = 0;
	uint64_t frametimedelta = 0;
	uint64_t frametimelast = 0;
	double frametime = 0.0;
	double _fps = 1000.0 / 120.0;

	int state = 0;

	auto sourcery = boost::shared_ptr < Sourcery > {boost::make_shared< Sourcery >()};

	sourcery->spriteHandler->Initialize(sourcery->ui);

	while(!quit)
	{
		startTime = SDL_GetTicks();
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				default: continue;
			}
		}


		if (state == 0)
		{
			sourcery->UpdateGame(deltaTime / 100.0f);
		}



		/* Frames per second */

		getticks = SDL_GetTicks();
		frametimedelta = getticks - frametimelast;
		frametimelast = getticks;

		frametime = alpha * frametimedelta + (1.0 - alpha) * frametime;
		//framespersecond = (int)(1000.0 / frametime);

		SDL_Delay(_fps);
		deltaTime = SDL_GetTicks() - startTime;
	}



	return 0;
}

