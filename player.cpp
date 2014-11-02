#include "player.h"

void Player::Update(std::vector<Sprite*>* entlist, double deltaTime)
{
	for (std::vector<Sprite*>::iterator it = entlist->begin(); it != entlist->end(); it++)
	{

		if (strcmp((*it)->name.c_str(), "cursor") == 0)
		{
			bool y_x = this->locationVec.y - (*it)->locationVec.y - frameheight / 2 < this->locationVec.x - (*it)->locationVec.x + framewidth / 2;
			bool yx = this->locationVec.y - (*it)->locationVec.y - frameheight / 2 > -1 * (this->locationVec.x - (*it)->locationVec.x + framewidth / 2);
			
			if (y_x && yx)
			{
				this->direction = 3;
				break;
			}
			if (!y_x && yx)
			{
				this->direction = 2;
				break;
			}
			if (y_x && !yx)
			{
				this->direction = 0;
				break;
			}
			else
			{
				this->direction = 1;
				break;
			}
		}
	}
    //Sprite::Update(entlist, deltaTime);

	//const Uint8* keybuf = SDL_GetKeyboardState(NULL);

	//bool keydown = false;

	//if (keybuf[SDL_SCANCODE_W])
	//{
	//	this->y += -velocity * deltaTime;
	//	this->direction = 2;
	//	keydown = true;
	//}
	//if (keybuf[SDL_SCANCODE_A])
	//{
	//	this->x += -velocity * deltaTime;
	//	this->direction = 3;
	//
	//	keydown = true;
	//}
	//if (keybuf[SDL_SCANCODE_S])
	//{
	//	this->y += velocity * deltaTime;
	//	this->direction = 0;
	//	keydown = true;
	//}
	//if (keybuf[SDL_SCANCODE_D])
	//{
	//	this->x += velocity * deltaTime;
	//	this->direction = 1;

	//	keydown = true;
	//}

	//bool fire = keybuf[SDL_SCANCODE_KP_ENTER];
	//if (fire)
	//{
	//	fire = !fire;
	//	/* ALL BECAUSE OF THIS ONE LINE OF CODE AAAGGGHHRH */
	//	//entlist->push_back( new Bullet((*sprites)["bullet"]) );
	//}
	//	
	//if (!keydown)
	//	this->FreezeStep(direction);
	//else
	//	this->AnimateStep(direction, deltaTime);
}

Player::Player(Sprite* templatesprite): Sprite(templatesprite) 
{
	maxVelocity = 23;
}

Player::Player(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{

}
