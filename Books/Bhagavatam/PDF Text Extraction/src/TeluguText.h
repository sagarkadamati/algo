#ifndef TELUGU_TEXT_H
#define TELUGU_TEXT_H

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>
#include <map>

#include <bitset>
#include <iomanip>

#include "TeluguDict.h"
#include "TeluguAksharam.h"

using namespace std;

extern map<unsigned int, int> MissingChar;
extern map<unsigned short, string> AllChar;

class TeluguText {
		TeluguDict lut;
		vector<TeluguAksharam> aksharalu;
		vector< pair<unsigned short, string> > text;
		struct strmake {
			std::stringstream s;
			template <typename T> strmake& operator << (const T& x) {
				s << x; return *this;
			}   
			operator std::string() {return s.str();}
		};
	public:
		TeluguText();
		unsigned short nextChar(string &str, int *i);
		bool isSkippable(unsigned short c);
		bool isReplaceable(unsigned short c);
		bool substitue(unsigned short c);
		void set(string &str);
		TeluguText(string &str);
		// string &operator[] (int index);
		string operator[] (int index);
		unsigned short charCode (int index);
		int size();
		~TeluguText();
		string details();
		string getChar(unsigned short c);
};

ostream & operator << (ostream &out, TeluguText &teluguText);

#endif /* TELUGU_TEXT_H */