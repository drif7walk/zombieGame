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
	void Update(double deltaTime, std::shared_ptr<UI> ui,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
		std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites) override;
	
	Zombie(std::shared_ptr< Sprite > templatesprite) ;
	Zombie(std::string filename, std::shared_ptr< SDL_Renderer > ren);

};

#endif

