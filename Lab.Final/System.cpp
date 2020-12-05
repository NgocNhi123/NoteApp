#include "System.h"
#include "TextureManager.h"
#include "Button.h"
#include "Background.h"
#include "TextBox.h"
#include "Loader.h"

SDL_Renderer* System::renderer = nullptr;
SDL_Event System::event;

vector<Button*> buttons, NoteBox;
vector<Background*> backgrounds;
vector<Textbox> tagName;

void System::init(const char* title, int xpos, int ypos, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() >= 0)
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		isRunning = true;
	}
	else
		isRunning = false;

	SDL_StartTextInput();
	Loader::loadNote(allNotes, NoteBox);
	Loader::loadTag(allTags, tagName);
	Loader::loadScreen(buttons, backgrounds, width, height);
}

void System::handleEvents(string& cur)
{
	switch (event.type)
	{
	default:
		break;
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEWHEEL:
		if (event.wheel.y > 0) {
			if (page > 0) page--;
		}
		else if (event.wheel.y < 0) {
			if (page < int(allNotes.size() / 8)) page++;
		}
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
		{
			inputText.pop_back();
			cur = "input";
		}
		else if (event.key.keysym.sym == SDLK_RETURN) { //SDLK_RETURN: enter key
			inputText.push_back('\n');
			cur = "input";
		}
		else if (event.key.keysym.sym == SDLK_DOWN){
			if (page < int(allNotes.size() / 8)) page++;
		}
		else if (event.key.keysym.sym == SDLK_UP) {
			if (page > 0) page--;
		}
		break;
	case SDL_TEXTINPUT:
		//Append character
		if ((mouseAt == 0 && inputText.size() < 70)
			|| (mouseAt == 1 && inputText.size() < 700)
			|| (mouseAt == 2 && inputText.size() < 25)
			|| mouseAt == 3) {
			if (inputText.size() == 1 && inputText[0] == ' ')
				inputText.pop_back();
			inputText += event.text.text;
			cur = "input";
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		default:
			break;
		case SDL_BUTTON_LEFT:
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (clicked) {
				for (int i = 0; i < buttons.size(); i++) {
					if (buttons[i]->isInside(x, y)) {
						if (i == 0) {
							cur = "quit";
							clicked = false;
							pos = -1;
							mouseAt = -1;
						}
						else if (i == 2) {
							if (allTags.size() < 10) {
								cur = "new tag";

								Tag newTag("New Tag");
								allTags.push_back(newTag);

								pos = allTags.size() - 1;
								inputText = allTags[pos].Name();

								Textbox text(inputText.c_str(), 10, 100 + pos * 50, 1, 150);
								tagName.push_back(text);

								mouseAt = 2;
							}
						}
						else if (i == 4) cur = "set tag";
						else if (i == 5) {
							cur = "title";
							inputText = allNotes[pos].noteName();
							mouseAt = 0;
						}
						else if (i == 6) {
							cur = "note";
							inputText = allNotes[pos].noteText();
							mouseAt = 1;
						}
						//else if (i == 8) cur = "edit";
					}
				}
				if (cur == "set tag") {
					for (int i = 1; i < tagName.size(); i++) {
						if (tagName[i].isInside(x, y))
							if (allTags[i].doubleClick() == false) {
								allNotes[pos].addTag(allTags[i].Name());
								allTags[i].setDoubleclick(true);
							}
							else {
								allNotes[pos].deleteTag(allTags[i].Name());
								allTags[i].setDoubleclick(false);
							}
					}
				}
			}
			else if (cur == "view in tag") {
				for (int i = 0; i < NoteBox.size(); i++) {
					if (NoteBox[i]->isInside(x, y)) {
						cur = "view note";
						clicked = true;
						pos = page * 8 + i;
					}
				}
				for (int i = 0; i < buttons.size(); i++) {
					if (buttons[i]->isInside(x, y)) {
						if (i == 0) {
							cur = "quit";
							clicked = false;
							pos = -1;
							mouseAt = -1;
						}
						else if (i == 1) {
							cur = "new note";
							clicked = true;
						}
						else if (i == 2) {
							if (allTags.size() < 10) {
								cur = "new tag";

								Tag newTag("New Tag");
								allTags.push_back(newTag);

								pos = allTags.size() - 1;
								inputText = allTags[pos].Name();

								Textbox text(inputText.c_str(), 10, 100 + pos * 50, 1, 150);
								tagName.push_back(text);

								mouseAt = 2;
							}
						}
						else if (i == 3) {
							cur = "search";
							inputText = "";
							mouseAt = 3;
						}
						else break;
					}
				}
			}
			else if (cur == "delete") {
				for (int i = 0; i < NoteBox.size(); i++) {
					if (NoteBox[i]->isInside(x, y)) {
						int place = i + page * 8;
						allNotes.erase(allNotes.begin() + place);
						NoteBox.pop_back();
					}
				}
				for (int i = 1; i < tagName.size(); i++) {
					if (tagName[i].isInside(x, y)) {
						for (int j = 0; j < allNotes.size(); j++)
							allNotes[j].deleteTag(allTags[i].Name());
						allTags.erase(allTags.begin() + i);
						tagName.erase(tagName.begin() + i);
						for (int k = i; k < allTags.size(); k++) {
							Textbox text(allTags[k].Name().c_str(), 10, 100 + k * 50, 1, 150);
							tagName[k] = text;
						}
					}
				}
				cur = "delete";
				if (buttons[0]->isInside(x, y))
					cur = "quit";
			}
			else {
				for (int i = 0; i < NoteBox.size(); i++) {
					if (NoteBox[i]->isInside(x, y)) {
						cur = "view note";
						pos = page * 8 + i;
						clicked = true;
					}
				}
				for (int i = 0; i < tagName.size(); i++) {
					if (tagName[i].isInside(x,y)) {
						cur = "view in tag";
						pos = i;
					}
				}
				for (int i = 0; i < buttons.size(); i++) {
					if (buttons[i]->isInside(x, y)) {
						if (i == 1) {
							cur = "new note";
							clicked = true;

							Note newNote;
							allNotes.push_back(newNote);

							pos = allNotes.size() - 1;

							NoteBox.push_back(new Button("Picture/notebox.png", 
								200 + 310 * abs(pos - int(pos / 4) * 4), 200 + 300 * int(pos / 4), 422, 434, 0.7));
						}
						else if (i == 2) {
							if (allTags.size() < 10) {
								cur = "new tag";

								Tag newTag("New Tag");
								allTags.push_back(newTag);

								pos = allTags.size() - 1;
								inputText = allTags[pos].Name();

								Textbox text(inputText.c_str(), 10, 100 + pos * 50, 1, 150);
								tagName.push_back(text);
								mouseAt = 2;
							}
						}
						else if (i == 3) {
							cur = "search";
							inputText = "";
							mouseAt = 3;
						}
						else if (i == 7) {
							cur = "delete";
						}
						else break;
					}
				}
			}
			break;
		}
		break;
	}
}

