#include<iostream>
#include<vector>
#include<string.h>
#include<iomanip>
#include<sstream>

using namespace std;

class Tokenizer {
public:
	static vector<string> Parse(string str, string seperator) {
		vector<string> tokens;

		int startPos = 0;
		size_t foundPos = str.find(seperator, startPos);

		while (foundPos != string::npos) {
			int count = foundPos - startPos;
			string token = str.substr(startPos, count);
			tokens.push_back(token);
			startPos = foundPos + seperator.length();
			foundPos = str.find(seperator, startPos);
		}

		int count = str.length() - startPos;
		string token = str.substr(startPos, count);
		tokens.push_back(token);

		return tokens;
	}

	static vector<int> convertStrToInt(vector<string> tokens) {
		vector<int> numbers;
		for (auto i = 0; i < tokens.size(); i++) {
			auto num = stoi(tokens[i]);
			numbers.push_back(num);
		}
		return numbers;
	}
};