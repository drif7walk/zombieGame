#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>
#include <string>
using namespace std;

class Player: public Sprite {

private:

public:

	void Update() override 
	{
		Sprite::Update();

		const Uint8* keybuf = SDL_GetKeyboardState(NULL);

		if (keybuf[SDL_SCANCODE_W])
		{
			this->y += -3.142;
			this->AnimateStep(2);
		}
		if (keybuf[SDL_SCANCODE_A])
		{
			this->x += -3.142;
			this->AnimateStep(3);
		}
		if (keybuf[SDL_SCANCODE_S])
		{
			this->y += 3.142;
			this->AnimateStep(0);
		}
		if (keybuf[SDL_SCANCODE_D])
		{
			this->x += 3.142;
			this->AnimateStep(1);
		}

	}

    Player(string filename, SDL_Renderer* ren)
        : Sprite(filename, ren)
    {
        ;;
    }

};
#endif
