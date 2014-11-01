#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"


class Player : public Sprite {

public:
	void Update(std::vector<Sprite*>* entlist, double deltaTime) override;

	Player(Sprite* templatesprite);
	Player(std::string filename, SDL_Renderer* ren);

};

#endif

