#include "System.h"

System* note = nullptr;
int main(int argc, char* argv[])
{
	string cur = "";
	note = new System();
	note->init("Note", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1500, 800);

	while (note->running()) {
		while(SDL_PollEvent(&System::event))
		{
			note->handleEvents(cur);
			note->render(cur);
		}
	}

	note->clean();

	return 0;
}