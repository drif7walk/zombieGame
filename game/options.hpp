#ifndef OPTIONS_HPP
#define OPTIONS_HPP

class Options
{
private:
	int fps = 60;
	int volume = 100;

public:
	Options()
	{

	}
	~Options()
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

	void parseOptionsFile()
	{

	}


};

#endif