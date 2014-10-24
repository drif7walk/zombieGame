#include <SDL2/SDL.h>

typedef enum
{
	newGameButton,
	optionsButton,
	highscoresButton,
	quitButton
} CurrentMenuButton;

#include "renderer.hpp"
#include "sdl.hpp"
//#include "userInput.hpp"

typedef enum
{
	mainMenuState,
	optionsState,
	highscoreState,
	gameplayState,
	pauseMenuState,
	quitState
} GameState;


int main(int argc, char** argv)
{
		
	GameState state = mainMenuState;
	CurrentMenuButton currentMenuButton = newGameButton;

	SDL_Event e;

	if (sdl::initialize() != 0)
	{
		SDL_Quit();
		return 1;
	}
	
	Renderer* renderer = new Renderer();
	
	if (renderer->intitialize() != 0)
	{
		SDL_Quit();
		return 1;
	}


	while(state != quitState)
	{
		if (state == mainMenuState)
		{
			
			while (state == mainMenuState)
			{
				while (SDL_PollEvent(&e))
				{
					switch (e.type)
					{
					case SDL_QUIT:
						state = quitState;
					case SDL_KEYDOWN:
						if (e.key.keysym.sym == SDLK_RETURN && currentMenuButton == quitButton)
						{
							state = quitState;
						}
						if (e.key.keysym.sym == SDLK_UP && currentMenuButton != newGameButton)
						{
							currentMenuButton = (CurrentMenuButton)((int)currentMenuButton - 1);
						}
						if (e.key.keysym.sym == SDLK_DOWN && currentMenuButton != quitButton)
						{
							currentMenuButton = (CurrentMenuButton)((int)currentMenuButton + 1);
						}
					default: continue;
					}
				}
				renderer->drawMenu(currentMenuButton);//zīmēt mainMenu
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

	SDL_Quit();

	return 0;
}
