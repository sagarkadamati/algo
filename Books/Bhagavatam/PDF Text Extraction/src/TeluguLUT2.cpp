#include "TeluguDict.h"

// అచ్చులు
// 	అ	ఆ	ఇ	ఈ	ఉ	ఊ
// 	ఋ	ౠ	ఌ	ౡ
// 	ఎ	ఏ	ఐ
// 	ఒ	ఓ	ఔ
// ఉభయాక్షరమలు
// 	ఁ	ం	ః

// హల్లులు
// 	క	ఖ	గ	ఘ	ఙ
// 	చ	ఛ	జ	ఝ	ఞ
// 	ట	ఠ	డ	ఢ	ణ
// 	త	థ	ద	ధ	న
// 	ప	ఫ	బ	భ	మ
// 	య	ర	ల	వ
// 	శ	ష	స	హ
// 	ళ	ఱ		క్ష
// 	ౘ	ౙ
// చిహ్నములు
// 	ఽ

static void setupAksharamlu(TeluguDict &lut) {
	// Fixed Aksharamlu
	lut.mapAksharam("వి", 0x24); //  36  $
	lut.mapAksharam("వీ", 0x4D); //  77  M
	lut.mapAksharam("రి", 0x5D); //  93  ]
	lut.mapAksharam("శ్రీ", 0x6C); // 108	l
	lut.mapAksharam("జూ", 0x70); // 112  p
	lut.mapAksharam("తీ", 0x72); // 114  r
	lut.mapAksharam("తీ", 0x2039);
	lut.mapAksharam("ని", 0xEC); // 236  ì
	lut.mapAksharam("జి", 0xF5); // 245  õ
	// lut.mapAksharam("", 0x2030); dough
	lut.mapAksharam("నీ", 0x02D9);
	lut.mapAksharam("రీ", 0xD8); // 216  Ø
	lut.mapAksharam("చి", 0x222B);
	lut.mapAksharam("గి", 0x2013);
	lut.mapAksharam("లి",  0x2A); //  42 *
	lut.mapAksharam("బీ", 0x3b); //  59 ;
	lut.mapAksharam("ాూ", 0x41); //  65  A dough
	lut.mapAksharam("దీ", 0x42); //  66 B
	lut.mapAksharam("జు", 0x45); //  69 E
	lut.mapAksharam("జీ", 0x4A); //  74 J
	lut.mapAksharam("చీ", 0x4E); //  78 N
	lut.mapAksharam("ాు", 0x51); //  81 Q dough
	// 5b alla
	lut.mapAksharam("గీ", 0x5E); //  94 ^
	lut.mapAksharam("బి", 0x5F); //  95 _

	lut.mapAksharam("శి", 0x2022);
	// lut.mapAksharam("", 0x2022);
	lut.mapAksharam("ది", 0x7E); // 126  ~
	lut.mapAksharam("ళీ", 0x221E);

	// == Numbers ==
	// lut.mapAchulu("౦", "");
	// lut.mapAchulu("౧", "");
	// lut.mapAchulu("౨", "");
	// lut.mapAchulu("౩", "");
	// lut.mapAchulu("౪", "");
	// lut.mapAchulu("౫", "");
	// lut.mapAchulu("౬", "");
	// lut.mapAchulu("౭", "");
	// lut.mapAchulu("౮", "");
	// lut.mapAchulu("౯", "");

	// == Teledu ==
	// lut.mapAchulu("౸", );
	// lut.mapAchulu("౹", );
	// lut.mapAchulu("౺", );
	// lut.mapAchulu("౻", );
	// lut.mapAchulu("౼", );
	// lut.mapAchulu("౽", );
	// lut.mapAchulu("౾", );
	// lut.mapAchulu("౿", );

	// == Vothulu ==
	// lut.mapAksharam("ౘ", );
	// lut.mapAksharam("ౙ", );
	// lut.mapAksharam("ౠ", );
	// lut.mapAksharam("ౡ", );
}

#define A(x, y) lut.mapAchulu(x, y)
#define S(x, y) lut.mapSarga(x, y)
#define H(x, y) lut.mapAchulu(x, y)

