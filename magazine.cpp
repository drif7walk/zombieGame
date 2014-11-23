#include "magazine.h"


Magazine::Magazine(Sprite* templatesprite): Sprite(templatesprite)  
{
	this->bulletCount = 30;
	this->src = { 0, 0, framewidth, frameheight};
	this->scale = 0.75f;
	this->plane = 1;
}

Magazine::Magazine(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{

}

void Magazine::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
	std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites)
{

}

void Magazine::decrement()
{
	this->bulletCount -= 1;
	int i = 0;
	if (bulletCount < 24)
	{
		i++;
		if (bulletCount < 18)
		{
			i++;
			if (bulletCount < 12)
			{
				i++;
				if (bulletCount < 6)
				{
					i++;;
					if (bulletCount < 3)
					{
						i++;
					}
				}
			}
		}
	}
	src.x = framewidth * i;
}

int Magazine::getCount() const
{
	return this->bulletCount;
}

void Magazine::pickUp()
{
	this->scale = 1;
	this->plane = 3;
}