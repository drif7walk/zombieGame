#ifndef BULLET_H
#define BULLET_H
#include "sprite.h"

class Bullet: public Sprite {

private:
	float angle;
public:
	void Update(std::vector<Sprite*>* entlist, double deltaTime) override;
	Bullet(Sprite* templatesprite, Vector location, Vector direction);
	Bullet(std::string filename, SDL_Renderer* ren);
	void Render(SDL_Renderer* ren) override;
};

#endif
