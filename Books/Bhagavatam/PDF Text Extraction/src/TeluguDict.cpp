#include "TeluguDict.h"
#include <iostream>

map<unsigned int, int> MissingChar;

// 0C00 - ఀ -      0C10 - ఐ -        0C20 - ఠ -        0C30 - ర -
// 0C01 - ఁ -                        0C21 - డ -        0C31 - ఱ -
// 0C02 - ం -    0C12 -  ఒ - 2c7     0C22 - ఢ -        0C32 - ల - 5c
// 0C03 - ః -     0C13 - ఓ - 7a      0C23 - ణ - 44     0C33 - ళ - 5b
// 0C04 - ఄ -     0C14 - ఔ -         0C24 - త -        0C34 - ఴ -
// 0C05 - అ - 6e  0C15 - క - f8      0C25 - థ -        0C35 - వ - 65
// 0C06 - ఆ - c4  0C16 - ఖ - 4b,55   0C26 - ద - 3c     0C36 - శ -
// 0C07 - ఇ - c7  0C17 - గ - 3e      0C27 - ధ - 394    0C37 - ష - 63
// 0C08 - ఈ - e1  0C18 - ఘ - c8      0C28 - న - 71     0C38 - స -
// 0C09 - ఉ - f1  0C19 - ఙ -                           0C39 - హ -
// 0C0A - ఊ - 7d  0C1A - చ - 23      0C2A - ప -
// 0C0B - ఋ -    0C1B - ఛ  -         0C2B - ఫ -
// 0C0C - ఌ -     0C1C - జ - 43      0C2C - బ - e3
//                0C1D - ఝ -         0C2D - భ -
// 0C0E - ఎ - 62  0C1E - ఞ - 201e    0C2E - మ -
// 0C0F - ఏ - 40  0C1F - ట - 66    0C2F - య - 6a (u missing)

// 0C3D - ఽ -
// 0C3E - ా - d5
// 0C3F - ి - e6
// 0C40 - ీ - fb                    0C60 - ౠ
// 0C41 - ు - df                  0C61 - ౡ
// 0C42 - ూ - 4c                  0C62 - ౢ
// 0C43 - ృ -                   0C63 - ౣ
// 0C44 - ౄ -
//                 0C55 - ౕ
// 0C46 - ె - d3   0C56 - ౖ        0C66 - ౦
// 0C47 - ే - d2                   0C67 - ౧
// 0C48 - ై -      0C58 - ౘ        0C68 - ౨        0C78 - ౸
//                 0C59 - ౙ        0C69 - ౩        0C79 - ౹
// 0C4A - ొ - a7                   0C6A - ౪        0C7A - ౺
// 0C4B - ో - c0                   0C6B - ౫        0C7B - ౻
// 0C4C - ౌ - c2                   0C6C - ౬        0C7C - ౼
// 0C4D - ్ - 74                   0C6D - ౭        0C7D - ౽
//                                 0C6E - ౮        0C7E - ౾
//                                 0C6F - ౯        0C7F - ౿

void TeluguDict::mapAchulu(string ch, unsigned int index) {
	Achulu[index] = ch;
}

void TeluguDict::mapAksharam(string ch, unsigned int index) {
	Aksharalu[index] = ch;
}

void TeluguDict::mapDeergalu(string ch, unsigned int index) {
	Deergalu[index] = ch;
}

void TeluguDict::mapVothulu(string ch, unsigned int index) {
	Vothulu[index] = ch;
}

void TeluguDict::mapSarga(string ch, unsigned int index) {
	Sargalu[index] = ch;
}

void TeluguDict::mapSpecial(string ch, unsigned int index) {
	Special[index] = ch;
}

void TeluguDict::mapSkip(string ch, unsigned int index) {
	Skip[index] = ch;
}

void TeluguDict::clear() {
	Achulu.clear();
	Vothulu.clear();
	Deergalu.clear();
	Sargalu.clear();
	Aksharalu.clear();
	Special.clear();
	Skip.clear();
}
bool TeluguDict::isAchu(unsigned short ch) {
	if ( Achulu.find(ch) != Achulu.end() )
		return true;
	else
		return false;
}

bool TeluguDict::isDeergam(unsigned short ch) {
	if ( Deergalu.find(ch) != Deergalu.end() )
		return true;
	else
		return false;
}

bool TeluguDict::isVothu(unsigned short ch) {
	if ( Vothulu.find(ch) != Vothulu.end() )
		return true;
	else
		return false;
}

bool TeluguDict::isSarga(unsigned short ch) {
	if ( Sargalu.find(ch) != Sargalu.end() )
		return true;
	else
		return false;
}

bool TeluguDict::isAksharam(unsigned short ch) {
	if ( Aksharalu.find(ch) != Aksharalu.end() )
		return true;
	else
		return false;
}

