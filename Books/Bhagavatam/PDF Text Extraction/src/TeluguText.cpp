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

// bool TeluguText::isSkippable(unsigned short c) {

	// if (lut.isSkip(c)) {
	// 	return true;
	// }

	// if (text.size() > 0) {
	// 	string prev = text.back().second;
	// 	if ( prev == string("య") || prev == string("మ") ) {
	// 	} else
	// 	if ( c == 0x54 ) { // "ు"
	// 		// if ( Deergalu[c] == string("ు") ) {
	// 		if ( prev == string("మ") ) {
	// 			text.push_back(make_pair(0x54, "ు"));
	// 			return true;
	// 		} else if ( lut[text.back().first].second == string("వ") ) {
	// 			text.pop_back();
	// 			text.push_back(make_pair(c, "మ"));
	// 			return true;
	// 		} else if ( lut[text.back().first].second == string("య") ) {
	// 			text.pop_back();
	// 			text.push_back(make_pair(c, "య"));
	// 			return true;
	// 		}
	// 	} else if ( c == 0xF7 ) {
	// 		if ( lut[text.back().first].second == string("వ") ) {
	// 			text.pop_back();
	// 			text.push_back(make_pair(c, "మ"));
	// 			text.push_back(make_pair(c, "ా"));
	// 			return true;
	// 		}
	// 	} else if ( prev == string("్") ) {
	// 		cout << endl << "entered"<< endl;
	// 		pair<unsigned short, string> ahrr = text.back();
	// 		text.pop_back();

	// 		pair<unsigned short, string> deergram = text.back();
	// 		if ( lut.isDeergam(deergram.first) ) {
	// 			text.pop_back();

	// 			text.push_back(ahrr);
	// 			text.push_back(lut.getCharPair(c));

	// 			text.push_back(deergram);
	// 		} else {
	// 			text.push_back(ahrr);
	// 			text.push_back(lut.getCharPair(c));
	// 		}

	// 		return true;
	// 	}
	// 	} else if ( lut.isVothu(c) ) {
	// 		pair<unsigned short, string> deergram = text.back();
	// 		if ( lut.isDeergam(deergram.first) ) {
	// 			text.pop_back();
	// 			text.push_back(lut.getCharPair(c));
	// 			text.push_back(deergram);
	// 		} else {
	// 			text.push_back(lut.getCharPair(c));
	// 		}

	// 		return true;
	// 	} else if ( lut.isAksharam(c) ) {
	// 		switch(c) {
	// 			case 0x24:  // "వి"
	// 				text.push_back(make_pair(c, "వ"));
	// 				text.push_back(make_pair(0xE6, "ి"));
	// 				break;
	// 			case 0x4D:  // "వీ"
	// 				text.push_back(make_pair(c, "వ"));
	// 				text.push_back(make_pair(0xB0, "ీ"));
	// 				break;
	// 			case 0x5D:  // "రి"
	// 				text.push_back(make_pair(c, "ర"));
	// 				text.push_back(make_pair(0xE6, "ి"));
	// 				break;
	// 			case 0x6C:   // "శ్రీ"
	// 				text.push_back(make_pair(c, "శ"));
	// 				text.push_back(make_pair(c, "్"));
	// 				text.push_back(make_pair(c, "ర"));
	// 				text.push_back(make_pair(c, "ీ"));
	// 				break;
	// 			case 0x70:  // "జూ"
	// 				text.push_back(make_pair(c, "జ"));
	// 				text.push_back(make_pair(0x4C, "ూ"));
	// 				break;
	// 			case 0x72:  // "తీ"
	// 				text.push_back(make_pair(c, "త"));
	// 				text.push_back(make_pair(0xB0, "ీ"));
	// 				break;
	// 			case 0x2039:// "తీ"
	// 				text.push_back(make_pair(c, "త"));
	// 				text.push_back(make_pair(0xB0, "ీ"));
	// 				break;
	// 			case 0xEC:  // "ని"
	// 				text.push_back(make_pair(c, "న"));
	// 				text.push_back(make_pair(0xE6, "ి"));
	// 				break;
	// 			case 0xF5:  // "జి"
	// 				text.push_back(make_pair(c, "జ"));
	// 				text.push_back(make_pair(0xE6, "ి"));
	// 				break;
	// 			case 0x02D9:// "నీ"
	// 				text.push_back(make_pair(c, "న"));
	// 				text.push_back(make_pair(0xB0, "ీ"));
	// 				break;
	// 			case 0xD8:  // "రీ"
	// 				text.push_back(make_pair(c, "ర"));
	// 				text.push_back(make_pair(0xB0, "ీ"));
	// 				break;
	// 			case 0x222B:// "చి"
	// 				text.push_back(make_pair(c, "చ"));
	// 				text.push_back(make_pair(0xE6, "ి"));
	// 				break;
	// 			case 0x2013:// "గి"
	// 				text.push_back(make_pair(c, "గ"));
	// 				text.push_back(make_pair(0xE6, "ి"));
	// 				break;
	// 			case 0x2A:  // "లి"
	// 				text.push_back(make_pair(c, "ల"));
	// 				text.push_back(make_pair(0xE6, "ి"));
	// 				break;
	// 			case 0x3b:  // "బీ"
	// 				text.push_back(make_pair(c, "బ"));
	// 				text.push_back(make_pair(0xB0, "ీ"));
	// 				break;
	// 			case 0x41:  // "ాూ"
	// 				text.push_back(make_pair(c, "ా"));
	// 				text.push_back(make_pair(0x4C, "ూ"));
	// 				break;
	// 			case 0x42:  // "దీ"
	// 				text.push_back(make_pair(c, "ద"));
	// 				text.push_back(make_pair(0xB0, "ీ"));
	// 				break;
	// 			case 0x45:  // "జు"
	// 				text.push_back(make_pair(c, "జ"));
	// 				text.push_back(make_pair(0x54, "ు"));
	// 				break;
	// 			case 0x4A:  // "జీ"
	// 				text.push_back(make_pair(c, "జ"));
	// 				text.push_back(make_pair(0xB0, "ీ"));
	// 				break;
	// 			case 0x4E:  // "చీ"
	// 				text.push_back(make_pair(c, "చ"));
	// 				text.push_back(make_pair(0xB0, "ీ"));
	// 				break;
	// 			case 0x51:  // "ాు"
	// 				text.push_back(make_pair(c, "ా"));
	// 				text.push_back(make_pair(0x54, "ు"));
	// 				break;
	// 			case 0x5E:  // "గీ"
	// 				text.push_back(make_pair(c, "గ"));
	// 				text.push_back(make_pair(0xB0, "ీ"));
	// 				break;
	// 			case 0x5F:  // "బి"
	// 				text.push_back(make_pair(c, "బ"));
	// 				text.push_back(make_pair(0xE6, "ి"));
	// 				break;
	// 			case 0x2022:// "శి"
	// 				text.push_back(make_pair(c, "శ"));
	// 				text.push_back(make_pair(0xE6, "ి"));
	// 				break;
	// 			case 0x7E:  // "ది"
	// 				text.push_back(make_pair(c, "ద"));
	// 				text.push_back(make_pair(0xE6, "ి"));
	// 				break;
	// 			case 0x221E:// "ళీ"
	// 				text.push_back(make_pair(c, "ళ"));
	// 				text.push_back(make_pair(0xB0, "ీ"));
	// 				break;
	// 		}
	// 		return true;
	// 	} else if ( prev == string("హ")  && lut[c].second == string("ా") ) {
	// 		return true;
	// 	}
	// }

