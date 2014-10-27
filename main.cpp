#include <SDL2/SDL.h>
#include <fstream>
#include <string>
#include <map>
#include <stdlib.h>
#include "sprite.h"

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
	SDL_Window* window = SDL_CreateWindow("hl2.exe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

	/* C++11 */
	if (window == nullptr)
	{
		SDL_Quit();
	}

	/* Rendereris */
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	double _fps = 1000 / 60.0f;

	/* Load assets */

	map<string, Sprite*> sprites;
	/* End load assets */

	LoadSpritesFromList(renderer, &sprites);



	while(!quit)
	{
		const Uint8* keybuf = SDL_GetKeyboardState(NULL);

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

		/* Update */
		if (keybuf[SDL_SCANCODE_W])
		{
			//guy->y += -3.142;
			//guy->AnimateStep(2);
		}
		if (keybuf[SDL_SCANCODE_A])
		{
			//guy->x += -3.142;
			//guy->AnimateStep(3);
		}
		if (keybuf[SDL_SCANCODE_S])
		{
			//guy->y += 3.142;
			//guy->AnimateStep(0);
		}
		if (keybuf[SDL_SCANCODE_D])
		{
			//guy->x += 3.142;
			//guy->AnimateStep(1);
		}

		//renderer->Render(a, b, c);
	
		SDL_RenderClear(renderer);

		/* XXX */
		sprites["guy"]->AnimateStep(0);
		sprites["guy"]->Render(renderer);

		SDL_RenderPresent(renderer);

		SDL_Delay(_fps);
		
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

			/* etc.  */



		}

		conffile.close();
	}
	else // File does not exist
	{
		/* PANIC */
	}

}
