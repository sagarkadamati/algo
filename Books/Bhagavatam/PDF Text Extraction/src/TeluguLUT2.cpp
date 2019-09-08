#include "TeluguDict.h"

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

static void setupAchulu(TeluguDict &lut) {
	lut.mapAchulu("అ", 0x6E); // 110 n
	lut.mapSkip("", 0xA1);
	lut.mapSkip("", 0xA3);
	lut.mapSkip("", 0xAF);
	lut.mapSkip("", 0xB7);
	lut.mapSkip("", 0xC9);
	lut.mapSkip("", 0xD1);
	lut.mapSkip("", 0xE4);
	lut.mapSkip("", 0xFC);
	lut.mapSkip("", 0x2211);

	lut.mapAchulu("ఆ", 0xC4); // 196 Ä
	lut.mapDeergalu("ా",  0xB1); // 177 ±
	lut.mapDeergalu("ా",  0xCA); // 202 Ê
	lut.mapDeergalu("ా",  0xD5); // 213 Õ
	lut.mapDeergalu("ా",  0xDC); // 220 Ü
	lut.mapDeergalu("ా",  0xEA); // 234 ê
	lut.mapDeergalu("ా",  0xEB); // 235 ë
	lut.mapDeergalu("ా",  0x2264);

	lut.mapAchulu("ఇ", 0xC7); // 199 Ç
	lut.mapDeergalu("ి", 0xE6); // 230 æ
	lut.mapDeergalu("ి", 0xE7); // 231 ç
	lut.mapDeergalu("ి", 0xCF); // 207 Ï

	lut.mapAchulu("ఈ", 0xE1); // 225 á
	lut.mapDeergalu("ీ", 0xB0); // 176 °
	lut.mapDeergalu("ీ", 0xFB); // 251 û
	lut.mapDeergalu("ీ", 0x201D);

	lut.mapAchulu("ఉ", 0xF1); // 241 ñ
	lut.mapDeergalu("ు", 0x54); //  84 T మ di u
	lut.mapDeergalu("ు", 0xDF); // 223 ß
	lut.mapDeergalu("ు", 0xEE); // 238 î
	lut.mapDeergalu("ు", 0xF3); // 243 ó
	lut.mapDeergalu("ు", 0x2044);

	lut.mapAchulu("ఊ", 0x7D); // 125 }
	lut.mapDeergalu("ూ", 0x4C); //  76 L
	lut.mapDeergalu("ూ", 0x4F); //  79 O // dough
	lut.mapDeergalu("ూ", 0x50); //  80 P
	lut.mapDeergalu("ూ", 0x53); //  83 S
	lut.mapDeergalu("ూ", 0xF7); // 247 ÷ // మ di dergam

	// lut.mapAchulu("ఋ", );
	lut.mapDeergalu("ృ", 0xE8); // 232 è
	// lut.mapAchulu("ఌ", );
	// lut.mapDeergalu("ౄ", );

	// lut.mapAchulu("ఎ", );
	lut.mapDeergalu("ె", 0xAC); // 172 ¬
	lut.mapDeergalu("ె", 0xCB); // 203 Ë
	lut.mapDeergalu("ె", 0xD3); // 211 Ó
	lut.mapDeergalu("ె", 0xF4); // 244 ô
	lut.mapDeergalu("ె", 0x2026);

	lut.mapAchulu("ఏ", 0x40); //  64 @
	lut.mapDeergalu("ే", 0xD2); // 210 Ò
	lut.mapDeergalu("ే", 0xF9); // 249 ù
	lut.mapDeergalu("ే", 0x03C0);
	lut.mapDeergalu("ే", 0x201A);
	lut.mapDeergalu("ే", 0x02DA);

	lut.mapAchulu("ఐ", 0x25CA);
	lut.mapDeergalu("ై", 0x2019); // is part of two chars
	lut.mapDeergalu("ై", 0x2206);

	lut.mapAchulu("ఒ", 0x02c7);
	lut.mapVothulu("ొ", 0x3D); //  61 =
	lut.mapVothulu("ొ", 0xA7); // 167 §
	lut.mapVothulu("ొ", 0x131);

	lut.mapAchulu("ఓ", 0x7A); // 122 z
	lut.mapDeergalu("ొ", 0xC0); // 192 À
	lut.mapDeergalu("ో", 0x02DB);
	lut.mapDeergalu("ో", 0x2218); // dough
	lut.mapDeergalu("ో", 0x221A);

	// lut.mapAchulu("ఔ", );
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
	lut.mapAchulu("క",  0xF8); // 248 ø
	lut.mapVothulu("్క", 0xFF); // 255 ÿ
	lut.mapAchulu("క",  0x2248);
	// lut.mapAchulu("్ర",  0x2248); dough

	lut.mapAchulu("ఖ", 0x4B); //  75 K
	lut.mapAchulu("ఖ", 0x55); //  85 U
	lut.mapVothulu("్ఖ",  0xE2); // 226	â

	lut.mapAchulu("గ",  0x3E); //  62 >
	lut.mapVothulu("్గ",  0x5A); //  90	Z

	// lut.mapAchulu("ఘ", );
	lut.mapVothulu("్ఘ", 0xC8); // 200 È

	// lut.mapAchulu("ఙ", );

	lut.mapAchulu("చ", 0x23); //  35 #
	lut.mapVothulu("్చ", 0xC3); // 195 Ã

	// lut.mapAchulu("ఛ", );
	lut.mapAchulu("జ", 0x43); //  67 C
	lut.mapVothulu("్జ",  0xAE); // 174 ®
	lut.mapAchulu("జ", 0xBB); // 187 »
	// lut.mapAchulu("ఝ", );
	// lut.mapAchulu("ఞ", );
	lut.mapVothulu("్ఞ", 0x201E);

	lut.mapAchulu("ట", 0x66); // 102 f
	lut.mapAchulu("ట", 0x7B); // 123 {
	lut.mapAchulu("ట", 0x2265);
	lut.mapVothulu("్ట",  0xBA); // 186 º

	// lut.mapAchulu("ఠ", );
	lut.mapVothulu("్ఠ", 0x02DC);

	lut.mapAchulu("డ", 0x26); //  38 &
	lut.mapVothulu("్డ",  0xB6); // 182 ¶

	// lut.mapAchulu("ఢ", );
	lut.mapAchulu("ణ", 0x44); //  68 D
	lut.mapVothulu("్ణ",  0xED); // 237 í

	lut.mapAchulu("త", 0x84); // 132 „
	lut.mapAchulu("త", 0x2018);
	lut.mapVothulu("్త",  0xD4); // 212 Ô

	// lut.mapAchulu("థ", );
	lut.mapVothulu("్థ",  0xFA); // 250 ú

	lut.mapAchulu("ద",  0x3C); //  60 <
	lut.mapVothulu("్ద", 0x203A);

	// lut.mapAchulu("ధ", );
	lut.mapVothulu("్ధ", 0x0394);

	lut.mapAchulu("న", 0x48); //  72 H
	lut.mapAchulu("న", 0x71); // 113 q
	lut.mapVothulu("్న", 0xEF); // 239 ï

	lut.mapAchulu("వ", 0x6D); // 109 m
	lut.mapAchulu("ప", 0x7C); // 124 |
	lut.mapAchulu("ప", 0x62); //  98 b ఎ
	lut.mapVothulu("్ప", 0x0152);

	// lut.mapAchulu("ఫ", );
	lut.mapAchulu("బ", 0x75); // 117 u
	lut.mapAchulu("బ", 0xE3); // 227 ã
	lut.mapVothulu("్బ", 0x201C);
	// lut.mapAchulu("భ", );
	// lut.mapAchulu("మ", );
	lut.mapVothulu("్మ", 0xE0); // 224 à

	lut.mapAchulu("య", 0x6A); // 106 j
	lut.mapVothulu("్య",  0xB4); // 180 ´

	lut.mapAchulu("ర", 0x73); // 115 s
	lut.mapVothulu("్ర", 0xC5); // 197 Å

	// lut.mapAchulu("ఱ", );
	lut.mapAchulu("ల", 0x5C); //  92 \ (for comments)
	lut.mapAchulu("ల", 0x2DD);
	lut.mapVothulu("్ల",  0xA2); // 162	¢

	lut.mapAchulu("ళ",  0x5B); //  91 [ // dough
	lut.mapAchulu("ళ",  0xFB01);

	// lut.mapAchulu("ఴ", );
	lut.mapAchulu("వ", 0x65); // 101 e
	lut.mapAchulu("వ", 0x79); // 121 y
	lut.mapVothulu("్వ", 0xAB); // 171  «

	lut.mapAchulu("శ",  0x58); //  88 X
	lut.mapVothulu("్శ", 0xD9); // 217  Ù

	lut.mapAchulu("ష", 0x63); //  99 c
	lut.mapAchulu("ష", 0xB8); // 184  ¸
	lut.mapAchulu("ష", 0x77); // 119 w
	lut.mapVothulu("్ష",  0xE5); // 229 å

	lut.mapAchulu("స", 0x64); // 100 d
	lut.mapAchulu("స", 0x6B); // 107 k
	lut.mapVothulu("్స", 0x2021);

	lut.mapAchulu("హ", 0x56); //  86 V
	lut.mapVothulu("్హ", 0x03A9);
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
	lut.mapSkip(".", 0xDB); // 219 Û
	lut.mapSpecial(".", 0xF2); // 242 ò
	lut.mapSpecial(".", 0x192);
	lut.mapSpecial("|", 0x02C6);
	lut.mapSpecial(":", 0x220F);
	lut.mapSpecial(",", 0x3BC);
	// lut.mapAchulu("", 0xAA); // 170 ª opposit to comma

	setupAchulu(lut);
	setupHallulu(lut);
	setupVothulu(lut);
	setupAksharamlu(lut);
}

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
