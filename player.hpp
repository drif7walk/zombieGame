#ifndef PLAYER_HPP
#define PLAYER_HPP

using namespace std;

class Player: public Sprite {

private:

	double velocity = 12;

public:

	void Update(vector<Sprite*> entlist, double deltaTime) override 
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
		
		if (!keydown)
			this->FreezeStep(direction);
		else
			this->AnimateStep(direction, deltaTime);
	}

	~Player()
	{

	}

    Player(string filename, SDL_Renderer* ren)
        : Sprite(filename, ren)
    {
        ;;
    }

};
#endif
