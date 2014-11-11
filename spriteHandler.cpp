#include "spriteHandler.h"

SpriteHandler::SpriteHandler(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

SpriteHandler::~SpriteHandler()
{
	std::vector<Sprite*>::iterator a;
	for (a = entities->begin(); a != entities->end(); a++)
	{
		delete(*a);
	}
	entities->clear();
	delete entities;

	std::map<std::string, Sprite*>::iterator p;
	for (p = sprites->begin(); p != sprites->end(); p++) {
		delete p->second;
	}
	sprites->erase(sprites->begin(), sprites->end());
	delete sprites;

	std::vector<Sprite*>::iterator c;
	for (c = spawnList->begin(); c != spawnList->end(); c++) {
		delete (*c);
	}
	spawnList->erase(spawnList->begin(), spawnList->end());
	delete spawnList;
}

void SpriteHandler::Initialize()
{
	spawnList = new std::vector<Sprite*>;
	sprites = new std::map<std::string, Sprite*>;
	entities = new std::vector<Sprite*>;

	LoadSpritesFromList(renderer, sprites);

	srand(time(NULL));

	/* Create a player object */

	entities->push_back(new Player((*sprites)["player"]));

	for (int i = 0; i < 50; i++)
	{
		/* Modifying spawned entities happens as back() */
		entities->push_back(new Zombie((*sprites)["zombie"]));
		entities->back()->locationVec.x = rand() % SCRW;
		entities->back()->locationVec.y = rand() % SCRH;
	}

	/* Cursor */
	entities->push_back(new Cursor((*sprites)["cursor"]));

	/* Create a tilemap */
	for (int y = 0; y <= SCRH / 32; y++)
	{
		for (int x = 0; x <= SCRW / 32; x++)
		{
		/* Modifying spawned entities happens as back() */	
			if (x == 10 && (y > 2 && y < 7))
			{
				entities->push_back(new Wall((*sprites)["wall"]));
			}
			else
			{
				entities->push_back(new Tile((*sprites)["floor"]));
			}
			entities->back()->locationVec.x = entities->back()->w * x * entities->back()->scale;
			entities->back()->locationVec.y = entities->back()->h * y * entities->back()->scale;
		}
	}
	
}

int zombieclock = 0;
int zombietimeout = 12;
void SpriteHandler::Update(UI* ui, double frameTime)
{

	sort(entities->begin(), entities->end(), [](const Sprite* a, const Sprite* b) -> bool { return a->locationVec.y < b->locationVec.y; });
	sort(entities->begin(), entities->end(), [](const Sprite* a, const Sprite* b) -> bool { return a->plane < b->plane; });

		


	SDL_Rect screen = { 0, 0, SCRW, SCRH };

	/* Draw entities */
	std::vector<Sprite*>::iterator it = entities->begin();
	while (it != entities->end())
	{
		(*it)->Update(ui, entities, frameTime, spawnList, sprites);
		(*it)->Render(renderer); 
		it++;
	}



	it = entities->begin();
	while (it != entities->end())
	{
		SDL_Rect entity = { (*it)->locationVec.x, (*it)->locationVec.y, (*it)->w, (*it)->h, };
		if (!SDL_HasIntersection(&screen, &entity))//check if outside bounds
		{
			delete (*it);
			it = entities->erase(it);
			continue;
		}
		else if ((*it)->destroyed == true)
		{
			delete(*it);
			it = entities->erase(it);
			continue;
		}
		it++;
	}

	spawn();//mainly bullets for now;

	/*
	XXX: zombie spawning
	*/
	zombieclock++;
	if (zombieclock > zombietimeout)
	{
		zombieclock = 0;

		entities->push_back(new Zombie( sprites->operator[]("zombie") ));
		entities->back()->locationVec.x = rand() % 700 + 50;
		entities->back()->locationVec.y = rand() % 500 + 50;
	}


}

void SpriteHandler::LoadSpritesFromList(SDL_Renderer* ren, std::map<std::string, Sprite*>* sprmap)
{
	/* open config then parse config */
	std::string s;
	std::ifstream conffile("sprites.list");

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

				std::string inln;
				getline(conffile, inln);
				spr = new Sprite(inln, ren);

				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = atoi(inln.c_str());

				getline(conffile, inln);
				spr->cols = atoi(inln.c_str());

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert(std::pair<std::string, Sprite*>(spr->name, spr));
			}

			if (s.compare("@WALL") == 0)
			{
				SDL_Log("Loading wall...");
				Sprite* spr;

				std::string inln;
				getline(conffile, inln);
				spr = new Wall(inln, ren);

				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = atoi(inln.c_str());

				getline(conffile, inln);
				spr->cols = atoi(inln.c_str());

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert(std::pair<std::string, Sprite*>(spr->name, spr));
			}

			if (s.compare("@PLAYER") == 0)
			{
				SDL_Log("Loading player...");
				Player* spr;

				std::string inln;
				getline(conffile, inln);
				spr = new Player(inln, ren);

				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = atoi(inln.c_str());

				getline(conffile, inln);
				spr->cols = atoi(inln.c_str());

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert(std::pair<std::string, Sprite*>(spr->name, spr));
			}

			if (s.compare("@TILE") == 0)
			{
				SDL_Log("Loading Tile...");
				Sprite* spr;

				std::string inln;
				getline(conffile, inln);
				spr = new Tile(inln, ren);

				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = atoi(inln.c_str());

				getline(conffile, inln);
				spr->cols = atoi(inln.c_str());

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert(std::pair<std::string, Sprite*>(spr->name, spr));

			}

			if (s.compare("@CURSOR") == 0)
			{
				SDL_Log("Loading cursor...");
				Cursor* spr;

				std::string inln;
				getline(conffile, inln);
				spr = new Cursor(inln, ren);

				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = 1;

				getline(conffile, inln);
				spr->cols = 1;

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert(std::pair<std::string, Sprite*>(spr->name, spr));
			}

			if (s.compare("@PROJECTILE") == 0)
			{
				SDL_Log("Loading projectile...");
				Bullet* spr;

				std::string inln;
				getline(conffile, inln);
				spr = new Bullet(inln, ren);

				getline(conffile, spr->name);
				getline(conffile, inln);
				spr->rows = 1;

				getline(conffile, inln);
				spr->cols = 1;
				
				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert(std::pair<std::string, Sprite*>(spr->name, spr));
			}

			if (s.compare("@ZOMBIE") == 0)
			{
				SDL_Log("Loading zombie...");
				Zombie* spr;

				std::string inln;
				getline(conffile, inln);
				spr = new Zombie(inln, ren);

				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = atoi(inln.c_str());;

				getline(conffile, inln);
				spr->cols = atoi(inln.c_str());;

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert(std::pair<std::string, Sprite*>(spr->name, spr));
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

void SpriteHandler::spawn()
{
	for (auto itt = spawnList->begin(); itt != spawnList->end(); itt++)
	{
		entities->push_back((*itt));
	}

	spawnList->clear();
	
}