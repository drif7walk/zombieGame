#ifdef OS_WINDOWS
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#else
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#endif
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <stdlib.h>

using namespace std;

#include "fonts.hpp"
#include "sound.hpp"

using namespace fonts;
using namespace sound;

#include "sprite.hpp"
#include "player.hpp"
#include "cursor.hpp"
#include "bullet.hpp"
#include "zombie.hpp"

#define SCRW 800
#define SCRH 600

using namespace std;

void LoadSpritesFromList(SDL_Renderer*, map<string, Sprite*>*);

/* Frames per seconds */


int main(int argc, char** argv)
{
	//_CrtSetBreakAlloc(138);
	SDL_Event e;
	bool quit = false;
	
	/* XXX: Tā vietā, lai lādētu _visu_ pēcāk sadalīt šo if
	vairākos if-os, kas salādē tikai izmantotos SDL modules. */
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		return 1;
	}

	/* iestāda skaņu */
	{
		const int     AUDIO_FREQ = 44100;
		const Uint16  AUDIO_FORMAT = MIX_DEFAULT_FORMAT;
		const int     AUDIO_CHANNELS = 2;
		const int     AUDIO_BUFFERS = 1024;

		if (Mix_OpenAudio(AUDIO_FREQ, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS) != 0)
		{
			SDL_Quit();
		}

		Mix_AllocateChannels(16);
	}

	Mix_AllocateChannels(16);
	
	/* Izveidot logu. */
	SDL_Window* window = SDL_CreateWindow("hl3.exe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCRW, SCRH, SDL_WINDOW_SHOWN);

	/* C++11 */
	if (window == nullptr)
	{
		SDL_Quit();
	}

	/* Rendereris */
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	double _fps = 1000 / 120.0f;

	/* Fonts happen here */
		if( initializeTTF(renderer) == -1 ) { 
			SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			SDL_Quit();	
		}
	
	/* End fonts */

	SDL_Log("SDL Started.");

	/* Load assets */

	map<string, Sprite*> sprites;
	vector<Sprite*> entities;
	/* End load assets */

	LoadSpritesFromList(renderer, &sprites);

	SDL_Log("numsprlist %d", sprites.size());


	double startTime;
	double deltaTime = 1;

	/* Last-Second FPS */
	float alpha = 0.2f;
	Uint32 getticks, frametimedelta, frametimelast = 0;
	float frametime = 0, framespersecond = 0;


	/* Spawn entities */

	entities.push_back( sprites["player"] );

	srand(time(NULL));

	/* make dis work */
	for (int i = 0; i < 50; i++)
	{
		entities.push_back(new Zombie(sprites["zombie"]));
		entities.back()->x = rand() % SCRW;
		entities.back()->y = rand() % SCRH;
	}



/*
	for (int i = 0; i < 50; i++)
	{
		entities.push_back( sprites["zombie"] );
		int x = rand() % SCRW;
		int y = rand() % SCRH;
		entities.back()->x = i;
		entities.back()->y = y;
		SDL_Log("Zombie created at x%d y %d", x, y); 
	}
*/
	while(!quit)
	{
		startTime = SDL_GetTicks();
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				default: continue;	
			}
		}


		SDL_RenderClear(renderer);


		/* Draw entities 
		map<string, Sprite*>::iterator p;
		for(p = sprites.begin(); p != sprites.end(); p++) {
			p->second->Update(deltaTime / 100.0f);
    			p->second->Render(renderer);
  		}
		*/
		/* Draw entities */
		for (vector<Sprite*>::iterator it = entities.begin(); it != entities.end(); it++)
		{
			(*it)->Update(entities, deltaTime / 100.0f);
			(*it)->Render(renderer);
		}
		/* End draw entities */

		stringstream s;
		s << "FPS: " << framespersecond << "\0";

		drawText(s.str(), { 0xff, 0xff, 0xff, 0xff }, { 10, 10 }, normal, 1);

		drawText("top lel", { 0xff, 0xff, 0xff, 0xff }, { 300, 200 }, normal, 4);

		SDL_RenderPresent(renderer);


		/* Frames per second */
		getticks = SDL_GetTicks();
		frametimedelta = getticks - frametimelast;
		frametimelast = getticks;

		frametime = alpha * frametimedelta + (1.0 - alpha) * frametime;
		framespersecond = (int)(1000.0 / frametime);
		
		SDL_Delay(_fps);
		deltaTime = SDL_GetTicks() - startTime;
	}

	/* Delete every texture from map */
	map<string, Sprite*>::iterator p;
	for(p = sprites.begin(); p != sprites.end(); p++) {

    		delete p->second;
  	}
	sprites.clear();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void LoadSpritesFromList(SDL_Renderer* ren, map<string, Sprite*>* sprmap)
{
	
	/* open config then parse config */
	string s;
	ifstream conffile("sprites.list");

	if (conffile.is_open()) // File exists
	{
		SDL_Log("sprites.list opened...");
		while (getline(conffile, s))
		{
			/* C++ does not do switch on strings, use if/else if/else if */
			if (s[0] == '#') continue; // comment

			if (s.compare("@SPRITE") == 0)
			{
				SDL_Log("Loading sprite...");
				Sprite* spr;

				string inln;
				getline(conffile, inln);	
				spr = new Sprite(inln, ren);
				
				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = atoi(inln.c_str());

				getline(conffile, inln);
				spr->cols = atoi(inln.c_str());

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert( pair<string, Sprite*>(spr->name, spr) );
			}

			if (s.compare("@PLAYER") == 0)
			{
				SDL_Log("Loading player...");
				Player* spr;

				string inln;
				getline(conffile, inln);	
				spr = new Player(inln, ren);
				
				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = atoi(inln.c_str());

				getline(conffile, inln);
				spr->cols = atoi(inln.c_str());

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert( pair<string, Sprite*>(spr->name, spr) );
			}

			if (s.compare("@CURSOR") == 0)
			{
				SDL_Log("Loading cursor...");
				Cursor* spr;

				string inln;
				getline(conffile, inln);	
				spr = new Cursor(inln, ren);
				
				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = 1;

				getline(conffile, inln);
				spr->cols = 1;

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert( pair<string, Sprite*>(spr->name, spr) );
			}

			if (s.compare("@PROJECTILE") == 0)
			{
				SDL_Log("Loading projectile...");
				Bullet* spr;

				string inln;
				getline(conffile, inln);	
				spr = new Bullet(inln, ren);
				
				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = 1;

				getline(conffile, inln);
				spr->cols = 1;

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert( pair<string, Sprite*>(spr->name, spr) );
			}

			if (s.compare("@ZOMBIE") == 0)
			{
				SDL_Log("Loading zombie...");
				Zombie* spr;

				string inln;
				getline(conffile, inln);	
				spr = new Zombie(inln, ren);
				
				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = atoi(inln.c_str());;

				getline(conffile, inln);
				spr->cols = atoi(inln.c_str());;

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert( pair<string, Sprite*>(spr->name, spr) );
			}

			/* etc.  */



		}

		conffile.close();
		
	}
	else // File does not exist
	{
		/* PANIC */
	}

} 
