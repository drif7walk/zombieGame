#ifndef BULLET_HPP
#define BULLET_HPP

using namespace std;

class Bullet: public Sprite {

private:

public:

	void Update(vector<Sprite*> entlist, double deltaTime) override 
	{
		Sprite::Update(entlist, deltaTime);

	}

    Bullet(string filename, SDL_Renderer* ren)
        : Sprite(filename, ren)
    {
        ;;
    }

};
#endif
