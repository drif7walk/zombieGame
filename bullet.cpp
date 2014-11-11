#include "bullet.h"

void Bullet::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites)
{
	Sprite::Update(ui, entlist, deltaTime, spawnList, sprites);

	for (std::vector<Sprite*>::iterator it = entlist->begin(); it != entlist->end(); it++)
	{
		if (strcmp((*it)->name.c_str(), "wall") == 0)
		{
			SDL_Rect r;
			r = this->GetRect();

			SDL_Rect r2;
			r2 =(*it)->GetRect();

			int x1 = locationVec.x;
			int y1 = locationVec.y;
			int x2 = velocityVec.x + locationVec.x;
			int y2 = velocityVec.y + locationVec.y;

			bool intersect = SDL_IntersectRectAndLine(&r2, &x1, &y1, &x2, &y2);
			
			if (intersect)
			{				
				this->destroyed = true;
				break;
			}
		}

		if (strcmp((*it)->name.c_str(), "zombie") == 0)
		{
			SDL_Rect r;
			r = this->GetRect();

			SDL_Rect r2;
			r2 =(*it)->GetRect();

			int x1 = locationVec.x;
			int y1 = locationVec.y;
			int x2 = velocityVec.x + locationVec.x;
			int y2 = velocityVec.y + locationVec.y;

			bool intersect = SDL_IntersectRectAndLine(&r2, &x1, &y1, &x2, &y2);
			
			if (intersect)
			{				
				(*it)->healthPoints -= 2;
				this->destroyed = true;
				if ((*it)->healthPoints < 0)
				{
					if ((*it)->destroyed == false)
					{
						ui->AddKill();
					}
					(*it)->destroyed = true;
				}
				break;
			}

		}
	}


	locationVec = locationVec + velocityVec * deltaTime;
}


void Bullet::Render(SDL_Renderer* ren)
{
	SDL_Rect r = { (int)this->locationVec.x, (int)this->locationVec.y,
		(int)this->w * (int)this->scale, (int)this->h  * (int)this->scale};
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
	directionVec *= maxVelocity;
	accelerationVec = directionVec;

	velocityVec = velocityVec + accelerationVec;
	velocityVec.limit(maxVelocity);
}

Bullet::Bullet(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{

}

