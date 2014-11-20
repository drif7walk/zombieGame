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
				if (magazineCount == 0)
				{
					return;
				}
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

void Player::Update(double deltaTime, std::shared_ptr<UI> ui,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
		std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites) 
{
	auto keybuf = SDL_GetKeyboardState(NULL);
	auto mouse = SDL_GetMouseState(NULL, NULL);

	auto keydown = false;
	
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

	for (auto it = entlist->begin(); it != entlist->end(); it++)
	{
		if (strcmp((*it)->name.c_str(), "magazine") == 0)
		{
			auto r = this->GetRect();
			auto r2 = (*it)->GetRect();

			auto intersect = SDL_HasIntersection(&r, &r2);

			if (intersect)
			{
				auto reload_ = false;
				if (magazines->size() == 0)
				{
					reload_ = true;
				}

				auto magazine = std::dynamic_pointer_cast < Magazine >(*it);

				this->magazineCount++;

				magazine->pickUp();
			
				this->magazines->push_back(magazine);

				sort(magazines->begin(), magazines->end(), 
					[](const std::shared_ptr< Magazine > a, const std::shared_ptr< Magazine > b) -> 
					bool { return a->getCount() < b->getCount(); });

				auto i = 1;

				if (reload_ == true)
				{
					reload();
				}
				continue;
			}
		}
		if (strcmp((*it)->name.c_str(), "zombie") == 0 && timeSinceLastHit <= 0)
		{
			auto r = this->GetRect();
			auto r2 = (*it)->GetRect();

			auto intersect = SDL_HasIntersection(&r, &r2);

			if (intersect)
			{
				this->timeSinceLastHit = 80;
				this->healthPoints -= 10;
				if (this->healthPoints <= 0)
				{
					/* when you die you turn into a zombie */
					spawnlist->push_back(std::make_shared< Zombie >((*sprites)["zombie"]));
					spawnlist->back()->name.assign("playerZombie");
					spawnlist->back()->locationVec = this->locationVec;
					spawnlist->back()->state = 1;// this wont work
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
				auto mid = Vector(locationVec.x + framewidth / 2, locationVec.y + frameheight / 2);
				if (strcmp(ui->fireMode.data(), "burst fire") == 0)
				{ 
					bulletDelay = 300;
					auto bulletDirection = (*it)->locationVec - locationVec;

					for (int i = 0; i < 3; i++)
					{
						spawnlist->push_back(std::make_shared< Bullet >(
						/*     warning     */	sprites->operator[]("bullet"),
						/*placeholder magic*/	mid,
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
							auto bulletDirection((*it)->locationVec - locationVec);
							spawnlist->push_back(std::make_shared< Bullet >(
								/*     warning     */	sprites->operator[]("bullet"),
								/*placeholder magic*/	mid,
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
	auto i = 0;
	for (auto it2 = magazines->begin(); it2 != magazines->end(); it2++)
	{
		(*it2)->locationVec = Vector((*it2)->framewidth * i, 550);
		i++;
	}

	/* Set UI */
	ui->maxplayerhealth = this->maxHealth;
	ui->playerHealth = healthPoints;

}

Player::Player(std::shared_ptr< Sprite > templatesprite): Sprite(templatesprite) 
{
	maxVelocity = 23.0f;
	this->maxHealth = 100;
	healthPoints = maxHealth;
	this->plane = 2;
	scale = 3;

	magazines = std::make_shared< std::vector< std::shared_ptr< Magazine > > >();
}

Player::Player(std::string filename, std::shared_ptr< SDL_Renderer > ren): Sprite(filename, ren)
{
	maxVelocity = 23.0f;
	this->plane = 2;
}


