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

#define A(x, y) lut.mapAchulu(x, y)
#define H(x, y) lut.mapAchulu(x, y)
#define S(x, y) lut.mapSarga(x, y)
#define D(x, y) lut.mapDeergalu(x, y)
#define V(x, y) lut.mapVothulu(x, y)
#define SK(x, y) lut.mapSkip(x, y)
#define AK(x, y) lut.mapAksharam(x, y)
#define SP(x, y) lut.mapSpecial(x, y)

#endif /* TELUGU_DICT_H */

// static void setupAchulu(TeluguDict &lut) {
// 	// అచ్చులు
// 	A("అ", 0x0000);	A("ఆ", 0x0000);		A("ఇ", 0x0000);	A("ఈ", 0x0000);	   A("ఉ", 0x0000);	A("ఊ", 0x0000);
// 	SK("", 0x0000);	D("ా", 0x0000);		D("ి", 0x0000);	D("ీ", 0x0000);		D("ు", 0x0000);	D("ూ", 0x0000);
// 	SK("", 0x0000);	D("ా", 0x0000);		D("ి", 0x0000);	D("ీ", 0x0000);		D("ు", 0x0000);	D("ూ", 0x0000);
// 	SK("", 0x0000);	D("ా", 0x0000);		D("ి", 0x0000);						D("ు", 0x0000);	D("ూ", 0x0000);
// 	SK("", 0x0000);	D("ా", 0x0000);											D("ు", 0x0000);	D("ూ", 0x0000);
// 	SK("", 0x0000);	D("ా", 0x0000);											D("ు", 0x0000);	D("ూ", 0x0000);
// 	SK("", 0x0000);	D("ా", 0x0000);											D("ు", 0x0000);	D("ూ", 0x0000);
// 	SK("", 0x0000);	D("ా", 0x0000);											D("ు", 0x0000);
// 	SK("", 0x0000);
// 	SK("", 0x0000);
// 	SK("", 0x0000); //
// 	SK("", 0x0000); //

// 	A("ఋ", 0x0000);	A("ౠ", 0x0000);	A("ఌ", 0x0000);	A("ౡ", 0x0000);
// 	D("ృ", 0x0000);	D("ౄ", 0x0000);

// 	A("ఎ", 0x0000);	A("ఏ", 0x0000);	A("ఐ", 0x0000);
// 	D("ె", 0x0000);	D("ే", 0x0000);	D("ై", 0x0000);
// 	D("ె", 0x0000);	D("ే", 0x0000);
// 	D("ె", 0x0000);	D("ే", 0x0000);
// 	D("ె", 0x0000);	D("ే", 0x0000);
// 	D("ె", 0x0000);

// 	A("ఒ", 0x0000);		A("ఓ", 0x0000);		A("ఔ", 0x0000);
// 	D("ొ", 0x0000);		D("ో", 0x0000);		D("ౌ", 0x0000);
// 	D("ొ", 0x0000);		D("ో", 0x0000);		D("ౌ", 0x0000);
// 											D("ౌ", 0x0000);
// 											D("ౌ", 0x0000);

// 	// ఉభయాక్షరమలు
// 	S("ఁ", 0x0000);	S("ం", 0x0000);	S("ః", 0x0000);

// 	// D("ౕ", );	D("ౖ", );	D("ౢ", );	D("ౣ", );	D("ఀ", );
// }

// static void setupHallulu(TeluguDict &lut) {

// 	// హల్లులు
// 	H("క", 0x0000);		H("ఖ", 0x0000);		H("గ", 0x0000);		H("ఘ", 0x0000);		H("ఙ", 0x0000);
// 	H("క", 0x0000);		H("ఖ", 0x0000);
// 	V("్క", 0x0000);	V("్ఖ", 0x0000);	 V("్గ", 0x0000);	  V("్ఘ", 0x0000);		V("్ఙ", 0x0000);

// 	H("చ", 0x0000);		H("ఛ", 0x0000);		H("జ", 0x0000);		H("ఝ", 0x0000);		H("ఞ", 0x0000);
// 	H("చ", 0x0000);							H("జ", 0x0000);
// 	V("్చ", 0x0000);	V("్ఛ", 0x0000);	 V("్జ", 0x0000);	   V("్ఝ", 0x0000);		V("్ఞ", 0x0000);

// 	H("ట", 0x0000);		H("ఠ", 0x0000);		H("డ", 0x0000);		H("ఢ", 0x0000);		H("ణ", 0x0000);
// 	H("ట", 0x0000);
// 	V("్ట", 0x0000);	V("్ఠ", 0x0000);		V("్డ", 0x0000);	V("్ఢ", 0x0000);	V("్ణ", 0x0000);

