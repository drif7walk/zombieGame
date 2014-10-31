#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

using namespace std;

class Zombie: public Sprite {

private:

	double velocity = 6;

public:

	void Update(vector<Sprite*>* entlist, double deltaTime) override 
	{
		Sprite::Update(entlist, deltaTime);

		/* raggamuffin */
<<<<<<< HEAD
		for (vector<Sprite*>::iterator it = entlist->begin(); it != entlist->end(); it++)
=======
		double stepx = 0;
		double stepy = 0;
		for (vector<Sprite*>::iterator it = entlist.begin(); it != entlist.end(); it++)
>>>>>>> 7972c681bc64ef2b442a91396f545c9e42cfa023
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
				

<<<<<<< HEAD
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
=======
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

>>>>>>> 7972c681bc64ef2b442a91396f545c9e42cfa023
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
