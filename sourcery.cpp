#include "sourcery.h"


int Sourcery::UpdateGame(double frameTime)
{
	SDL_RenderClear(renderer.get());

	switch (this->state)
	{
		case 0:
		{
			spriteHandler->Update(ui, frameTime);
			ui->RenderMainMenu(renderer);

			auto keybuf = SDL_GetKeyboardState(NULL);

			if (keybuf[SDL_SCANCODE_Z])
			{
				this->state = 1;

				//===========================
				// CREATE GAME
				spriteHandler->entities->clear();
								/* Create a player object */

				spriteHandler->entities->push_back(boost::make_shared< Player >((*spriteHandler->sprites)["player"]));


				auto playerLocation = spriteHandler->entities->back()->locationVec;
				for (auto i = 0; i < 5; i++)
				{
					spriteHandler->entities->push_back(boost::make_shared< Magazine >((*spriteHandler->sprites)["magazine"]));
					spriteHandler->entities->back()->locationVec = playerLocation;
				}

			}
			
		}
		break;
		case 1:
			spriteHandler->Update(ui, frameTime);
			ui->Render(renderer);
		break;
		
	}

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

	/* Create demo scenario. */
				auto playerLocation = spriteHandler->entities->back()->locationVec;
				for (auto i = 0; i < 5; i++)
				{
					spriteHandler->entities->push_back(boost::make_shared< Magazine >((*spriteHandler->sprites)["magazine"]));
					spriteHandler->entities->back()->locationVec = playerLocation;
				}
				this->state = 1;

	spriteHandler->Initialize(ui);

	srand(time(NULL));


}
Sourcery::~Sourcery()
{
	/* Delete every texture from map */
	SDL_Quit();
}

