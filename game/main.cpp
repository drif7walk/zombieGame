#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <SDL.h>
#include <SDL_mixer.h>
#include <string.h>
#include <vector>

using namespace std;//bad practice should not use this, only usage right now is for <vector>

//#include "userInput.hpp"

//DuPsys dereference everything

typedef enum
{
	newGameButton,
	settingsButton,
	highscoresButton,
	quitButton
} CurrentMenuButton;

typedef enum
{
	mainMenuState,
	settingsState,
	highscoreState,
	gameplayState,
	pauseMenuState,
	quitState
} GameState;

typedef enum
{
	ASCII,
	BLOCK,
	SKY,
	MAPTEXTURE
}TextureIdentifier;

typedef enum
{
	block = 1,
	sky
}Tile;

struct Texture{
	SDL_Texture* texture;
	SDL_Rect source;
	TextureIdentifier identifier;
};

class MapTile
{
public:
	MapTile()
	{

	}

	~MapTile()
	{

	}

private:
	bool traversible;
	Tile tileID;
	SDL_Rect rect;

public:
	inline Tile getTileID()
	{
		return tileID;
	}

	inline SDL_Rect getRect()
	{
		return rect;
	}

	inline void intialize(int x, int y, Tile tile)
	{
		tileID = tile;
		if (tile == sky)
		{
			traversible = true;
		}
		else if (tile == block)
		{
			traversible = false;
		}
		rect.h = 8;
		rect.w = 8;
		rect.x = x * 8;
		rect.y = y * 8;
	}
};

inline bool pointInRect(const SDL_Point* p, const SDL_Rect* r)
{
	return ((p->x >= r->x) && (p->x < (r->x + r->w)) && (p->y >= r->y) && (p->y < (r->y + r->h)) ? true : false);
}

inline void play(Mix_Chunk* audio, const int VOL_PERCENT_TOT, const int VOL_PERCENT_L)// volume in percentages 0-100 VOL_PERCENT_L would be the how much sound comes out of the left earphones/speakers
{
	int curChannel = 0;//TO-DO pick the next free channel
	const int VOL_TOT = (255 * VOL_PERCENT_TOT) / 100;
	const int VOL_L = (VOL_PERCENT_L * VOL_TOT) / 100;
	const int VOL_R = VOL_TOT - VOL_L;

	Mix_SetPanning(curChannel, VOL_L, VOL_R);

	if (Mix_Playing(0) == 0)//if the sound is already playing then dont play it again, this should only be for music
	{
		Mix_PlayChannel(curChannel, audio, 0);
	}
}



