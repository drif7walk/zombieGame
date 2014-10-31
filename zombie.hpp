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
				bool y_x = this->y - (*it)->y - frameheight / 2 < this->x - (*it)->x + framewidth / 2;
				bool yx = this->y - (*it)->y - frameheight / 2 > -1 * (this->x - (*it)->x + framewidth / 2);
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
				

				//else
				//{
				//	this->direction = 3;
				//}
				//if (this->y - (*it)->y < 0)
				//{
				//	this->direction = 0;
				//}
				//else
				//{
				//	this->direction = 2;
				//}
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
