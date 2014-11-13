#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "sprite.h"

class Zombie: public Sprite {

private:
	double velocity = 1.2;
	bool playerFound;
	int aggrodist = 500;
	int state = 0; /* 0 - spawning, 1 - walking */
public:
	void Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites) override;
	Zombie(Sprite* templatesprite) ;
	Zombie(std::string filename, SDL_Renderer* ren);

};

#endif

