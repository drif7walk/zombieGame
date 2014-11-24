#ifndef SPRITE_H
#define SPRITE_H

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include <SDL2/SDL.h>

#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include "vector.h"
#include "UI.h"

class Sprite {

protected:
	virtual void setDirection(Vector direction);// virtual because zombie is lacking textures and using the
	//full aglo will make the zombies dissapear under certain conditions so zombie has an override to
	//setDirection(Vector direction)

public:
	SDL_Texture* texture;
	Vector locationVec;
	double w = 1;
	double h = 1;
	int plane; // 0 - bg, 1 - entities on ground , 2 - entities with z-axis, 3 - ui
	double velocity;
	int state = 0;
	float animSpeed = 0.6;

	Vector velocityVec;
	Vector accelerationVec;
	Vector directionVec;
	float maxVelocity;

	bool destroyed;
	bool item;

	int healthPoints;
	int maxHealth;

	std::string name;

	int rows = 1;
	int cols = 1;
	float scale = 2;
	int framewidth;
	int frameheight;
	double framecount = 0;
	unsigned char direction = 0;
	bool persistent = true;
	SDL_Rect src;

	void AnimateStep(int direction, double deltaTime);
	void FreezeStep(int direction);

	SDL_Rect GetRect();

	virtual void Render(boost::shared_ptr< SDL_Renderer > ren);
	virtual void Render(boost::shared_ptr< SDL_Renderer > ren, Vector offset);

	virtual void Update(double deltaTime, boost::shared_ptr<UI> ui,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > entlist,
		boost::shared_ptr< std::vector< boost::shared_ptr< Sprite > > > spawnlist,
		boost::shared_ptr< std::map < std::string, boost::shared_ptr< Sprite > > > sprites);


	Sprite(boost::shared_ptr< Sprite > templatesprite);
	Sprite(std::string filename, boost::shared_ptr< SDL_Renderer > ren);

	virtual ~Sprite(){};

};

#endif

