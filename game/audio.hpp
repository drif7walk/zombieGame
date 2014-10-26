#ifndef AUDIO_HPP
#define AUDIO_HPP

class Audio
{
public:
	Audio()
	{
		audio = Mix_LoadWAV("assets/120.wav");
	}

	~Audio()
	{
		Mix_CloseAudio();
		Mix_FreeChunk(audio);
	}

private:
	Mix_Chunk* audio;	//TO-DO: create a vector of audio sounds, so that we can play other types of sound

public:
	inline void play(const int VOL_PERCENT_TOT, const int VOL_PERCENT_L)// volume in percentages 0-100 VOL_PERCENT_L would be the how much sound comes out of the left earphones/speakers
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

};
#endif 