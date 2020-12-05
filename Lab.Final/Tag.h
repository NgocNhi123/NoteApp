#pragma once
#include<iostream>
#include<string.h>
#include<vector>
#include<iomanip>
#include<sstream>

using namespace std;

class Tag {
private:
	string _tagName;
	bool _doubleClick = false;
public:
	Tag() { _tagName = "New Tag"; }
	Tag(string name) { _tagName = name; }
	//2. view tag
	string Name() { return _tagName; }

	//6. delete tag
	bool is_Tag(string name) {
		if (name == _tagName) return true;
		return false;
	}

	void setName(string name) { _tagName = name; }
	bool doubleClick() { return _doubleClick; }
	void setDoubleclick(bool x) { _doubleClick = x; }
};