#ifndef ENGINE_HPP
#define ENGINE_HPP



class Engine
{
public:
	Engine()
	{
		failedToInit = false;
		settings = new Settings;
		if (sdl::initialize())
		{
			failedToInit = true;
		}
		audio = new Audio;
		renderer = new Renderer;
		if (renderer->intitialize())
		{
			failedToInit = true;
		}
		state = new GameState;
		*state = mainMenuState;
		e = new SDL_Event;
	}
	~Engine()
	{
		delete settings;
		delete audio;
		delete renderer;
		delete e;
		delete state;
		SDL_Quit();
	}
public:
	Audio* audio;
	Settings* settings;
	Renderer* renderer;
	GameState* state;
	SDL_Event* e;
	bool failedToInit;
};

#endif