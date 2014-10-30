#ifndef CURSOR_HPP
#define CURSOR_HPP

using namespace std;

class Cursor: public Sprite {

private:

public:

	void Update(vector<Sprite*> entlist, double deltaTime) override 
	{
		Sprite::Update(entlist, deltaTime);

		int x, y;
		SDL_GetMouseState(&x, &y);
		this->x = x;
		this->y = y;
	}
	
	~Cursor()
	{

	}

    Cursor(string filename, SDL_Renderer* ren)
        : Sprite(filename, ren)
    {
        SDL_ShowCursor(false);
    }

};
#endif
