#include "Button.h"
#include "TextureManager.h"
Button::Button(const char* texturesheet, int x, int y, int height, int width, double des)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	scrRect.h = height;
	scrRect.w = width;
	scrRect.x = 0;
	scrRect.y = 0;

	desRect.x = x;
	desRect.y = y;
	desRect.w = scrRect.w * des;
	desRect.h = scrRect.h * des;
}

void Button::Render()
{
	SDL_RenderCopy(System::renderer, objTexture, &scrRect, &desRect);
}

bool Button::isInside(int mposx, int mposy)
{
	if (mposx < desRect.x)
		return false;
	else if (mposx > desRect.x + desRect.w)
		return false;
	else if (mposy < desRect.y)
		return false;
	else if (mposy > desRect.y + desRect.h)
		return false;
	else
		return true;
}