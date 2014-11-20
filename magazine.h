#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "sprite.h"

class Magazine: public Sprite
{
private:
	int bulletCount = 0;

public:
	void Update(double deltaTime, std::shared_ptr<UI> ui,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
		std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites) override;

	Magazine(std::shared_ptr< Sprite > templatesprite);
	Magazine(std::string filename, std::shared_ptr< SDL_Renderer > ren);

	void decrement();
	int getCount() const;
	void pickUp();
};


#endif 
