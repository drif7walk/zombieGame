#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "sprite.h"

class Magazine: public Sprite
{
private:
	int bulletCount = 0;

public:
	void Update(double deltaTime, boost::shared_ptr<UI> ui,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > entlist,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > spawnlist,
		boost::shared_ptr< std::map < std::string, boost::shared_ptr< Sprite > > > sprites) override;

	Magazine(boost::shared_ptr< Sprite > templatesprite);
	Magazine(std::string filename, boost::shared_ptr< SDL_Renderer > ren);

	void decrement();
	int getCount() const;
	void pickUp();
};


#endif