// 	return false;
// }

// bool TeluguText::isReplaceable(unsigned short c) {
	// if (text.size() > 0) {
	// 	string prev = text.back().second;
	// 	if ( prev == string("ె")  && lut[c].second == string("ై") ) {
	// 		return true;
	// 	}
	// }

// 	return false;
// }

// bool TeluguText::substitue(unsigned short c) {
	// if (text.size() > 0) {
	// 	string prev = text.back().second;
	// 	string current = getCharPair(c).second;

	// 	if ( prev == string("్") ) {
	// 		text.pop_back();
	// 		pair<unsigned short, string> deegram = text.back();
	// 		if ( Deergalu.find(deegram.first) != Deergalu.end() ) {
	// 			text.pop_back();
	// 		}

	// 		if ( current == string("క") ) {
	// 			text.push_back(make_pair(c, "్క"));
	// 			return true;
	// 		} else if ( current == string("ఖ") ) {
	// 			text.push_back(make_pair(c, "్ఖ"));
	// 			return true;
	// 		} else if ( current == string("గ") ) {
	// 			text.push_back(make_pair(c, "్గ"));
	// 			return true;
	// 		} else if ( current == string("ఘ") ) {
	// 			text.push_back(make_pair(c, "్ఘ"));
	// 			return true;
	// 		} else if ( current == string("ఙ") ) {
	// 			text.push_back(make_pair(c, "్ఙ"));
	// 			return true;
	// 		} else if ( current == string("చ") ) {
	// 			text.push_back(make_pair(c, "్చ"));
	// 			return true;
	// 		} else if ( current == string("ఛ") ) {
	// 			text.push_back(make_pair(c, "్ఛ"));
	// 			return true;
	// 		} else if ( current == string("జ") ) {
	// 			text.push_back(make_pair(c, "్జ"));
	// 			return true;
	// 		} else if ( current == string("జ") ) {
	// 			text.push_back(make_pair(c, "్జ"));
	// 			return true;
	// 		} else if ( current == string("ఝ") ) {
	// 			text.push_back(make_pair(c, "్ఝ"));
	// 			return true;
	// 		} else if ( current == string("ఞ") ) {
	// 			text.push_back(make_pair(c, "్ఞ"));
	// 			return true;
	// 		} else if ( current == string("ట") ) {
	// 			text.push_back(make_pair(c, "్ట"));
	// 			return true;
	// 		} else if ( current == string("ఠ") ) {
	// 			text.push_back(make_pair(c, "్ఠ"));
	// 			return true;
	// 		} else if ( current == string("డ") ) {
	// 			text.push_back(make_pair(c, "్డ"));
	// 			return true;
	// 		} else if ( current == string("ఢ") ) {
	// 			text.push_back(make_pair(c, "్ఢ"));
	// 			return true;
	// 		} else if ( current == string("ణ") ) {
	// 			text.push_back(make_pair(c, "్ణ"));
	// 			return true;
	// 		} else if ( current == string("త") ) {
	// 			text.push_back(make_pair(c, "్త"));
	// 			return true;
	// 		} else if ( current == string("థ") ) {
	// 			text.push_back(make_pair(c, "్థ"));
	// 			return true;
	// 		} else if ( current == string("ద") ) {
	// 			text.push_back(make_pair(c, "్ద"));
	// 			return true;
	// 		} else if ( current == string("ధ") ) {
	// 			text.push_back(make_pair(c, "్ధ"));
	// 			return true;
	// 		} else if ( current == string("న") ) {
	// 			text.push_back(make_pair(c, "్న"));
	// 			return true;
	// 		} else if ( current == string("ప") ) {
	// 			text.push_back(make_pair(c, "్ప"));
	// 			return true;
	// 		} else if ( current == string("ఫ") ) {
	// 			text.push_back(make_pair(c, "్ఫ"));
	// 			return true;
	// 		} else if ( current == string("బ") ) {
	// 			text.push_back(make_pair(c, "్బ"));
	// 			return true;
	// 		} else if ( current == string("భ") ) {
	// 			text.push_back(make_pair(c, "్భ"));
	// 			return true;
	// 		} else if ( current == string("మ") ) {
	// 			text.push_back(make_pair(c, "్మ"));
	// 			return true;
	// 		} else if ( current == string("య") ) {
	// 			text.push_back(make_pair(c, "్య"));
	// 			return true;
	// 		} else if ( current == string("ర") ) {
	// 			text.push_back(make_pair(c, "్ర"));
	// 			return true;
	// 		} else if ( current == string("ఱ") ) {
	// 			text.push_back(make_pair(c, "్ఱ"));
	// 			return true;
	// 		} else if ( current == string("ల") ) {
	// 			text.push_back(make_pair(c, "్ల"));
	// 			return true;
	// 		} else if ( current == string("ళ") ) {
	// 			text.push_back(make_pair(c, "్ళ"));
	// 			return true;
	// 		} else if ( current == string("ఴ") ) {
	// 			text.push_back(make_pair(c, "్ఴ"));
	// 			return true;
	// 		} else if ( current == string("వ") ) {
	// 			text.push_back(make_pair(c, "్వ"));
	// 			return true;
	// 		} else if ( current == string("శ") ) {
	// 			text.push_back(make_pair(c, "్శ"));
	// 			return true;
	// 		} else if ( current == string("ష") ) {
	// 			text.push_back(make_pair(c, "్ష"));
	// 			return true;
	// 		} else if ( current == string("స") ) {
	// 			text.push_back(make_pair(c, "్స"));
	// 			return true;
	// 		} else if ( current == string("హ") ) {
	// 			text.push_back(make_pair(c, "్హ"));
	// 			return true;
	// 		} else {
	// 			return false;
	// 		}

	// 		if ( Deergalu.find(deegram.first) != Deergalu.end() ) {
	// 			text.push_back(deegram);
	// 		}
	// 	}
	// }

