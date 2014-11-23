<<<<<<< HEAD
#include <vld.h>

#include <memory>

#include "sdl.hpp"
=======
#include <SDL.h>
#include <SDL_ttf.h>
>>>>>>> parent of 7bd50a5... magazine update for rapid fire mode

#include "sourcery.h"

#include "vector.h"

//intellisense will help me

int main(int argc, char** argv)
{
<<<<<<< HEAD
	auto e = SDL_Event{};

	auto quit = false;
=======
	Vector a(1, 0);
	int b = 0;
	for (int i = 0; i <= 720; i+= 36)
	{
		a.rotate(36);
		b = a.angle();
	}

	a = Vector(0, -1);
	b = a.angle();


	SDL_Event e;
	bool quit = false;
>>>>>>> parent of 7bd50a5... magazine update for rapid fire mode

	auto startTime = 1.0;
	auto deltaTime = 1.0;
	auto alpha = 0.2;
	auto getticks = uint64_t( 0 );
	auto frametimedelta = uint64_t( 0 );
	auto frametimelast = uint64_t( 0 );
	auto frametime = 0.0;
	auto _fps = 1000.0 / 120.0;

	auto state = 0;
	//			type				new Sourcery
	auto sourcery = std::unique_ptr < Sourcery > {std::make_unique< Sourcery >()};

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

