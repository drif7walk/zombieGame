#ifndef SDL_HPP
#define SDL_HPP

#include <SDL2\SDL.h>

namespace sdl
{
	bool initialize()
	{
		if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) != 0)
		{
			return 1;
		}
		return 0;
	}
}

#endif