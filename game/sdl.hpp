#ifndef SDL_HPP
#define SDL_HPP

namespace sdl
{
	bool initialize()
	{
		if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		{
			return 1;
		}

		const int     AUDIO_FREQ = 44100;
		const Uint16  AUDIO_FORMAT = MIX_DEFAULT_FORMAT;
		const int     AUDIO_CHANNELS = 2;
		const int     AUDIO_BUFFERS = 1024;

		if (Mix_OpenAudio(AUDIO_FREQ, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS) != 0) 
		{
			return 1;
		}

		Mix_AllocateChannels(16);


		return 0;
	}
}

#endif