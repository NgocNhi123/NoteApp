#include "Note.h"

//1.add new notes
Note::Note() {
	_title = "Title";
	_note = "Blank";
	Tag newTag("Untagged");
	_noteTags.push_back(newTag);
}

Note::Note(string name, string text, vector<Tag> Tags) {
	_title = name;
	_note = text;
	for (int i = 0; i < Tags.size(); i++) {
		_noteTags.push_back(Tags[i]);
	}
}

//3.return notes that have tagName
bool Note::tagged(string tagName) {
	for (int i = 0; i < _noteTags.size(); i++) {
		if (_noteTags[i].is_Tag(tagName))
			return true;
	}
	return false;
}

//4.view tags
string Note::viewTags() {
	stringstream out;
	if (_noteTags.size() == 0)
		out << "Untagged";
	else {
		for (int i = 0; i < _noteTags.size() - 1; i++)
			out << _noteTags[i].Name() << ", ";
	}
	out << _noteTags[_noteTags.size() - 1].Name();
	return out.str();
}

//5.delete note
bool Note::is_Note(string name) {
	if (name == _title) return true;
	return false;
}

void Note::addTag(string tagName) {
	if (tagged("Untagged"))
		_noteTags.erase(_noteTags.begin());
	Tag newTag(tagName);
	_noteTags.push_back(newTag);
}

void Note::deleteTag(string tagName) {
	if (_noteTags.size() == 1 && _noteTags[0].is_Tag(tagName)) {
		Tag untag("Untagged");
		_noteTags.push_back(untag);
		_noteTags.erase(_noteTags.begin());
		return;
	}
	for (int i = 0; i < _noteTags.size(); i++) {
		if (_noteTags[i].is_Tag(tagName))
			_noteTags.erase(_noteTags.begin() + i);
	}
}