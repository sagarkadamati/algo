#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stack>
#include <map>
#include <vector>
#include <locale>
#include <clocale>
#include <bitset>
#include <iomanip>

#include <podofo/podofo.h>

using namespace std;
using namespace PoDoFo;

map<unsigned int, string> Achulu;
map<unsigned int, string> Vothulu;
map<unsigned int, string> Deergalu;
map<unsigned int, string> Aksharalu;
map<unsigned int, string> Skip;
map<unsigned int, int> Missing;
map<string, string> MissingCmds;

ofstream outdata("data.txt");

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

void mapAchulu(string ch, unsigned int index) {
	Achulu[index] = ch;
}

void mapAkshram(string ch, unsigned int index) {
	Aksharalu[index] = ch;
}

void mapDeergalu(string ch, unsigned int index) {
	Deergalu[index] = ch;
}

void mapVothulu(string ch, unsigned int index) {
	Vothulu[index] = ch;
}

void mapSkip(string ch, unsigned int index) {
	Skip[index] = ch;
}

void setupOther() {
	// Fixed Aksharamlu
	mapAkshram("వి", 0x24); //  36  $
	mapAkshram("వీ", 0x4D); //  77  M
	mapAkshram("రి", 0x5D); //  93  ]
	mapAkshram("శ్రీ", 0x6C); // 108	l
	mapAkshram("జూ", 0x70); // 112  p
	mapAkshram("తీ", 0x72); // 114  r
	mapAkshram("తీ", 0x2039);
	mapAkshram("ని", 0xEC); // 236  ì
	mapAkshram("జి", 0xF5); // 245  õ
	// mapAkshram("", 0x2030); dough
	mapAkshram("నీ", 0x02D9);
	mapAkshram("రీ", 0xD8); // 216  Ø
	mapAkshram("చి", 0x222B);
	mapAkshram("గి", 0x2013);
	mapAkshram("లి",  0x2A); //  42 *
	mapAkshram("బీ", 0x3b); //  59 ;
	mapAkshram("ాూ", 0x41); //  65  A dough
	mapAkshram("దీ", 0x42); //  66 B
	mapAkshram("జు", 0x45); //  69 E
	mapAkshram("జీ", 0x4A); //  74 J
	mapAkshram("చీ", 0x4E); //  78 N
	mapAkshram("ాు", 0x51); //  81 Q dough
	// 5b alla
	mapAkshram("గీ", 0x5E); //  94 ^
	mapAkshram("బి", 0x5F); //  95 _

	mapAkshram("శి", 0x2022);
	// mapAkshram("", 0x2022);
	mapAkshram("ది", 0x7E); // 126  ~
	mapAkshram("ళీ", 0x221E);

	// == Numbers ==
	// mapAchulu("౦", "");
	// mapAchulu("౧", "");
	// mapAchulu("౨", "");
	// mapAchulu("౩", "");
	// mapAchulu("౪", "");
	// mapAchulu("౫", "");
	// mapAchulu("౬", "");
	// mapAchulu("౭", "");
	// mapAchulu("౮", "");
	// mapAchulu("౯", "");

	// == Teledu ==
	// mapAchulu("౸", );
	// mapAchulu("౹", );
	// mapAchulu("౺", );
	// mapAchulu("౻", );
	// mapAchulu("౼", );
	// mapAchulu("౽", );
	// mapAchulu("౾", );
	// mapAchulu("౿", );

	// == Vothulu ==
	// mapAkshram("ౘ", );
	// mapAkshram("ౙ", );
	// mapAkshram("ౠ", );
	// mapAkshram("ౡ", );
}

