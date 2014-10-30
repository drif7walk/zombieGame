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
#define fontPath "SansationRegular.ttf"

	TTF_Font* _font_ = nullptr;
	SDL_Texture* _texture_ = nullptr;
	SDL_Renderer* _renderer_ = nullptr;
	SDL_Rect* _source_ = nullptr;
	SDL_Rect* _destination_ = nullptr;
	bool fontsAreInitialized = false;

	enum
	{
		normal = TTF_STYLE_NORMAL,
		bold = TTF_STYLE_BOLD,
		italic = TTF_STYLE_ITALIC,
		underline = TTF_STYLE_UNDERLINE,
		strikethrough = TTF_STYLE_STRIKETHROUGH
	};

	int initializeTTF(SDL_Renderer* renderer_)
	{
		if (fontsAreInitialized == false)
		{
			_source_ = new SDL_Rect;
			_destination_ = new SDL_Rect;
			_source_->x = 0;
			_source_->y = 0;
			if (renderer_ != nullptr)
			{
				_renderer_ = renderer_;
			}
			else
			{
				return -1;
			}
			if (TTF_Init() == -1)
			{
				return -1;
			}
			_font_ = TTF_OpenFont(fontPath, 24);
			if (_font_ == nullptr)
			{
				return -1;
			}
		}
		fontsAreInitialized = true;
		return 0;
		
	}

	int deinitializeTTF()
	{
		if (fontsAreInitialized == true)
		{
			delete _source_;
			delete _destination_;
			TTF_CloseFont(_font_);
			SDL_DestroyTexture(_texture_);
		}
		fontsAreInitialized = false;
		return 0;
	}
	
	void drawText(string text, SDL_Color textColor, SDL_Point location, int fontStyle, int scale)
	{
		TTF_SetFontStyle(_font_, fontStyle);

		SDL_Surface* textSurface = nullptr;
		textSurface = TTF_RenderText_Solid(_font_, text.data(), textColor);
		
		_texture_ = SDL_CreateTextureFromSurface(_renderer_, textSurface);
	
		_source_->w = textSurface->w;
		_source_->h = textSurface->h;
		*_destination_ = { textSurface->h * scale, textSurface->w * scale, location.x, location.y };
		
		SDL_FreeSurface(textSurface);
		SDL_RenderCopy(_renderer_, _texture_, _source_, _destination_);
	}

}

#endif