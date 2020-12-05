#ifndef _LOADER_H_
#define _LOADER_H_

#include<fstream>

#include "Note.h"
#include "Button.h"
#include "Background.h"
#include "TextBox.h"
#include "Tokenizer.h"

class Loader {
public:
	static void loadScreen(vector<Button*>& buttons, vector<Background*>& backgrounds, int width, int height);
	static void loadNote(vector<Note>& allNotes, vector<Button*>& NoteBox);
	static void loadTag(vector<Tag>& allTags, vector<Textbox>& tagName);
	Loader() {}
	~Loader() {}
};

#endif // !_LOADER_H_