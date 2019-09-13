#include "TeluguText.h"

string empty("");
unsigned short TeluguText::nextChar(string &str, int *i) {
	unsigned short c = 0;

	if ((str[(*i)] & 0x80) == 0x00){ // check msb bit zero
		c = (str[(*i)++] & 0x7F);
		if (c != 0 && AllChar.find(c) == AllChar.end())
			AllChar[c] = str.substr (*i - 1, 1);
	} else if ((str[(*i)] & 0xE0) == 0xC0) { // 1100 - check if two byte char
		c  = (str[(*i)++] & 0x1F) << 6;
		c |= (str[(*i)++] & 0x3F);
		if (c != 0 && AllChar.find(c) == AllChar.end())
			AllChar[c] = str.substr (*i - 2, 2);
	} else if ((str[(*i)] & 0xF0) == 0xE0) { // 1110 - check if three byte char
		c  = (str[(*i)++] & 0x0F) << 12;
		c |= (str[(*i)++] & 0x3F) << 6;
		c |= (str[(*i)++] & 0x3F);
		if (c != 0 && AllChar.find(c) == AllChar.end())
			AllChar[c] = str.substr (*i - 3, 3);
	} else {
		cout << "Found 4 byte char" << endl;
	}

	text.push_back(lut.getCharPair(c));
	return c;
}

void TeluguText::set(string &str) {
	text.clear();
	aksharalu.clear();

	int i = 0;
	int textSize = str.length();
	while (i < textSize) {
		unsigned short c = nextChar(str, &i);
		string ch;

		if (aksharalu.size() == 0 ||
				lut.isSpecial(c) ||
				lut.isAchu(c) ||
				lut.isAksharam(c)) {
			aksharalu.push_back(TeluguAksharam(lut));
		}

		if ( lut[c].second == string("్") ) {
			c = nextChar(str, &i);
			aksharalu.back().insertVothu(c);;
		} else {
			aksharalu.back().insert(c);;
		}
	}
}

TeluguText::TeluguText() {
	setupFontLUT(lut);
}

TeluguText::TeluguText(string &str) {
	setupFontLUT(lut);
	set(str);
}

string TeluguText::operator[] (int index) {
	bool debug = true;

	if (index < aksharalu.size()) {
		return aksharalu[index].toString();
	} else {
		return empty;
	}
}

unsigned short TeluguText::charCode (int index) {
	if (index < text.size()) {
		return text[index].first;
	} else {
		return 0;
	}
}

int TeluguText::size() {
	return aksharalu.size();
}

TeluguText::~TeluguText() {
	aksharalu.clear();
	text.clear();
}

ostream & operator << (ostream &out, TeluguText &teluguText) {
	int textSize = teluguText.size();

	int i = 0;
	while (i < textSize) {
		out << teluguText[i++];
	}

	return out;
}

string TeluguText::details() {
	int textSize = text.size();
	string data = "";

	int i = 0;
	while (i < textSize) {
		 data += "| ";
		 data += text[i].second;
		 data += " -> ";
		 data += strmake() << "0x" <<  hex << text[i++].first;
		 data += " ";
	}
	data += "|";

	return data;
}

string TeluguText::getChar(unsigned short c) {
	return lut.getCharPair(c).second;
}