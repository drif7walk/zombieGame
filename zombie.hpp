#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

using namespace std;

class Zombie: public Sprite {

private:

	double velocity = 6;

public:

	void Update(vector<Sprite*> entlist, double deltaTime) override 
	{
		Sprite::Update(entlist, deltaTime);

		/* raggamuffin */
		double stepx = 0;
		double stepy = 0;
		for (vector<Sprite*>::iterator it = entlist.begin(); it != entlist.end(); it++)
		{
			if (strcmp((*it)->name.c_str(), "player") == 0)
			{

				if ((*it)->y > this->y)
				{
					stepy += this->velocity;
				}
				else if ((*it)->y < this->y)
					stepy -= this->velocity;
				else
					stepy += 0;

				if ((*it)->x > this->x)
					stepx += this->velocity;
				else if ((*it)->x < this->x)
					stepx -= this->velocity;
				else
					stepx = 0;

			}
		}

		this->x += stepx * deltaTime;
		if ( stepx*stepx > stepy*stepy)
		{
			//choose on x axis
			if (stepx > 0)
				this->direction = 1;
			else
				this->direction = 3;
		}
		else    //choose on y axis
		{
			if (stepy > 0)
				this->direction = 0;
			else
				this->direction = 2;
		}
		this->AnimateStep(direction, deltaTime);
		this->y += stepy * deltaTime;
	}

    Zombie(Sprite* templatesprite)
        : Sprite(templatesprite)
    {
    }

    Zombie(string filename, SDL_Renderer* ren)
        : Sprite(filename, ren)
    {
	this->velocity = rand()%5 - 2.5;
    }

};
#endif
