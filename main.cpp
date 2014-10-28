#include <SDL2/SDL.h>
#include <fstream>
#include <string>
#include <map>
#include <stdlib.h>
#include "sprite.h"
#include "player.h"
#include "cursor.hpp"

using namespace std;

void LoadSpritesFromList(SDL_Renderer*, map<string, Sprite*>*);

int main(int argc, char** argv)
{
	SDL_Event e;
	bool quit = false;
	
	/* XXX: Tā vietā, lai lādētu _visu_ pēcāk sadalīt šo if
	vairākos if-os, kas salādē tikai izmantotos SDL modules. */
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		return 1;
	}

	/* Izveidot logu. */
	SDL_Window* window = SDL_CreateWindow("hl3.exe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

	/* C++11 */
	if (window == nullptr)
	{
		SDL_Quit();
	}

	/* Rendereris */
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	double _fps = 1000 / 120.0f;

	/* Load assets */

	map<string, Sprite*> sprites;
	/* End load assets */

	LoadSpritesFromList(renderer, &sprites);


	double startTime;
	double deltaTime;

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

		/* WARNING: DEEP SORCERY */ 
		
	
		SDL_RenderClear(renderer);

		/* XXX */
		/*
		sprites["guy"]->AnimateStep(0);
		sprites["guy"]->Render(renderer);
		*/
		/* Draw all sprites */
		map<string, Sprite*>::iterator p;
		for(p = sprites.begin(); p != sprites.end(); p++) {
			p->second->Update(deltaTime / 100.0f);
    			p->second->Render(renderer);
  		}

		SDL_RenderPresent(renderer);

		SDL_Delay(_fps);
		deltaTime = SDL_GetTicks() - startTime;
		
	}

	/* Delete every texture from map */

	//delete guy;

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
		while (getline(conffile, s))
		{
			/* C++ does not do switch on strings, use if/else if/else if */
			if (s[0] == '#') continue; // comment

			if (s.compare("@STARTSPRITE") == 0)
			{
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

			if (s.compare("@STARTPLAYER") == 0)
			{
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

			if (s.compare("@STARTCURSOR") == 0)
			{
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

			/* etc.  */



		}

		conffile.close();
	}
	else // File does not exist
	{
		/* PANIC */
	}

}