void setupAchulu() {
	mapAchulu("అ", 0x6E); // 110 n
	mapSkip("", 0xA1);
	mapSkip("", 0xA3);
	mapSkip("", 0xAF);
	mapSkip("", 0xB7);
	mapSkip("", 0xC9);
	mapSkip("", 0xD1);
	mapSkip("", 0xE4);
	mapSkip("", 0xFC);
	mapSkip("", 0x2211);

	mapAchulu("ఆ", 0xC4); // 196 Ä
	mapDeergalu("ా",  0xB1); // 177 ±
	mapDeergalu("ా",  0xCA); // 202 Ê
	mapDeergalu("ా",  0xD5); // 213 Õ
	mapDeergalu("ా",  0xDC); // 220 Ü
	mapDeergalu("ా",  0xEA); // 234 ê
	mapDeergalu("ా",  0xEB); // 235 ë
	mapDeergalu("ా",  0x2264);

	mapAchulu("ఇ", 0xC7); // 199 Ç
	mapDeergalu("ి", 0xE6); // 230 æ
	mapDeergalu("ి", 0xE7); // 231 ç
	mapDeergalu("ి", 0xCF); // 207 Ï

	mapAchulu("ఈ", 0xE1); // 225 á
	mapDeergalu("ీ", 0xB0); // 176 °
	mapDeergalu("ీ", 0xFB); // 251 û
	mapDeergalu("ీ", 0x201D);

	mapAchulu("ఉ", 0xF1); // 241 ñ
	mapDeergalu("ు", 0x54); //  84 T మ di u
	mapDeergalu("ు", 0xDF); // 223 ß
	mapDeergalu("ు", 0xEE); // 238 î
	mapDeergalu("ు", 0xF3); // 243 ó
	mapDeergalu("ు", 0x2044);

	mapAchulu("ఊ", 0x7D); // 125 }
	mapDeergalu("ూ", 0x4C); //  76 L
	mapDeergalu("ూ", 0x4F); //  79 O // dough
	mapDeergalu("ూ", 0x50); //  80 P
	mapDeergalu("ూ", 0x53); //  83 S
	mapDeergalu("ూ", 0xF7); // 247 ÷ // మ di dergam

	// mapAchulu("ఋ", );
	mapDeergalu("ృ", 0xE8); // 232 è
	// mapAchulu("ఌ", );
	// mapDeergalu("ౄ", );

	// mapAchulu("ఎ", );
	mapDeergalu("ె", 0xAC); // 172 ¬
	mapDeergalu("ె", 0xCB); // 203 Ë
	mapDeergalu("ె", 0xD3); // 211 Ó
	mapDeergalu("ె", 0xF4); // 244 ô
	mapDeergalu("ె", 0x2026);

	mapAchulu("ఏ", 0x40); //  64 @
	mapDeergalu("ే", 0xD2); // 210 Ò
	mapDeergalu("ే", 0xF9); // 249 ù
	mapDeergalu("ే", 0x03C0);
	mapDeergalu("ే", 0x201A);
	mapDeergalu("ే", 0x02DA);

	mapAchulu("ఐ", 0x25CA);
	mapDeergalu("ై", 0x2019); // is part of two chars
	mapDeergalu("ై", 0x2206);

	mapAchulu("ఒ", 0x02c7);
	mapVothulu("ొ", 0x3D); //  61 =
	mapVothulu("ొ", 0xA7); // 167 §
	mapVothulu("ొ", 0x131);

	mapAchulu("ఓ", 0x7A); // 122 z
	mapDeergalu("ొ", 0xC0); // 192 À
	mapDeergalu("ో", 0x02DB);
	mapDeergalu("ో", 0x2218); // dough
	mapDeergalu("ో", 0x221A);

	// mapAchulu("ఔ", );
	mapDeergalu("ౌ",  0xC2); // 194 Â
	mapDeergalu("ౌ",  0xD6); // 214 Ö
	mapDeergalu("ౌ",  0xDA); // 218 Ú
	mapDeergalu("ౌ",  0xF6); // 246 ö

	// mapDeergalu("ౕ", );
	// mapDeergalu("ౖ", );

	// mapDeergalu("ౢ", );
	// mapDeergalu("ౣ", );

	//  skip ్
	mapDeergalu("్", 0x59); //  89 Y
	mapDeergalu("్", 0x74); // 116 t
	mapDeergalu("్", 0xE9); // 233 é
	mapDeergalu("్", 0x0178);
	mapDeergalu("్", 0x02D8);

	mapDeergalu("ం",  0x2B); //  43 +
	// mapDeergalu("ః", );
	// mapDeergalu("ఁ", );
	// mapDeergalu("ఀ", );
}

void setupHallulu() {
	mapAchulu("క",  0xF8); // 248 ø
	mapVothulu("్క", 0xFF); // 255 ÿ
	mapAchulu("క",  0x2248);
	// mapAchulu("్ర",  0x2248); dough

	mapAchulu("ఖ", 0x4B); //  75 K
	mapAchulu("ఖ", 0x55); //  85 U
	mapVothulu("్ఖ",  0xE2); // 226	â

	mapAchulu("గ",  0x3E); //  62 >
	mapVothulu("్గ",  0x5A); //  90	Z

	// mapAchulu("ఘ", );
	mapVothulu("్ఘ", 0xC8); // 200 È

	// mapAchulu("ఙ", );

	mapAchulu("చ", 0x23); //  35 #
	mapVothulu("్చ", 0xC3); // 195 Ã

	// mapAchulu("ఛ", );
	mapAchulu("జ", 0x43); //  67 C
	mapVothulu("్జ",  0xAE); // 174 ®
	mapAchulu("జ", 0xBB); // 187 »
	// mapAchulu("ఝ", );
	// mapAchulu("ఞ", );
	mapVothulu("్ఞ", 0x201E);

	mapAchulu("ట", 0x66); // 102 f
	mapAchulu("ట", 0x7B); // 123 {
	mapAchulu("ట", 0x2265);
	mapVothulu("్ట",  0xBA); // 186 º

	// mapAchulu("ఠ", );
	mapVothulu("్ఠ", 0x02DC);

	mapAchulu("డ", 0x26); //  38 &
	mapVothulu("్డ",  0xB6); // 182 ¶

	// mapAchulu("ఢ", );
	mapAchulu("ణ", 0x44); //  68 D
	mapVothulu("్ణ",  0xED); // 237 í

	mapAchulu("త", 0x84); // 132 „
	mapAchulu("త", 0x2018);
	mapVothulu("్త",  0xD4); // 212 Ô

	// mapAchulu("థ", );
	mapVothulu("్థ",  0xFA); // 250 ú

	mapAchulu("ద",  0x3C); //  60 <
	mapVothulu("్ద", 0x203A);

	// mapAchulu("ధ", );
	mapVothulu("్ధ", 0x0394);

	mapAchulu("న", 0x48); //  72 H
	mapAchulu("న", 0x71); // 113 q
	mapVothulu("్న", 0xEF); // 239 ï

	mapAchulu("వ", 0x6D); // 109 m
	mapAchulu("ప", 0x7C); // 124 |
	mapAchulu("ప", 0x62); //  98 b ఎ
	mapVothulu("్ప", 0x0152);

	// mapAchulu("ఫ", );
	mapAchulu("బ", 0x75); // 117 u
	mapAchulu("బ", 0xE3); // 227 ã
	mapVothulu("్బ", 0x201C);
	// mapAchulu("భ", );
	// mapAchulu("మ", );
	mapVothulu("్మ", 0xE0); // 224 à

	mapAchulu("య", 0x6A); // 106 j
	mapVothulu("్య",  0xB4); // 180 ´

	mapAchulu("ర", 0x73); // 115 s
	mapVothulu("్ర", 0xC5); // 197 Å

	// mapAchulu("ఱ", );
	mapAchulu("ల", 0x5C); //  92 \ (for comments)
	mapAchulu("ల", 0x2DD);
	mapVothulu("్ల",  0xA2); // 162	¢

	mapAchulu("ళ",  0x5B); //  91 [ // dough
	mapAchulu("ళ",  0xFB01);

	// mapAchulu("ఴ", );
	mapAchulu("వ", 0x65); // 101 e
	mapAchulu("వ", 0x79); // 121 y
	mapVothulu("్వ", 0xAB); // 171  «

	mapAchulu("శ",  0x58); //  88 X
	mapVothulu("్శ", 0xD9); // 217  Ù

	mapAchulu("ష", 0x63); //  99 c
	mapAchulu("ష", 0xB8); // 184  ¸
	mapAchulu("ష", 0x77); // 119 w
	mapVothulu("్ష",  0xE5); // 229 å

	mapAchulu("స", 0x64); // 100 d
	mapAchulu("స", 0x6B); // 107 k
	mapVothulu("్స", 0x2021);

	mapAchulu("హ", 0x56); //  86 V
	mapVothulu("్హ", 0x03A9);
}

