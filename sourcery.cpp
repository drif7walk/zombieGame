#include "sourcery.h"

int Sourcery::Update(double frameTime)
{
	SDL_RenderClear(renderer);
	
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