static void setupTeluguVarnamala(TeluguDict &lut) {
	// అచ్చులు
    A("అ",  0x006E);    A("ఆ",   0x00C4);    A("ఇ", 0x00C7);    A("ఈ", 0x00E1);    A("ఉ", 0x00F1);    A("ఊ", 0x007D);
    A("ఋ", 0x0000);    A("ౠ", 0x0000);    A("ఌ", 0x0000);    A("ౡ", 0x0000);
    A("ఎ",  0x0000);    A("ఏ",   0x0040);    A("ఐ", 0x25CA);
    A("ఒ",  0x02c7);    A("ఓ",   0x007A);    A("ఔ", 0x0000);

    // ఉభయాక్షరమలు
    S("ఁ", 0x0000);    S("ం",  0x002B);    S("ః", 0x0000);

    // హల్లులు
    H("క",  0x2248);    H("ఖ", 0x0055);    H("గ",  0x003E);    H("ఘ", 0x0000);    H("ఙ", 0x0000);
    H("చ", 0x0023);    H("ఛ", 0x0000);    H("జ", 0x0043);    H("ఝ", 0x0000);    H("ఞ", 0x0000);
    H("ట", 0x0066);    H("ఠ", 0x0000);    H("డ", 0x0026);    H("ఢ", 0x0000);    H("ణ", 0x0044);
    H("త", 0x0084);    H("థ", 0x0000);    H("ద", 0x003C);    H("ధ", 0x0000);    H("న", 0x0048);
    H("ప", 0x007C);    H("ఫ", 0x0000);    H("బ", 0x0075);    H("భ", 0x0000);    H("మ", 0x0000);

	H("య", 0x006A);    H("ర", 0x0073);    H("ల", 0x005C);    H("వ", 0x0065);
	H("శ",  0x0058);    H("ష", 0x0063);    H("స", 0x0064);    H("హ", 0x0056);
	H("ళ",  0x005B);    H("ఱ", 0x0000);                       H("క్ష", 0x0000);
	H("ౘ", 0x0000);    H("ౙ", 0x0000);

	// చిహ్నములు
	H("ఽ", 0x0000);
}

static void setupAchulu(TeluguDict &lut) {
	A("అ", 0x6E);	A("ఆ", 0xC4);	A("ఇ", 0xC7);	A("ఈ", 0xE1);	A("ఉ", 0xF1);	A("ఊ", 0x7D);
	A("ఋ", 0); A("ఎ", 0);		A("ఏ", 0x40);	A("ఐ", 0x25CA);	A("ఒ", 0x02c7);	A("ఓ", 0x7A);	A("ఔ", 0);

	lut.mapSkip("", 0xA1);
	lut.mapSkip("", 0xA3);
	lut.mapSkip("", 0xAF);
	lut.mapSkip("", 0xB7);
	lut.mapSkip("", 0xC9);
	lut.mapSkip("", 0xD1);
	lut.mapSkip("", 0xE4);
	lut.mapSkip("", 0xFC);
	lut.mapSkip("", 0x2211);

	lut.mapDeergalu("ా",  0xB1); // 177 ±
	lut.mapDeergalu("ా",  0xCA); // 202 Ê
	lut.mapDeergalu("ా",  0xD5); // 213 Õ
	lut.mapDeergalu("ా",  0xDC); // 220 Ü
	lut.mapDeergalu("ా",  0xEA); // 234 ê
	lut.mapDeergalu("ా",  0xEB); // 235 ë
	lut.mapDeergalu("ా",  0x2264);

	lut.mapDeergalu("ి", 0xE6); // 230 æ
	lut.mapDeergalu("ి", 0xE7); // 231 ç
	lut.mapDeergalu("ి", 0xCF); // 207 Ï

	lut.mapDeergalu("ీ", 0xB0); // 176 °
	lut.mapDeergalu("ీ", 0xFB); // 251 û
	lut.mapDeergalu("ీ", 0x201D);

	lut.mapDeergalu("ు", 0x54); //  84 T మ di u
	lut.mapDeergalu("ు", 0xDF); // 223 ß
	lut.mapDeergalu("ు", 0xEE); // 238 î
	lut.mapDeergalu("ు", 0xF3); // 243 ó
	lut.mapDeergalu("ు", 0x2044);

	lut.mapDeergalu("ూ", 0x4C); //  76 L
	lut.mapDeergalu("ూ", 0x4F); //  79 O // dough
	lut.mapDeergalu("ూ", 0x50); //  80 P
	lut.mapDeergalu("ూ", 0x53); //  83 S
	lut.mapDeergalu("ూ", 0xF7); // 247 ÷ // మ di dergam

	lut.mapDeergalu("ృ", 0xE8); // 232 è
	// lut.mapAchulu("ఌ", );
	// lut.mapDeergalu("ౄ", );

	lut.mapDeergalu("ె", 0xAC); // 172 ¬
	lut.mapDeergalu("ె", 0xCB); // 203 Ë
	lut.mapDeergalu("ె", 0xD3); // 211 Ó
	lut.mapDeergalu("ె", 0xF4); // 244 ô
	lut.mapDeergalu("ె", 0x2026);

	lut.mapDeergalu("ే", 0xD2); // 210 Ò
	lut.mapDeergalu("ే", 0xF9); // 249 ù
	lut.mapDeergalu("ే", 0x03C0);
	lut.mapDeergalu("ే", 0x201A);
	lut.mapDeergalu("ే", 0x02DA);

	lut.mapDeergalu("ై", 0x2019); // is part of two chars
	lut.mapDeergalu("ై", 0x2206);

	lut.mapVothulu("ొ", 0x3D); //  61 =
	lut.mapVothulu("ొ", 0xA7); // 167 §
	lut.mapVothulu("ొ", 0x131);

	lut.mapDeergalu("ొ", 0xC0); // 192 À
	lut.mapDeergalu("ో", 0x02DB);
	lut.mapDeergalu("ో", 0x2218); // dough
	lut.mapDeergalu("ో", 0x221A);

	lut.mapDeergalu("ౌ",  0xC2); // 194 Â
	lut.mapDeergalu("ౌ",  0xD6); // 214 Ö
	lut.mapDeergalu("ౌ",  0xDA); // 218 Ú
	lut.mapDeergalu("ౌ",  0xF6); // 246 ö

	// lut.mapDeergalu("ౕ", );
	// lut.mapDeergalu("ౖ", );

	// lut.mapDeergalu("ౢ", );
	// lut.mapDeergalu("ౣ", );

	//  skip ్
	lut.mapDeergalu("్", 0x59); //  89 Y
	lut.mapDeergalu("్", 0x74); // 116 t
	lut.mapDeergalu("్", 0xE9); // 233 é
	lut.mapDeergalu("్", 0x0178);
	lut.mapDeergalu("్", 0x02D8);

	lut.mapSarga("ం",  0x2B); //  43 +
	// lut.mapDeergalu("ః", );
	// lut.mapDeergalu("ఁ", );
	// lut.mapDeergalu("ఀ", );
}

