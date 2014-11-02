#ifndef SPRITEHANDLER_H
#define SPRITEHANDLER_H

#define SCRW 800
#define SCRH 600

#include <map>
#include <vector>
#include <time.h>
#include <fstream>
#include <string>
#include <algorithm>

#include "sprite.h"
#include "player.h"
#include "cursor.h"
#include "bullet.h"
#include "zombie.h"

class SpriteHandler
{
private:
	SDL_Renderer* renderer;

	void LoadSpritesFromList(SDL_Renderer* ren, std::map<std::string, Sprite*>* sprmap);

public:

	std::map<std::string, Sprite*>* sprites;
	std::vector<Sprite*>* entities;

	Sprite* player;

	void Initialize();

	void Update(double frameTime);

	SpriteHandler(SDL_Renderer* renderer);
	~SpriteHandler();

};


#endif