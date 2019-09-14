#include "MyPDF.h"

extern map<unsigned short, string> AllChar;
map<unsigned short, string> AllChar;

void MyPDF::printMissingChar() {
	cout << endl << endl << "=== MissingChar (" << dec << MissingChar.size() << ") ===";
	for(map<unsigned int, int>::iterator c = MissingChar.begin(); c != MissingChar.end(); c++) {
		cout << endl << " New: ";
		cout << setw(8) << dec << c->first;
		cout << setw(8) << hex << c->first;
		cout << setw(20) << bitset<16>(c->first);
	}
	cout << endl;
}

void MyPDF::printMissingCmds() {
	cout << endl << endl << "=== MissingChar CMDS (" << dec << MissingCmds.size() << ") ===";
	for(map<string, string>::iterator c = MissingCmds.begin(); c != MissingCmds.end(); c++) {
		cout << endl << " CMD: " << c->first;
	}
	cout << endl;
}

void MyPDF::printMissing() {
	printMissingChar();
	printMissingCmds();
}

void MyPDF::ReplaceStringInPlace(std::string& subject, const std::string& search,
						const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

std::string MyPDF::extract(int pn)
{
	const char*      pszToken = NULL;
	PdfVariant       var;
	EPdfContentsType eType;

	double cur_fontSize		= 0.0;
	double cur_x            = 0.0;
	double cur_y            = 0.0;

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

	bool debug = false;
	bool record = true;
	int count = 0;

	bool   bTextBlock   = false;
	PdfObject* pFont;
	PdfFont* pCurFont   = NULL;

	std::stack<PdfVariant> stack;

	PdfPage* pPage = PDF.GetPage(pn);
	PdfContentsTokenizer tokenizer( pPage );

	while( tokenizer.ReadNext( eType, pszToken, var ) )
	{
		if( eType == ePdfContentsType_Keyword )
		{
			if( strcmp( pszToken, "BT" ) == 0 || strcmp( pszToken, "ET" ) == 0 ) {
				// Text object operators

				if( strcmp( pszToken, "BT" ) == 0 ) {

					bTextBlock   = true;
					if(record) { }

				} else if( strcmp( pszToken, "ET" ) == 0 ) {
					if(record) {
						outdata << endl;
					}
				}

			} else if( strcmp( pszToken, "Tc" ) == 0 || strcmp( pszToken, "Tw" ) == 0 ||
					strcmp( pszToken, "Tz" ) == 0 || strcmp( pszToken, "TL" ) == 0 ||
					strcmp( pszToken, "Tr" ) == 0 || strcmp( pszToken, "Ts" ) == 0 ||
					strcmp( pszToken, "Tf" ) == 0 ) {
					// Text state operators

				if( strcmp( pszToken, "Tf" ) == 0 ) {
					double fontSize;
					if (cur_x !=0 && cur_y != 0)
						outdata << endl;

					size = stack.top().GetReal(); stack.pop();
					PdfName fontName = stack.top().GetName(); stack.pop();

					pFont = pPage->GetFromResources( PdfName("Font"), fontName );
					pCurFont = PDF.GetFont( pFont );
					fontSize = pCurFont->GetFontSize();

					if (cur_fontSize != fontSize)
						outdata << endl;
					cur_fontSize = fontSize;

					// cout << fontName.GetName() << endl;
					if(fontName.GetName().compare( skipFont ) == 0)
						record = false;
					else {
						record = true;
					}
				} else if (strcmp( pszToken, "Tz" ) == 0 ) {
					g = stack.top().GetReal(); stack.pop();
				} else {
					td_y = stack.top().GetReal(); stack.pop();
				}

			} else if( strcmp( pszToken, "Td" ) == 0 || strcmp( pszToken, "TD" ) == 0 ||
					strcmp( pszToken, "Tm" ) == 0 || strcmp( pszToken, "T*" ) == 0 ) {
				// Text positioning operators

				if( strcmp( pszToken, "TD" ) == 0 || strcmp( pszToken, "Td" ) == 0) {
					// TD - move to x, y
					// Td - move to x, y

					y = cur_y + stack.top().GetReal(); stack.pop();
					x = cur_x + stack.top().GetReal(); stack.pop();

				} else if( strcmp( pszToken, "Tm" ) == 0 ) {

					offset_y = stack.top().GetReal(); stack.pop();
					offset_x = stack.top().GetReal(); stack.pop();
					scale_y  = stack.top().GetReal(); stack.pop();
					shear_y  = stack.top().GetReal(); stack.pop();
					shear_x  = stack.top().GetReal(); stack.pop();
					scale_x  = stack.top().GetReal(); stack.pop();

					x = cur_x + offset_x;
					y = cur_y + offset_y;
				} else if ( strcmp( pszToken, "T*" ) == 0 ) {
					// T* - New line
					// outdata << endl;

					y = cur_y - pCurFont->GetFontMetrics()->GetLineSpacing();
				}

				if (cur_x !=0 && cur_y != 0)
					if (abs(cur_y - y) > pCurFont->GetFontMetrics()->GetLineSpacing()) {
						outdata << endl << endl;
					} else {
							// outdata << endl;
					}

				cur_x = x;
				cur_y = y;
				// outdata << endl;
			} else if( strcmp( pszToken, "Tj" ) == 0 || strcmp( pszToken, "'" ) == 0 ||
					strcmp( pszToken, "\"" ) == 0 || strcmp( pszToken, "TJ" ) == 0 ) {
				// Text showing operators

				if( strcmp( pszToken, "TJ" ) == 0 ) {
					PdfArray array = stack.top().GetArray(); stack.pop();
					// outdata << endl;
					for( int i=0; i<static_cast<int>(array.GetSize()); i++ )
					{
						if( array[i].IsString() || array[i].IsHexString() ) {
							PdfString pStr = array[i].GetString();
							if (pStr.IsUnicode()) {
								pStr = pCurFont->GetEncoding()->ConvertToUnicode(pStr, pCurFont);
								// pdfstr = pStr.ToUnicode();
							}
							string text = pStr.GetStringUtf8();
							teluguText.set(text);

							outdata << teluguText << " ";
							if (debug)
								outdata << endl << x << ", " << y << teluguText.details() << endl;
						} else if( array[i].IsNumber() ) {
							// long long n = stack.top().GetNumber(); stack.pop();
						} else if( array[i].IsReal() ) {
							double r = stack.top().GetReal(); stack.pop();
						} else {
							cout << "TJ - New Type detected in page " << pn << endl;
						}
					}
				} else {
					// "  - Use Character and word spacing (TC and TW), and then ' operator
					// '  - move to new line, and then Tj operator
					// Tj - print text at current co-ordinates
					// if(record) {
						PdfString pStr = stack.top().GetString(); stack.pop();
						if (pStr.IsUnicode()) {
							// pStr = pStr.ToUnicode();
							pStr = pCurFont->GetEncoding()->ConvertToUnicode(pStr, pCurFont);
						}
						string text = pStr.GetStringUtf8();
						teluguText.set(text);

						if (strcmp( pszToken, "'" ) == 0 || strcmp( pszToken, "\"" ) == 0) {
							if (strcmp( pszToken, "\"" ) == 0) {
								double tc_c = stack.top().GetReal(); stack.pop();
								double tc_w = stack.top().GetReal(); stack.pop();
							}
							// outdata << endl;
						} else {
							if ( strcmp( pszToken, "Tj" ) != 0 )
								cout << "Tj - New Type detected in page " << pn << endl;
						}

						// Handle TJ or ' or " here
						outdata << teluguText << " ";
						if (debug)
							outdata << endl << x << ", " << y << teluguText.details() << endl;
					// }
				}

			} else if( strcmp( pszToken, "cm" ) == 0 || strcmp( pszToken, "gs" ) == 0 ||
					strcmp( pszToken, "w" ) == 0 || strcmp( pszToken, "i" ) == 0 ||
					strcmp( pszToken, "q" ) == 0 ||	strcmp( pszToken, "Q" ) == 0 ) {
				// Graphics state operators

				if( strcmp( pszToken, "cm" ) == 0 )	{
					offset_y = stack.top().GetReal(); stack.pop();
					offset_x = stack.top().GetReal(); stack.pop();
					scale_y  = stack.top().GetReal(); stack.pop();
					shear_y  = stack.top().GetReal(); stack.pop();
					shear_x  = stack.top().GetReal(); stack.pop();
					scale_x  = stack.top().GetReal(); stack.pop();
				} else if ( strcmp( pszToken, "i" ) == 0 ) {

				} else if( strcmp( pszToken, "gs" ) == 0 ) {

				} else if ( strcmp( pszToken, "w" ) == 0 ) {

					g = stack.top().GetReal(); stack.pop();
				} 

			} else if( strcmp( pszToken, "CS" ) == 0 || strcmp( pszToken, "cs" ) == 0  ||
				strcmp( pszToken, "SC" ) == 0 || strcmp( pszToken, "SCN" ) == 0 ||
				strcmp( pszToken, "sc" ) == 0 || strcmp( pszToken, "scn" ) == 0 ||
				strcmp( pszToken, "G" ) == 0  || strcmp( pszToken, "g" ) == 0   ||
				strcmp( pszToken, "RG" ) == 0 || strcmp( pszToken, "rg" ) == 0  ||
				strcmp( pszToken, "K" ) == 0  || strcmp( pszToken, "k" ) == 0 ) {
				// Color Space operators
	
				if ( strcmp( pszToken, "cs" ) == 0 ) {

				} else if ( strcmp( pszToken, "scn" ) == 0 ) {

				} else if ( strcmp( pszToken, "g" ) == 0 || strcmp( pszToken, "G" ) == 0 ) {

				} else if ( strcmp( pszToken, "rg" ) == 0 || strcmp( pszToken, "RG" ) == 0 ) {

					blue = stack.top().GetReal(); stack.pop();
					green = stack.top().GetReal(); stack.pop();
					red = stack.top().GetReal(); stack.pop();

					red = 0.396;   // 0.0 for black
					green = 0.482; // 0.0 for black
					blue = 0.514;  // 0.0 for black
				}

			} else if ( strcmp( pszToken, "re" ) == 0 || strcmp( pszToken, "W" ) == 0 ||
					strcmp( pszToken, "l" ) == 0 || strcmp( pszToken, "m" ) == 0 ||
					strcmp( pszToken, "n" ) == 0 ) {
				// Path operators

				if( strcmp( pszToken, "re" ) == 0 ) {

					offset_y = stack.top().GetReal(); stack.pop();
					offset_x = stack.top().GetReal(); stack.pop();
					scale_y  = stack.top().GetReal(); stack.pop();
					shear_y  = stack.top().GetReal(); stack.pop();

				} else if ( strcmp( pszToken, "W" ) == 0 ||
					strcmp( pszToken, "n" ) == 0 ) {

				} else if( strcmp( pszToken, "l" ) == 0 || strcmp( pszToken, "m" ) == 0 ) {
					// support 'l' and 'm' tokens
					x = stack.top().GetReal(); stack.pop();
					y = stack.top().GetReal(); stack.pop();

					if (cur_x !=0 && cur_y != 0)
						if (abs(cur_y - y) > pCurFont->GetFontMetrics()->GetLineSpacing()) {
							outdata << endl << endl;
						} else {
								outdata << endl;
						}

					cur_x = x;
					cur_y = y;
				}

			} else {
				MissingCmds[pszToken] = pszToken;
			}
		} else if ( eType == ePdfContentsType_Variant ) {
			stack.push( var );
		} else {
			cout << endl << "Unknown variant" << endl;
		}
	}

	return "";
}

void MyPDF::saveAs(string output)
{
	PDF.Write(output.c_str());
}

void MyPDF::deletePages (int del_start, int del_end) {
	if(del_start)
		PDF.DeletePages(0, del_start);

	if(del_end)
		PDF.DeletePages(pc - del_end - 1, del_end);

	pc = PDF.GetPageCount();
}

void MyPDF::removeFont(string rFont) {
	skipFont = rFont;
}

void MyPDF::extractTo(string outText) {
	outdata.open(outText.c_str());
	outdata.imbue(std::locale());

	for (int pn = 0; pn < pc; ++pn) {
		extract(pn);
		// outdata << endl;
	}
	pc = PDF.GetPageCount();

	outdata.close();
}

void MyPDF::genMap(string outMap) {
	cout << "Generating map" << endl;
	for (int pn = 0; pn < pc - 1; ++pn) {
		PDF.DeletePages(0, 1);
	}
	pc = PDF.GetPageCount();

	// PdfObject* fontObject =  PDF.GetPage(0)->GetFromResources( PdfName("Font"), PdfName("R7") );
	PdfObject* fontObject =  PDF.GetPage(0)->GetFromResources( PdfName("Font"), PdfName("F1") );
	PdfFont* telugu = PDF.GetFont( fontObject );
    telugu->SetFontSize( 32.0 );

    PdfFont* english = PDF.CreateFont( "Arial" );
    english->SetFontSize( 32.0 );

	// noto sans telugu regular
    PdfFont* teluguNoto = PDF.CreateFont( "Noto Sans Telugu", false, false, new PdfIdentityEncoding( 0, 0xffff, true ));
    teluguNoto->SetFontSize( 32.0 );

	PDF.DeletePages(0, 1);
	PdfPage* page = PDF.CreatePage( PdfPage::CreateStandardPageSize( ePdfPageSize_A4 ) );
    if( !page ) {
		cout << "Error creating page" << endl;
        PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
    }

    PdfPainter painter;
	painter.SetPage( page );

	int x = 60;
	int y = page->GetPageSize().GetHeight() - 60;
	for(map<unsigned short, string >::iterator c = AllChar.begin(); c != AllChar.end(); c++) {
		if (y <= 20) {
			page = PDF.CreatePage( PdfPage::CreateStandardPageSize( ePdfPageSize_A4 ) );
			if( !page ) {
				cout << "Error creating page" << endl;
				PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
			}
			y = page->GetPageSize().GetHeight() - 60;
			painter.SetPage( page );
		}

		PdfString pdfStr = PdfString(reinterpret_cast<const pdf_utf8*>(c->second.c_str()));
		painter.SetFont( telugu );
		painter.DrawText( x, y, pdfStr );

		painter.SetFont( english );
		painter.DrawText( x + 40, y, PdfString(string(strmake() << " -> " << hex << c->first)) );

		if (x == 60) {
			x = 350;
		} else {
			x = 60;
			y -= painter.GetFont()->GetFontMetrics()->GetLineSpacing();
			y -= painter.GetFont()->GetFontMetrics()->GetLineSpacing();
		}
	}

    painter.FinishPage();
	PDF.Write(outMap.c_str());
}

MyPDF::MyPDF(string input) {
	PDF.Load(input.c_str());
	pc = PDF.GetPageCount();

	PdfError::EnableDebug( false );
}

MyPDF::~MyPDF() {
	outdata.close();
	cout << endl;
}