#ifndef CURSOR_HPP
#define CURSOR_HPP

using namespace std;

class Cursor: public Sprite {

private:

public:

	void Update(double deltaTime) override 
	{
		Sprite::Update(deltaTime);

		int x, y;
		SDL_GetMouseState(&x, &y);
		this->x = x;
		this->y = y;
	}

    Cursor(string filename, SDL_Renderer* ren)
        : Sprite(filename, ren)
    {
        SDL_ShowCursor(false);
    }

};
#endif
