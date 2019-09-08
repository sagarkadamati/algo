#ifndef MY_PDF_H
#define MY_PDF_H

#include <iostream>
#include <iomanip>
#include <fstream>

#include <string>
#include <sstream>
#include <stack>
#include <map>

#include <podofo/podofo.h>

#include "TeluguText.h"

using namespace std;
using namespace PoDoFo;

class MyPDF {
	int      pc;

	// ofstream actual;
	// ofstream modified;
	ofstream outdata;

	PdfMemDocument PDF;
	string skipFont;

	map<string, string> MissingCmds;
	TeluguText teluguText;
	void setExtractFile(string outText);
	struct strmake {
		std::stringstream s;
		template <typename T> strmake& operator << (const T& x) {
			s << x; return *this;
		}   
		operator std::string() {return s.str();}
	};
public:
	MyPDF(string input);
	~MyPDF();

	void printMissingChar();
	void printMissingCmds();
	void printMissing();
	void ReplaceStringInPlace(std::string& subject, const std::string& search,
							const std::string& replace);
	string extract(int pn);

	void extractTo(string outText);
	void saveAs(string output);
	void genMap(string outMap);

	void deletePages(int del_start, int del_end);
	void removeFont(string rFont);
};

// int is_exist(char ch, char glimps[1024], int size)
// {
// 	for(int i = 0; i < size; i++) {
// 		if(glimps[i] == ch)
// 			return 1;
// 	}

// 	return 0;
// }

// std::string process_glimps(string font, char glimps[1024], int size)
// {
// 	char glimps[1024];
// 	int size = 0;
// 	std::ostringstream block;
// 	int x = 0, y = 800;

// 	block << "q" << endl;
// 	block << "0 0 1 rg" << endl;
// 	block << "0.99999 0 0 -1 951 67 Tm" << endl;
// 	block << "BT" << endl;
// 	block << "/" << font << 20 << endl;

// 	for(int i = 0; i < size; i++) {
// 		if(!(x % 450)) {
// 			x = 30;
// 			y -= 40;
// 		}
// 		else
// 			x += 30;

// 		block << "1 0 0 1 " << x << " " << y << " Tm" << endl;
// 		if(glimps[i] == '(')
// 			block << "(\()Tj" << endl;
// 		else if(glimps[i] == ')')
// 			block << "(\\))Tj" << endl;
// 		else if(glimps[i] == '\\')
// 			block << "(\\\\)Tj" << endl;
// 		else
// 			block << "(" << glimps[i] << ")Tj" << endl;
// 	}

// 	block << "ET" << endl;
// 	block << "Q";

// 	return block.str();
// }

// void get_glimpse( PdfMemDocument* pDocument, PdfPage* pPage )
// {
// 	const char*          pszToken = NULL;
// 	PdfVariant           var;
// 	EPdfContentsType     eType;
// 	string               str;

// 	PdfContentsTokenizer tokenizer( pPage );

// 	while( tokenizer.ReadNext( eType, pszToken, var ) )
// 		if( eType == ePdfContentsType_Keyword ) {
// 			if( strcmp( pszToken, "Tj" ) == 0 ||
// 				strcmp( pszToken, "'" ) == 0 ) {

// 				str = var.GetString().GetString();
// 				for (int i = 0; i < str.size(); i++)
// 					if(!is_exist(str.at(i), glimps, size)))
// 						glimps[size++] = str.at(i);
// 			}
// 			else if( strcmp( pszToken, "TJ" ) == 0 )
// 			{
// 				PdfArray array = var.GetArray();

// 				for( int i=0; i<static_cast<int>(array.GetSize()); i++ )
// 				{
// 					string str;
// 					if( array[i].IsString() || array[i].IsHexString() ) {
// 						str = array[i].GetString().GetString();
// 						for (int i = 0; i < str.size(); i++)
// 							if(!is_exist(str.at(i), glimps, size))
// 								glimps[size++] = str.at(i);
// 					}
// 				}
// 			}

// 		}
// }

#endif /* MY_PDF_H */