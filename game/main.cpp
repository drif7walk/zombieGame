#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <SDL.h>
#include <SDL_mixer.h>
#include <string.h>
#include <vector>

using namespace std;

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
	Engine* engine = new Engine();
	if (engine->failedToInit == true)
	{
		delete engine;
		_CrtDumpMemoryLeaks();//parbauda vai ir kaads memory leak
		return 1;
	}

	while(*engine->state != quitState)
	{
		if (*engine->state == mainMenuState)
		{
			MainMenu* mainMenu = new MainMenu(engine);
			while (*engine->state == mainMenuState)	
			{
				mainMenu->updateMainMenu();
			}
			delete mainMenu;//main menu vairs nebus nepiecieshams
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
