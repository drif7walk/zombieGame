#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "UI.h"


class Player : public Sprite {
private:	
	int switchDelay = 0;
	const int maxHealth = 300;
	int timeSinceLastHit = 0;
	int bulletDelay = 0;


public:
	void Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites) override;
	
	Player(Sprite* templatesprite);
	Player(std::string filename, SDL_Renderer* ren);

};

#endif


