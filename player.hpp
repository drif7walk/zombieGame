#ifndef PLAYER_HPP
#define PLAYER_HPP

using namespace std;

class Player: public Sprite {

private:

	double velocity = 12;

public:

	void Update(double deltaTime) override 
	{
		Sprite::Update(deltaTime);

		const Uint8* keybuf = SDL_GetKeyboardState(NULL);

		if (keybuf[SDL_SCANCODE_W])
		{
			this->y += -velocity * deltaTime;
			this->AnimateStep(2, deltaTime);
		}
		if (keybuf[SDL_SCANCODE_A])
		{
			this->x += -velocity * deltaTime;
			this->AnimateStep(3, deltaTime);
		}
		if (keybuf[SDL_SCANCODE_S])
		{
			this->y += velocity * deltaTime;
			this->AnimateStep(0, deltaTime);
		}
		if (keybuf[SDL_SCANCODE_D])
		{
			this->x += velocity * deltaTime;
			this->AnimateStep(1, deltaTime);
		}

	}

    Player(string filename, SDL_Renderer* ren)
        : Sprite(filename, ren)
    {
        ;;
    }

};
#endif
