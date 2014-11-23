#include "player.h"

#include "bullet.h"
#include "zombie.h"

#include <algorithm>

void Player::reload()
{
	if (magazines->size() > 0)
	{
		auto it = magazines->begin();
		while (it != magazines->end())
		{
			if ((*it)->destroyed == true)
			{
			it = magazines->erase(it);
				this->magazineCount -= 1;
				continue;
			}
			it++;
		}

		reloading = true;
		reloadDelay = 400;
		currentMagazine = magazines->back();

		for (auto it = magazines->begin(); it != magazines->end(); it++)
		{
			if ((*it)->getCount() > currentMagazine->getCount())
			{
				currentMagazine = (*it);
			}
		}
	}
}

void Player::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites)

{

	const Uint8* keybuf = SDL_GetKeyboardState(NULL);
	Uint32 mouse = SDL_GetMouseState(NULL, NULL);

	bool keydown = false;

	
	this->directionVec = Vector(0, 0);
	if (keybuf[SDL_SCANCODE_R] && reloading == false)
	{
		this->reload();
	}
	if (keybuf[SDL_SCANCODE_W])
	{
		this->directionVec = this->directionVec + Vector(0, -1);
		keydown = true;
	}
	if (keybuf[SDL_SCANCODE_A])
	{
		this->directionVec = this->directionVec + Vector(-1, 0);
		keydown = true;
	}
	if (keybuf[SDL_SCANCODE_S])
	{
		this->directionVec = this->directionVec + Vector(0, 1);
		keydown = true;
	}
	if (keybuf[SDL_SCANCODE_D])
	{
		this->directionVec = this->directionVec + Vector(1, 0);
		keydown = true;
	}
	if (mouse & SDL_BUTTON(SDL_BUTTON_RIGHT) && switchDelay <=0)
	{
		switchDelay = 500;
		if (strcmp(ui->fireMode.data(), "rapid fire") == 0)
		{
			ui->fireMode = "burst fire";
		}
		else
		{
			ui->fireMode = "rapid fire";
		}
	}
	this->directionVec.normalize();
	this->accelerationVec = this->directionVec * 4.0f;
	this->velocityVec = this->velocityVec + this->accelerationVec;
	this->velocityVec.limit(this->maxVelocity);

	this->locationVec = this->locationVec + this->velocityVec * deltaTime;

	if (timeSinceLastHit >= 0)
	{
		timeSinceLastHit -= deltaTime * 25;
	}

	for (std::vector<Sprite*>::iterator it = entlist->begin(); it != entlist->end(); it++)
	{
		if (strcmp((*it)->name.c_str(), "magazine") == 0)
		{
			SDL_Rect r;
			r = this->GetRect();

			SDL_Rect r2;
			r2 = (*it)->GetRect();

			bool intersect = SDL_HasIntersection(&r, &r2);

			if (intersect)
			{
				bool reload_ = false;
				if (magazines->size() == 0)
				{
					reload_ = true;
				}
				dynamic_cast<Magazine*>(*it)->pickUp();
				this->magazineCount++;
				this->magazines->push_back(dynamic_cast<Magazine*>(*it));

				sort(magazines->begin(), magazines->end(), 
					[](const Magazine* a, const Magazine* b) -> 
					bool { return a->getCount() < b->getCount(); });

				int i = 1;

				if (reload_ == true)
				{
					reload();
				}
				continue;
			}
		}
		if (strcmp((*it)->name.c_str(), "zombie") == 0 && timeSinceLastHit <= 0)
		{
			SDL_Rect r;
			r = this->GetRect();

			SDL_Rect r2;
			r2 = (*it)->GetRect();

			bool intersect = SDL_HasIntersection(&r, &r2);

			if (intersect)
			{
				this->timeSinceLastHit = 80;
				this->healthPoints -= 10;
				if (this->healthPoints <= 0)
				{
					/* when you die you turn into a zombie */
					spawnList->push_back(new Zombie(sprites->operator[]("zombie")));
					spawnList->back()->name.assign("playerZombie");
					spawnList->back()->locationVec = this->locationVec;
					spawnList->back()->state = 1;// this wont work
					this->destroyed = true;
					continue;
				}
				continue;
			}
		}
		if (strcmp((*it)->name.c_str(), "cursor") == 0 && mouse & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			if (mouse & SDL_BUTTON(SDL_BUTTON_LEFT) && bulletDelay <= 0)
			{
				if (strcmp(ui->fireMode.data(), "burst fire") == 0)
				{ 
					bulletDelay = 300;
					Vector bulletDirection((*it)->locationVec - locationVec);

					for (int i = 0; i < 3; i++)
					{
						spawnList->push_back(new Bullet(
						/*     warning     */	sprites->operator[]("bullet"),
						/*placeholder magic*/	locationVec,
						/*                 */	bulletDirection));
					bulletDirection.rotate(rand() % 20 - 10);
					}
				}
				else
				{
					if (currentMagazine != nullptr && magazines->size() != 0)
					{
						if (currentMagazine->getCount() > 0 && reloading == false)
						{
							currentMagazine->decrement();
							bulletDelay = 10;
							Vector bulletDirection((*it)->locationVec - locationVec);
							spawnList->push_back(new Bullet(
								/*     warning     */	sprites->operator[]("bullet"),
								/*placeholder magic*/	locationVec,
								/*                 */	bulletDirection));
						}
						else if (currentMagazine->getCount() <= 0)
						{
							currentMagazine->destroyed = true;
							reload();
						}
					}
					else
					{
						reload();
					}

				}
			}


			setDirection((*it)->locationVec - locationVec);

			continue;
		}
			else if (!(mouse & SDL_BUTTON(SDL_BUTTON_LEFT)))
			{
				if (velocityVec.x == 0 && velocityVec.y == 0)
				{
					this->direction = 0;
					continue;
				}
				setDirection(velocityVec);
			}
	}

	if (!keydown)
	{
		FreezeStep(direction);
		velocityVec = Vector(0, 0);
	}
	else
	{
		AnimateStep(direction, deltaTime);
	}

	if (bulletDelay > 0)
	{
		bulletDelay -= deltaTime * 25;
	}
	if (switchDelay > 0)
	{
		switchDelay -= deltaTime * 25;
	}
	if (reloadDelay > 0)
	{
		reloadDelay -= deltaTime * 25;
	}
	else
	{
		reloading = false;
	}

	/* places the magazines in player inventory on the bottom of the screen */
	int i = 0;
	for (auto it2 = magazines->begin(); it2 != magazines->end(); it2++)
	{
		(*it2)->locationVec = Vector((*it2)->framewidth * i, 550);
		i++;
	}

	/* Set UI */
	ui->maxplayerhealth = this->maxHealth;
	ui->playerHealth = healthPoints;

}

Player::~Player()
{
	SDL_Log("player destructor...");
	delete magazines;/* entity list still points to the magazine
	objects so no need to delete those her*/
}

Player::Player(Sprite* templatesprite): Sprite(templatesprite) 
{
	maxVelocity = 23.0f;
	this->maxHealth = 100;
	healthPoints = maxHealth;
	this->plane = 2;
	scale = 3;

	magazines = new std::vector<Magazine*>;
}

Player::Player(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{
	maxVelocity = 23.0f;
	this->plane = 2;
}


