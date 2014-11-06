#include "player.h"

void Player::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime)
{
	for (std::vector<Sprite*>::iterator it = entlist->begin(); it != entlist->end(); it++)
	{

		if (strcmp((*it)->name.c_str(), "cursor") == 0)
		{
			bool y_2x = this->locationVec.y - (*it)->locationVec.y < (this->locationVec.x - (*it)->locationVec.x) * 2;
			bool y__2x = this->locationVec.y - (*it)->locationVec.y < (this->locationVec.x - (*it)->locationVec.x) * 2 * -1;
			bool y_x2 = this->locationVec.y - (*it)->locationVec.y < (this->locationVec.x - (*it)->locationVec.x) / 2;
			bool y__x2 = this->locationVec.y - (*it)->locationVec.y < (this->locationVec.x - (*it)->locationVec.x) / 2 * -1;

			if (y__2x && y_2x)
			{
				this->direction = 0;
				break;
			}
			if (!y_x2 && y__x2)
			{
				this->direction = 1;
				break;
			}
			if (!y_2x && !y__2x)
			{
				this->direction = 2;
				break;
			}
			if (y_x2 && !y__x2)
			{
				this->direction = 3;
				break;
			}
			if (y__2x && !y__x2)
			{
				this->direction = 6;
				break;
			}
			if (!y_2x && y_x2)
			{
				this->direction = 4;
				break;
			}
			if (!y__2x && y__x2)
			{
				this->direction = 5;
				break;
			}
			if (y_2x && !y_x2)
			{
				this->direction = 7;
				break;
			}
			break;
		}
	}

}

Player::Player(Sprite* templatesprite): Sprite(templatesprite) 
{
	maxVelocity = 23;
}

Player::Player(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{
	
}

