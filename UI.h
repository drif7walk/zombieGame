#ifndef UI_H
#define UI_H

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <sstream>
#include <memory>

class UI {

public:

	int killcount = 0;
	void AddKill();
	int getkillcount();
	std::string fireMode;
	int playerHealth;
	int maxplayerhealth;

	int SCRW = 800;
	int SCRH = 600;

	int RenderText (boost::shared_ptr< SDL_Renderer > ren, std::string text, int x, int y);

	void RenderMainMenu(boost::shared_ptr< SDL_Renderer > ren);
	void Render(boost::shared_ptr< SDL_Renderer > ren);

	UI()
	{
		fireMode = "burst fire";
	}

	~UI()
	{
	}

};

#endif