void System::render(string cur)
{
	cout << cur << " " << pos << " " << mouseAt << " " << clicked << endl;
	if (cur == "input") {
		Textbox* text;
		if (mouseAt == 0) {
			SDL_Rect rect = { 390,245,610,70 };
			if (inputText == "")
				inputText = " ";

			allNotes[pos].setName(inputText);

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &rect);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderDrawRect(renderer, &rect);

			text = new Textbox(inputText.c_str(), 400, 250, 1.2, 500);
			text->Render();
		}
		else if (mouseAt == 1) {
			SDL_Rect rect = { 390,335,860,365 };
			if (inputText == "")
				inputText = " ";

			allNotes[pos].setText(inputText);

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &rect);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderDrawRect(renderer, &rect);

			text = new Textbox(inputText.c_str(), 400, 340, 1.2, 700);
			text->Render();
		}
		else if (mouseAt == 2) {
			SDL_Rect rect = { 10,100 + pos * 50,150,50 };
			if (inputText == "")
				inputText = " ";

			allTags[pos].setName(inputText);

			text = new Textbox(allTags[pos].Name().c_str(), 10, 100 + pos * 50, 1, 150);
			tagName[pos] = *text;
		}
		else if (mouseAt == 3) {
			SDL_RenderClear(renderer);
			backgrounds[0]->DrawBackground();

			SDL_Rect rect = { 680,120,300,50 };
			if (inputText == "")
				inputText = " ";

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &rect);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderDrawRect(renderer, &rect);

			text = new Textbox(inputText.c_str(), 680, 120, 1.2, 300);
			text->Render();

			cout << inputText << endl;
			//search
			vector<int> found;
			for (int i = 0; i < allNotes.size(); i++) {
				if (inputText.size() == 1 && inputText[0] == ' ')
					inputText.pop_back();

				string text = allNotes[i].noteText();
				for (int j = 0; j < allNotes[i].noteText().length(); ++j) {
					if (text[j] <= 'Z' && text[j] >= 'A')
						text[j] += 32;
				}

				string pattern = inputText;
				for (int j = 0; j < inputText.length(); ++j) {
					if (pattern[j] <= 'Z' && pattern[j] >= 'A')
						pattern[j] += 32;
				}

				if (text.find(pattern) != string::npos)
					found.push_back(i);
			}

			for (int i = 0, place = page * 8 + i; i < 8 && place < found.size(); i++, place++) {
				Textbox* title, * text, * tags;

				NoteBox[i]->Render();

				title = new Textbox(allNotes[found[place]].noteName().c_str(),
					240 + 310 * abs(i - int(i / 4) * 4), 220 + 300 * int(i / 4), 1, 250);
				string note = allNotes[found[place]].noteText();
				if (note.size() > 76) {
					note = note.substr(0, 76);
					note.push_back('.');
					note.push_back('.');
					note.push_back('.');
				}
				text = new Textbox(note.c_str(),
					240 + 310 * abs(i - int(i / 4) * 4), 270 + 300 * int(i / 4), 1, 250);
				tags = new Textbox(allNotes[found[place]].viewTags().c_str(),
					240 + 310 * abs(i - int(i / 4) * 4), 430 + 300 * int(i / 4), 1, 250);

				title->Render();
				text->Render();
				tags->Render();
			}

			for (int i = 1; i < 4; i++)
				buttons[i]->Render();
			
		}
	}
	else if (cur == "new tag") {
		//do nothing
	}
	else if (cur == "title") {
		SDL_Rect rect = { 390,245,610,70 };

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &rect);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawRect(renderer, &rect);

		string withCursor = inputText;
		withCursor.push_back('|');
		Textbox text(withCursor.c_str(), 400, 250, 1.2, 500);
		text.Render();
	}
	else if (cur == "note") {
		SDL_Rect rect = { 390,335,860,365 };

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &rect);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawRect(renderer, &rect);

		string withCursor = inputText;
		withCursor.push_back('|');
		Textbox text(withCursor.c_str(), 400, 340, 1.2, 700);
		text.Render();
	}
	else if (cur == "new note") {
		SDL_RenderClear(renderer);
		backgrounds[1]->DrawBackground();
		buttons[0]->Render();
		//buttons[2]->Render();
		//buttons[8]->Render();

		Textbox noteTitle(allNotes[pos].noteName().c_str(), 400, 250, 1.2, 500);
		Textbox noteText(allNotes[pos].noteText().c_str(), 400, 340, 1.2, 700);
		Textbox noteTags(allNotes[pos].viewTags().c_str(), 400, 200, 1.2, 600);
		noteTitle.Render();
		noteText.Render();
		noteTags.Render();

		SDL_Rect rect = { 390,245,610,70 };

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawRect(renderer, &rect);

		rect = { 390,335,860,365 };

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawRect(renderer, &rect);
	}
	else if (cur == "set tag") {
		SDL_Rect rect = { 400,200,500,35 };
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &rect);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawRect(renderer, &rect);

		Textbox noteTags(allNotes[pos].viewTags().c_str(), 400, 200, 1.2, 600);
		noteTags.Render();
	}
	else if (cur == "search") {
		SDL_Rect rect = { 680,120,300,50 };
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &rect);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawRect(renderer, &rect);

		string withCursor = inputText;
		withCursor.push_back('|');
		Textbox text(withCursor.c_str(), 680, 120, 1.2, 300);
		text.Render();
	}
	else if (cur == "view note") {
		SDL_RenderClear(renderer);
		backgrounds[1]->DrawBackground();
		buttons[0]->Render();

		Textbox noteTitle(allNotes[pos].noteName().c_str(), 400, 250, 1.2, 500);
		Textbox noteText(allNotes[pos].noteText().c_str(), 400, 340, 1.2, 700);
		Textbox noteTags(allNotes[pos].viewTags().c_str(), 400, 200, 1.2, 600);
		noteTitle.Render();
		noteText.Render();
		noteTags.Render();

		SDL_Rect rect = { 390,245,610,70 };

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawRect(renderer, &rect);

		rect = { 390,335,860,365 };

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawRect(renderer, &rect);
	}
	else if (cur == "view in tag") {
		vector<int> belong;
		for (int i = 0; i < allNotes.size(); i++) {
			if (allNotes[i].tagged(allTags[pos].Name()))
				belong.push_back(i);
		}

		SDL_RenderClear(renderer);
		backgrounds[0]->DrawBackground();

		for (int i = 0, place = page * 8 + i; i < 8 && place < belong.size(); i++, place++) {
			Textbox* title, * text, * tags;

			NoteBox[i]->Render();

			title = new Textbox(allNotes[belong[place]].noteName().c_str(),
				240 + 310 * abs(i - int(i / 4) * 4), 220 + 300 * int(i / 4), 1, 250);
			string note = allNotes[belong[place]].noteText();
			if (note.size() > 76) {
				note = note.substr(0, 76);
				note.push_back('.');
				note.push_back('.');
				note.push_back('.');
			}
			text = new Textbox(note.c_str(),
				240 + 310 * abs(i - int(i / 4) * 4), 270 + 300 * int(i / 4), 1, 250);
			tags = new Textbox(allNotes[belong[place]].viewTags().c_str(),
				240 + 310 * abs(i - int(i / 4) * 4), 430 + 300 * int(i / 4), 1, 250);

			title->Render();
			text->Render();
			tags->Render();
		}

		for (int i = 0; i < 4; i++)
			buttons[i]->Render();
	}
	else if (cur == "delete") {
		SDL_RenderClear(renderer);
		backgrounds[0]->DrawBackground();

		for (int i = 0, place = page * 8 + i; i < 8 && place < allNotes.size(); i++, place++) {
			Textbox* title, * text, * tags;

			NoteBox[i]->Render();

			title = new Textbox(allNotes[place].noteName().c_str(),
				240 + 310 * abs(i - int(i / 4) * 4), 220 + 300 * int(i / 4), 1, 250);
			string note = allNotes[place].noteText();
			if (note.size() > 76) {
				note = note.substr(0, 76);
				note.push_back('.');
				note.push_back('.');
				note.push_back('.');
			}
			text = new Textbox(note.c_str(),
				240 + 310 * abs(i - int(i / 4) * 4), 270 + 300 * int(i / 4), 1, 250);
			tags = new Textbox(allNotes[place].viewTags().c_str(),
				240 + 310 * abs(i - int(i / 4) * 4), 430 + 300 * int(i / 4), 1, 250);

			title->Render();
			text->Render();
			tags->Render();
		}

		buttons[0]->Render();
	}
	else { //userScreen
		SDL_RenderClear(renderer);
		backgrounds[0]->DrawBackground();

		for (int i = 0, place = page * 8 + i; i < 8 && place < allNotes.size(); i++, place++) {
			Textbox* title, * text, * tags;

			NoteBox[i]->Render();

			title = new Textbox(allNotes[place].noteName().c_str(),
				240 + 310 * abs(i - int(i / 4) * 4), 220 + 300 * int(i / 4), 1, 250);
			string note = allNotes[place].noteText();
			if (note.size() > 76) {
				note = note.substr(0, 76);
				note.push_back('.');
				note.push_back('.');
				note.push_back('.');
			}
			text = new Textbox(note.c_str(),
				240 + 310 * abs(i - int(i / 4) * 4), 270 + 300 * int(i / 4), 1, 250);
			tags = new Textbox(allNotes[place].viewTags().c_str(),
				240 + 310 * abs(i - int(i / 4) * 4), 430 + 300 * int(i / 4), 1, 250);

			title->Render();
			text->Render();
			tags->Render();
		}

		for (int i = 1; i < 4; i++)
			buttons[i]->Render();
		buttons[7]->Render();
	}

	SDL_Rect rect = { 0,80,180,550 };
	SDL_SetRenderDrawColor(renderer, 240, 230, 150, 0);
	SDL_RenderFillRect(renderer, &rect);
	for (int i = 0; i < allTags.size(); i++)
		tagName[i].Render();

	SDL_RenderPresent(renderer);
}

void System::clean()
{
	ofstream file("totalFiles.txt", ios::trunc);
	file << allNotes.size() << endl;
	file.close();

	for (int i = 0; i < allNotes.size(); i++) {
		stringstream out;
		out << "00" << i + 1 << ".txt";
		ofstream fileNote(out.str(), ios::trunc);
		fileNote << allNotes[i].noteName() << endl;
		fileNote << allNotes[i].viewTags() << endl;
		fileNote << allNotes[i].noteText();
		fileNote.close();
	}

	ofstream fileTag("allTags.txt", ios::trunc);
	for (int i = 0; i < allTags.size() - 1; i++)
		fileTag << allTags[i].Name() << endl;
	fileTag << allTags[allTags.size() - 1].Name();
	fileTag.close();

	SDL_StopTextInput();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	renderer = nullptr;

	TTF_Quit();
	SDL_Quit();
}