void setupVothulu() {
	// mapVothulu("ఽ", );


	// == Extra ==

	// Ignore ticks
}

void setupFontLUT() {
	// map("",   0); //   0	(0x00) ^@
	// map("",   1); //   1	(0x01) ^A
	// map("",   2); //   2	(0x02) ^B
	// map("",   3); //   3	(0x03) ^C
	// map("",   4); //   4	(0x04) ^D
	// map("",   5); //   5	(0x05) ^E
	// map("",   6); //   6	(0x06) ^F
	// map("",   7); //   7	(0x07) ^G
	// map("",   8); //   8	(0x08) ^H
	// map("",   9); //   9	(0x09) ^I
	// map("",  10); //  10	(0x0a) ^J
	// map("",  11); //  11	(0x0b) ^K
	// map("",  12); //  12	(0x0c) ^L
	// map("",  13); //  13	(0x0d) ^M
	// map("",  14); //  14	(0x0e) ^N
	// map("",  15); //  15	(0x0f) ^O
	// map("",  16); //  16	(0x10) ^P
	// map("",  17); //  17	(0x11) ^Q
	// map("",  18); //  18	(0x12) ^R
	// map("",  19); //  19	(0x13) ^S
	// map("",  22); //  22	(0x16) ^V
	// map("",  20); //  20	(0x14) ^T
	// map("",  21); //  21	(0x15) ^U
	// map("",  23); //  23	(0x17) ^W
	// map("",  24); //  24	(0x18) ^X
	// map("",  25); //  25	(0x19) ^Y
	// map("",  26); //  26	(0x1a) ^Z
	// map("",  27); //  27	(0x1b) ^[
	// map("",  28); //  28	(0x1c) ^\ (for commenting)
	// map("",  29); //  29	(0x1d) ^]
	// map("",  30); //  30	(0x1e) ^^
	// map("",  31); //  31	(0x1f) ^_
	// map("",  34); //  34	(0x22) “
	// map("",  37); //  37	(0x25) %
	// map("",  39); //  39	(0x27) ‘
	// map("",  45); //  45	(0x2d) –
	// map("",  47); //  47	(0x2f) /
	// map("",  70); //  70	(0x46) F
	// map("",  71); //  71	(0x47) G
	// map("",  73); //  73	(0x49) I
	// map("",  82); //  82	(0x52) R
	// map("",  87); //  87	(0x57) W
	// map("",  97); //  97	(0x61) a
	// map("", 103); // 103	(0x67) g
	// map("", 104); // 104	(0x68) h
	// map("", 105); // 105	(0x69) i
	// map("", 111); // 111	(0x6f) o
	// map("", 118); // 118	(0x76) v
	// map("", 120); // 120	(0x78) x
	// map("", 128); // 128	(0x80) €
	// map("", 129); // 129	(0x81) 
	// map("", 130); // 130	(0x82) ‚
	// map("", 131); // 131	(0x83) ƒ
	// map("", 133); // 133	(0x85) …
	// map("", 134); // 134	(0x86) †
	// map("", 135); // 135	(0x87) ‡
	// map("", 136); // 136	(0x88) ˆ
	// map("", 137); // 137	(0x89) ‰
	// map("", 138); // 138	(0x8a) Š
	// map("", 139); // 139	(0x8b) ‹
	// map("", 140); // 140	(0x8c) Œ
	// map("", 141); // 141	(0x8d) 
	// map("", 142); // 142	(0x8e) Ž
	// map("", 143); // 143	(0x8f) 
	// map("", 144); // 144	(0x90) 
	// map("", 145); // 145	(0x91) ‘
	// map("", 146); // 146	(0x92) ’
	// map("", 147); // 147	(0x93) “
	// map("", 148); // 148	(0x94) ”
	// map("", 149); // 149	(0x95) •
	// map("", 150); // 150	(0x96) –
	// map("", 151); // 151	(0x97) —
	// map("", 152); // 152	(0x98) ˜
	// map("", 153); // 153	(0x99) ™
	// map("", 154); // 154	(0x9a) š
	// map("", 155); // 155	(0x9b) ›
	// map("", 156); // 156	(0x9c) œ
	// map("", 157); // 157	(0x9d) ¥
	// map("", 158); // 158	(0x9e) ž
	// map("", 159); // 159	(0x9f) Ÿ
	// map("", 161); // 161	(0xa1) ¡ no need tick
	// map("", 163); // 163	(0xa3) £ no need tick
	// map("", 165); // 165	(0xa5) ¥
	// map("", 166); // 166	(0xa6) ¦
	// map("", 168); // 168	(0xa8) ¨
	// map("", 169); // 169	(0xa9) ©
	// map("", 173); // 173	(0xad)
	// map("", 175); // 175	(0xaf) ¯ no need tick
	// map("", 178); // 178	(0xb2) ²
	// map("", 179); // 179	(0xb3) ³
	// map("", 181); // 181	(0xb5) µ
	// map("", 183); // 183	(0xb7) · no need tick
	// map("", 185); // 185	(0xb9) ¹
	// map("", 188); // 188	(0xbc) ¼
	// map("", 189); // 189	(0xbd) ½
	// map("", 190); // 190	(0xbe) ¾
	// map("", 191); // 191	(0xbf) ¿
	// map("", 193); // 193	(0xc1) Á
	// map("", 198); // 198	(0xc6) Æ
	// map("", 201); // 201	(0xc9) É no need tick
	// map("", 204); // 204	(0xcc) Ì
	// map("", 205); // 205	(0xcd) Í
	// map("", 206); // 206	(0xce) Î
	// map("", 208); // 208	(0xd0) Ð
	// map("", 209); // 209	(0xd1) Ñ
	// map("", 215); // 215	(0xd7) ×
	// map("", 221); // 221	(0xdd) Ý
	// map("", 222); // 222	(0xde) Þ
	// map("", 228); // 228	(0xe4) ä no need tick
	// map("", 240); // 240	(0xf0) ð
	// map("", 252); // 252	(0xfc) ü no need tick
	// map("", 253); // 253	(0xfd) ý
	// map("", 254); // 254	(0xfe) þ

	mapAchulu(" ", 0x20); //  32 <space>
	mapAchulu(" ", 0x7F); // 127 <space>
	mapAchulu(" ", 0xA0); // 160 <space>
	mapAchulu("!", 0x21); //  33 !
	mapAchulu(",", 0x2C); //  44 ,
	mapAchulu(".", 0x2E); //  46 .
	mapAchulu("(", 0x28); //  40 (
	mapAchulu(")", 0x29); //  41 )
	mapAchulu("0", 0x30); //  48 0
	mapAchulu("1", 0x31); //  49 1
	mapAchulu("2", 0x32); //  50 2
	mapAchulu("3", 0x33); //  51 3
	mapAchulu("4", 0x34); //  52 4
	mapAchulu("5", 0x35); //  53 5
	mapAchulu("6", 0x36); //  54 6
	mapAchulu("7", 0x37); //  55 7
	mapAchulu("8", 0x38); //  56 8
	mapAchulu("9", 0x39); //  57 9
	mapAchulu(":", 0x3A); //  58 :
	mapAchulu("?", 0x3F); //  63 ?
	mapAchulu("-", 0x60); //  96 `
	mapAchulu(".", 0xA4); // 164 ¤
	mapSkip(".", 0xDB); // 219 Û
	mapAchulu(".", 0xF2); // 242 ò
	mapAchulu(".", 0x192);
	mapAchulu("|", 0x02C6);
	mapAchulu(":", 0x220F);
	mapAchulu(",", 0x3BC);
	// mapAchulu("", 0xAA); // 170 ª opposit to comma

	setupAchulu();
	setupHallulu();
	setupOther();
	setupVothulu();
}