bool TeluguDict::isSpecial(unsigned short ch) {
	if ( Special.find(ch) != Special.end() )
		return true;
	else
		return false;
}

bool TeluguDict::isSkip(unsigned short ch) {
	if ( Skip.find(ch) != Skip.end() )
		return true;
	else
		return false;
}

bool TeluguDict::isAchu(string ch) {
	for(map<unsigned int, string>::iterator c = Achulu.begin(); c != Achulu.end(); c++) {
		if (c->second == ch)
			return true;
	}
	return false;
}

bool TeluguDict::isDeergam(string ch) {
	for(map<unsigned int, string>::iterator c = Deergalu.begin(); c != Deergalu.end(); c++) {
		if (c->second == ch)
			return true;
	}
	return false;
}

bool TeluguDict::isVothu(string ch) {
	for(map<unsigned int, string>::iterator c = Vothulu.begin(); c != Vothulu.end(); c++) {
		if (c->second == ch)
			return true;
	}
	return false;
}

bool TeluguDict::isSarga(string ch) {
	for(map<unsigned int, string>::iterator c = Sargalu.begin(); c != Sargalu.end(); c++) {
		if (c->second == ch)
			return true;
	}
	return false;
}

bool TeluguDict::isAksharam(string ch) {
	for(map<unsigned int, string>::iterator c = Aksharalu.begin(); c != Aksharalu.end(); c++) {
		if (c->second == ch)
			return true;
	}
	return false;
}

bool TeluguDict::isSpecial(string ch) {
	for(map<unsigned int, string>::iterator c = Special.begin(); c != Special.end(); c++) {
		if (c->second == ch)
			return true;
	}
	return false;
}

bool TeluguDict::fixDeergam(unsigned short old, unsigned short c, pair<unsigned short, string> &achchu, pair<unsigned short, string> &deergam, vector< pair<unsigned short, string> > &vothulu) {
	if ( c == 0x54 ) { // "ు"
		if ( achchu.second == string("వ") ) { // fix మ
			achchu = make_pair(c, "మ");
			return true;
		} else if ( achchu.second == string("య") ) {
			achchu = make_pair(c, "య");
			return true;
		}
	} else if ( c == 0xF7 ) {
		if ( achchu.second == string("వ") ) {
			achchu = make_pair(c, "మ");
			deergam = make_pair(c, "ా");
			return true;
		}
	} else if ( achchu.second == string("హ")  && Deergalu[c] == string("ా") ) {
		// skip this
		return true;
	} else if (old) {
		// if ( prev == string("ె")  && lut[c].second == string("ై")
		deergam = make_pair(c, Deergalu[c]);
		return true;
	} else {
		return false;
	}
}

void TeluguDict::getNewDeergam(unsigned short old, unsigned short c, pair<unsigned short, string> &achchu, pair<unsigned short, string> &deergam, vector< pair<unsigned short, string> > &vothulu) {
	if (!fixDeergam(old, c, achchu, deergam, vothulu)) {
		deergam = make_pair(c, Deergalu[c]);
	}
}

void TeluguDict::fillVothulu(unsigned short c, pair<unsigned short, string> &achchu, pair<unsigned short, string> &deergam, vector< pair<unsigned short, string> > &vothulu) {
	if (c == 0xDB) {
		if (achchu.second == string("చ")) {
			achchu = make_pair(c, "ఛ");
		}
		else if (achchu.second == string("డ")) {
			achchu = make_pair(c, "ఢ");
		}
		else if (achchu.second == string("ద")) {
			achchu = make_pair(c, "ధ");
		}
		else if (achchu.second == string("ప")) {
			achchu = make_pair(c, "ఫ");
		}
		else if (achchu.second == string("బ")) {
			achchu = make_pair(c, "భ");
		} else {
			std::cout << "Fount new . vothu" << endl;
		}
	} else {
		vothulu.push_back(make_pair(c, Vothulu[c]));
	}
}

