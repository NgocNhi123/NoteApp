#include "Background.h"
#include "TextureManager.h"

Background::Background(const char* texturesheet, int width, int height)
{
	background = TextureManager::LoadTexture(texturesheet);
	
	scr.x = dest.x = 0;
	scr.y = dest.y = 0;
	scr.w = dest.w = width;
	scr.h = dest.h = height;
}

void Background::DrawBackground()
{
	TextureManager::Draw(background, scr, dest);
}