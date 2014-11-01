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
	entities->push_back(new Player((*sprites)["player"]));

	for (int i = 0; i < 50; i++)
	{
		/* Modifying spawned entities happens as back() */
		entities->push_back(new Zombie((*sprites)["zombie"]));
		entities->back()->x = rand() % SCRW;
		entities->back()->y = rand() % SCRH;
	}


	/* Cursor */
	entities->push_back(new Cursor((*sprites)["cursor"]));
}

void SpriteHandler::Update(double frameTime)
{
	sort(entities->begin(), entities->end(), [](const Sprite* a, const Sprite* b) -> bool { return a->y < b->y; /* also plane ordering */ });

	bool createBullet = false;
	SDL_Point bulletLocation;
	int bulletDirection;
	/* Draw entities */
	for (std::vector<Sprite*>::iterator it = entities->begin(); it != entities->end(); it++)
	{
		if (strcmp((*it)->name.c_str(), "player") == 0)
		{
			const Uint8* keybuf = SDL_GetKeyboardState(NULL);

			bool keydown = false;

			if (keybuf[SDL_SCANCODE_W])
			{
				(*it)->y += -(*it)->velocity * frameTime;
				(*it)->direction = 2;
				keydown = true;
			}
			if (keybuf[SDL_SCANCODE_A])
			{
				(*it)->x += -(*it)->velocity * frameTime;
				(*it)->direction = 3;
				keydown = true;
			}
			if (keybuf[SDL_SCANCODE_S])
			{
				(*it)->y += (*it)->velocity * frameTime;
				(*it)->direction = 0;
				keydown = true;
			}
			if (keybuf[SDL_SCANCODE_D])
			{
				(*it)->x += (*it)->velocity * frameTime;
				(*it)->direction = 1;
				keydown = true;
			}

			if (keybuf[SDL_SCANCODE_RETURN])
			{
				createBullet = true;
				bulletLocation = { (*it)->x, (*it)->y };
				bulletDirection = (*it)->direction;
			}

			if (!keydown)
				(*it)->FreezeStep((*it)->direction);
			else
				(*it)->AnimateStep((*it)->direction, frameTime);
			(*it)->Render(renderer);
			continue;
		}
		(*it)->Update(entities, frameTime);
		(*it)->Render(renderer);
	}
	if (createBullet == true)
	{
		entities->push_back(new Bullet((*sprites)["bullet"], bulletLocation, bulletDirection));
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
				spr->rows = 4;

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