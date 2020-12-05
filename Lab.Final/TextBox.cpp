#include "TextBox.h"
#include "TextureManager.h"

Textbox::Textbox(const char* text, int x, int y, double des, int split)
{
	objTexture = TextureManager::LoadText(text, scrRect.h, scrRect.w, split);

	scrRect.x = 0;
	scrRect.y = 0;

	desRect.x = x;
	desRect.y = y;
	desRect.w = scrRect.w * des;
	desRect.h = scrRect.h * des;
}

void Textbox::Render()
{
	SDL_RenderCopy(System::renderer, objTexture, &scrRect, &desRect);
}

bool Textbox::isInside(int mposx, int mposy)
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