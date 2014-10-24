#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2\SDL.h>
#include <string.h>

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

	inline void clear()
	{
		SDL_RenderClear(renderer);
	}
	inline void present()
	{
		SDL_RenderPresent(renderer);
	}

	bool loadASCII()
	{
		SDL_Surface* surface = nullptr;

		surface = SDL_LoadBMP("assets/ascii.bmp");
		if (surface == nullptr)
		{
			return 1;
		}

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

	void drawCharacter(char* charCode, SDL_Rect* destination)
	{
		SDL_Rect Src = ascii.source;
		if (*charCode > 125 || *charCode < 0)
		{
			*charCode = 0;
		}
		Src.y = ((int)*charCode / 16) * ascii.source.h;
		Src.x = ((int)*charCode - ((int)*charCode / 16) * 16) * ascii.source.w;
		
		SDL_RenderCopy(renderer, ascii.texture, &Src, destination);
	}

	void drawText(char* string, SDL_Rect* destination)
	{
		char* ptr;
		SDL_Rect original = *destination;
		ptr = string;
		destination->h = ascii.source.h;
		destination->w = ascii.source.w;
		for (int i = 0; i < strlen(string); i++)
		{
			drawCharacter(ptr, destination);
			destination->x += destination->w;
			ptr++;
		}
		*destination = original;
		
		//	SDL_RenderCopy(renderer, texture, source, destination);
	}

	void drawText(char* string, SDL_Rect* destination, int scale)
	{
		destination->w *= scale;
		destination->h *= scale;
		drawText(string, destination);
	}

public:
	bool intitialize()
	{
		window = SDL_CreateWindow("alpha.exe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			return 1;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);// | SDL_RENDERER_PRESENTVSYNC);
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
	}

	void drawMenu(CurrentMenuButton currentMenuButton)
	{
		SDL_Rect destination;
		destination.x = 100;
		destination.y = 100;
		destination.h = ascii.source.h;

		clear();

		destination.x = 100 - ascii.source.w;
		destination.y = 100 + currentMenuButton * ascii.source.h;
		drawText(">", &destination);



		destination.x = 100;
		destination.y = 100;
		drawText("New Game", &destination);
		destination.y += destination.h;
		destination.x = 100;
		drawText("Options", &destination);
		destination.y += destination.h;
		destination.x = 100;
		drawText("Highscore", &destination);
		destination.y += destination.h;
		destination.x = 100;
		drawText("Quit", &destination);

		
		present();
	}

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	asciiTexture ascii;
};

#endif