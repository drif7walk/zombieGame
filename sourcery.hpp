#ifndef SOURCERY_HPP
#define SOURCERY_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <algorithm>

#include "sprite.hpp"
#include "player.hpp"
#include "cursor.hpp"
#include "bullet.hpp"
#include "zombie.hpp"

#define SCRW 800
#define SCRH 600
using namespace std;

class Sourcery {

public:

	SDL_Window* window;
	SDL_Renderer* renderer;

	map<string, Sprite*>* sprites;
	vector<Sprite*>* entities;

	int Initialize()
	{
		srand(time(NULL));

		/* Create a player object */
		entities->push_back( new Player((*sprites)["player"]) );

		for (int i = 0; i < 50; i++)
		{
			/* Modifying spawned entities happens as back() */
			entities->push_back(new Zombie((*sprites)["zombie"]));
			entities->back()->x = rand() % SCRW;
			entities->back()->y = rand() % SCRH;
		}

	
		/* Cursor */
		entities->push_back(new Cursor((*sprites)["cursor"]));

		return 0;
	}

	int Update(double frameTime)
	{
		SDL_RenderClear(renderer);

		sort(entities->begin(), entities->end(), [](const Sprite* a, const Sprite* b) -> bool { return a->y < b->y; /* also plane ordering */ });

		/* Draw entities */
		for (vector<Sprite*>::iterator it = entities->begin(); it != entities->end(); it++)
		{
			(*it)->Update(entities, frameTime);
			(*it)->Render(renderer);
		}
		/* End draw entities */
 
		/* ask irc to make this not eat memory */
		if (false)
		{
			stringstream s;
			s << "FPS: " << 1000.0 / frameTime;

			RenderText(renderer, s.str(), 10, 10);
		}

		SDL_RenderPresent(renderer);

		return 0;
	}

	int RenderText (SDL_Renderer* ren, string text, int x, int y)
	{
		TTF_Font* font = NULL;
		font = TTF_OpenFont("font.ttf", 12);
		if (font == NULL)
			SDL_Log("Font is null: %s", SDL_GetError());

		SDL_Color col = { 255, 255, 255, 255 };

		SDL_Surface* surf = TTF_RenderText_Solid(font, (const char*)text.c_str(), col);
		SDL_Texture* mytex = SDL_CreateTextureFromSurface( ren, surf);	

		TTF_CloseFont(font);

		int w, h;
		SDL_QueryTexture(mytex, NULL, NULL, &w, &h);

		SDL_Rect r = { x, y, w, h };
		SDL_RenderCopy(ren, mytex, NULL, &r);
		SDL_FreeSurface(surf);

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

	Sourcery() 
	{

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0 )
		{
			SDL_Log("Failed to initialize.");
		}

		window = SDL_CreateWindow("hl3.exe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCRW, SCRH, SDL_WINDOW_SHOWN);

		if (window == nullptr)
		{
			SDL_Log("Failed to initialize.");
		}
		
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if ( TTF_Init() == -1 ) 
		{
			SDL_Log("Could not initialize SDL_TTF.");
		}

		sprites = new map<string, Sprite*>;
		entities = new vector<Sprite*>;

		LoadSpritesFromList(renderer, sprites);

		srand(time(NULL));
		
		/* ENTITY SPAWN BLOCK */
		/* END ENTITY SPAWN BLOCK */

	}

	~Sourcery()
	{
		/* Delete every texture from map */
		vector<Sprite*>::iterator a;
		for (a = entities->begin(); a != entities->end(); a++)
		{
			delete(*a);
		}
		entities->clear();
		delete entities;

		map<string, Sprite*>::iterator p;
		for(p = sprites->begin(); p != sprites->end(); p++) {

	    		delete p->second;
	  	}
		sprites->clear();
		delete sprites;

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	

};

#endif
