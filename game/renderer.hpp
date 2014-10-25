#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer
{
public:
	Renderer()
	{

	}

	~Renderer()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_DestroyTexture(ascii.texture);
	}

private:
	struct asciiTexture{
		SDL_Texture* texture;
		SDL_Rect source;
	};

	bool loadASCII()
	{
		SDL_Surface* surface = nullptr;

		surface = SDL_LoadBMP("assets/ascii.bmp");
		if (surface == nullptr)
		{
			return 1;
		}
		int i = SDL_SetColorKey(surface, 1, 0xff00ff);
		if ((ascii.texture = SDL_CreateTextureFromSurface(renderer, surface)) == nullptr)
		{
			return 1;
		}

		ascii.source.h = surface->h / 16;
		ascii.source.w = surface->w / 16;
		ascii.source.x = 0;
		ascii.source.y = 0;

		SDL_FreeSurface(surface);

		return 0;
	}

	void drawCharacter(const char* charCode, SDL_Rect* destination)
	{
		SDL_Rect Src = ascii.source;

		Src.y = ((int)*charCode / 16) * ascii.source.h;
		Src.x = ((int)*charCode - ((int)*charCode / 16) * 16) * ascii.source.w;
		
		SDL_RenderCopy(renderer, ascii.texture, &Src, destination);
	}

	void drawText(const char* string, SDL_Rect* destination)
	{
		char* ptr;
		SDL_Rect original = *destination;
		ptr = (char*)string;
		if (destination->h < 0)
		{
			destination->h = ascii.source.h;
		}
		if (destination->w < 0)
		{
			destination->w = ascii.source.w;
		}
		for (unsigned int i = 0; i < strlen(string); i++)
		{
			drawCharacter(ptr, destination);
			destination->x += destination->w;
			ptr++;
		}
		*destination = original;
		destination->y += destination->h;
	}

public:
	void drawText(const char* string, SDL_Rect* destination, int scale)
	{
		destination->w = ascii.source.w * scale;
		destination->h = ascii.source.h * scale;
		drawText(string, destination);
	}

	bool intitialize()
	{
		window = SDL_CreateWindow("alpha.exe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			return 1;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == nullptr)
			{
				return 1;
			}
		}

		if (loadASCII() != 0)
		{
			return 1;
		}

		return 0;
	}

	void drawFrame() // vajadzēs atseviškas katrai stadijai
	{
		clear();
		//render
		present();
	}//varbut jaatdala ka ar mainMenu.hpp

	inline void clear()
	{
		SDL_RenderClear(renderer);
	}

	inline void present()
	{
		SDL_RenderPresent(renderer);
	}

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	asciiTexture ascii;
};

#endif