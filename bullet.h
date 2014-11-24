#ifndef BULLET_H
#define BULLET_H

#include <memory>

#include "sprite.h"
#include "UI.h"

class Bullet: public Sprite {

private:
	float angle;
public:
	void Update(double deltaTime, boost::shared_ptr<UI> ui,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > entlist,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > spawnlist,
		boost::shared_ptr< std::map < std::string, boost::shared_ptr< Sprite > > > sprites) override;

	Bullet(boost::shared_ptr< Sprite > templatesprite, Vector location, Vector direction);
	Bullet(std::string filename, boost::shared_ptr< SDL_Renderer > ren);
	void Render(boost::shared_ptr < SDL_Renderer > ren) override;

};

#endif

