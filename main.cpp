#include <vld.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include "sourcery.h"

#include "vector.h"

int main(int argc, char** argv)
{
	SDL_Event e;
	bool quit = false;

	double startTime;
	double deltaTime = 1;
	float alpha = 0.2f;
	Uint32 getticks, frametimedelta, frametimelast = 0;
	float frametime = 0;
	double _fps = 1000 / 120.0f;

	Sourcery* sourcery = new Sourcery();

	sourcery->spriteHandler->Initialize();

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

		sourcery->Update(deltaTime / 100.0f);

		/* Frames per second */
		
		getticks = SDL_GetTicks();
		frametimedelta = getticks - frametimelast;
		frametimelast = getticks;

		frametime = alpha * frametimedelta + (1.0 - alpha) * frametime;
		//framespersecond = (int)(1000.0 / frametime);
		
		SDL_Delay(_fps);
		deltaTime = SDL_GetTicks() - startTime;
	}

	delete sourcery;

	return 0;
}

