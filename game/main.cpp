#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <SDL.h>
#include <SDL_mixer.h>
#include <string.h>

typedef enum
{
	mainMenuState,
	settingsState,
	highscoreState,
	gameplayState,
	pauseMenuState,
	quitState
} GameState;

#include "utility.hpp"
#include "renderer.hpp"
#include "sdl.hpp"
#include "audio.hpp"
#include "settings.hpp"
#include "mainMenu.hpp"
//#include "userInput.hpp"

int main(int argc, char** argv)
{
		
	GameState state = mainMenuState;

	SDL_Event e;

	Settings* settings = new Settings();

	if (sdl::initialize() != 0)
	{
		SDL_Quit();
		delete settings;
		return 1;
	}

	Audio* audio = new Audio();
	
	Renderer* renderer = new Renderer();
	
	if (renderer->intitialize() != 0)//ievieto contstructoraa
	{
		SDL_Quit();
		delete settings;
		delete renderer;
		delete audio;
		return 1;
	}
	
	while(state != quitState)
	{
		if (state == mainMenuState)
		{
			MainMenu* mainMenu = new MainMenu(renderer, &e, &state, settings, audio);	//vajadzetu izveidot engine class
			while (state == mainMenuState)												//shis jau paliek smiekliigi
			{
				mainMenu->updateMainMenu();
			}
			delete mainMenu;
		}

		if (state == settingsState)
		{

		}

		if (state == highscoreState)
		{

		}

		if (state == gameplayState)
		{

		}

	}

	delete renderer;
	delete settings;
	delete audio;

	SDL_Quit();

	_CrtDumpMemoryLeaks();
	return 0;
}
