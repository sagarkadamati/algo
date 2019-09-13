#ifndef TELUGU_AKSHARAM_H
#define TELUGU_AKSHARAM_H

#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>

#include <bitset>
#include <iomanip>

#include "TeluguDict.h"

using namespace std;

class TeluguAksharam {
	pair<unsigned short, string> achchu;
	pair<unsigned short, string> deergam;
	pair<unsigned short, string> sarga;
	vector< pair<unsigned short, string> > vothulu;
	TeluguDict* lut;
	bool isSpecial;
public:
	TeluguAksharam();
	TeluguAksharam(TeluguDict &l, queue< pair<unsigned short, string> > &backup);
	~TeluguAksharam();
	string toString();
	void insert(unsigned short c, queue< pair<unsigned short, string> > &backup);
	void insertVothu(unsigned short c, queue< pair<unsigned short, string> > &backup);
};

#endif /* TELUGU_AKSHARAM_H */