#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <SDL_mixer.h>
namespace audio
{

	Mix_Chunk* audio;

	void load()
	{
		audio = Mix_LoadWAV("assets/120.wav");
	}


	void play(const int VOL_PERCENT_TOT, const int VOL_PERCENT_L)
	{
		int curChannel = 0;
		const int VOL_TOT = (255 * VOL_PERCENT_TOT) / 100;
		const int VOL_L = (VOL_PERCENT_L * VOL_TOT) / 100;
		const int VOL_R = VOL_TOT - VOL_L;

		Mix_SetPanning(curChannel, VOL_L, VOL_R);

		if (Mix_Playing(0) == 0)
		{
			Mix_PlayChannel(curChannel, audio, 0);
		}
	}

	void deinitialize()
	{
		Mix_CloseAudio();
		Mix_FreeChunk(audio);
	}

}
#endif 