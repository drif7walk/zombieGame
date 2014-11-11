#ifndef WALL_H
#define WALL_H

#include <SDL.h>
#include "sprite.h"
#include "UI.h"

class Wall: public Sprite {

private:

public:
	void Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites) override;
	void Render(SDL_Renderer* ren) override;
	SDL_Rect GetRect() override;	
	Wall(Sprite* templatesprite) ;
	Wall(std::string filename, SDL_Renderer* ren);
};

#endif
