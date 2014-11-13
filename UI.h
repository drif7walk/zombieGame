#ifndef UI_H
#define UI_H


#include <SDL.h>
#include <SDL_ttf.h>



#include <string>
#include <sstream>

class UI {

public:

	void AddKill();
	int getkillcount();
	std::string fireMode;
	int playerHealth;
	int maxplayerhealth;

	int SCRW = 800;
	int SCRH = 600;

	int RenderText (SDL_Renderer* ren, std::string text, int x, int y);

	void Render(SDL_Renderer* ren);

	UI()
	{
		fireMode = "burst fire";
	}

	~UI()
	{
	}

};

#endif
