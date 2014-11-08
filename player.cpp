#include "player.h"

void Player::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime)
{
	if (timeSinceLastHit >= 0)
	{
		timeSinceLastHit -= deltaTime * 25;
	}
	Uint32 mouse = SDL_GetMouseState(NULL, NULL); 
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
				this->timeSinceLastHit = 100;
				this->healthPoints -= rand() % 20 + 20;
				if (this->healthPoints <= 0)
				{
					this->destroyed = true;
					ui->playerHealth.str(std::string());
					ui->playerHealth << "DEAD";
					continue;
				}
				ui->playerHealth.str(std::string());
				int buffer = (double)healthPoints / (double)maxHealth * 100;
				ui->playerHealth << buffer << "%";
				continue;
			}
		}
		if (strcmp((*it)->name.c_str(), "cursor") == 0 && mouse & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			bool y_2x = this->locationVec.y - (*it)->locationVec.y < (this->locationVec.x - (*it)->locationVec.x) * 2;
			bool y__2x = this->locationVec.y - (*it)->locationVec.y < (this->locationVec.x - (*it)->locationVec.x) * 2 * -1;
			bool y_x2 = this->locationVec.y - (*it)->locationVec.y < (this->locationVec.x - (*it)->locationVec.x) / 2;
			bool y__x2 = this->locationVec.y - (*it)->locationVec.y < (this->locationVec.x - (*it)->locationVec.x) / 2 * -1;

			if (y__2x && y_2x)
			{
				this->direction = 0;
				continue;
			}
			else if (!y_x2 && y__x2)
			{
				this->direction = 1;
				continue;
			}
			else if (!y_2x && !y__2x)
			{
				this->direction = 2;
				continue;
			}
			else if (y_x2 && !y__x2)
			{
				this->direction = 3;
				continue;
			}
			else if (y__2x && !y__x2)
			{
				this->direction = 6;
				continue;
			}
			else if (!y_2x && y_x2)
			{
				this->direction = 4;
				continue;
			}
			else if (!y__2x && y__x2)
			{
				this->direction = 5;
				continue;
			}
			else if (y_2x && !y_x2)
			{
				this->direction = 7;
				continue;
			}
			continue;
		}
			else if (!(mouse & SDL_BUTTON(SDL_BUTTON_LEFT)))
			{
				if (velocityVec.x == 0 && velocityVec.y == 0)
				{
					this->direction = 0;
					continue;
				}
				bool y_2x = this->velocityVec.y > (this->velocityVec.x) * 2;
				bool y__2x = this->velocityVec.y > (this->velocityVec.x) * 2 * -1;
				bool y_x2 = this->velocityVec.y > (this->velocityVec.x) / 2;
				bool y__x2 = this->velocityVec.y > (this->velocityVec.x) / 2 * -1;

				if (y__2x && y_2x)
				{
					this->direction = 0;
				}
				else if (!y_x2 && y__x2)
				{
					this->direction = 1;
				}
				else if (!y_2x && !y__2x)
				{
					this->direction = 2;
				}
				else if (y_x2 && !y__x2)
				{
					this->direction = 3;
				}
				else if (y__2x && !y__x2)
				{
					this->direction = 6;
				}
				else if (!y_2x && y_x2)
				{
					this->direction = 4;
				}
				else if (!y__2x && y__x2)
				{
					this->direction = 5;
				}
				else if (y_2x && !y_x2)
				{
					this->direction = 7;
				}
			}
	}

}

Player::Player(Sprite* templatesprite): Sprite(templatesprite) 
{
	maxVelocity = 23.0f;
	healthPoints = maxHealth;
	this->plane = 1;
}

Player::Player(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{
	maxVelocity = 23.0f;
	this->plane = 1;
}


