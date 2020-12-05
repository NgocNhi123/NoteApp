#ifndef _NOTE_H_
#define _NOTE_H_

#include"Tag.h"
extern class Tag;
class Note {
private:
	string _title;
	string _note;
	vector<Tag> _noteTags;

public:
	Note();
	Note(string name, string text, vector<Tag> tags);
	~Note() {};

	string noteName() { return _title; }
	string noteText() { return _note; }

	void setName(string name) { _title = name; }
	void setText(string text) { _note = text; }

	void addTag(string tagName);
	void deleteTag(string tagName);
	bool tagged(string tagName);
	string viewTags();
	bool is_Note(string name);
};

#endif // !_NOTE_H_