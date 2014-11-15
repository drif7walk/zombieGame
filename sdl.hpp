#ifndef SDL_HPP
#define SDL_HPP

#define SHORTHPATH

#ifdef SHORTHPATH
	#include <SDL.h>
	#include <SDL_ttf.h>
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_ttf.h>
#endif

#endif