void ReplaceStringInPlace(std::string& subject, const std::string& search,
                          const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

string empty("");
class TeluguText {
	private:
		vector< pair<unsigned short, string> > text;
	public:
		unsigned short nextChar(string &text, int *i) {
			unsigned short c = 0;

			if ((text[(*i)] & 0x80) == 0x00){ // check msb bit zero
				c = (text[(*i)++] & 0x7F);
			} else if ((text[(*i)] & 0xE0) == 0xC0) { // 1100 - check if two byte char
				c  = (text[(*i)++] & 0x1F) << 6;
				c |= (text[(*i)++] & 0x3F);
			} else if ((text[(*i)] & 0xF0) == 0xE0) { // 1110 - check if three byte char
				c  = (text[(*i)++] & 0x0F) << 12;
				c |= (text[(*i)++] & 0x3F) << 6;
				c |= (text[(*i)++] & 0x3F);
			}

			return c;
		}

		pair<unsigned short, string> getCharPair(unsigned short c) {
			if ( Achulu.find(c) != Achulu.end() ) {
				return make_pair(c, Achulu[c]);
			} else if ( Vothulu.find(c) != Vothulu.end() ) {
				return make_pair(c, Vothulu[c]);
			} else if ( Deergalu.find(c) != Deergalu.end() ) {
				return make_pair(c, Deergalu[c]);
			} else if ( Aksharalu.find(c) != Aksharalu.end() ) {
				return make_pair(c, Aksharalu[c]);
			} else {
				Missing[c]++;
				return make_pair(c, "");
			}
		}

		bool isSkippable(unsigned short c) {

			if (Skip.find(c) != Skip.end()) {
				return true;
			}

			if (text.size() > 0) {
				string prev = text.back().second;
				// if ( prev == string("య") || prev == string("మ") ) {
				// } else
				if ( c == 0x54 ) { // "ు"
					// if ( Deergalu[c] == string("ు") ) {
					if ( prev == string("మ") ) {
						text.push_back(make_pair(0x54, "ు"));
						return true;
					} else if ( Achulu[text.back().first] == string("వ") ) {
						text.pop_back();
						text.push_back(make_pair(c, "మ"));
						return true;
					} else if ( Achulu[text.back().first] == string("య") ) {
						text.pop_back();
						text.push_back(make_pair(c, "య"));
						return true;
					}
				} else if ( c == 0xF7 ) {
					if ( Achulu[text.back().first] == string("వ") ) {
						text.pop_back();
						text.push_back(make_pair(c, "మ"));
						text.push_back(make_pair(c, "ా"));
						return true;
					}
				} else if ( prev == string("్") ) {
					cout << endl << "entered"<< endl;
					pair<unsigned short, string> ahrr = text.back();
					text.pop_back();

					pair<unsigned short, string> deergram = text.back();
					if ( Deergalu.find(deergram.first) != Deergalu.end() ) {
						text.pop_back();

						text.push_back(ahrr);
						text.push_back(getCharPair(c));

						text.push_back(deergram);
					} else {
						text.push_back(ahrr);
						text.push_back(getCharPair(c));
					}

					return true;
				} else if ( Vothulu.find(c) != Vothulu.end() ) {
					pair<unsigned short, string> deergram = text.back();
					if ( Deergalu.find(deergram.first) != Deergalu.end() ) {
						text.pop_back();
						text.push_back(getCharPair(c));
						text.push_back(deergram);
					} else {
						text.push_back(getCharPair(c));
					}

					return true;
				} else if ( Aksharalu.find(c) != Aksharalu.end() ) {
					switch(c) {
						case 0x24:  // "వి"
							text.push_back(make_pair(c, "వ"));
							text.push_back(make_pair(0xE6, "ి"));
							break;
						case 0x4D:  // "వీ"
							text.push_back(make_pair(c, "వ"));
							text.push_back(make_pair(0xB0, "ీ"));
							break;
						case 0x5D:  // "రి"
							text.push_back(make_pair(c, "ర"));
							text.push_back(make_pair(0xE6, "ి"));
							break;
						case 0x6:   // "శ్రీ"
							text.push_back(make_pair(c, "శ"));
							text.push_back(make_pair(c, "్"));
							text.push_back(make_pair(c, "ర"));
							break;
						case 0x70:  // "జూ"
							text.push_back(make_pair(c, "జ"));
							text.push_back(make_pair(0x4C, "ూ"));
							break;
						case 0x72:  // "తీ"
							text.push_back(make_pair(c, "త"));
							text.push_back(make_pair(0xB0, "ీ"));
							break;
						case 0x2039:// "తీ"
							text.push_back(make_pair(c, "త"));
							text.push_back(make_pair(0xB0, "ీ"));
							break;
						case 0xEC:  // "ని"
							text.push_back(make_pair(c, "న"));
							text.push_back(make_pair(0xE6, "ి"));
							break;
						case 0xF5:  // "జి"
							text.push_back(make_pair(c, "జ"));
							text.push_back(make_pair(0xE6, "ి"));
							break;
						case 0x02D9:// "నీ"
							text.push_back(make_pair(c, "న"));
							text.push_back(make_pair(0xB0, "ీ"));
							break;
						case 0xD8:  // "రీ"
							text.push_back(make_pair(c, "ర"));
							text.push_back(make_pair(0xB0, "ీ"));
							break;
						case 0x222B:// "చి"
							text.push_back(make_pair(c, "చ"));
							text.push_back(make_pair(0xE6, "ి"));
							break;
						case 0x2013:// "గి"
							text.push_back(make_pair(c, "గ"));
							text.push_back(make_pair(0xE6, "ి"));
							break;
						case 0x2A:  // "లి"
							text.push_back(make_pair(c, "ల"));
							text.push_back(make_pair(0xE6, "ి"));
							break;
						case 0x3b:  // "బీ"
							text.push_back(make_pair(c, "బ"));
							text.push_back(make_pair(0xB0, "ీ"));
							break;
						case 0x41:  // "ాూ"
							text.push_back(make_pair(c, "ా"));
							text.push_back(make_pair(0x4C, "ూ"));
							break;
						case 0x42:  // "దీ"
							text.push_back(make_pair(c, "ద"));
							text.push_back(make_pair(0xB0, "ీ"));
							break;
						case 0x45:  // "జు"
							text.push_back(make_pair(c, "జ"));
							text.push_back(make_pair(0x54, "ు"));
							break;
						case 0x4A:  // "జీ"
							text.push_back(make_pair(c, "జ"));
							text.push_back(make_pair(0xB0, "ీ"));
							break;
						case 0x4E:  // "చీ"
							text.push_back(make_pair(c, "చ"));
							text.push_back(make_pair(0xB0, "ీ"));
							break;
						case 0x51:  // "ాు"
							text.push_back(make_pair(c, "ా"));
							text.push_back(make_pair(0x54, "ు"));
							break;
						case 0x5E:  // "గీ"
							text.push_back(make_pair(c, "గ"));
							text.push_back(make_pair(0xB0, "ీ"));
							break;
						case 0x5F:  // "బి"
							text.push_back(make_pair(c, "బ"));
							text.push_back(make_pair(0xE6, "ి"));
							break;
						case 0x2022:// "శి"
							text.push_back(make_pair(c, "శ"));
							text.push_back(make_pair(0xE6, "ి"));
							break;
						case 0x7E:  // "ది"
							text.push_back(make_pair(c, "ద"));
							text.push_back(make_pair(0xE6, "ి"));
							break;
						case 0x221E:// "ళీ"
							text.push_back(make_pair(c, "ళ"));
							text.push_back(make_pair(0xB0, "ీ"));
							break;
					}
					return true;
				} else if ( prev == string("హ")  && Deergalu[c] == string("ా") ) {
					return true;
				}
			}

			return false;
		}

		bool isReplaceable(unsigned short c) {
			if (text.size() > 0) {
				string prev = text.back().second;
				if ( prev == string("ె")  && Deergalu[c] == string("ై") ) {
					return true;
				}
			}

			return false;
		}

		bool substitue(unsigned short c) {
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

			return false;
		}

		void set(string &str) {
			text.clear();

			int i = 0;
			int textSize = str.length();
			while (i < textSize) {
				unsigned short c = nextChar(str, &i);
				string ch;

				if (!isSkippable(c)) {
					if (isReplaceable(c)) {
						text.pop_back();

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
					}

					if (!substitue(c)) {
						text.push_back(getCharPair(c));
					}
				}
			}
		}

		TeluguText(string &str) {
			set(str);
		}

		string &operator[] (int index) {
			bool debug = true;

			if (index < text.size()) {
				if (debug) {
					unsigned short c = text[index].first;

					cout << setw(8) << dec << c;
					cout << setw(8) << hex << c;
					cout << setw(20) << bitset<16>(c);

					if (c == 32 || c == 46) {
						cout << setw(4);
					} else {
						cout << setw(6);
					}

					cout << text[index].second;
					cout << endl;
				}

				return text[index].second;
			} else {
				return empty;
			}
		}

		unsigned short charCode (int index) {
			if (index < text.size()) {
				return text[index].first;
			} else {
				return 0;
			}
		}

		int size() {
			return text.size();
		}

		~TeluguText() {
			text.clear();
		}
};

ostream & operator << (ostream &out, TeluguText &teluguText) {
	int textSize = teluguText.size();

	int i = 0;
	while (i < textSize) {
		out << teluguText[i++];
	}

	return out;
}

void printMissing() {
	cout << endl << endl << "=== Missing (" << dec << Missing.size() << ") ===";
	for(map<unsigned int, int>::iterator c = Missing.begin(); c != Missing.end(); c++) {
		cout << endl << " New: ";
		cout << setw(8) << dec << c->first;
		cout << setw(8) << hex << c->first;
		cout << setw(20) << bitset<16>(c->first);
	}
	cout << endl;
}

void printMissingCmds() {
	cout << endl << endl << "=== Missing CMDS (" << dec << MissingCmds.size() << ") ===";
	for(map<string, string>::iterator c = MissingCmds.begin(); c != MissingCmds.end(); c++) {
		cout << endl << " CMD: " << c->first;
	}
	cout << endl;
}

std::string extract( PdfMemDocument* pDocument, PdfPage* pPage , string removefont)
{
	const char*      pszToken = NULL;
	PdfVariant       var;
	EPdfContentsType eType;

	PdfContentsTokenizer tokenizer( pPage );

	double x            = 0.0;
	double y            = 0.0;

	double red          = 0.0;
	double green        = 0.0;
	double blue         = 0.0;

	double td_x         = 0.0;
	double td_y         = 0.0;

	double scale_x      = 0.0;
	double shear_x      = 0.0;
	double shear_y      = 0.0;
	double scale_y      = 0.0;
	double offset_x     = 0.0;
	double offset_y     = 0.0;

	double size;
	double g;
	string str;

	bool record = true;

	bool   bTextBlock   = false;
	PdfObject* pFont;
	PdfFont* pCurFont   = NULL;

	int count = 0;

	std::stack<PdfVariant> stack;
	std::ostringstream block;

	while( tokenizer.ReadNext( eType, pszToken, var ) )
	{
		if( eType == ePdfContentsType_Keyword )
		{
			if( strcmp( pszToken, "cm" ) == 0 )	{
				offset_y = stack.top().GetReal();
				stack.pop();
				offset_x = stack.top().GetReal();
				stack.pop();
				scale_y  = stack.top().GetReal();
				stack.pop();
				shear_y  = stack.top().GetReal();
				stack.pop();
				shear_x  = stack.top().GetReal();
				stack.pop();
				scale_x  = stack.top().GetReal();
				stack.pop();

				if(record) {
					block << scale_x << " "
					      << shear_x << " "
					      << shear_y << " "
					      << scale_y << " "
					      << offset_x << " "
					      << offset_y << " cm " << endl;
				}
			} else if( strcmp( pszToken, "re" ) == 0 ) {
				offset_y = stack.top().GetReal();
				stack.pop();
				offset_x = stack.top().GetReal();
				stack.pop();
				scale_y  = stack.top().GetReal();
				stack.pop();
				shear_y  = stack.top().GetReal();
				stack.pop();

				if(record) {
					block << shear_y << " "
					      << scale_y << " "
					      << offset_x << " "
					      << offset_y << " "
					      << pszToken << " " << endl;
				}
			} else if ( strcmp( pszToken, "W" ) == 0 ||
			    strcmp( pszToken, "n" ) == 0 ||
			    strcmp( pszToken, "q" ) == 0 ||
			    strcmp( pszToken, "Q" ) == 0 ) {
				if(record) {
					block << pszToken << endl;
				}
			} else if ( strcmp( pszToken, "w" ) == 0 ||
				strcmp( pszToken, "Tz" ) == 0 ||
				strcmp( pszToken, "g" ) == 0 ||
				strcmp( pszToken, "G" ) == 0 ) {
					g = stack.top().GetReal();
					stack.pop();
				if(record) {
					block << g << " " << pszToken << endl;
				}
			} else if ( strcmp( pszToken, "rg" ) == 0 || strcmp( pszToken, "RG" ) == 0 ) {
				blue = stack.top().GetReal();
				stack.pop();
				green = stack.top().GetReal();
				stack.pop();
				red = stack.top().GetReal();
				stack.pop();

				red = 0.396;   // 0.0 for black
				green = 0.482; // 0.0 for black
				blue = 0.514;  // 0.0 for black

				if(record) {
					block << red << " "
					      << green << " "
					      << blue << " "
					      << pszToken << endl;
				}

				// cout << red << " "
				//       << green << " "
				//       << blue << " "
				//       << pszToken << endl;
			} else if( strcmp( pszToken, "l" ) == 0 || strcmp( pszToken, "m" ) == 0 ) {
				// support 'l' and 'm' tokens
				x = stack.top().GetReal(); stack.pop();
				y = stack.top().GetReal(); stack.pop();
			} else if( strcmp( pszToken, "BT" ) == 0 ) {
				bTextBlock   = true;
				if(record) {
					block << "BT" << endl;
				}
			} else if( strcmp( pszToken, "ET" ) == 0 ) {
				if(record) {
					block << "ET" << endl;
					outdata << endl;
				}
			} else if( strcmp( pszToken, "Tf" ) == 0 ) {
				size = stack.top().GetReal(); stack.pop();

				PdfName fontName = stack.top().GetName();
				pFont = pPage->GetFromResources( PdfName("Font"), fontName );
				pCurFont = pDocument->GetFont( pFont );

				if(fontName.GetName().compare( removefont ) == 0)
					record = false;
				else {
					if(count)
						record = true;
					else
						record = false;
					count++;
				}

				if(record)
					block << "/"
							<< fontName.GetName()
							<< " " << size << " "
							<< "Tf" << endl;

				// cout << "/"
				//       << str
				//       << " " << size << " "
				//       << "Tf" << endl;
			} else if( strcmp( pszToken, "gs" ) == 0 ) {
				block << "/"
						<< stack.top().GetName().GetName()
						<< " " << "gs" << endl;
			} else if( strcmp( pszToken, "Tc" ) == 0 || strcmp( pszToken, "TL" ) == 0 || strcmp( pszToken, "Tw" ) == 0 ) {
				td_y = stack.top().GetReal(); stack.pop();

				block << td_y << " " << pszToken << endl;
			} else if( strcmp( pszToken, "TD" ) == 0 || strcmp( pszToken, "Td" ) == 0) {
				td_y = stack.top().GetReal(); stack.pop();
				td_x = stack.top().GetReal(); stack.pop();

				block << td_x << " "
						<< td_y << " "
						<< pszToken << endl;
			} else if( strcmp( pszToken, "Tm" ) == 0 ) {
				offset_y = stack.top().GetReal(); stack.pop();
				offset_x = stack.top().GetReal(); stack.pop();
				scale_y  = stack.top().GetReal(); stack.pop();
				shear_y  = stack.top().GetReal(); stack.pop();
				shear_x  = stack.top().GetReal(); stack.pop();
				scale_x  = stack.top().GetReal(); stack.pop();

				block << scale_x << " "
						<< shear_x << " "
						<< shear_y << " "
						<< scale_y << " "
						<< offset_x << " "
						<< offset_y << " "
						<< pszToken << endl;
			} else if ( strcmp( pszToken, "T*" ) == 0 ) {

			} else if ( strcmp( pszToken, "cs" ) == 0 ) {

			} else if ( strcmp( pszToken, "i" ) == 0 ) {

			} else if ( strcmp( pszToken, "scn" ) == 0 ) {

			} else if( strcmp( pszToken, "Tj" ) == 0 || strcmp( pszToken, "'" ) == 0 ) {

			// if( bTextBlock )
			// {
				if(record) {
					if (strcmp( pszToken, "'" ) == 0) {
						// cout << endl;
					}
					PdfString pStr = stack.top().GetString(); stack.pop();
					string text = pCurFont->GetEncoding()->ConvertToUnicode(pStr, pCurFont).GetStringUtf8();
					TeluguText teluguText(text);

					cout << endl;
					outdata << teluguText << endl;
					// return "";

					ReplaceStringInPlace(str, "\\", "\\\\");
					ReplaceStringInPlace(str, "(", "\\(");
					ReplaceStringInPlace(str, ")", "\\)");

					block << "(" << str
							<< ")" << pszToken << endl;
				}
			} else if( strcmp( pszToken, "TJ" ) == 0 ) {
				PdfArray array = stack.top().GetArray();
				stack.pop();

				block << "[";

				for( int i=0; i<static_cast<int>(array.GetSize()); i++ )
				{
					if( array[i].IsString() || array[i].IsHexString() ) {
						PdfString pdfstr = array[i].GetString();
						string text = pdfstr.GetStringUtf8();
						TeluguText teluguText(text);

						cout << endl;
						outdata << teluguText;

						string str = pdfstr.GetString();
						// cout << "String TJ, " << text.length() << " String: " << boolalpha << array[i].IsString() << endl;
						ReplaceStringInPlace(str, "\\", "\\\\");
						ReplaceStringInPlace(str, "(", "\\(");
						ReplaceStringInPlace(str, ")", "\\)");

						block << "("
								<< str
								<< ")";
					}
					else if( array[i].IsNumber()) {
						// cout << "Real TJ" << endl;
						block << array[i].GetReal();
					}
				}
				block << "]" << pszToken << endl;
			} else {
				MissingCmds[pszToken] = pszToken;
			}
		} else if ( eType == ePdfContentsType_Variant ) {
			stack.push( var );
		} else {
			cout << endl << "Unknown variant" << endl;
		}
	}

	return block.str();
}

char glimps[1024];
int size = 0;
int is_exist(char ch)
{
	for(int i = 0; i < size; i++) {
		if(glimps[i] == ch)
			return 1;
	}

	return 0;
}

std::string process_glimps(string font)
{
	std::ostringstream block;
	int x = 0, y = 800;

	block << "q" << endl;
	block << "0 0 1 rg" << endl;
	block << "0.99999 0 0 -1 951 67 Tm" << endl;
	block << "BT" << endl;
	block << "/" << font << 20 << endl;

	for(int i = 0; i < size; i++) {
		if(!(x % 450)) {
			x = 30;
			y -= 40;
		}
		else
			x += 30;

		block << "1 0 0 1 " << x << " " << y << " Tm" << endl;
		if(glimps[i] == '(')
			block << "(\()Tj" << endl;
		else if(glimps[i] == ')')
			block << "(\\))Tj" << endl;
		else if(glimps[i] == '\\')
			block << "(\\\\)Tj" << endl;
		else
			block << "(" << glimps[i] << ")Tj" << endl;
	}

	block << "ET" << endl;
	block << "Q";

	return block.str();
}

void get_glimpse( PdfMemDocument* pDocument, PdfPage* pPage )
{
	const char*          pszToken = NULL;
	PdfVariant           var;
	EPdfContentsType     eType;
	string               str;

	PdfContentsTokenizer tokenizer( pPage );

	while( tokenizer.ReadNext( eType, pszToken, var ) )
		if( eType == ePdfContentsType_Keyword ) {
			if( strcmp( pszToken, "Tj" ) == 0 ||
			    strcmp( pszToken, "'" ) == 0 ) {

				str = var.GetString().GetString();
				for (int i = 0; i < str.size(); i++)
					if(!is_exist(str.at(i)))
						glimps[size++] = str.at(i);
			}
			else if( strcmp( pszToken, "TJ" ) == 0 )
			{
				PdfArray array = var.GetArray();

				for( int i=0; i<static_cast<int>(array.GetSize()); i++ )
				{
					string str;
					if( array[i].IsString() || array[i].IsHexString() ) {
						str = array[i].GetString().GetString();
						for (int i = 0; i < str.size(); i++)
							if(!is_exist(str.at(i)))
								glimps[size++] = str.at(i);
					}
				}
			}

		}
}

void convert(string input,string output, string removefont, int del_start, int del_end)
{
	int pn, pc;

	PdfMemDocument pdf(input.c_str());

	PdfPage*       page = pdf.GetPage(1);
	PdfObject*     contents = page->GetContents();
	PdfObject*     resources = page->GetResources();
	// PdfStream*     stream = contents->GetStream();
	PdfRect        mediabox = page->GetMediaBox();

	char*          pBuffer;
	pdf_long       lLen;
	string         str;

	cout << "Skandam " << input << " Processing..." << endl << endl;

	ofstream modified;
	ofstream actual;
	modified.open("modified.txt");
	actual.open("actual.txt");

	PdfError::EnableDebug( false );

	pc = pdf.GetPageCount();
	if(del_start)
		pdf.DeletePages(0, del_start);

	if(del_end)
		pdf.DeletePages(pc - del_end - 1, del_end);


	pc = pdf.GetPageCount();
	pc = 3;
	for (pn = 2; pn < pc; ++pn) {
		PdfPage*        page = pdf.GetPage(pn);

		get_glimpse(&pdf, page);

		// page->GetContents()->GetStream()->GetFilteredCopy(&pBuffer, &lLen);
		// actual << pBuffer;
		// free(pBuffer);

		str = extract(&pdf, page, removefont);
		// modified << str;

		page->GetContents()->GetStream()->Set(str.c_str());
		// cout << str.c_str();

		// actual.close();
		// modified.close();

		// system("diff -up actual.txt modified.txt | egrep '^\\+|^-' > diff.txt");
	}

	page->GetContents()->GetStream()->Set(process_glimps(removefont).c_str());

	pdf.Write(output.c_str());
	// cout << "Total Glimps: " << size;
	// cout << endl;
}

int main()
{
	std::setlocale(LC_ALL, "en_US.utf8"); // for C and C++ where synced with stdio
	std::locale::global(std::locale("en_US.utf8")); // for C++
	std::cout.imbue(std::locale());
	std::cout.imbue(std::locale(std::cout.getloc(), new std::numpunct<char>()));
	outdata.imbue(std::locale());

	setupFontLUT();

	system("mkdir -p finial");

	// convert("org/Skandamu01.pdf" , "finial/Skandamu01.pdf" , "F1" , 11, 0);
	convert("org/Skandamu02.pdf" , "finial/Skandamu02.pdf" , "R10", 1, 0);
 	// convert("org/Skandamu03.pdf" , "finial/Skandamu03.pdf" , "R10", 1, 0);
	// convert("org/Skandamu04.pdf" , "finial/Skandamu04.pdf" , "F3" , 1, 0);
	// convert("org/Skandamu05.pdf" , "finial/Skandamu05.pdf" , "R10", 1, 4);

	// convert("org/Skandamu06.pdf" , "finial/Skandamu06.pdf" , "R10", 1, 0);
	// convert("org/Skandamu07.pdf" , "finial/Skandamu07.pdf" , "R10", 1, 0);
	// convert("org/Skandamu08.pdf" , "finial/Skandamu08.pdf" , "R10", 1, 0);
	// convert("org/Skandamu09.pdf" , "finial/Skandamu09.pdf" , "R10", 1, 4);
	// convert("org/Skandamu10A.pdf", "finial/Skandamu10A.pdf", "F2" , 1, 0);

	// convert("org/Skandamu10B.pdf", "finial/Skandamu10B.pdf", "F2" , 1, 0);
	// convert("org/Skandamu10C.pdf", "finial/Skandamu10C.pdf", "F2" , 1, 0);
	// convert("org/Skandamu11A.pdf", "finial/Skandamu11A.pdf", "F3" , 1, 0);
	// convert("org/Skandamu11B.pdf", "finial/Skandamu11B.pdf", "F2" , 1, 0);
	// convert("org/Skandamu12.pdf" , "finial/Skandamu12.pdf" , "F3" , 1, 1);

	outdata.close();
	cout << endl;

	printMissing();
	printMissingCmds();

	return 0;
}
