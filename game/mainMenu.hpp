#ifndef MAINMENU_HPP
#define MAINMENU_HPP



class MainMenu
{
public:
	MainMenu(Engine* _engine)
	{
		engine = _engine;
		currentMenuButton = newGameButton;
		textScale = 5;//parasti burti ir 10x10 pikseli
		topRightX = 100;//varbu veidu kaa nocentreet tekstu?
		topRightY = 100;
		waittime = 1000 / engine->settings->getFPS();
		framestarttime = 0;
		
//vareetu ielikt ciklaa lai buutu smukaak bet izveerts ir performance boost un jau viss ir uzrakstiits :D
		newGameRect.x = topRightX; 
		newGameRect.y = topRightY;
		newGameRect.h = textScale * engine->renderer->ascii.source.h;
		newGameRect.w = textScale * engine->renderer->ascii.source.w * strlen(newGameText);

		settingsRect.x = topRightX;
		settingsRect.y = topRightY + textScale * engine->renderer->ascii.source.h * 1;
		settingsRect.h = textScale * engine->renderer->ascii.source.h;
		settingsRect.w = textScale * engine->renderer->ascii.source.w * strlen(settingsText);

		highscoreRect.x = topRightX;
		highscoreRect.y = topRightY + textScale * engine->renderer->ascii.source.h * 2;
		highscoreRect.h = textScale * engine->renderer->ascii.source.h;
		highscoreRect.w = textScale * engine->renderer->ascii.source.w * strlen(highscoreText);

		quitRect.x = topRightX;
		quitRect.y = topRightY + textScale * engine->renderer->ascii.source.h * 3;
		quitRect.h = textScale * engine->renderer->ascii.source.h;
		quitRect.w = textScale * engine->renderer->ascii.source.w * strlen(quitText);

		fullRect.x = topRightX;
		fullRect.y = topRightY;
		fullRect.h = textScale * engine->renderer->ascii.source.h * 4;
		fullRect.w = textScale * engine->renderer->ascii.source.w * strlen(quitText);
	}

	~MainMenu()
	{

	}

private:
	int textScale;
	int topRightX;
	int topRightY;
	
	Engine* engine;

	Uint32 waittime;
	Uint32 framestarttime;
	Sint32 delaytime;

	SDL_Rect fullRect;//visas 4 pogas kopaa

	SDL_Rect newGameRect;
	SDL_Rect settingsRect;
	SDL_Rect highscoreRect;
	SDL_Rect quitRect;

	const char* newGameText =	" New Game ";
	const char* settingsText =	" Settings ";
	const char* highscoreText = "Highscores";
	const char* quitText =		"   Quit   ";

	SDL_Point mouse_position;

	SDL_Rect destination;
	
	typedef enum
	{
		newGameButton,
		settingsButton,
		highscoresButton,
		quitButton
	} CurrentMenuButton;

	CurrentMenuButton currentMenuButton;

public:
	inline void drawMenu()
	{		
		engine->renderer->clear();

		destination.x = topRightX - engine->renderer->ascii.source.w * textScale;
		destination.y = topRightY + currentMenuButton * engine->renderer->ascii.source.h * textScale;
		engine->renderer->drawText(">", &destination, textScale);

		destination.x = topRightX;
		destination.y = topRightY;
		engine->renderer->drawText(newGameText, &destination, textScale);	//katru reizi tiek teksts veidots no atseviskiem burtiem
		engine->renderer->drawText(settingsText, &destination, textScale);	//performance boost buutu izveidot tekstuuru no jau izveidota
		engine->renderer->drawText(highscoreText, &destination, textScale);	//teksta, bet tas ir tikai kartupeliem, main menu nav tik
		engine->renderer->drawText(quitText, &destination, textScale);		//expensive, vismaz uz doto briidi

		engine->renderer->present();
	}

	inline void userInput()
	{
		while (SDL_PollEvent(engine->e))
		{
			switch (engine->e->type)
			{
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
				if (pointInRect(&mouse_position, &fullRect))
				{
					if (pointInRect(&mouse_position, &newGameRect))
					{
						currentMenuButton = newGameButton;
					}
						else if (pointInRect(&mouse_position, &settingsRect))
						{
							currentMenuButton = settingsButton;
						}
							else if (pointInRect(&mouse_position, &highscoreRect))
							{
								currentMenuButton = highscoresButton;
							}
								else if (pointInRect(&mouse_position, &quitRect))
								{
									currentMenuButton = quitButton;
								}
				}
				break;
			case SDL_QUIT:
				*engine->state = quitState;
				break;
			case SDL_KEYDOWN:
				if (engine->e->key.keysym.sym == SDLK_RETURN && currentMenuButton == quitButton)
				{
					*engine->state = quitState;
					break;
				}
				if (engine->e->key.keysym.sym == SDLK_UP)
				{
					if (currentMenuButton != newGameButton)
					{
						currentMenuButton = (CurrentMenuButton)((int)currentMenuButton - 1);
						break;
					}
					else
					{
						currentMenuButton = (CurrentMenuButton)3;
						break;
					}
				}
				if (engine->e->key.keysym.sym == SDLK_DOWN)
				{
					if (currentMenuButton != quitButton)
					{
						currentMenuButton = (CurrentMenuButton)((int)currentMenuButton + 1);
						break;
					}
					else
					{
						currentMenuButton = (CurrentMenuButton)0;
						break;
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (pointInRect(&mouse_position, &fullRect))
				{
/*					if (engine->e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &newGameRect))
					{
						*engine->state = gameplayState;
					}
					else if (engine->e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &settingsRect))
					{
						*engine->state = settingsState;
					}
					else if (engine->e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &highscoreRect))
					{
						*engine->state = highscoreState;
					}
					else */if (engine->e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &quitRect))
					{
						*engine->state = quitState;
						break;
					}
				}
				break;


			default: continue;
			}
		}
	}

	inline void updateMainMenu()
	{
		this->userInput();
		this->drawMenu();

		engine->audio->play(engine->settings->getVolume(), 50);

		delaytime = waittime - (SDL_GetTicks() - framestarttime);
		if (delaytime > 0)
			SDL_Delay((Uint32)delaytime);
		framestarttime = SDL_GetTicks();
	}
};

#endif