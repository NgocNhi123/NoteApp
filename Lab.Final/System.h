#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string.h>
#include <vector>

#include "Note.h"
using namespace std;

class System {
private:
	int count = 0;
	int page = 0;
	bool isRunning;

	string inputText = " ";
	int mouseAt = -1;
	bool clicked = false;

	vector<Note> allNotes;
	vector<Tag> allTags;

	int pos = -1;
	SDL_Window* window;
public:
	System(){}
	~System(){}

	void init(const char* title, int xpos, int ypos, int widht, int height); // create window

	void handleEvents(string &cur);
	void render(string cur);
	void clean();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
};

#endif // !SYSTEM_H