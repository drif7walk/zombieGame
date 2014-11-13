#include "player.h"
#include "bullet.h"

void Player::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites)

{

	const Uint8* keybuf = SDL_GetKeyboardState(NULL);
	Uint32 mouse = SDL_GetMouseState(NULL, NULL);

	bool keydown = false;

	if (this->healthPoints > 0)
	{
		this->directionVec = Vector(0, 0);
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
				this->healthPoints -= 1;
				if (this->healthPoints <= 0)
				{
					/* die(); ? */
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
					bulletDelay = 10;
					Vector bulletDirection((*it)->locationVec
						- locationVec);
					spawnList->push_back(new Bullet(
						/*     warning     */	sprites->operator[]("bullet"),
						/*placeholder magic*/	locationVec,
						/*                 */	bulletDirection));
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
	}

	if (bulletDelay > 0)
	{
		bulletDelay -= deltaTime * 25;
	}
	if (switchDelay > 0)
	{
		switchDelay -= deltaTime * 25;
	}

	/* Set UI */
	ui->maxplayerhealth = this->maxHealth;
	ui->playerHealth = healthPoints;
}

Player::Player(Sprite* templatesprite): Sprite(templatesprite) 
{
	maxVelocity = 23.0f;
	this->maxHealth = 100;
	healthPoints = maxHealth;
	this->plane = 1;
	scale = 2;
}

Player::Player(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{
	maxVelocity = 23.0f;
	this->plane = 1;
}


