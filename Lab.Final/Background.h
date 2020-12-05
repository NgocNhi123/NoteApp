#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "System.h"

class Background {
private:
	SDL_Rect scr, dest;
	SDL_Texture* background;

public:
	Background(const char* texturesheet, int width, int height);
	~Background() {}

	void DrawBackground();
};

#endif // !_BACKGROUND_H_