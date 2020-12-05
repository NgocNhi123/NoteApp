#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "System.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* filename);
	static SDL_Texture* LoadText(const char* text,int &height, int &width, int split);

	static void Draw(SDL_Texture* tex, SDL_Rect scr, SDL_Rect dest);
};

#endif // !_TEXTUREMANAGER_H_
