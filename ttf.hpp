#ifndef TTF_HPP
#define TTF_HPP

class FontWrapper
{
public:
	FontWrapper()
	{
		font = TTF_OpenFont("SansationRegular.ttf", 24);
	}
	~FontWrapper()
	{

	}
private:
	TTF_Font* font;

public:
};

#endif TTF_HPP