#ifndef GAME_HPP
#define GAME_HPP

class Entity
{
public:
	Entity()
	{

	}

	~Entity()
	{

	}

protected:
	SDL_Rect rect;

public:
	//virtual void update() = 0;
	
};

class MapTile
{
public:
	MapTile()
	{

	}

	~MapTile()
	{

	}

private:
	bool traversible;
	Tile tileID;
	SDL_Rect rect;
	
public:
	inline Tile getTileID()
	{
		return tileID;
	}

	inline SDL_Rect getRect()//getRekt...
	{
		return rect;
	}
	
	inline void intialize(int x, int y, Tile tile)
	{
		tileID = tile;
		if (tile == sky)
		{
			traversible = true;
		}
			else if (tile == block)
			{
				traversible = false;
			}
		rect.h = 8;
		rect.w = 8;
		rect.x = x * 8;
		rect.y = y * 8;
	}
};

class Game
{
public:
	Game(Engine* _engine)
	{
		engine = _engine;
		waittime = 1000 / engine->settings->getFPS();
		framestarttime = 0;
		fullScreen.x = 0;
		fullScreen.y = 0;
		fullScreen.h = engine->settings->getScreenY();
		fullScreen.w = engine->settings->getScreenX();
		setupGameWorld();
	}

	~Game()
	{

	}

private:
	Engine* engine;

	inline void setupGameWorld()
	{
		Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
#endif
		SDL_Surface* mapSurface = nullptr;
		mapSurface = SDL_CreateRGBSurface(0, 800, 600, 32, rmask, gmask, bmask, amask); 
		SDL_Rect source;	
		source.x = 0;
		source.y = 0;
		source.h = 8;
		source.w = 8;

		SDL_Surface* blockSurface = nullptr;
		blockSurface = SDL_LoadBMP("assets/block.bmp");
		SDL_SetColorKey(blockSurface, 1, 0xff00ff);

		SDL_Surface* skySurface = nullptr;
		skySurface = SDL_LoadBMP("assets/sky.bmp");
		SDL_SetColorKey(skySurface, 1, 0xff00ff);

		for (int y = 0; y < 75; y++)
		{
			for (int x = 0; x < 100; x++)
			{
				map[y][x].intialize(x, y, sky);
			}
		}
		for (int x = 0; x < 100; x++)
		{
			map[74][x].intialize(x, 74, block);
		}	

		for (int y = 0; y < 75; y++)
		{
			for (int x = 0; x < 100; x++)
			{
				if (map[y][x].getTileID() == block)
				{
					SDL_BlitSurface(blockSurface, &source, mapSurface, &map[y][x].getRect());
				}
					else if (map[y][x].getTileID() == sky)
					{
						SDL_BlitSurface(skySurface, &source, mapSurface, &map[y][x].getRect());
					}
			}
		}

		engine->renderer->loadMapTexture(mapSurface);

		SDL_FreeSurface(mapSurface);
		SDL_FreeSurface(blockSurface);
		SDL_FreeSurface(skySurface);
	}

	inline void drawMap()
	{
		//for (int y = 0; y < 75; y++)
		//{
		//	for (int x = 0; x < 100; x++)
		//	{
		//		engine->renderer->drawTexture((TextureIdentifier)(map[y][x].getTileID()), &map[y][x].getRect());
		//	}
		//}
		engine->renderer->drawTexture(MAPTEXTURE, &fullScreen);
	}

	inline void drawGame()
	{
		engine->renderer->clear();

		drawMap();

		engine->renderer->present();
	}

	inline void userInput()
	{
		while (SDL_PollEvent(engine->e))
		{
			switch (engine->e->type)
			{
			case SDL_QUIT:
				*engine->state = quitState;
				break;
			case SDL_KEYDOWN:
				if (engine->e->key.keysym.sym == SDLK_RETURN)
				{
					*engine->state = quitState;
					break;
				}
			default: continue;
			}
		}
	}

	MapTile map[75][100];
	SDL_Rect fullScreen;

	Uint32 waittime;
	Uint32 framestarttime;
	Sint32 delaytime;

public:
	inline void updateGame()
	{
		this->userInput();
		this->drawGame();

		delaytime = waittime - (SDL_GetTicks() - framestarttime);
		if (delaytime > 0)
			SDL_Delay((Uint32)delaytime);
		framestarttime = SDL_GetTicks();
	}


};

#endif