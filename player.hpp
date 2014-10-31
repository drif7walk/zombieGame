#ifndef PLAYER_HPP
#define PLAYER_HPP

using namespace std;

class Player: public Sprite {

private:

	double velocity = 23;

public:

	void Update(vector<Sprite*>* entlist, double deltaTime) override 
	{
		Sprite::Update(entlist, deltaTime);

		const Uint8* keybuf = SDL_GetKeyboardState(NULL);

		bool keydown = false;

		if (keybuf[SDL_SCANCODE_W])
		{
			this->y += -velocity * deltaTime;
			this->direction = 2;
			keydown = true;
		}
		if (keybuf[SDL_SCANCODE_A])
		{
			this->x += -velocity * deltaTime;
			this->direction = 3;
	
			keydown = true;
		}
		if (keybuf[SDL_SCANCODE_S])
		{
			this->y += velocity * deltaTime;
			this->direction = 0;

			keydown = true;
		}
		if (keybuf[SDL_SCANCODE_D])
		{
			this->x += velocity * deltaTime;
			this->direction = 1;

			keydown = true;
		}

		for (vector<Sprite*>::iterator it = entlist->begin(); it != entlist->end(); it++)
		{
			if (strcmp((*it)->name.c_str(), "cursor") == 0)
			{
				bool y_x = this->y - (*it)->y + this->frameheight / 2 < this->x - (*it)->x + framewidth / 2;
				bool yx = this->y - (*it)->y + this->frameheight / 2 > -1 * (this->x - (*it)->x + framewidth / 2);
				if (y_x && yx)
				{
					this->direction = 3;
					return;
				}
				if (!y_x && yx)
				{
					this->direction = 2;
					return;
				}
				if (y_x && !yx)
				{
					this->direction = 0;
					return;
				}
				else
				{
					this->direction = 1;
					return;
				}
			}
		}
		
		if (!keydown)
			this->FreezeStep(direction);
		else
			this->AnimateStep(direction, deltaTime);
	}

	~Player()
	{

	}

	Player(Sprite* templatesprite)
		: Sprite(templatesprite)
	{

	}

    Player(string filename, SDL_Renderer* ren)
        : Sprite(filename, ren)
    {
        ;;
    }

};
#endif
