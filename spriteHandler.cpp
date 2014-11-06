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
}

void SpriteHandler::Initialize()
{
	sprites = new std::map<std::string, Sprite*>;
	entities = new std::vector<Sprite*>;

	LoadSpritesFromList(renderer, sprites);

	srand(time(NULL));

	/* Create a player object */
	player = new Player((*sprites)["player"]);

	entities->push_back(player);

	for (int i = 0; i < 50; i++)
	{
		/* Modifying spawned entities happens as back() */
		entities->push_back(new Zombie((*sprites)["zombie"]));
		entities->back()->locationVec.x = rand() % SCRW;
		entities->back()->locationVec.y = rand() % SCRH;
	}

	cursor = new Cursor((*sprites)["cursor"]);
	/* Cursor */
	entities->push_back(cursor);
}

int zombieclock = 0;
int zombietimeout = 12;
void SpriteHandler::Update(UI* ui, double frameTime)
{
	sort(entities->begin(), entities->end(), [](const Sprite* a, const Sprite* b) -> bool { return a->locationVec.y < b->locationVec.y; /* also plane ordering */ });
	SDL_Rect screen = { 0, 0, SCRW, SCRH };

	/* Draw entities */
	std::vector<Sprite*>::iterator it = entities->begin();
	while (it != entities->end())
	{
		SDL_Rect entity = { (*it)->locationVec.x, (*it)->locationVec.y, (*it)->w, (*it)->h, };
		if (!SDL_HasIntersection(&screen, &entity))//check if outside bounds
		{
			delete (*it);
			it = entities->erase(it);
			continue;
		}
		(*it)->Update(ui, entities, frameTime);
		(*it)->Render(renderer); 
		it++;
	}


	it = entities->begin();
	while (it != entities->end())
	{
		if ((*it)->destroyed == true)
		{
			delete(*it);
			it = entities->erase(it);
			continue;
		}
		it++;
	}

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
