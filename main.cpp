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
#include "audio.hpp"
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

	audio::load();
	audio::play(255, 255);


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
						if (e.key.keysym.sym == SDLK_UP)
						{
							if (currentMenuButton != newGameButton)
							{
								currentMenuButton = (CurrentMenuButton)((int)currentMenuButton - 1);
							}
							else
							{
								currentMenuButton = (CurrentMenuButton)3;
							}
						}
						if (e.key.keysym.sym == SDLK_DOWN)
						{
							if (currentMenuButton != quitButton)
							{
								currentMenuButton = (CurrentMenuButton)((int)currentMenuButton + 1);
							}
							else
							{
								currentMenuButton = (CurrentMenuButton)0;
							}
						}
					default: continue;
					}
				}
				audio::play(255, 255/2);
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

	audio::deinitialize();

	SDL_Quit();

	return 0;
}
