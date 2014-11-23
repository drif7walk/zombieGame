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
	Magazine* currentMagazine;
	std::vector<Magazine*>* magazines;
	bool reloading = false;


	void reload();

public:
	void Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites) override;
	
	Player(Sprite* templatesprite);
	Player(std::string filename, SDL_Renderer* ren);

	~Player() override;

};

#endif


