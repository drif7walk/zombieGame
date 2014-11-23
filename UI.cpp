/* TODO: Render HUD. */
#include "UI.h"

int killcount = 0;

void UI::AddKill()
{
	killcount++;
}
int UI::getkillcount()
{
	return killcount;
}

void UI::Render(SDL_Renderer* ren)
{
	std::stringstream ss (std::stringstream::in | std::stringstream::out);

	ss << "KILLS: " << this->getkillcount();

	RenderText(ren, ss.str(), 10, 10);

	ss.str(std::string());


	ss << "FIRE MODE: " << fireMode;
	RenderText(ren, ss.str(), 10, 20);

	/* Draw health bar */
	int h = 15;
	int x = 0;
	int y = SCRH - h;

	/* Background */
	SDL_SetRenderDrawColor( ren, 55, 55, 55, 255 );
	SDL_Rect r = { x, y, this->maxplayerhealth, h };
	SDL_RenderFillRect(ren, &r);
	SDL_SetRenderDrawColor( ren, 0, 0, 0, 255 );

	/* Bar */
	SDL_SetRenderDrawColor( ren, 255, 0, 0, 255 );
	r = { x + 5, y + 5, this->playerHealth - 5, h - 5};
	SDL_RenderFillRect(ren, &r);
	SDL_SetRenderDrawColor( ren, 0, 0, 0, 255 );
}

int UI::RenderText (SDL_Renderer* ren, std::string text, int x, int y)
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
