#include "bullet.h"

void Bullet::Update(double deltaTime, std::shared_ptr<UI> ui,
	std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
	std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
	std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites)
{
	Sprite::Update(deltaTime, ui, entlist, spawnlist, sprites);
	locationVec = locationVec + velocityVec * deltaTime;

	for (auto it = entlist->begin(); it != entlist->end(); it++)
	{
		if (strcmp((*it)->name.c_str(), "zombie") == 0)
		{
			auto r = this->GetRect();
			auto r2 = (*it)->GetRect();

			auto intersect = SDL_HasIntersection( &r, &r2 );

			if (intersect)
			{			
				if ((*it)->healthPoints > 0)
				{
					this->destroyed = true;
				}
				(*it)->healthPoints -= 1;
				break;
			}
		}
	}
}


void Bullet::Render(std::shared_ptr< SDL_Renderer > ren)
{
	auto r = SDL_Rect{ (int)this->locationVec.x, (int)this->locationVec.y,
		(int)this->w * (int)this->scale, (int)this->h  * (int)this->scale};
	SDL_RenderCopyEx(ren.get(), this->texture, &src, &r, angle, NULL, SDL_FLIP_NONE);
}

Bullet::Bullet(std::shared_ptr< Sprite > templatesprite, Vector location, Vector direction): Sprite(templatesprite)  
{
	this->locationVec.x = location.x;
	this->locationVec.y = location.y;
	this->directionVec = direction;

	angle = directionVec.angle();

	directionVec.normalize();
	maxVelocity = 59;
	directionVec *= maxVelocity;
	accelerationVec = directionVec;

	velocityVec = velocityVec + accelerationVec;
	velocityVec.limit(maxVelocity);

	this->scale = 1;
	this->persistent = false;
	
}

Bullet::Bullet(std::string filename, std::shared_ptr< SDL_Renderer > ren) : Sprite(filename, ren)
{

}

