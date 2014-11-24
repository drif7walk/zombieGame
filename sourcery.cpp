#include "sourcery.h"


int Sourcery::UpdateGame(double frameTime)
{
	SDL_RenderClear(renderer.get());

	spriteHandler->Update(ui, frameTime);

	ui->Render(renderer);

	SDL_RenderPresent(renderer.get());
	return 0;
}


Sourcery::Sourcery()
{
	ui = boost::make_shared<UI>();

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 )
	{
		SDL_Log("Failed to initialize.");
	}

	window = boost::shared_ptr<SDL_Window>(
		SDL_CreateWindow("hl3.exe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			ui->SCRW, ui->SCRH, SDL_WINDOW_SHOWN),
		[](SDL_Window* wind){SDL_DestroyWindow(wind); });

	if (window == nullptr)
	{
		SDL_Log("Failed to initialize.");
	}

	renderer = boost::shared_ptr<SDL_Renderer>(
		SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED),
		[](SDL_Renderer* ren){SDL_DestroyRenderer(ren); });

	if ( TTF_Init() == -1 )
	{
		SDL_Log("Could not initialize SDL_TTF.");
	}

	spriteHandler = boost::make_shared<SpriteHandler>(renderer);

	//LoadSpritesFromList(renderer, sprites);

	srand(time(NULL));


}
Sourcery::~Sourcery()
{
	/* Delete every texture from map */
	SDL_Quit();
}

