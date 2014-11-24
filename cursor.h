#ifndef CURSOR_H
#define CURSOR_H

#include "sprite.h"
#include "UI.h"

class Cursor: public Sprite {

private:

public:
	void Update(double deltaTime, boost::shared_ptr<UI> ui,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > entlist,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > spawnlist,
		boost::shared_ptr< std::map < std::string, boost::shared_ptr< Sprite > > > sprites) override;

	void Render(boost::shared_ptr< SDL_Renderer > ren) override;

	Cursor(boost::shared_ptr< Sprite > templatesprite);
	Cursor(std::string filename, boost::shared_ptr< SDL_Renderer > ren);

};

#endif


