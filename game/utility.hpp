#ifndef UTILITY_HPP
#define UTILITY_HPP

inline bool pointInRect(const SDL_Point* p, const SDL_Rect* r)
{
	return ((p->x >= r->x) && (p->x < (r->x + r->w)) && (p->y >= r->y) && (p->y < (r->y + r->h)) ? true : false);
}//original code do not steal

typedef enum
{
	mainMenuState,
	settingsState,
	highscoreState,
	gameplayState,
	pauseMenuState,
	quitState
} GameState;

#endif