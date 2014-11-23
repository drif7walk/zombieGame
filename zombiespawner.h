#ifndef ZOMBIESPAWNER_H
#define ZOMBIESPAWNER_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "sprite.h"
#include "UI.h"

class Zombiespawner: public Sprite {

private:

public:
	int interval = 120;
	int spawntimer = 0;
	int maxzombies = 50;

	void Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites) override;

	Zombiespawner(Sprite* templatesprite) ;
	Zombiespawner(std::string filename, SDL_Renderer* ren);

};

#endif


