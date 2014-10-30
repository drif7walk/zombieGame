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
		map<string, Mix_Chunk*>::iterator p;
		for (p = audioMap->begin(); p != audioMap->end(); p++)
		{
			Mix_FreeChunk(p->second);
		}
		audioMap->clear();
		delete audioMap;
		return 0;
	}


	void play(const int volumePercentage, const int balanceLeft, string audioName)
	{
		const int totalVolume = (255 * volumePercentage) / 100;
		const int volumeLeft = (balanceLeft * totalVolume) / 100;
		const int volumeRight = totalVolume - volumeLeft;

		Mix_SetPanning(curChannel, volumeLeft, volumeRight);
		
		Mix_PlayChannelTimed(curChannel, audioMap->operator[](audioName), -1, -1);//third parameter being -1 means "infinite" loop

		curChannel++;

		if (curChannel >= 16)//16 being the number of allocated channels
		{
			curChannel = 0;
		}
	}


}
#endif 