static void setupHallulu(TeluguDict &lut) {
	lut.mapAchulu("క",  0x2248);
	lut.mapAchulu("ఖ", 0x55); //  85 U
	lut.mapAchulu("గ",  0x3E); //  62 >
	// lut.mapAchulu("ఘ", );
	// lut.mapAchulu("ఙ", );

	lut.mapAchulu("చ", 0x23); //  35 #
	// lut.mapAchulu("ఛ", );
	lut.mapAchulu("జ", 0x43); //  67 C
	// lut.mapAchulu("ఝ", );
	// lut.mapAchulu("ఞ", );

	lut.mapAchulu("ట", 0x66); // 102 f
	// lut.mapAchulu("ఠ", );
	lut.mapAchulu("డ", 0x26); //  38 &
	// lut.mapAchulu("ఢ", );
	lut.mapAchulu("ణ", 0x44); //  68 D

	lut.mapAchulu("త", 0x84); // 132 „
	// lut.mapAchulu("థ", );
	lut.mapAchulu("ద",  0x3C); //  60 <
	// lut.mapAchulu("ధ", );
	lut.mapAchulu("న", 0x48); //  72 H

	lut.mapAchulu("ప", 0x7C); // 124 |
	// lut.mapAchulu("ఫ", );
	lut.mapAchulu("బ", 0x75); // 117 u
	// lut.mapAchulu("భ", );
	// lut.mapAchulu("మ", );

	lut.mapAchulu("య", 0x6A); // 106 j
	lut.mapAchulu("ర", 0x73); // 115 s
	// lut.mapAchulu("ఱ", );
	lut.mapAchulu("ల", 0x5C); //  92 \ (for comments)
	// lut.mapAchulu("ఴ", );
	lut.mapAchulu("ళ",  0x5B); //  91 [ // dough
	lut.mapAchulu("వ", 0x65); // 101 e
	lut.mapAchulu("శ",  0x58); //  88 X
	lut.mapAchulu("ష", 0x63); //  99 c
	lut.mapAchulu("స", 0x64); // 100 d
	lut.mapAchulu("హ", 0x56); //  86 V

	lut.mapAchulu("క",  0xF8); // 248 ø
	lut.mapAchulu("ఖ", 0x4B); //  75 K

	lut.mapVothulu("్క", 0xFF); // 255 ÿ
	lut.mapVothulu("్ఖ",  0xE2); // 226	â
	lut.mapVothulu("్గ",  0x5A); //  90	Z
	lut.mapVothulu("్ఘ", 0xC8); // 200 È
	// lut.mapAchulu("్ర",  0x2248); dough

	lut.mapVothulu("్చ", 0xC3); // 195 Ã

	lut.mapVothulu("్జ",  0xAE); // 174 ®
	lut.mapAchulu("జ", 0xBB); // 187 »
	lut.mapVothulu("్ఞ", 0x201E);

	lut.mapAchulu("ట", 0x7B); // 123 {
	lut.mapAchulu("ట", 0x2265);
	lut.mapVothulu("్ట",  0xBA); // 186 º

	lut.mapVothulu("్ఠ", 0x02DC);

	lut.mapVothulu("్డ",  0xB6); // 182 ¶

	lut.mapVothulu("్ణ",  0xED); // 237 í

	lut.mapAchulu("త", 0x2018);
	lut.mapVothulu("్త",  0xD4); // 212 Ô

	lut.mapVothulu("్థ",  0xFA); // 250 ú

	lut.mapVothulu("్ద", 0x203A);

	lut.mapVothulu("్ధ", 0x0394);

	lut.mapAchulu("న", 0x71); // 113 q
	lut.mapVothulu("్న", 0xEF); // 239 ï

	lut.mapAchulu("వ", 0x6D); // 109 m
	lut.mapAchulu("ప", 0x62); //  98 b ఎ
	lut.mapVothulu("్ప", 0x0152);

	lut.mapAchulu("బ", 0xE3); // 227 ã
	lut.mapVothulu("్బ", 0x201C);
	lut.mapVothulu("్మ", 0xE0); // 224 à

	lut.mapVothulu("్య",  0xB4); // 180 ´

	lut.mapVothulu("్ర", 0xC5); // 197 Å

	lut.mapAchulu("ల", 0x2DD);
	lut.mapVothulu("్ల",  0xA2); // 162	¢

	lut.mapAchulu("ళ",  0xFB01);

	lut.mapAchulu("వ", 0x79); // 121 y
	lut.mapVothulu("్వ", 0xAB); // 171  «

	lut.mapVothulu("్శ", 0xD9); // 217  Ù

	lut.mapAchulu("ష", 0xB8); // 184  ¸
	lut.mapAchulu("ష", 0x77); // 119 w
	lut.mapVothulu("్ష",  0xE5); // 229 å

	lut.mapAchulu("స", 0x6B); // 107 k
	lut.mapVothulu("్స", 0x2021);

	lut.mapVothulu("్హ", 0x03A9);

	// convert to vothu
	lut.mapVothulu(".", 0xDB); // 219 Û
}

