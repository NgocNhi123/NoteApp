#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "System.h"

class Button {
private:
	SDL_Texture* objTexture;
	SDL_Rect scrRect, desRect;

public:
	Button(const char* texturesheet, int x, int y, int height, int width, double des);
	~Button() {}

	void Render();
	bool isInside(int mposx, int mposy);
};

#endif // !_BUTTON_H_