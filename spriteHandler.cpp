#include "spriteHandler.h"

SpriteHandler::SpriteHandler(boost::shared_ptr<SDL_Renderer> renderer)
{
	this->renderer = renderer;
}

SpriteHandler::~SpriteHandler()
{
}

void SpriteHandler::Initialize(boost::shared_ptr<UI> ui)
{
	spawnList = boost::make_shared< std::vector< boost::shared_ptr< Sprite > > >();
	sprites = boost::make_shared< std::map< std::string, boost::shared_ptr< Sprite > > >();
	entities = boost::make_shared< std::vector< boost::shared_ptr< Sprite > > >();

	LoadSpritesFromList(renderer, sprites);

	srand(time(NULL));

	/* Create a player object */

	entities->push_back(boost::make_shared< Player >((*sprites)["player"]));


	auto playerLocation = entities->back()->locationVec;
	for (auto i = 0; i < 5; i++)
	{
		entities->push_back(boost::make_shared< Magazine >((*sprites)["magazine"]));
		entities->back()->locationVec = playerLocation;
	}

	for (auto i = 0; i < 50; i++)
	{
		/* Modifying spawned entities happens as back() */
		entities->push_back(boost::make_shared< Zombie >((*sprites)["zombie"]));
		entities->back()->locationVec.x = rand() % ui->SCRW;
		entities->back()->locationVec.y = rand() % ui->SCRH;
	}

	/* Cursor */
	entities->push_back(boost::make_shared< Cursor >((*sprites)["cursor"]));

	/* Create a tilemap */
	for (auto y = 0; y <= ui->SCRH / 32; y++)
	{
		for (auto x = 0; x <= ui->SCRW / 32; x++)
		{
		/* Modifying spawned entities happens as back() */
		entities->push_back(boost::make_shared< Tile >((*sprites)["floor"]));
		entities->back()->locationVec.x = entities->back()->w * x * entities->back()->scale;
		entities->back()->locationVec.y = entities->back()->h * y * entities->back()->scale;
		}
	}

	/* Create MANY zombie spawner */
	for (auto i = 0; i < 10; i++)
	{
		entities->push_back(boost::make_shared< Zombiespawner >((*sprites)["zombiespawner"]));
		entities->back()->locationVec.x = rand() % ui->SCRW;
		entities->back()->locationVec.y = rand() % ui->SCRH;
	}
}

auto zombieclock = 0;
auto zombietimeout = 12;

void SpriteHandler::Update(boost::shared_ptr<UI> ui, double frameTime)
{

	sort(entities->begin(), entities->end(),
		[](const boost::shared_ptr< Sprite > a, const boost::shared_ptr< Sprite > b)
		-> bool { return a->locationVec.y < b->locationVec.y; });

	sort(entities->begin(), entities->end(),
		[](const boost::shared_ptr< Sprite > a, const boost::shared_ptr< Sprite > b)
		-> bool { return a->plane < b->plane; });

	auto it = entities->begin();
	auto offset = Vector(ui->SCRW / 2, ui->SCRH / 2);

	if (playerIsAlive == true)
	{
		auto playerNotFound = true;
		while (it != entities->end())
		{
			if (strcmp((*it)->name.c_str(), "player") == 0)
			{
				offset -= (*it)->locationVec;
				playerNotFound = false;
			}
			it++;
		}
		if (playerNotFound == true)
		{
			it = entities->begin();
			while (it != entities->end())
			{
				if (strcmp((*it)->name.c_str(), "playerZombie") == 0)
				{
					offset -= (*it)->locationVec;
					playerNotFound = false;
				}
				it++;
			}
			playerIsAlive = false;
		}
	}
	else
	{
		while (it != entities->end())
		{
			if (strcmp((*it)->name.c_str(), "playerZombie") == 0)
			{
				offset -= (*it)->locationVec;
			}
			it++;
		}
	}

	auto screen = SDL_Rect{ (int)-offset.x, (int)-offset.y, ui->SCRW, ui->SCRH };

	/* Iterate through entities, draw, update, etc */
	it = entities->begin();
	while (it != entities->end())
	{

		(*it)->Update(frameTime, ui, entities, spawnList, sprites);

		/* Do not render if destroyed */
		if (!(*it)->destroyed)
		{
			/* If UI element, then change its x and y to not be affected by the offset */
			if ((*it)->plane == 3)
			{
				(*it)->locationVec -= offset;
			}
			(*it)->Render(renderer, offset);
		}


		/* Check if outside bounds, unless persistent */
		auto entity = SDL_Rect{ (int)(*it)->locationVec.x, (int)(*it)->locationVec.y, (int)(*it)->w, (int)(*it)->h, };
		if (!SDL_HasIntersection(&screen, &entity) && !(*it)->persistent)
		{
			it = entities->erase(it);
			continue;
		}
		else if ((*it)->destroyed == true)
		{
			it = entities->erase(it);
			continue;
		}
		it++;
	}

	/* Spawnlist */
	for (it = spawnList->begin(); it != spawnList->end(); it++)
	{
		entities->push_back((*it));
	}
	spawnList->clear();

}

