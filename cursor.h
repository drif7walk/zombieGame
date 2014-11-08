#ifndef CURSOR_H
#define CURSOR_H
#include <SDL.h>
#include <SDL_ttf.h>
#include "cursor.h"
#include "sprite.h"
#include "UI.h"

class Cursor: public Sprite {

private:

public:
	void Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime) override;
	
	void Render(SDL_Renderer* ren);

	Cursor(Sprite* templatesprite) ;
	Cursor(std::string filename, SDL_Renderer* ren);

};

#endif


