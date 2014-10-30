#ifndef SOUND_HPP
#define SOUND_HPP


namespace sound
{

	map<string, Mix_Chunk>* audioMap = nullptr;

	int loadSounds()
	{
		audioMap = new map <string, Mix_Chunk>;
		return 0;
	}

	int unloadSounds()
	{

		return 0;
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
			//Mix_PlayChannel(curChannel, audio, 0);
		}
	}



}
#endif 