void SpriteHandler::LoadSpritesFromList(boost::shared_ptr<SDL_Renderer> ren,
	boost::shared_ptr<std::map<std::string, boost::shared_ptr< Sprite > > > sprmap)
{
	/* open config then parse config */

	auto s = std::string();
	std::ifstream conffile("sprites.list");

	if (conffile.is_open()) // File exists
	{
		SDL_Log("sprites.list opened...");
		while (getline(conffile, s))
		{
			/* C++ does not do switch on strings, use if/else if/else if */
			if (s[0] == '#') continue; // comment

			//if (s.compare("@SPRITE") == 0)
			//{
			//	SDL_Log("Loading sprite...");
			//	Sprite* spr;
			//
			//	std::string inln;
			//	getline(conffile, inln);
			//	spr = new Sprite(inln, ren);
			//
			//	getline(conffile, spr->name);
			//
			//	getline(conffile, inln);
			//	spr->rows = atoi(inln.c_str());
			//
			//	getline(conffile, inln);
			//	spr->cols = atoi(inln.c_str());
			//
			//	spr->framewidth = spr->w / spr->cols;
			//	spr->frameheight = spr->h / spr->rows;
			//
			//	sprmap->insert(std::pair<std::string, Sprite*>(spr->name, spr));
			//}

			if (s.compare("@TILE") == 0)
			{
				SDL_Log("Loading tile...");

				auto inln = std::string();
				getline(conffile, inln);

				auto spr = boost::shared_ptr < Sprite > {boost::make_shared< Tile >(inln, ren)};

				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = atoi(inln.c_str());

				getline(conffile, inln);
				spr->cols = atoi(inln.c_str());

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert(std::pair<std::string,boost::shared_ptr< Sprite > >(spr->name, spr));
			}

			if (s.compare("@PLAYER") == 0)
			{
				SDL_Log("Loading player...");

				auto inln = std::string();
				getline(conffile, inln);
				auto spr = boost::shared_ptr < Sprite > { boost::make_shared< Sprite >(inln, ren)};

				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = atoi(inln.c_str());

				getline(conffile, inln);
				spr->cols = atoi(inln.c_str());

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert(std::pair<std::string, boost::shared_ptr< Sprite > >(spr->name, spr));
			}

			if (s.compare("@CURSOR") == 0)
			{
				SDL_Log("Loading cursor...");

				auto inln = std::string();
				getline(conffile, inln);
				auto spr = boost::shared_ptr < Sprite > { boost::make_shared< Cursor >(inln, ren)};

				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = 1;

				getline(conffile, inln);
				spr->cols = 1;

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert(std::pair<std::string, boost::shared_ptr< Sprite > >(spr->name, spr));;
			}

			if (s.compare("@PROJECTILE") == 0)
			{
				SDL_Log("Loading projectile...");

				auto inln = std::string();
				getline(conffile, inln);
				auto spr = boost::shared_ptr < Sprite > { boost::make_shared< Bullet >(inln, ren)};

				getline(conffile, spr->name);
				getline(conffile, inln);
				spr->rows = 1;

				getline(conffile, inln);
				spr->cols = 1;

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert(std::pair<std::string, boost::shared_ptr< Sprite > >(spr->name, spr));
			}

			if (s.compare("@ZOMBIE") == 0)
			{
				SDL_Log("Loading zombie...");

				auto inln = std::string();
				getline(conffile, inln);
				auto spr = boost::shared_ptr < Sprite > {boost::make_shared< Zombie >(inln, ren)};

				getline(conffile, spr->name);

				getline(conffile, inln);
				spr->rows = atoi(inln.c_str());;

				getline(conffile, inln);
				spr->cols = atoi(inln.c_str());;

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert(std::pair<std::string, boost::shared_ptr< Sprite > >(spr->name, spr));
			}

			if (s.compare("@ZOMBIESPAWNER") == 0)
			{
				SDL_Log("Loading zombie spawner...");

				/* name */
				auto inln = std::string();
				getline(conffile, inln);
				auto spr = boost::shared_ptr < Sprite > {boost::make_shared< Zombiespawner >(inln, ren)};

				getline(conffile, spr->name);

				/* rows */
				getline(conffile, inln);
				spr->rows = atoi(inln.c_str());

				/* columns */
				getline(conffile, inln);
				spr->cols = atoi(inln.c_str());

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert(std::pair<std::string, boost::shared_ptr< Sprite > >(spr->name, spr));
			}

			if (s.compare("@MAGAZINE") == 0)
			{
				SDL_Log("Loading magazine...");

				/* name */
				auto inln = std::string();
				getline(conffile, inln);
				auto spr = boost::shared_ptr < Sprite > {boost::make_shared< Magazine >(inln, ren)};

				getline(conffile, spr->name);

				/* rows */
				getline(conffile, inln);
				spr->rows = atoi(inln.c_str());

				/* columns */
				getline(conffile, inln);
				spr->cols = atoi(inln.c_str());

				spr->framewidth = spr->w / spr->cols;
				spr->frameheight = spr->h / spr->rows;

				sprmap->insert(std::pair<std::string, boost::shared_ptr< Sprite > >(spr->name, spr));
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

