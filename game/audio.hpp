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
	Mix_Chunk* audio;	//TO-DO: izveidot vektoru ar audio failiem, un iespeju speleet uz vairakiem kanaliem

public:
	inline void play(const int VOL_PERCENT_TOT, const int VOL_PERCENT_L)// VOL_PERCENT_TOT/L var buut no 0-100
	{
		int curChannel = 0;//TO-DO jaizveelas briivs kanaals
		const int VOL_TOT = (255 * VOL_PERCENT_TOT) / 100;
		const int VOL_L = (VOL_PERCENT_L * VOL_TOT) / 100;
		const int VOL_R = VOL_TOT - VOL_L;

		Mix_SetPanning(curChannel, VOL_L, VOL_R);

		if (Mix_Playing(0) == 0)
		{
			Mix_PlayChannel(curChannel, audio, 0);
		}
	}

};
#endif 