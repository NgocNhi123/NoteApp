#include "Loader.h"

void Loader::loadScreen(vector<Button*>& buttons, vector<Background*>& backgrounds, int width, int height) {
	//load buttons
	buttons.push_back(new Button("Picture/quit.png", 1350, 80, 130, 129, 0.7));

	buttons.push_back(new Button("Picture/newNote.png", 1350, 680, 130, 129, 0.7));
	buttons.push_back(new Button("Picture/newTag.png", 20, 660, 83, 219, 0.6));
	buttons.push_back(new Button("Picture/search.png", 1000, 130, 142, 140, 0.3));

	buttons.push_back(new Button("Picture/setTag.png", 400, 200, 56, 190, 0.7));
	buttons.push_back(new Button("Picture/title.png", 400, 260, 50, 700, 0.7));
	buttons.push_back(new Button("Picture/note.png", 400, 340, 200, 1000, 0.7));
	buttons.push_back(new Button("Picture/trash.png", 65, 720, 127, 120, 0.4));

	buttons.push_back(new Button("Picture/edit.png", 1350, 170, 130, 129, 0.7));
	//load backgrounds
	backgrounds.push_back(new Background("Picture/userScreen.png", width, height));
	backgrounds.push_back(new Background("Picture/newNoteScreen.png", width, height));
}

void Loader::loadNote(vector<Note>& allNotes, vector<Button*>& NoteBox) {
	int totalFiles;
	ifstream file("totalFiles.txt");
	file >> totalFiles;
	file.close();

	for (int i = 0; i < totalFiles; i++) {
		stringstream out;
		out << "00" << i + 1 << ".txt";

		ifstream fileNote(out.str());

		if (!fileNote.is_open()) {
			cout << "Can't open file" << endl;
			return;
		}

		string name, text, tags;
		vector<Tag> allTags;

		getline(fileNote, name);

		getline(fileNote, tags);
		vector<string> tokens = Tokenizer::Parse(tags, ", ");
		for (auto i = 0; i < tokens.size(); i++) {
			Tag loadTag(tokens[i]);
			allTags.push_back(loadTag);
		}

		string tmp;
		while (!fileNote.eof()) {
			getline(fileNote, tmp, '\n');
			if (tmp == "\0") break;
			text += tmp;
			text += '\n';
		}

		Note note(name, text, allTags);
		allNotes.push_back(note);

		fileNote.close();
	}

	for (int i = 0; i < allNotes.size(); i++)
		NoteBox.push_back(new Button("Picture/notebox.png",
			200 + 310 * abs(i - int(i / 4) * 4), 200 + 300 * int(i / 4), 422, 434, 0.7));
}

void Loader::loadTag(vector<Tag>& allTags, vector<Textbox>& tagName) {
	ifstream fileTag("allTags.txt");
	if (!fileTag.is_open()) {
		cout << "Can't open file" << endl;
		return;
	}

	while (!fileTag.eof()) {
		string name;
		getline(fileTag, name);
		Tag tag(name);
		allTags.push_back(tag);
	}

	fileTag.close();

	for (int i = 0; i < allTags.size(); i++) {
		Textbox text(allTags[i].Name().c_str(), 10, 100 + i * 50, 1, 150);
		tagName.push_back(text);
	}
}