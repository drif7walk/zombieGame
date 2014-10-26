#ifndef SETTINGS_HPP
#define SETTINGS_HPP

class Settings//To-Do: pievienot veidu ka lasit no Settings faila un izmanto default vertibas ja tas nav;
{
private:
	int fps;
	int volume;
	int screenX;
	int screenY;

public:
	Settings()
	{//default variables kuri tiks parrakstiiti ja to vertibas tiks atrastas settings failaa
		fps = 60;
		volume = 100;
		screenX = 800;
		screenY = 600;
		parseSettingsFile();
	}

	~Settings()
	{

	}

	inline int getFPS()
	{
		return fps;
	}

	inline int getVolume()
	{
		return volume;
	}

	inline int getScreenX()
	{
		return screenX;
	}

	inline int getScreenY()
	{
		return screenY;
	}

	inline void parseSettingsFile()
	{

	}
	
	inline void writeToSettingsFile()
	{

	}

	inline void createNewSettingsFile()
	{

	}



};

#endif