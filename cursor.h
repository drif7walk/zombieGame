#ifndef CURSOR_H
#define CURSOR_H

#include <SDL.h>
#include <SDL_ttf.h>


#include "sprite.h"
#include "UI.h"

class Cursor: public Sprite {

private:

public:
<<<<<<< HEAD
	void Update(double deltaTime, std::shared_ptr<UI> ui,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
		std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites) override;
=======
	void Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites) override;
	
	void Render(SDL_Renderer* ren);
>>>>>>> parent of 7bd50a5... magazine update for rapid fire mode

	void Render(std::shared_ptr< SDL_Renderer > ren) override;

	Cursor(std::shared_ptr< Sprite > templatesprite);
	Cursor(std::string filename, std::shared_ptr< SDL_Renderer > ren);

};

#endif


