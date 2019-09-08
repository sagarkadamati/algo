#ifndef TELUGU_DICT_H
#define TELUGU_DICT_H

#include <string>
#include <vector>
#include <map>

using namespace std;

extern map<unsigned int, int> MissingChar;

class TeluguDict {
	map<unsigned int, string> Achulu;
	map<unsigned int, string> Vothulu;
	map<unsigned int, string> Deergalu;
	map<unsigned int, string> Sargalu;
	map<unsigned int, string> Aksharalu;
	map<unsigned int, string> Special;
	map<unsigned int, string> Skip;
public:
	void mapAchulu(string ch, unsigned int index);
	void mapAksharam(string ch, unsigned int index);
	void mapDeergalu(string ch, unsigned int index);
	void mapVothulu(string ch, unsigned int index);
	void mapSarga(string ch, unsigned int index);
	void mapSkip(string ch, unsigned int index);
	void mapSpecial(string ch, unsigned int index);
	void clear();

	bool isAchu(unsigned short ch);
	bool isAksharam(unsigned short ch);
	bool isDeergam(unsigned short ch);
	bool isVothu(unsigned short ch);
	bool isSarga(unsigned short ch);
	bool isSkip(unsigned short ch);
	bool isSpecial(unsigned short ch);

	bool isAchu(string ch);
	bool isAksharam(string ch);
	bool isDeergam(string ch);
	bool isVothu(string ch);
	bool isSarga(string ch);
	bool isSpecial(string ch);

	bool fixDeergam(unsigned short old, unsigned short c, pair<unsigned short, string> &achchu, pair<unsigned short, string> &deergam, vector< pair<unsigned short, string> > &vothulu);
	void getNewDeergam(unsigned short old, unsigned short c, pair<unsigned short, string> &achchu, pair<unsigned short, string> &deergam, vector< pair<unsigned short, string> > &vothulu);
	void fillVothulu(unsigned short c, pair<unsigned short, string> &achchu, pair<unsigned short, string> &deergam, vector< pair<unsigned short, string> > &vothulu);
	void fillAksharam(unsigned short c, pair<unsigned short, string> &achchu, pair<unsigned short, string> &deergam, vector< pair<unsigned short, string> > &vothulu);
	pair<unsigned short, string> getCharPair(unsigned short c);
	pair<unsigned short, string> operator[] (unsigned short c);
};

void setupFontLUT(TeluguDict &lut);

#endif /* TELUGU_DICT_H */