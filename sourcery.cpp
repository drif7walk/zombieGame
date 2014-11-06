#include "sourcery.h"

int Sourcery::Update(double frameTime)
{
	SDL_RenderClear(renderer);


	const Uint8* keybuf = SDL_GetKeyboardState(NULL);
	Uint32 mouse = SDL_GetMouseState(NULL, NULL);

	bool keydown = false;

	if (spriteHandler->player->healthPoints > 0)
	{
		spriteHandler->player->directionVec = Vector(0, 0);
		if (keybuf[SDL_SCANCODE_W])
		{
			spriteHandler->player->directionVec = spriteHandler->player->directionVec + Vector(0, -1);
			keydown = true;
		}
		if (keybuf[SDL_SCANCODE_A])
		{
			spriteHandler->player->directionVec = spriteHandler->player->directionVec + Vector(-1, 0);
			keydown = true;
		}
		if (keybuf[SDL_SCANCODE_S])
		{
			spriteHandler->player->directionVec = spriteHandler->player->directionVec + Vector(0, 1);
			keydown = true;
		}
		if (keybuf[SDL_SCANCODE_D])
		{
			spriteHandler->player->directionVec = spriteHandler->player->directionVec + Vector(1, 0);
			keydown = true;
		}
		spriteHandler->player->directionVec.normalize();
		spriteHandler->player->accelerationVec = spriteHandler->player->directionVec * 4.0f;
		spriteHandler->player->velocityVec = spriteHandler->player->velocityVec + spriteHandler->player->accelerationVec;
		spriteHandler->player->velocityVec.limit(spriteHandler->player->maxVelocity);
		spriteHandler->player->locationVec = spriteHandler->player->locationVec + spriteHandler->player->velocityVec * frameTime;


		if (keybuf[SDL_SCANCODE_RETURN] || mouse & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			spriteHandler->entities->push_back(new Bullet(
				/*     warning     */	spriteHandler->sprites->operator[]("bullet"),
				/*placeholder magic*/	spriteHandler->player->locationVec + Vector(0, spriteHandler->player->framewidth * spriteHandler->player->scale + 5),
				/*                 */	spriteHandler->cursor->locationVec - spriteHandler->player->locationVec + Vector(0, -19.0f)));
		}

		if (!keydown)
		{
			spriteHandler->player->FreezeStep(spriteHandler->player->direction);
			spriteHandler->player->velocityVec = Vector();
		}
		else
		{
			spriteHandler->player->AnimateStep(spriteHandler->player->direction, frameTime);
		}
	}


	spriteHandler->Update(ui, frameTime);
 
	ui->Render(renderer);

	SDL_RenderPresent(renderer);
	 
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

	ui = new UI();
		

}
Sourcery::~Sourcery()
{
	/* Delete every texture from map */
	delete spriteHandler;

	//std::vector<Sprite*>::iterator a;
	//for (a = entities->begin(); a != entities->end(); a++)
	//{
	//	delete(*a);
	//}
	//entities->clear();
	//delete entities;
	//
	//std::map<std::string, Sprite*>::iterator p;
	//for(p = sprites->begin(); p != sprites->end(); p++) {
	//  	delete p->second;
	// 	}
	//sprites->erase(sprites->begin(), sprites->end());
	//delete sprites;

	delete ui;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