static void setupVothulu(TeluguDict &lut) {
	// lut.mapVothulu("ఽ", );

	// == Extra ==

	// Ignore ticks
}

void setupFontLUT(TeluguDict &lut) {
	lut.clear();

	lut.mapSpecial(" ", 0x20); //  32 <space>
	lut.mapSpecial(" ", 0x7F); // 127 <space>
	lut.mapSpecial(" ", 0xA0); // 160 <space>
	lut.mapSpecial("!", 0x21); //  33 !
	lut.mapSpecial(",", 0x2C); //  44 ,
	lut.mapSpecial(".", 0x2E); //  46 .
	lut.mapSpecial("(", 0x28); //  40 (
	lut.mapSpecial(")", 0x29); //  41 )
	lut.mapSpecial("0", 0x30); //  48 0
	lut.mapSpecial("1", 0x31); //  49 1
	lut.mapSpecial("2", 0x32); //  50 2
	lut.mapSpecial("3", 0x33); //  51 3
	lut.mapSpecial("4", 0x34); //  52 4
	lut.mapSpecial("5", 0x35); //  53 5
	lut.mapSpecial("6", 0x36); //  54 6
	lut.mapSpecial("7", 0x37); //  55 7
	lut.mapSpecial("8", 0x38); //  56 8
	lut.mapSpecial("9", 0x39); //  57 9
	lut.mapSpecial(":", 0x3A); //  58 :
	lut.mapSpecial("?", 0x3F); //  63 ?
	lut.mapSpecial("-", 0x60); //  96 `
	lut.mapSpecial(".", 0xA4); // 164 ¤
	lut.mapSpecial(".", 0xF2); // 242 ò
	lut.mapSpecial(".", 0x192);
	lut.mapSpecial("|", 0x02C6);
	lut.mapSpecial(":", 0x220F);
	lut.mapSpecial(",", 0x3BC);

	setupAchulu(lut);
	setupHallulu(lut);
	setupVothulu(lut);
	setupAksharamlu(lut);
}