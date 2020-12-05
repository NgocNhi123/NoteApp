#include "TextureManager.h"

SDL_Color color = { 0, 0, 0 };

SDL_Texture* TextureManager::LoadTexture(const char* filename)
{
	SDL_Surface* tmpSurface = IMG_Load(filename);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(System::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return tex;
}

SDL_Texture* TextureManager::LoadText(const char* text, int &height, int &width, int split)
{
	//SDL_Surface* tmpSurface = TTF_RenderText_Solid(TTF_OpenFont("Blenda Script.otf", 20), text, color);
	SDL_Surface* tmpSurface = TTF_RenderText_Blended_Wrapped(TTF_OpenFont("Blenda Script.otf", 20), text, color, split);
	height = tmpSurface->h;
	width = tmpSurface->w;

	SDL_Texture* tex = SDL_CreateTextureFromSurface(System::renderer, tmpSurface);
	
	SDL_FreeSurface(tmpSurface);
	TTF_CloseFont(TTF_OpenFont("Blenda Script.otf", 20));

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect scr, SDL_Rect dest)
{
	SDL_RenderCopy(System::renderer, tex, &scr, &dest);
}