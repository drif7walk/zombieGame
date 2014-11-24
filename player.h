#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "UI.h"

#include "magazine.h"

class Player : public Sprite {
private:
	int switchDelay = 0;
	int timeSinceLastHit = 0;
	int bulletDelay = 0;


	int reloadDelay = 0;
	int magazineCount = 0;
	boost::shared_ptr< Magazine > currentMagazine;
	boost::shared_ptr< std::vector< boost::shared_ptr< Magazine > > > magazines;
	bool reloading = false;


	void reload();

public:
	void Update(double deltaTime, boost::shared_ptr<UI> ui,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > entlist,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > spawnlist,
		boost::shared_ptr< std::map < std::string, boost::shared_ptr< Sprite > > > sprites) override;

	Player(boost::shared_ptr< Sprite > templatesprite);
	Player(std::string filename, boost::shared_ptr< SDL_Renderer > ren);
};

#endif


