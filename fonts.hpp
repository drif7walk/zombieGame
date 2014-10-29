#ifndef TTF_HPP
#define TTF_HPP


/* to display any text you can use any of the overloaded drawText functions
 * int drawText(string text, SDL_Color textColor, SDL_Point location, int fontStyle, int scale)
 * int drawText(char* text, SDL_Color textColor, SDL_Point location, int fontStyle, int scale)
 * int drawText(char* text, int x, int y, int fontStyle, int scale)
 * int drawText(char* text, int r, int g, int b, int x, int y, int fontStyle, int scale)
 * int drawText(char* text, SDL_Point location, int fontStyle, int scale)
 * on failure -1 is returned and on success 0
 * 
 * 
 * to use more than one style at a time you need to use a bitwise or operator "bold | italic"
 * would produce a text that is both bold and italic
 * 
 * 
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
			SDL_DestroyTexture(_texture_);
		}
		fontsAreInitialized = false;
		return 0;
	}
	
	int drawText(string text, SDL_Color textColor, SDL_Point location, int fontStyle, int scale)
	{
		if (fontsAreInitialized == true)
		{
			SDL_DestroyTexture(_texture_);

			if (scale <= 0)
			{
				scale = 1;
			}

			if (fontStyle < 0)
			{
				fontStyle = 0;
			}

			TTF_SetFontStyle(_font_, fontStyle);

			SDL_Surface* textSurface = nullptr;
			textSurface = TTF_RenderText_Solid(_font_, text.data(), textColor);
			if (textSurface == nullptr)
			{
				return -1;
			}
			else
			{
				_texture_ = SDL_CreateTextureFromSurface(_renderer_, textSurface);
				if (_texture_ == nullptr)
				{
					return -1;
				}
				else
				{
					_source_->w = textSurface->w;
					_source_->h = textSurface->h;
					_destination_->h = textSurface->h * scale;
					_destination_->w = textSurface->w * scale;
					_destination_->x = location.x;
					_destination_->y = location.y;
				}
				SDL_FreeSurface(textSurface);
				SDL_RenderCopy(_renderer_, _texture_, _source_, _destination_);
			}
			return 0;
		}
		return -1;
	}
	
	int drawText(char* text, SDL_Color textColor, SDL_Point location, int fontStyle, int scale)
	{
		string text_;
		text_.assign(text);
		if (drawText(text_, textColor, location, fontStyle, scale) == -1)
		{
			return -1;
		}
		return 0;
	}

	int drawText(char* text, SDL_Point location, int fontStyle, int scale)
	{
		string text_;
		text_.assign(text);
		SDL_Color color = { 0xff, 0xff, 0xff, 0xff };
		if (drawText(text_, color, location, fontStyle, scale) == -1)
		{
			return -1;
		}
		return 0;
	}

	int drawText(char* text, int x, int y, int fontStyle, int scale)
	{
		string text_;
		text_.assign(text);
		SDL_Color color = { 0xff, 0xff, 0xff, 0xff };
		SDL_Point location = { x, y };
		if (drawText(text_, color, location, fontStyle, scale) == -1)
		{
			return -1;
		}
		return 0;
	}

	int drawText(char* text, int r, int g, int b, int x, int y, int fontStyle, int scale)
	{
		string text_;
		text_.assign(text);
		SDL_Color color = { r, g, b, 0xff };
		SDL_Point location = { x, y };
		if (drawText(text_, color, location, fontStyle, scale) == -1)
		{
			return -1;
		}
		return 0;
	}

}

#endif