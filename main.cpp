#include <SDL.h>
#include <SDL_ttf.h>

#include "sourcery.h"

#include "vector.h"

//test

int main(int argc, char** argv)
{
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

	double startTime;
	double deltaTime = 1;
	float alpha = 0.2f;
	Uint32 getticks, frametimedelta, frametimelast = 0;
	float frametime = 0;
	double _fps = 1000 / 120.0f;

	Sourcery* sourcery = new Sourcery();

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

