
#include <SDL.h>
#include <SDL_mixer.h>
#include <string.h>

typedef enum
{
	mainMenuState,
	optionsState,
	highscoreState,
	gameplayState,
	pauseMenuState,
	quitState
} GameState;

#include "utility.hpp"
#include "renderer.hpp"
#include "sdl.hpp"
#include "audio.hpp"
#include "options.hpp"
#include "mainMenu.hpp"
//#include "userInput.hpp"

int main(int argc, char** argv)
{
		
	GameState state = mainMenuState;

	SDL_Event e;

	Options* options = new Options();

	if (sdl::initialize() != 0)
	{
		SDL_Quit();
		return 1;
	}
	
	Renderer* renderer = new Renderer();
	
	if (renderer->intitialize() != 0)
	{
		SDL_Quit();
		renderer->~Renderer();
		return 1;
	}

	MainMenu* mainMenu = new MainMenu(renderer, &e, &state);

	audio::load();

	Uint32 waittime = 1000 / options->getFPS();
	Uint32 framestarttime = 0;
	Sint32 delaytime;

	while(state != quitState)
	{
		if (state == mainMenuState)
		{
			
			while (state == mainMenuState)
			{
				mainMenu->userInput();
				mainMenu->drawMenu();

				audio::play(options->getVolume(), 50);
				
				delaytime = waittime - (SDL_GetTicks() - framestarttime);
				if (delaytime > 0)
					SDL_Delay((Uint32)delaytime);
				framestarttime = SDL_GetTicks();
			}
		}

		if (state == optionsState)
		{

		}

		if (state == highscoreState)
		{

		}

		if (state == gameplayState)
		{

		}

	}

	renderer->~Renderer();
	delete renderer;

	mainMenu->~MainMenu();
	delete mainMenu;

	options->~Options();
	delete options;

	audio::deinitialize();

	SDL_Quit();

	return 0;
}
