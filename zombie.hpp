#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

using namespace std;

class Zombie: public Sprite {

private:

	double velocity = 12;

public:

	void Update(double deltaTime) override 
	{
		Sprite::Update(deltaTime);


	}

    Zombie(SDL_Texture* tex)
        : Sprite(tex)
    {
        ;;
    }

    Zombie(string filename, SDL_Renderer* ren)
        : Sprite(filename, ren)
    {
        ;;
    }

};
#endif
