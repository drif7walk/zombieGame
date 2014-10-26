#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer	//handles everything related to drawing things on the screen not really true
{				//because in game.hpp the map assembled and sent here to be made into a texture
public:
	Renderer()
	{

	}

	~Renderer()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		int size = textures.size();//upon deleting the renderer the texture in the texture vector are cleaned
		for (int i = 0; i < size; i++)//up as with the texture structures since they were allocated on the heap
		{	
			SDL_DestroyTexture(textures.at(textures.size() - 1)->texture);
			delete textures.at(textures.size() - 1);
			textures.pop_back();
		}
	}

private:
	struct Texture{
		SDL_Texture* texture;
		SDL_Rect source;
		TextureIdentifier identifier;
	};

	inline Texture* loadASCII()
		//loadASCII and loadTexture could become redundant if we use a descriptor
		//file to specify the location, source rectangle and the identifier that would be syncronised with
		//what the map tiles/entities would be identified by
	{
		SDL_Surface* surface = nullptr;
		SDL_Texture* texture = nullptr;
		Texture* _texture = new Texture;

		surface = SDL_LoadBMP("assets/ascii.bmp");
		if (surface == nullptr)
		{
			return nullptr;
		}
		int i = SDL_SetColorKey(surface, 1, 0xff00ff);//0xff00ff is equivalent to magenta or r=255, g=0, b=255;
		if ((_texture->texture = SDL_CreateTextureFromSurface(renderer, surface)) == nullptr)
		{
			return nullptr;
		}

		_texture->source.h = surface->h / 16;//div by 16 because ascii tilesets are usually 16x16 characters, 256 char codes
		_texture->source.w = surface->w / 16;//and we only want to display one at a time
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
		//converts an ascii char code to the x and y coodrdinates where the char can be found on the tileset
		Src.y = ((int)*charCode / 16) * (*iterator)->source.h;
		Src.x = ((int)*charCode - ((int)*charCode / 16) * 16) * (*iterator)->source.w;

		SDL_RenderCopy(renderer, (*iterator)->texture, &Src, destination);
	}

	inline void drawText(const char* string, SDL_Rect* destination)
	{
		char* ptr;
		SDL_Rect original = *destination;
		ptr = (char*)string;
		if (destination->h < 0)//this code is a fallback that REALLY should never run, i once commented it out and nothing changed
		{
			destination->h = (*iterator)->source.h;
		}
		if (destination->w < 0)
		{
			destination->w = (*iterator)->source.w;
		}
		for (unsigned int i = 0; i < strlen(string); i++)
		{//goes through the whole string and prints out every single char with no overlap 
			drawCharacter(ptr, destination);
			destination->x += destination->w;
			ptr++;
		}
		*destination = original;//goes to the next line
		destination->y += destination->h;
	}

	inline void loadTextures()//this funtion should be made to load all the bmp files acording to some text file that described where the files are and how they should be treated
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
		iterator = textures.begin();
	}
	//destination is a rectangle of pixels that the char should be drawn in
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
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == nullptr)
			{
				return 1;
			}
		}
		//should be in the loadTextures() function, whis is still a To-Do
		textures.push_back(loadASCII());
		textures.push_back(loadTexture("assets/block.bmp"));
		textures.at(1)->identifier = BLOCK;
		textures.push_back(loadTexture("assets/sky.bmp"));
		textures.at(2)->identifier = SKY;
		iterator = textures.begin();


		return 0;
	}
	//draws a texture by specifying its ID and where to draw it
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