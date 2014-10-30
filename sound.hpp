#ifndef SOUND_HPP
#define SOUND_HPP

#define audioFileID "background"
#define audioFileName "120.wav"
//move to txt


namespace sound
{

	map<string, Mix_Chunk*>* audioMap = nullptr;
	int curChannel = 0;

	int loadSounds()
	{
		audioMap = new map <string, Mix_Chunk*>;

		audioMap->insert(pair<string, Mix_Chunk*>(string(audioFileID), Mix_LoadWAV((char*)audioFileName)));

		return 0;
	}

	int unloadSounds()
	{

		return 0;
	}


	void play(const int VOL_PERCENT_TOT, const int VOL_PERCENT_L, string audioName)
	{
		const int VOL_TOT = (255 * VOL_PERCENT_TOT) / 100;
		const int VOL_L = (VOL_PERCENT_L * VOL_TOT) / 100;
		const int VOL_R = VOL_TOT - VOL_L;

		Mix_SetPanning(curChannel, VOL_L, VOL_R);
		

		Mix_PlayChannelTimed(curChannel, audioMap->operator[](audioName), -1, -1);//third parameter being -1 means "infinite" loop

		curChannel++;

		if (curChannel >= 16)//16 being the nubmer of allocated channels
		{
			curChannel = 0;
		}

	}

}
#endif 