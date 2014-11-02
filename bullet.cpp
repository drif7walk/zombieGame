#include "bullet.h"

void Bullet::Update(std::vector<Sprite*>* entlist, double deltaTime)
{
	Sprite::Update(entlist, deltaTime);
	locationVec = locationVec + velocityVec * deltaTime;

}


void Bullet::Render(SDL_Renderer* ren)
{
	SDL_Rect r = { (int)this->locationVec.x, (int)this->locationVec.y, (int)this->w, (int)this->h };
	SDL_RenderCopyEx(ren, this->texture, &src, &r, angle, NULL, SDL_FLIP_NONE);
}

Bullet::Bullet(Sprite* templatesprite, Vector location, Vector direction): Sprite(templatesprite)  
{
	this->locationVec.x = location.x;
	this->locationVec.y = location.y;
	this->directionVec = direction;

	angle = directionVec.angle();

	directionVec.normalize();
	maxVelocity = 40;
	directionVec = directionVec * 30.0f;//0.5f magic number do not touch
	accelerationVec = directionVec;

	velocityVec = velocityVec + accelerationVec;
	velocityVec.limit(maxVelocity);

}

Bullet::Bullet(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{
}
