#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "sprite.h"

class Zombie: public Sprite {

private:
	double velocity = 1.2;
	bool playerFound;
	int aggrodist = 500;
	int state = 0; /* 0 - spawning, 1 - walking, 2 - dying, 3 - deceased */
public:
	void Update(double deltaTime, boost::shared_ptr<UI> ui,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > entlist,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > spawnlist,
		boost::shared_ptr< std::map < std::string, boost::shared_ptr< Sprite > > > sprites) override;

	Zombie(boost::shared_ptr< Sprite > templatesprite) ;
	Zombie(std::string filename, boost::shared_ptr< SDL_Renderer > ren);

};

#endif

