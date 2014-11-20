#ifndef CURSOR_H
#define CURSOR_H

#include "sprite.h"
#include "UI.h"

class Cursor: public Sprite {

private:

public:
	void Update(double deltaTime, std::shared_ptr<UI> ui,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
		std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites) override;

	void Render(std::shared_ptr< SDL_Renderer > ren) override;

	Cursor(std::shared_ptr< Sprite > templatesprite);
	Cursor(std::string filename, std::shared_ptr< SDL_Renderer > ren);

};

#endif