int main(int argc, char** argv)
{
	int fps = 60;
	int volume = 100;
	int screenX = 800;
	int screenY = 600;

	Mix_Chunk* audio;
	audio = Mix_LoadWAV("assets/120.wav");
	
	GameState state;
	SDL_Event e;
	bool failedToInit;

	failedToInit = false;

	if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		failedToInit = true;
	}

	const int     AUDIO_FREQ = 44100;
	const Uint16  AUDIO_FORMAT = MIX_DEFAULT_FORMAT;
	const int     AUDIO_CHANNELS = 2;
	const int     AUDIO_BUFFERS = 1024;

	if (Mix_OpenAudio(AUDIO_FREQ, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS) != 0)
	{
		failedToInit = true;
	}

	Mix_AllocateChannels(16);

	SDL_Window* window;
	SDL_Renderer* renderer = nullptr;
	vector<Texture*> textures;
	vector<Texture*>::iterator iterator;

	window = SDL_CreateWindow("alpha.exe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		failedToInit = true;
	}
	else
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr)
		{
			failedToInit = true;
		}
	}
	//should be in the loadTextures() function, whis is still a To-Do		
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	Texture* _texture = new Texture;

	surface = SDL_LoadBMP("assets/ascii.bmp");
	if (surface == nullptr)
	{
		delete audio;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		int size = textures.size();//upon deleting the renderer the texture in the texture vector are cleaned
		for (int i = 0; i < size; i++)//up as with the texture structures since they were allocated on the heap
		{
			SDL_DestroyTexture(textures.at(textures.size() - 1)->texture);
			delete textures.at(textures.size() - 1);
			textures.pop_back();
		}
		SDL_Quit();
		_CrtDumpMemoryLeaks();
		return 1;
	}
	int i = SDL_SetColorKey(surface, 1, 0xff00ff);//0xff00ff is equivalent to magenta or r=255, g=0, b=255;
	if ((_texture->texture = SDL_CreateTextureFromSurface(renderer, surface)) == nullptr)
	{
		delete audio;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		int size = textures.size();//upon deleting the renderer the texture in the texture vector are cleaned
		for (int i = 0; i < size; i++)//up as with the texture structures since they were allocated on the heap
		{
			SDL_DestroyTexture(textures.at(textures.size() - 1)->texture);
			delete textures.at(textures.size() - 1);
			textures.pop_back();
		}
		SDL_Quit();
		_CrtDumpMemoryLeaks();
		return 1;
	}

	_texture->source.h = surface->h / 16;//div by 16 because ascii tilesets are usually 16x16 characters, 256 char codes
	_texture->source.w = surface->w / 16;//and we only want to display one at a time
	_texture->source.x = 0;
	_texture->source.y = 0;

	_texture->identifier = ASCII;

	SDL_FreeSurface(surface);

	textures.push_back(_texture);

	SDL_Surface* surface_1 = nullptr;
	SDL_Texture* texture1 = nullptr;
	Texture* _texture1 = new Texture;
	surface_1 = SDL_LoadBMP("assets/block.bmp");
	if (surface_1 == nullptr)
	{
		delete audio;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		int size = textures.size();//upon deleting the renderer the texture in the texture vector are cleaned
		for (int i = 0; i < size; i++)//up as with the texture structures since they were allocated on the heap
		{
			SDL_DestroyTexture(textures.at(textures.size() - 1)->texture);
			delete textures.at(textures.size() - 1);
			textures.pop_back();
		}
		SDL_Quit();
		_CrtDumpMemoryLeaks();
		return 1;
	}
	SDL_SetColorKey(surface_1, 1, 0xff00ff);
	if ((_texture1->texture = SDL_CreateTextureFromSurface(renderer, surface_1)) == nullptr)
	{
		delete audio;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		int size = textures.size();//upon deleting the renderer the texture in the texture vector are cleaned
		for (int i = 0; i < size; i++)//up as with the texture structures since they were allocated on the heap
		{
			SDL_DestroyTexture(textures.at(textures.size() - 1)->texture);
			delete textures.at(textures.size() - 1);
			textures.pop_back();
		}
		SDL_Quit();
		_CrtDumpMemoryLeaks();
		return 1;
	}

	_texture1->source.h = surface->h;
	_texture1->source.w = surface->w;
	_texture1->source.x = 0;
	_texture1->source.y = 0;

	SDL_FreeSurface(surface_1);

	textures.push_back(_texture1);
	textures.at(1)->identifier = BLOCK;

	SDL_Surface* surface2 = nullptr;
	SDL_Texture* texture2 = nullptr;
	Texture* _texture2 = new Texture;
	surface2 = SDL_LoadBMP("assets/sky.bmp");
	if (surface2 == nullptr)
	{
		delete audio;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		int size = textures.size();//upon deleting the renderer the texture in the texture vector are cleaned
		for (int i = 0; i < size; i++)//up as with the texture structures since they were allocated on the heap
		{
			SDL_DestroyTexture(textures.at(textures.size() - 1)->texture);
			delete textures.at(textures.size() - 1);
			textures.pop_back();
		}
		SDL_Quit();
		_CrtDumpMemoryLeaks();
		return 1;
	}
	SDL_SetColorKey(surface2, 1, 0xff00ff);
	if ((_texture2->texture = SDL_CreateTextureFromSurface(renderer, surface2)) == nullptr)
	{
		delete audio;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		int size = textures.size();//upon deleting the renderer the texture in the texture vector are cleaned
		for (int i = 0; i < size; i++)//up as with the texture structures since they were allocated on the heap
		{
			SDL_DestroyTexture(textures.at(textures.size() - 1)->texture);
			delete textures.at(textures.size() - 1);
			textures.pop_back();
		}
		SDL_Quit();
		_CrtDumpMemoryLeaks(); 
		return 1;
	}

	_texture2->source.h = surface->h;
	_texture2->source.w = surface->w;
	_texture2->source.x = 0;
	_texture2->source.y = 0;

	SDL_FreeSurface(surface);

	textures.push_back(_texture2);
	textures.at(2)->identifier = SKY;

	iterator = textures.begin();
	state = mainMenuState;

	if (failedToInit == true)
	{
		delete audio;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		int size = textures.size();//upon deleting the renderer the texture in the texture vector are cleaned
		for (int i = 0; i < size; i++)//up as with the texture structures since they were allocated on the heap
		{
			SDL_DestroyTexture(textures.at(textures.size() - 1)->texture);
			delete textures.at(textures.size() - 1);
			textures.pop_back();
		}
		SDL_Quit();
		_CrtDumpMemoryLeaks();//this is just for testing so i remember to deallocate dynamic memory that was created on the heap
		return 1;
	}

	while(state != quitState)//the main loop of the program
	{
		if (state == mainMenuState)
		{
			int textScale;
			int topRightX;
			int topRightY;

			Uint32 waittime;
			Uint32 framestarttime;
			Sint32 delaytime;

			SDL_Rect fullRect;

			SDL_Rect newGameRect;
			SDL_Rect settingsRect;
			SDL_Rect highscoreRect;
			SDL_Rect quitRect;

			const char* newGameText =	" New Game ";
			const char* settingsText =	" Settings ";
			const char* highscoreText = "Highscores";
			const char* quitText =		"   Quit   ";

			SDL_Point mouse_position;//mouse position represented as its x and y coordinates

			SDL_Rect destination;

			CurrentMenuButton currentMenuButton;

			currentMenuButton = newGameButton;
			textScale = 5;//the characters are 10x10 pixels by default, this is the amount they are scaled by
			topRightX = 100;//the top right coordinates of the main menu text
			topRightY = 100;
			waittime = 1000 / fps;//1000/fps would be the ms that one frame should take to do its logic and render if it does this faster the remaining time is delayed using SDL_Delay
			framestarttime = 0;

			if ((*iterator)->identifier == ASCII)
			{
			}
			else
			for (iterator = textures.begin(); iterator != textures.end(); iterator++)
			{
				if ((*iterator)->identifier == ASCII)
				{
					break;
				}
			}//used so that the texture iterator is currently pointing to the ascii tileset

			//i have not tested it but the drawing of the text on the main menu should work with any tileset it "should" take minimal changes to the code
			//this assigns rectangles so that hovering the mouse over the text would select the button as if you were using your keyboard
			newGameRect.x = topRightX;
			newGameRect.y = topRightY;//the next line is the the reason for using findTextureInVector(ASCII) is used to get the parameters of the ascii tileset
			newGameRect.h = textScale * (*iterator)->source.h;
			newGameRect.w = textScale * (*iterator)->source.w * strlen(newGameText);

			settingsRect.x = topRightX;
			settingsRect.y = topRightY + textScale * (*iterator)->source.h * 1;
			settingsRect.h = textScale * (*iterator)->source.h;
			settingsRect.w = textScale * (*iterator)->source.w * strlen(settingsText);

			highscoreRect.x = topRightX;
			highscoreRect.y = topRightY + textScale * (*iterator)->source.h * 2;
			highscoreRect.h = textScale * (*iterator)->source.h;
			highscoreRect.w = textScale * (*iterator)->source.w * strlen(highscoreText);

			quitRect.x = topRightX;
			quitRect.y = topRightY + textScale * (*iterator)->source.h * 3;
			quitRect.h = textScale * (*iterator)->source.h;
			quitRect.w = textScale * (*iterator)->source.w * strlen(quitText);

			//the full size of the main menu text
			fullRect.x = topRightX;
			fullRect.y = topRightY;
			fullRect.h = textScale * (*iterator)->source.h * 4;
			fullRect.w = textScale * (*iterator)->source.w * strlen(quitText);
			while (state == mainMenuState)	
			{
				while (SDL_PollEvent(&e))//cycles through all the events in the event buffer
				{
					switch (e.type)
					{
					case SDL_MOUSEMOTION:
						SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
						if (pointInRect(&mouse_position, &fullRect))//first checks if the mouse pointer is on any of the four buttons
						{
							if (pointInRect(&mouse_position, &newGameRect))
							{
								currentMenuButton = newGameButton;
							}
							else if (pointInRect(&mouse_position, &settingsRect))
							{
								currentMenuButton = settingsButton;
							}
							else if (pointInRect(&mouse_position, &highscoreRect))
							{
								currentMenuButton = highscoresButton;
							}
							else if (pointInRect(&mouse_position, &quitRect))
							{
								currentMenuButton = quitButton;
							}
						}
						break;
					case SDL_QUIT:
						state = quitState;
						break;
					case SDL_KEYDOWN:
						if (e.key.keysym.sym == SDLK_RETURN && currentMenuButton == quitButton)
						{
							state = quitState;
							break;
						}
						if (e.key.keysym.sym == SDLK_UP)
						{
							if (currentMenuButton != newGameButton)
							{//using casting we can go through the 4 button states
								currentMenuButton = (CurrentMenuButton)((int)currentMenuButton - 1);
								break;
							}
							else
							{
								currentMenuButton = (CurrentMenuButton)3;
								break;
							}
						}
						if (e.key.keysym.sym == SDLK_DOWN)
						{
							if (currentMenuButton != quitButton)
							{
								currentMenuButton = (CurrentMenuButton)((int)currentMenuButton + 1);
								break;
							}
							else
							{
								currentMenuButton = (CurrentMenuButton)0;
								break;
							}
						}
						break;
					case SDL_MOUSEBUTTONDOWN:
						if (pointInRect(&mouse_position, &fullRect))//first checks if the mouse pointer is on any of the four buttons
						{
							if (e.button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &newGameRect))
							{
								state = gameplayState;
							}
							else /*if (e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &settingsRect))
								 //not currently used since both settings and highscores are not implemented
								 {
								 *state = settingsState;
								 }
								 else if (e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &highscoreRect))
								 {
								 *state = highscoreState;
								 }
								 else*/ if (e.button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &quitRect))
								 {
								state = quitState;
								break;
								 }
						}
						break;
					default: continue;
					}
				}
				SDL_RenderClear(renderer);

				//draws the ">" so the user know which button is currently selected
				destination.x = topRightX - (*iterator)->source.w * textScale;
				destination.y = topRightY + currentMenuButton * (*iterator)->source.h * textScale;
				
				if ((*iterator)->identifier == ASCII)
				{
				}
				else
				for (iterator = textures.begin(); iterator != textures.end(); iterator++)
				{
					if ((*iterator)->identifier == ASCII)
					{
						break;
					}
				}

				destination.w = (*iterator)->source.w * textScale;
				destination.h = (*iterator)->source.h * textScale;

				char* string1 = ">";

				if ((*iterator)->identifier == ASCII)
				{
				}
				else
				for (iterator = textures.begin(); iterator != textures.end(); iterator++)
				{
					if ((*iterator)->identifier == ASCII)
					{
						break;
					}
				}

				destination.w = (*iterator)->source.w * textScale;
				destination.h = (*iterator)->source.h * textScale;

				char* ptr1;
				SDL_Rect original5 = destination;
				ptr1 = (char*)string1;
				for (unsigned int i = 0; i < strlen(string1); i++)
				{//goes through the whole string and prints out every single char with no overlap 
					char* charCode = ptr1;
					SDL_Rect Src = (*iterator)->source;
					//converts an ascii char code to the x and y coodrdinates where the char can be found on the tileset
					Src.y = ((int)*charCode / 16) * (*iterator)->source.h;
					Src.x = ((int)*charCode - ((int)*charCode / 16) * 16) * (*iterator)->source.w;

					SDL_RenderCopy(renderer, (*iterator)->texture, &Src, &destination);
					destination.x += destination.w;
					ptr1++;
				}
				destination = original5;//goes to the next line
				destination.y += destination.h;

				//draws the menu text, this could be premade in a surface and coverted to a single texture but it is a non-issue right now, this sort of optimization will be used for the map when gameplay starts
				destination.x = topRightX;
				destination.y = topRightY;


				char* string2 = (char*)newGameText;
				char* ptr2;
				SDL_Rect original4 = destination;
				ptr2 = (char*)string2;
				for (unsigned int i = 0; i < strlen(string2); i++)
				{//goes through the whole string and prints out every single char with no overlap 
					char* charCode = ptr2;
					SDL_Rect Src = (*iterator)->source;
					//converts an ascii char code to the x and y coodrdinates where the char can be found on the tileset
					Src.y = ((int)*charCode / 16) * (*iterator)->source.h;
					Src.x = ((int)*charCode - ((int)*charCode / 16) * 16) * (*iterator)->source.w;

					SDL_RenderCopy(renderer, (*iterator)->texture, &Src, &destination);
					destination.x += destination.w;
					ptr2++;
				}
				destination = original4;//goes to the next line
				destination.y += destination.h;


				char* string3 = (char*)settingsText;
				char* ptr3;
				SDL_Rect original3 = destination;
				ptr3 = (char*)string3;
				for (unsigned int i = 0; i < strlen(string3); i++)
				{//goes through the whole string and prints out every single char with no overlap 
					char* charCode = ptr3;
					SDL_Rect Src = (*iterator)->source;
					//converts an ascii char code to the x and y coodrdinates where the char can be found on the tileset
					Src.y = ((int)*charCode / 16) * (*iterator)->source.h;
					Src.x = ((int)*charCode - ((int)*charCode / 16) * 16) * (*iterator)->source.w;

					SDL_RenderCopy(renderer, (*iterator)->texture, &Src, &destination);
					destination.x += destination.w;
					ptr3++;
				}
				destination = original3;//goes to the next line
				destination.y += destination.h;


				char* string4 = (char*)highscoreText;
				char* ptr4;
				SDL_Rect original2 = destination;
				ptr4 = (char*)string4;
				for (unsigned int i = 0; i < strlen(string4); i++)
				{//goes through the whole string and prints out every single char with no overlap 
					char* charCode = ptr4;
					SDL_Rect Src = (*iterator)->source;
					//converts an ascii char code to the x and y coodrdinates where the char can be found on the tileset
					Src.y = ((int)*charCode / 16) * (*iterator)->source.h;
					Src.x = ((int)*charCode - ((int)*charCode / 16) * 16) * (*iterator)->source.w;

					SDL_RenderCopy(renderer, (*iterator)->texture, &Src, &destination);
					destination.x += destination.w;
					ptr4++;
				}
				destination = original2;//goes to the next line
				destination.y += destination.h;


				char* string5 = (char*)quitText;
				char* ptr5;
				SDL_Rect original1 = destination;
				ptr5 = (char*)string5;
				for (unsigned int i = 0; i < strlen(string5); i++)
				{//goes through the whole string and prints out every single char with no overlap 
					char* charCode = ptr5;
					SDL_Rect Src = (*iterator)->source;
					//converts an ascii char code to the x and y coodrdinates where the char can be found on the tileset
					Src.y = ((int)*charCode / 16) * (*iterator)->source.h;
					Src.x = ((int)*charCode - ((int)*charCode / 16) * 16) * (*iterator)->source.w;

					SDL_RenderCopy(renderer, (*iterator)->texture, &Src, &destination);
					destination.x += destination.w;
					ptr5++;
				}
				destination = original1;//goes to the next line
				destination.y += destination.h;

				SDL_RenderPresent(renderer);

				play(audio, volume, 50);//currently only plays one soundtrack on a loop

				delaytime = waittime - (SDL_GetTicks() - framestarttime);//this is semi redundant because of vsync
				if (delaytime > 0)
					SDL_Delay((Uint32)delaytime);
				framestarttime = SDL_GetTicks();
			}
		}

		if (state == settingsState)
		{

		}

		if (state == highscoreState)
		{

		}

		if (state == gameplayState)
		{
			MapTile map[75][100];
			SDL_Rect fullScreen;

			Uint32 waittime;
			Uint32 framestarttime;
			Sint32 delaytime;	
			waittime = 1000 / fps;
			framestarttime = 0;
			fullScreen.x = 0;
			fullScreen.y = 0;
			fullScreen.h = screenY;
			fullScreen.w = screenX;		Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			rmask = 0xff000000;
			gmask = 0x00ff0000;
			bmask = 0x0000ff00;
			amask = 0x000000ff;
#else
			rmask = 0x000000ff;
			gmask = 0x0000ff00;
			bmask = 0x00ff0000;
			amask = 0xff000000;
#endif
			SDL_Surface* mapSurface = nullptr;
			mapSurface = SDL_CreateRGBSurface(0, 800, 600, 32, rmask, gmask, bmask, amask);
			SDL_Rect source;
			source.x = 0;
			source.y = 0;
			source.h = 8;
			source.w = 8;

			SDL_Surface* blockSurface = nullptr;
			blockSurface = SDL_LoadBMP("assets/block.bmp");
			SDL_SetColorKey(blockSurface, 1, 0xff00ff);

			SDL_Surface* skySurface = nullptr;
			skySurface = SDL_LoadBMP("assets/sky.bmp");
			SDL_SetColorKey(skySurface, 1, 0xff00ff);

			for (int y = 0; y < 75; y++)
			{
				for (int x = 0; x < 100; x++)
				{
					map[y][x].intialize(x, y, sky);
				}
			}
			for (int x = 0; x < 100; x++)
			{
				map[74][x].intialize(x, 74, block);
			}

			for (int y = 0; y < 75; y++)
			{
				for (int x = 0; x < 100; x++)
				{
					if (map[y][x].getTileID() == block)
					{
						SDL_BlitSurface(blockSurface, &source, mapSurface, &map[y][x].getRect());
					}
					else if (map[y][x].getTileID() == sky)
					{
						SDL_BlitSurface(skySurface, &source, mapSurface, &map[y][x].getRect());
					}
				}
			}

			Texture* texture = new Texture;
			texture->texture = SDL_CreateTextureFromSurface(renderer, mapSurface);
			SDL_Rect source1;
			source1.h = mapSurface->h;
			source1.w = mapSurface->w;
			source1.x = 0;
			source1.y = 0;
			texture->source = source1;
			texture->identifier = MAPTEXTURE;
			textures.push_back(texture);
			iterator = textures.begin();

			SDL_FreeSurface(mapSurface);
			SDL_FreeSurface(blockSurface);
			SDL_FreeSurface(skySurface);
			while (state == gameplayState)
			{
				while (SDL_PollEvent(&e))
				{
					switch (e.type)
					{
					case SDL_QUIT:
						state = quitState;
						break;
					case SDL_KEYDOWN:
						if (e.key.keysym.sym == SDLK_RETURN)
						{
							state = quitState;
							break;
						}
					default: continue;
					}
				}
				SDL_RenderClear(renderer);


				if ((*iterator)->identifier == MAPTEXTURE)
				{
				}
				else
				for (iterator = textures.begin(); iterator != textures.end(); iterator++)
				{
					if ((*iterator)->identifier == MAPTEXTURE)
					{
						break;
					}
				}
				SDL_RenderCopy(renderer, (*iterator)->texture, &(*iterator)->source, &fullScreen);

				SDL_RenderPresent(renderer);

				delaytime = waittime - (SDL_GetTicks() - framestarttime);
				if (delaytime > 0)
					SDL_Delay((Uint32)delaytime);
				framestarttime = SDL_GetTicks();
			}
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	int size = textures.size();//upon deleting the renderer the texture in the texture vector are cleaned
	for (int i = 0; i < size; i++)//up as with the texture structures since they were allocated on the heap
	{
		SDL_DestroyTexture(textures.at(textures.size() - 1)->texture);
		delete textures.at(textures.size() - 1);
		textures.pop_back();
	}
	SDL_Quit();
	_CrtDumpMemoryLeaks();
	return 0;
}
