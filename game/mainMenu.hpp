#ifndef MAINMENU_HPP
#define MAINMENU_HPP

class MainMenu
{
public:
	MainMenu(Renderer* _renderer, SDL_Event* _e, GameState* _state)
	{
		renderer = _renderer;
		e = _e;
		state = _state;
		currentMenuButton = newGameButton;
		textScale = 5;
		topRightX = 100;
		topRightY = 100;
		

//vareetu ielikt ciklaa lai buutu smukaak bet izveerts ir performance boost un jau viss ir uzrakstiits :D
		newGameRect.x = topRightX; 
		newGameRect.y = topRightY + textScale * renderer->ascii.source.h * 0;
		newGameRect.h = textScale * renderer->ascii.source.h;
		newGameRect.w = textScale * renderer->ascii.source.w * strlen(newGameText);

		optionsRect.x = topRightX;
		optionsRect.y = topRightY + textScale * renderer->ascii.source.h * 1;
		optionsRect.h = textScale * renderer->ascii.source.h;
		optionsRect.w = textScale * renderer->ascii.source.w * strlen(optionsText);

		highscoreRect.x = topRightX;
		highscoreRect.y = topRightY + textScale * renderer->ascii.source.h * 2;
		highscoreRect.h = textScale * renderer->ascii.source.h;
		highscoreRect.w = textScale * renderer->ascii.source.w * strlen(highscoreText);

		quitRect.x = topRightX;
		quitRect.y = topRightY + textScale * renderer->ascii.source.h * 3;
		quitRect.h = textScale * renderer->ascii.source.h;
		quitRect.w = textScale * renderer->ascii.source.w * strlen(quitText);

	}

	~MainMenu()
	{
		
	}

private:
	int textScale;
	int topRightX;
	int topRightY;
	
	Renderer* renderer;
	SDL_Event* e;
	GameState* state;

	SDL_Rect newGameRect;
	SDL_Rect optionsRect;
	SDL_Rect highscoreRect;
	SDL_Rect quitRect;

	SDL_Point mouse_position;

	SDL_Rect destination;

	char* newGameText = "New Game";
	char* optionsText = "Options";
	char* highscoreText = "Highscore";
	char* quitText = "Quit";

	typedef enum
	{
		newGameButton,
		optionsButton,
		highscoresButton,
		quitButton
	} CurrentMenuButton;

	CurrentMenuButton currentMenuButton;

public:
	void drawMenu()
	{		
		renderer->clear();

		destination.x = topRightX - renderer->ascii.source.w * textScale;
		destination.y = topRightY + currentMenuButton * renderer->ascii.source.h * textScale;
		renderer->drawText(">", &destination, textScale);

		destination.x = topRightX;
		destination.y = topRightY;
		renderer->drawText(newGameText, &destination, textScale);
		renderer->drawText(optionsText, &destination, textScale);
		renderer->drawText(highscoreText, &destination, textScale);
		renderer->drawText(quitText, &destination, textScale);

		renderer->present();
	}

	void userInput()
	{
		while (SDL_PollEvent(e))
		{
			switch (e->type)
			{
			case SDL_QUIT:
				*state = quitState;
			case SDL_KEYDOWN:
				if (e->key.keysym.sym == SDLK_RETURN && currentMenuButton == quitButton)
				{
					*state = quitState;
				}
				if (e->key.keysym.sym == SDLK_UP)
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
				if (e->key.keysym.sym == SDLK_DOWN)
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
				case SDL_MOUSEBUTTONDOWN:
				/*	if (e->button.button == SDL_BUTTON_LEFT && currentMenuButton == newGameButton)
					{
						*state = gameplayState;
					}*/
					if (e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &quitRect))
					{
						*state = quitState;
					}

				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
					if (pointInRect(&mouse_position, &newGameRect) == true)
					{
						currentMenuButton = newGameButton;
					}
					if (pointInRect(&mouse_position, &optionsRect) == true)
					{
						currentMenuButton = optionsButton;
					}
					if (pointInRect(&mouse_position, &highscoreRect) == true)
					{
						currentMenuButton = highscoresButton;
					}
					if (pointInRect(&mouse_position, &quitRect) == true)
					{
						currentMenuButton = quitButton;
					}
			default: continue;
			}
		}
	}

};

#endif