// 	H("త", 0x0000);		H("థ", 0x0000);		H("ద", 0x0000);		H("ధ", 0x0000);		H("న", 0x0000);
// 																					 H("న", 0x0000);
// 	V("్త", 0x0000);	V("్థ", 0x0000);		V("్ద", 0x0000);	V("్ధ", 0x0000);	V("్న", 0x0000);
// 																					V("్న", 0x0000);

// 	H("ప", 0x0000);		H("ఫ", 0x0000);		H("బ", 0x0000);		H("భ", 0x0000);		H("మ", 0x0000);
// 	H("ప", 0x0000);							H("బ", 0x0000);		H("భ", 0x0000);		H("మ", 0x0000);
// 	H("ప", 0x0000);
// 	H("ప", 0x0000);
// 	H("ప", 0x0000);
// 	V("్ప", 0x0000);	V("్ఫ", 0x0000);	V("్బ", 0x0000);	V("్భ", 0x0000);	V("్మ", 0x0000);

// 	// ----

// 	H("య", 0x0000);		H("ర", 0x0000);		H("ల", 0x0000);		H("వ", 0x0000);
// 	V("్య", 0x0000);	V("్ర", 0x0000);	V("్ల", 0x0000);	V("్వ", 0x0000);

// 	H("శ", 0x0000);		H("ష", 0x0000);		H("స", 0x0000);		H("హ", 0x0000);
// 						H("ష", 0x0000);		H("స", 0x0000);
// 	V("్శ", 0x0000);	V("్ష", 0x0000);	V("్స", 0x0000);	V("్హ", 0x0000);

// 	H("ళ", 0x0000);		H("ఱ", 0x0000);		   H("క్ష", 0x0000);
// 	V("్ళ", 0x0000);	V("్ఱ", 0x0000);

// 	H("ౘ", 0x0000);		H("ౙ", 0x0000);

// 	// చిహ్నములు
// 	H("ఽ", 0x0000);

// 	//  skip ్
// 	H("్", 0x0000);
// 	H("్", 0x0000);
// 	H("్", 0x0000);
// 	H("్", 0x0000);
// 	H("్", 0x0000);

// 	// convert to vothu
// 	V(".", 0x0000); // Aksharam vothu
// 	V(".", 0x0000); // Chinna vothu
// }

// static void setupTeluguVarnamala(TeluguDict &lut) {
// 	setupAchulu(lut);
// 	setupHallulu(lut);
// }

// static void setupAksharamlu(TeluguDict &lut) {
// 	AK("చి", 0x0000);
// 	AK("చీ", 0x0000);

// 	AK("వి", 0x0000);
// 	AK("వీ", 0x0000);

// 	AK("రి", 0x0000);
// 	AK("రీ", 0x0000);

// 	AK("జి", 0x0000);
// 	AK("జి", 0x0000); //
// 	AK("జీ", 0x0000);
// 	AK("జు", 0x0000);
// 	AK("జూ", 0x0000);

// 	AK("ది", 0x0000);
// 	AK("దీ", 0x0000);

// 	AK("శి", 0x0000);
// 	AK("ళీ", 0x0000);
// 	AK("ళీ", 0x0000); //

// 	AK("లి", 0x0000);
// 	AK("లీ", 0x0000); //

// 	AK("బి", 0x0000);
// 	AK("బీ", 0x0000);

// 	AK("తి", 0x0000);
// 	AK("తీ", 0x0000);

// 	AK("గి", 0x0000);
// 	AK("గీ", 0x0000);

// 	AK("ని", 0x0000);
// 	AK("నీ", 0x0000);

// 	AK("శ్రీ", 0x0000);
// 	AK("స్త్ర", 0x0000);
// 	AK("క్ష్మ", 0x0000); // new
// }

// void setupSpecial(TeluguDict &lut) {
// 	SP("0", 0x0000);	SP("1", 0x0000);	SP("2", 0x0000);	SP("3", 0x0000);	SP("4", 0x0000);
// 	SP("5", 0x0000);	SP("6", 0x0000);	SP("7", 0x0000);	SP("8", 0x0000);	SP("9", 0x0000);

// 	SP(".", 0x0000);	SP(":", 0x0000);	SP("?", 0x0000);	SP("(", 0x0000); SP(")", 0x0000);
// 	SP("!", 0x0000);	SP(",", 0x0000);	SP("`", 0x0000);	SP("`", 0x0000);	SP("`", 0x0000);

// 	SP(" ", 0x0000);	SP(" ", 0x0000);	SP(" ", 0x0000);	SP(" ", 0x0000);	SP(" ", 0x0000);
// 	SP(" ", 0x0000);	SP(" ", 0x0000);	SP(" ", 0x0000);	SP(" ", 0x0000);	SP(" ", 0x0000);
// 	SP(" ", 0x0000);	SP(" ", 0x0000);
// }