// 	return false;
// }

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

		// if (!isSkippable(c)) {
			// if (isReplaceable(c)) {
				// text.pop_back();

				// if (( fchar == string("య") || fchar == string("వ") ) && teluguText[i] == string("ు") ) {
				// 	i++;

				// 	if (fchar == string("వ")) {
				// 		out << "మ";
				// 		// cout << "మ";
				// 		// cout << " Found maa, using maa" << endl;
				// 	}
				// } else if ( fchar == string("ె")  && teluguText[i] == string("ై") ) {
				// 	// cout << teluguText[i++] << endl;
				// 	out << teluguText[i++];
				// } else if ( fchar == string("హ")  && teluguText[i] == string("ా") ) {
				// 	out << fchar;
				// 	i++;
				// } else {
				// 	// cout << fchar << endl;
				// 	out << fchar;
			// }

			// if (!substitue(c)) {
				// text.push_back(lut.getCharPair(c));
			// }
		// }
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
	// if (index < text.size()) {
	// 	if (debug) {
	// 		unsigned short c = text[index].first;

	// 		cout << setw(8) << dec << c;
	// 		cout << setw(8) << hex << c;
	// 		cout << setw(20) << bitset<16>(c);

	// 		if (c == 32 || c == 46) {
	// 			cout << setw(4);
	// 		} else {
	// 			cout << setw(6);
	// 		}

	// 		cout << text[index].second;
	// 		cout << endl;
	// 	}

		// cout << aksharalu[index].toString() << endl;
		return aksharalu[index].toString();
	// 	return text[index].second;
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
	// return text.size();
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

// string TeluguText::details() {
// 	int textSize = text.size();
// 	string data = "";

// 	int i = 0;
// 	while (i < textSize) {
// 		 data += "| ";
// 		 data += text[i].second;
// 		 data += " -> ";
// 		 data += strmake() << "0x" <<  hex << text[i++].first;
// 		 data += " ";
// 	}
// 	data += "|";

// 	return data;
// }

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