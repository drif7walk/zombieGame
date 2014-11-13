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

void SpriteHandler::Initialize(UI* ui)
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
		entities->back()->locationVec.x = rand() % ui->SCRW;
		entities->back()->locationVec.y = rand() % ui->SCRH;
	}

	/* Cursor */
	entities->push_back(new Cursor((*sprites)["cursor"]));

	/* Create a tilemap */
	for (int y = 0; y <= ui->SCRH / 32; y++)
	{
		for (int x = 0; x <= ui->SCRW / 32; x++)
		{
		/* Modifying spawned entities happens as back() */	
		entities->push_back(new Tile((*sprites)["floor"]));
		entities->back()->locationVec.x = entities->back()->w * x * entities->back()->scale;
		entities->back()->locationVec.y = entities->back()->h * y * entities->back()->scale;
		}
	}
	
	/* Create MANY zombie spawner */
	for (int i = 0; i < 10; i++)
	{
		entities->push_back(new Zombiespawner(sprites->operator[]("zombiespawner") ));
		entities->back()->locationVec.x = rand() % ui->SCRW;
		entities->back()->locationVec.y = rand() % ui->SCRH;
	}
}

int zombieclock = 0;
int zombietimeout = 12;
void SpriteHandler::Update(UI* ui, double frameTime)
{

	sort(entities->begin(), entities->end(), [](const Sprite* a, const Sprite* b) -> bool { return a->locationVec.y < b->locationVec.y; });
	sort(entities->begin(), entities->end(), [](const Sprite* a, const Sprite* b) -> bool { return a->plane < b->plane; });

	std::vector<Sprite*>::iterator it = entities->begin();
	Vector offset;
	offset.x = ui->SCRW / 2;
	offset.y = ui->SCRH / 2;
	while (it != entities->end())
	{
		if (strcmp((*it)->name.c_str(), "player") == 0)
		{
			offset -= (*it)->locationVec;
		}
		it++;
	}

	SDL_Rect screen = { (int)-offset.x, (int)-offset.y, ui->SCRW, ui->SCRH };

	/* Iterate through entities, draw, update, etc */
	it = entities->begin();
	while (it != entities->end())
	{

		(*it)->Update(ui, entities, frameTime, spawnList, sprites);

		/* If UI element, then change its x and y to not be affected by the offset */
		if ((*it)->plane == 2) 
		{
			(*it)->locationVec -= offset;
		}
		(*it)->Render(renderer, offset); 
		

		/* Check if outside bounds, unless persistent */
		SDL_Rect entity = { (int)(*it)->locationVec.x, (int)(*it)->locationVec.y, (int)(*it)->w, (int)(*it)->h, };
		if (!SDL_HasIntersection(&screen, &entity) && !(*it)->persistent)
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

	/* Spawnlist */
	for (auto itt = spawnList->begin(); itt != spawnList->end(); itt++)
	{
		entities->push_back((*itt));
	}

	spawnList->clear();

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

			if (s.compare("@TILE") == 0)
			{
				SDL_Log("Loading tile...");
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

			if (s.compare("@ZOMBIESPAWNER") == 0)
			{
				SDL_Log("Loading zombie spawner...");
				Zombiespawner* spr;

				/* name */
				std::string inln;
				getline(conffile, inln);
				spr = new Zombiespawner(inln, ren);

				getline(conffile, spr->name);

				/* rows */
				getline(conffile, inln);
				spr->rows = atoi(inln.c_str());

				/* columns */
				getline(conffile, inln);
				spr->cols = atoi(inln.c_str());

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

