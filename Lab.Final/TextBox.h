#ifndef _TEXTBOX_H_
#define _TEXTBOX_H_

#include "System.h"

class Textbox {
private:
	SDL_Texture* objTexture;
	SDL_Rect scrRect, desRect;

public:
	Textbox(const char* text, int x, int y, double des, int split);
	~Textbox() {}

	void Render();
	bool isInside(int mposx, int mposy);

	void setHeight(int num) { scrRect.h = num; }
};

#endif // !_TEXTBOX_H_