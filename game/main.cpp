#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <SDL.h>
#include <SDL_mixer.h>
#include <string.h>
#include <vector>

using namespace std;//bad practice should not use this, only usage right now is for <vector>

#include "utility.hpp"
#include "settings.hpp"
#include "renderer.hpp"
#include "sdl.hpp"
#include "audio.hpp"
#include "engine.hpp"
#include "mainMenu.hpp"
#include "game.hpp"
//#include "userInput.hpp"

//DuPsys dereference everything

int main(int argc, char** argv)
{
	Engine* engine = new Engine();//creates a new game engine and initializes most of the components, except the actual game or the menus
	if (engine->failedToInit == true)//upon any of components failing to initialize the program will quit
	{
		delete engine;
		_CrtDumpMemoryLeaks();//this is just for testing so i remember to deallocate dynamic memory that was created on the heap
		return 1;
	}

	while(*engine->state != quitState)//the main loop of the program
	{
		if (*engine->state == mainMenuState)
		{
			MainMenu* mainMenu = new MainMenu(engine);
			while (*engine->state == mainMenuState)	
			{
				mainMenu->updateMainMenu();
			}
			delete mainMenu;
		}

		if (*engine->state == settingsState)
		{

		}

		if (*engine->state == highscoreState)
		{

		}

		if (*engine->state == gameplayState)
		{
			Game* game = new Game(engine);
			while (*engine->state == gameplayState)
			{
				game->updateGame();
			}
			delete game;
		}

	}

	delete engine;
	_CrtDumpMemoryLeaks();
	return 0;
}
