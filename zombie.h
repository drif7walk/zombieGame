#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "sprite.h"

class Zombie: public Sprite {

private:
	double velocity = 1.2;

public:
	void Update(std::vector<Sprite*>* entlist, double deltaTime) override;

	Zombie(Sprite* templatesprite) ;
	Zombie(std::string filename, SDL_Renderer* ren);

};

#endif
