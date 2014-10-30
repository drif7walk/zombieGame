#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

using namespace std;

class Zombie: public Sprite {

private:

	double velocity = 12;

public:

	void Update(vector<Sprite*>* entlist, double deltaTime) override 
	{
		Sprite::Update(entlist, deltaTime);

		/* raggamuffin */
		for (vector<Sprite*>::iterator it = entlist->begin(); it != entlist->end(); it++)
		{
			if (strcmp((*it)->name.c_str(), "player") == 0)
			{

			}
		}
	}

    Zombie(Sprite* templatesprite)
        : Sprite(templatesprite)
    {
    }

    Zombie(string filename, SDL_Renderer* ren)
        : Sprite(filename, ren)
    {
    }

};
#endif