void TeluguDict::fillAksharam(unsigned short c, pair<unsigned short, string> &achchu, pair<unsigned short, string> &deergam, vector< pair<unsigned short, string> > &vothulu) {
	switch(c) {
		case 0x24:  // "వి"
			achchu = make_pair(c, "వ");
			deergam = make_pair(0xE6, "ి");
			break;
		case 0x4D:  // "వీ"
			achchu = make_pair(c, "వ");
			deergam = make_pair(0xB0, "ీ");
			break;
		case 0x5D:  // "రి"
			achchu = make_pair(c, "ర");
			deergam = make_pair(0xE6, "ి");
			break;
		case 0x70:  // "జూ"
			achchu = make_pair(c, "జ");
			deergam = make_pair(0x4C, "ూ");
			break;
		case 0x72:  // "తీ"
			achchu = make_pair(c, "త");
			deergam = make_pair(0xB0, "ీ");
			break;
		case 0x2039:// "తీ"
			achchu = make_pair(c, "త");
			deergam = make_pair(0xB0, "ీ");
			break;
		case 0xEC:  // "ని"
			achchu = make_pair(c, "న");
			deergam = make_pair(0xE6, "ి");
			break;
		case 0xF5:  // "జి"
			achchu = make_pair(c, "జ");
			deergam = make_pair(0xE6, "ి");
			break;
		case 0x02D9:// "నీ"
			achchu = make_pair(c, "న");
			deergam = make_pair(0xB0, "ీ");
			break;
		case 0xD8:  // "రీ"
			achchu = make_pair(c, "ర");
			deergam = make_pair(0xB0, "ీ");
			break;
		case 0x222B:// "చి"
			achchu = make_pair(c, "చ");
			deergam = make_pair(0xE6, "ి");
			break;
		case 0x2013:// "గి"
			achchu = make_pair(c, "గ");
			deergam = make_pair(0xE6, "ి");
			break;
		case 0x2A:  // "లి"
			achchu = make_pair(c, "ల");
			deergam = make_pair(0xE6, "ి");
			break;
		case 0x3b:  // "బీ"
			achchu = make_pair(c, "బ");
			deergam = make_pair(0xB0, "ీ");
			break;
		case 0x42:  // "దీ"
			achchu = make_pair(c, "ద");
			deergam = make_pair(0xB0, "ీ");
			break;
		case 0x45:  // "జు"
			achchu = make_pair(c, "జ");
			deergam = make_pair(0x54, "ు");
			break;
		case 0x4A:  // "జీ"
			achchu = make_pair(c, "జ");
			deergam = make_pair(0xB0, "ీ");
			break;
		case 0x4E:  // "చీ"
			achchu = make_pair(c, "చ");
			deergam = make_pair(0xB0, "ీ");
			break;
		case 0x5E:  // "గీ"
			achchu = make_pair(c, "గ");
			deergam = make_pair(0xB0, "ీ");
			break;
		case 0x5F:  // "బి"
			achchu = make_pair(c, "బ");
			deergam = make_pair(0xE6, "ి");
			break;
		case 0x2022:// "శి"
			achchu = make_pair(c, "శ");
			deergam = make_pair(0xE6, "ి");
			break;
		case 0x7E:  // "ది"
			achchu = make_pair(c, "ద");
			deergam = make_pair(0xE6, "ి");
			break;
		case 0x221E:// "ళీ"
			achchu = make_pair(c, "ళ");
			deergam = make_pair(0xB0, "ీ");
			break;

		case 0x51:  // "ాు"
			// text.push_back(make_pair(c, "ా"));
			deergam = make_pair(0x54, "ు");
			break;

		case 0x41:  // "ాూ"
			// text.push_back(make_pair(c, "ా"));
			deergam = make_pair(0x4C, "ూ");
			break;

		case 0x6C:   // "శ్రీ"
			achchu = make_pair(c, "శ");
			vothulu.push_back(make_pair(c, "్ర"));
			deergam = make_pair(c, "ీ");
			break;
	}
}

pair<unsigned short, string> TeluguDict::getCharPair(unsigned short c) {
	if ( Achulu.find(c) != Achulu.end() ) {
		return make_pair(c, Achulu[c]);
	} else if ( Vothulu.find(c) != Vothulu.end() ) {
		return make_pair(c, Vothulu[c]);
	} else if ( Deergalu.find(c) != Deergalu.end() ) {
		return make_pair(c, Deergalu[c]);
	} else if ( Sargalu.find(c) != Sargalu.end() ) {
		return make_pair(c, Sargalu[c]);
	} else if ( Aksharalu.find(c) != Aksharalu.end() ) {
		return make_pair(c, Aksharalu[c]);
	} else if ( Special.find(c) != Special.end() ) {
		return make_pair(c, Special[c]);
	} else {
		MissingChar[c]++;
		return make_pair(c, "");
	}
}

pair<unsigned short, string> TeluguDict::operator[] (unsigned short c) {
	if ( isAchu(c) ) {
		return make_pair(c, Achulu[c]);
	} else if ( isVothu(c) ) {
		return make_pair(c, Vothulu[c]);
	} else if ( isDeergam(c) ) {
		return make_pair(c, Deergalu[c]);
	} else if ( isSarga(c) ) {
		return make_pair(c, Sargalu[c]);
	} else if ( isAksharam(c) ) {
		return make_pair(c, Aksharalu[c]);
	} else if ( isSpecial(c) ) {
		return make_pair(c, Special[c]);
	} else {
		MissingChar[c]++;
		return make_pair(c, "");
	}
}