#include "sourcery.h"

int Sourcery::Update(double frameTime)
{
	SDL_RenderClear(renderer);

	
	const Uint8* keybuf = SDL_GetKeyboardState(NULL);

	bool keydown = false;

	if (keybuf[SDL_SCANCODE_W])
	{
		spriteHandler->player->locationVec.y += -spriteHandler->player->velocity * frameTime;
		spriteHandler->player->direction = 2;
		keydown = true;
	}
	if (keybuf[SDL_SCANCODE_A])
	{
		spriteHandler->player->locationVec.x += -spriteHandler->player->velocity * frameTime;
		spriteHandler->player->direction = 3;
		keydown = true;
	}
	if (keybuf[SDL_SCANCODE_S])
	{
		spriteHandler->player->locationVec.y += spriteHandler->player->velocity * frameTime;
		spriteHandler->player->direction = 0;
		keydown = true;
	}
	if (keybuf[SDL_SCANCODE_D])
	{
		spriteHandler->player->locationVec.x += spriteHandler->player->velocity * frameTime;
		spriteHandler->player->direction = 1;
		keydown = true;
	}

	if (keybuf[SDL_SCANCODE_RETURN])
	{
		spriteHandler->entities->push_back(new Bullet(
		  spriteHandler->sprites->operator[]("bullet"),
		{ spriteHandler->player->locationVec.x, spriteHandler->player->locationVec.y },
		  spriteHandler->player->direction));
	}

	if (!keydown)
		spriteHandler->player->FreezeStep(spriteHandler->player->direction);
	else
		spriteHandler->player->AnimateStep(spriteHandler->player->direction, frameTime);


	spriteHandler->Update(frameTime);
 
	/* ask irc to make this not eat memory */
	if (true)
	{
		std::stringstream s;
		s << "FPS: " << 1000.0 / frameTime;
		RenderText(renderer, s.str(), 10, 10);
	}

	SDL_RenderPresent(renderer);

	return 0;
}

int Sourcery::RenderText (SDL_Renderer* ren, std::string text, int x, int y)
{
	TTF_Font* font = NULL;
	font = TTF_OpenFont("font.ttf", 12);
	if (font == NULL)
		SDL_Log("Font is null: %s", SDL_GetError());

	SDL_Color col = { 255, 255, 255, 255 };

	SDL_Surface* surf = TTF_RenderText_Solid(font, (const char*)text.c_str(), col);
	SDL_Texture* mytex = SDL_CreateTextureFromSurface( ren, surf);	

	TTF_CloseFont(font);

	int w, h;
	SDL_QueryTexture(mytex, NULL, NULL, &w, &h);

	SDL_Rect r = { x, y, w, h };
	SDL_RenderCopy(ren, mytex, NULL, &r);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(mytex);
	mytex = nullptr;

	return 0;
}


Sourcery::Sourcery()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 )
	{
		SDL_Log("Failed to initialize.");
	}

	window = SDL_CreateWindow("hl3.exe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCRW, SCRH, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		SDL_Log("Failed to initialize.");
	}
		
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if ( TTF_Init() == -1 ) 
	{
		SDL_Log("Could not initialize SDL_TTF.");
	}

	spriteHandler = new SpriteHandler(renderer);

	//LoadSpritesFromList(renderer, sprites);

	srand(time(NULL));
		

}
Sourcery::~Sourcery()
{
	delete spriteHandler;
	/* Delete every texture from map */
	//std::vector<Sprite*>::iterator a;
	//for (a = entities->begin(); a != entities->end(); a++)
	//{
	//	delete(*a);
	//}
	//entities->clear();
	//delete entities;

	//std::map<std::string, Sprite*>::iterator p;
	//for(p = sprites->begin(); p != sprites->end(); p++) {
	//  	delete p->second;
	// 	}
	//sprites->erase(sprites->begin(), sprites->end());
	//delete sprites;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
