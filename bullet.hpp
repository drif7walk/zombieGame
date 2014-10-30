#ifndef BULLET_HPP
#define BULLET_HPP

using namespace std;

class Bullet: public Sprite {

private:

public:

	void Update(double deltaTime) override 
	{
		Sprite::Update(deltaTime);

	}

    Bullet(string filename, SDL_Renderer* ren)
        : Sprite(filename, ren)
    {
        ;;
    }

};
#endif
