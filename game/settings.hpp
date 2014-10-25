#ifndef SETTINGS_HPP
#define SETTINGS_HPP

class Settings//To-Do: pievienot veidu ka lasit no Settings faila un izmanto default vertibas ja tas nav;
{
private:
	int fps;
	int volume;

public:
	Settings()
	{
		fps = 60;
		volume = 100;
	}

	~Settings()
	{

	}

	int getFPS()
	{
		return fps;
	}

	int getVolume()
	{
		return volume;
	}

	void parseSettingsFile()
	{

	}


};

#endif