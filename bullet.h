#ifndef BULLET_H
#define BULLET_H

#include <memory>

#include "sprite.h"
#include "UI.h"

class Bullet: public Sprite {

private:
	float angle;
public:
	void Update(double deltaTime, std::shared_ptr<UI> ui,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
		std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites) override;
	
	Bullet(std::shared_ptr< Sprite > templatesprite, Vector location, Vector direction);
	Bullet(std::string filename, std::shared_ptr< SDL_Renderer > ren);
	void Render(std::shared_ptr < SDL_Renderer > ren) override;

};

#endif

