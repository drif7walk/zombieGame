#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "UI.h"


class Player : public Sprite {
private:	
	int switchDelay = 0;
	int timeSinceLastHit = 0;
	int bulletDelay = 0;


<<<<<<< HEAD
	int reloadDelay = 0;
	int magazineCount = 0;
	std::shared_ptr< Magazine > currentMagazine;
	std::shared_ptr< std::vector< std::shared_ptr< Magazine > > > magazines;
	bool reloading = false;


	void reload();

=======
>>>>>>> parent of 7bd50a5... magazine update for rapid fire mode
public:
	void Update(double deltaTime, std::shared_ptr<UI> ui,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
		std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites) override;
	
<<<<<<< HEAD
	Player(std::shared_ptr< Sprite > templatesprite);
	Player(std::string filename, std::shared_ptr< SDL_Renderer > ren);
=======
	Player(Sprite* templatesprite);
	Player(std::string filename, SDL_Renderer* ren);

>>>>>>> parent of 7bd50a5... magazine update for rapid fire mode
};

#endif


