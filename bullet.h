#ifndef BULLET_H
#define BULLET_H
#include "sprite.h"

class Bullet: public Sprite {

private:

public:
	void Update(std::vector<Sprite*>* entlist, double deltaTime) override;
	Bullet(Sprite* templatesprite, SDL_Point location, int direction);
	Bullet(std::string filename, SDL_Renderer* ren);
};

#endif
