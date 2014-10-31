#ifndef TTF_HPP
#define TTF_HPP


/* to display any text you can use the followint function
 * you can call it like this drawText(yourString, { 0xff, 0x00, 0x00, 0xff }, { 100, 100 }, 2};
 * int drawText(string text, SDL_Color textColor, SDL_Point location, int fontStyle, int scale)
 * on failure -1 is returned and on success 0
 * 
 * to use more than one style at a time you need to use a bitwise or operator "bold | italic"
 * would produce a text that is both bold and italic
 */
namespace fonts
{
#define fontPath "font.ttf"


	bool fontsAreInitialized = false;

	enum
	{
		normal = TTF_STYLE_NORMAL,
		bold = TTF_STYLE_BOLD,
		italic = TTF_STYLE_ITALIC,
		underline = TTF_STYLE_UNDERLINE,
		strikethrough = TTF_STYLE_STRIKETHROUGH
	};

	//int initializeTTF(SDL_Renderer* renderer_)
	//{
	//	if (fontsAreInitialized == false)
	//	{
	//		if (renderer_ != nullptr)
	//		{
	//			_renderer_ = renderer_;
	//		}
	//		else
	//		{
	//			return -1;
	//		}
	//		if (TTF_Init() == -1)
	//		{
	//			return -1;
	//		}
	//		_font_ = TTF_OpenFont(fontPath, 12);
	//		if (_font_ == nullptr)
	//		{
	//			return -1;
	//		}
	//	}
	//	fontsAreInitialized = true;
	//	return 0;
	//	
	//}

	//int deinitializeTTF()
	//{
	//	if (fontsAreInitialized == true)
	//	{
	//		TTF_CloseFont(_font_);
	//		SDL_DestroyTexture(_texture_);
	//		SDL_FreeSurface(&textSurface);
	//	}
	//	fontsAreInitialized = false;
	//	return 0;
	//}
	
	void drawText(SDL_Renderer* renderer,string text, SDL_Color textColor, SDL_Point location, int fontStyle, int scale)
	{
		TTF_Font* font = NULL;
		font = TTF_OpenFont("font.ttf", 12);
		
		TTF_SetFontStyle(font, fontStyle);

		SDL_Surface* surf = TTF_RenderText_Solid(font, (const char*)text.c_str(), textColor);
		SDL_Texture* mytex = SDL_CreateTextureFromSurface(renderer, surf);

		SDL_FreeSurface(surf);
		TTF_CloseFont(font);
		

		int w, h;
		SDL_QueryTexture(mytex, NULL, NULL, &w, &h);

		SDL_Rect r = { location.x, location.y, w * scale, h * scale };
		SDL_RenderCopy(renderer, mytex, NULL, &r);
	}

}

#endif