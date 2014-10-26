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
		for (iterator = textures.begin(); iterator != textures.end(); iterator++)
		{
			SDL_DestroyTexture((*iterator)->texture);
		}
		int size = textures.size();
		for (int i = 0; i < size; i++)
		{
			delete textures.at(textures.size()-1);
			textures.pop_back();
		}
	}

private:
	struct Texture{
		SDL_Texture* texture;
		SDL_Rect source;
		TextureIdentifier identifier;//lai varetu zinat ar kuru teksturu tiek stradats
	};

	inline Texture* loadASCII()
	{
		SDL_Surface* surface = nullptr;
		SDL_Texture* texture = nullptr;
		Texture* _texture = new Texture;

		surface = SDL_LoadBMP("assets/ascii.bmp");
		if (surface == nullptr)
		{
			return nullptr;
		}
		int i = SDL_SetColorKey(surface, 1, 0xff00ff);
		if ((_texture->texture = SDL_CreateTextureFromSurface(renderer, surface)) == nullptr)
		{
			return nullptr;
		}

		_texture->source.h = surface->h / 16;
		_texture->source.w = surface->w / 16;
		_texture->source.x = 0;
		_texture->source.y = 0;

		_texture->identifier = ASCII;

		SDL_FreeSurface(surface);

		return _texture;
	}

	inline Texture* loadTexture(char* location)
	{
		SDL_Surface* surface = nullptr;
		SDL_Texture* texture = nullptr;
		Texture* _texture = new Texture;
		surface = SDL_LoadBMP(location);
		if (surface == nullptr)
		{
			return nullptr;
		}
		int i = SDL_SetColorKey(surface, 1, 0xff00ff);
		if ((_texture->texture = SDL_CreateTextureFromSurface(renderer, surface)) == nullptr)
		{
			return nullptr;
		}

		_texture->source.h = surface->h;
		_texture->source.w = surface->w;
		_texture->source.x = 0;
		_texture->source.y = 0;

		SDL_FreeSurface(surface);

		return _texture;
	}

	inline void drawCharacter(const char* charCode, SDL_Rect* destination)
	{
		SDL_Rect Src = (*iterator)->source;

		Src.y = ((int)*charCode / 16) * (*iterator)->source.h;
		Src.x = ((int)*charCode - ((int)*charCode / 16) * 16) * (*iterator)->source.w;

		SDL_RenderCopy(renderer, (*iterator)->texture, &Src, destination);
	}

	inline void drawText(const char* string, SDL_Rect* destination)
	{
		char* ptr;
		SDL_Rect original = *destination;
		ptr = (char*)string;
		if (destination->h < 0)
		{
			destination->h = (*iterator)->source.h;
		}
		if (destination->w < 0)
		{
			destination->w = (*iterator)->source.w;
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

	inline void loadTextures()
	{


	}

public:
	inline void loadMapTexture(SDL_Surface* surface)
	{
		Texture* texture = new Texture;
		texture->texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_Rect source;
		source.h = surface->h;
		source.w = surface->w;
		source.x = 0;
		source.y = 0;
		texture->source = source;
		texture->identifier = MAPTEXTURE;
		textures.push_back(texture);
	}

	inline void drawText(const char* string, SDL_Rect* destination, int scale)
	{
		findTextureInVector(ASCII);
		destination->w = (*iterator)->source.w * scale;
		destination->h = (*iterator)->source.h * scale;
		drawText(string, destination);
	}

	inline bool intitialize()
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
		textures.push_back(loadASCII());
		textures.push_back(loadTexture("assets/block.bmp"));
		textures.at(1)->identifier = BLOCK;
		textures.push_back(loadTexture("assets/sky.bmp"));
		textures.at(2)->identifier = SKY;
		iterator = textures.begin();


		return 0;
	}

	inline void drawTexture(TextureIdentifier textureID, SDL_Rect* destination)
	{
		findTextureInVector(textureID);
		SDL_RenderCopy(renderer, (*iterator)->texture, &(*iterator)->source, destination);

	}

	inline void clear()
	{
		SDL_RenderClear(renderer);
	}

	inline void present()
	{
		SDL_RenderPresent(renderer);
	}

	inline void findTextureInVector(TextureIdentifier identifier)
	{
		iterator = textures.begin();
		if ((*iterator)->identifier == identifier)
		{
			return;
		}
		for (iterator = textures.begin(); iterator != textures.end(); iterator++)
		{
			if ((*iterator)->identifier == identifier)
			{
				break;
			}
		}
	}

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	vector<Texture*> textures;
	vector<Texture*>::iterator iterator;

};

#endif