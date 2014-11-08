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
	std::stringstream playerHealth;

	int RenderText (SDL_Renderer* ren, std::string text, int x, int y);

	void Render(SDL_Renderer* ren);

	UI()
	{
		playerHealth << 100 << "%";
		fireMode = "burst fire";
	}

	~UI()
	{
	}

};

#endif
