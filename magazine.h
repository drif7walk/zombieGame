#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "sprite.h"

class Magazine: public Sprite
{
private:
	int bulletCount = 0;

public:
	void Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites) override;
	Magazine(Sprite* templatesprite) ;
	Magazine(std::string filename, SDL_Renderer* ren);

	void decrement();
	int getCount() const;
	void pickUp();
};


#endif 
