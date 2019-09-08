#include "MyPDF.h"

#include <cwchar>

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

	PdfPage* pPage = PDF.GetPage(pn);
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
				// cout << fontName.GetName() << endl;
				pFont = pPage->GetFromResources( PdfName("Font"), fontName );
				pCurFont = PDF.GetFont( pFont );

				if(fontName.GetName().compare( skipFont ) == 0)
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
					teluguText.set(text);

					// cout << endl;
					outdata << teluguText << endl;
					// outdata << teluguText.details() << endl << endl;
					
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
						teluguText.set(text);

						// cout << endl;
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

void MyPDF::saveAs(string output)
{
	string   str;
	pdf_long lLen;

	PdfPage*       page = PDF.GetPage(1);
	PdfObject*     resources = page->GetResources();
	PdfRect        mediabox = page->GetMediaBox();
	// PdfObject*     contents = page->GetContents();
	// PdfStream*     stream = contents->GetStream();

	pc = 3;
	for (int pn = 2; pn < pc; ++pn) {
		// PdfPage*        page = PDF.GetPage(pn);
		// char*    pBuffer;

		// get_glimpse(&pdf, page);

		// page->GetContents()->GetStream()->GetFilteredCopy(&pBuffer, &lLen);
		// actual << pBuffer;
		// free(pBuffer);

		// str = extract(pn);
		// page->GetContents()->GetStream()->Set(str.c_str());

		// modified << str;
		// cout << str.c_str();

		// system("diff -up actual.txt modified.txt | egrep '^\\+|^-' > diff.txt");
	}

	// page->GetContents()->GetStream()->Set(process_glimps(skipFont).c_str());

	PDF.Write(output.c_str());
	// cout << "Total Glimps: " << size;
	// cout << endl;
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

	// pc = 3;
	for (int pn = 0; pn < pc; ++pn) {
		extract(pn);
	}
	pc = PDF.GetPageCount();

	outdata.close();
}

// void HelloWorld( const char* pszFilename ) 
// {
//     /*
//      * PdfStreamedDocument is the class that can actually write a PDF file.
//      * PdfStreamedDocument is much faster than PdfDocument, but it is only
//      * suitable for creating/drawing PDF files and cannot modify existing
//      * PDF documents.
//      *
//      * The document is written directly to pszFilename while being created.
//      */
//     PdfStreamedDocument document( pszFilename );
//     /*
//      * This pointer will hold the page object later. 
//      * PdfSimpleWriter can write several PdfPage's to a PDF file.
//      */
//     PdfPage* pPage;
//     /*
//      * PdfPainter is the class which is able to draw text and graphics
//      * directly on a PdfPage object.
//      */
//     PdfPainter painter;
//     /*
//      * A PdfFont object is required to draw text on a PdfPage using a PdfPainter.
//      * PoDoFo will find the font using fontconfig on your system and embedd truetype
//      * fonts automatically in the PDF file.
//      */     
//     PdfFont* pFont;

//     /*
//      * The PdfDocument object can be used to create new PdfPage objects.
//      * The PdfPage object is owned by the PdfDocument will also be deleted automatically
//      * by the PdfDocument object.
//      *
//      * You have to pass only one argument, i.e. the page size of the page to create.
//      * There are predefined enums for some common page sizes.
//      */
//     pPage = document.CreatePage( PdfPage::CreateStandardPageSize( ePdfPageSize_A4 ) );

//     /*
//      * If the page cannot be created because of an error (e.g. ePdfError_OutOfMemory )
//      * a NULL pointer is returned.
//      * We check for a NULL pointer here and throw an exception using the RAISE_ERROR macro.
//      * The raise error macro initializes a PdfError object with a given error code and
//      * the location in the file in which the error ocurred and throws it as an exception.
//      */
//     if( !pPage ) 
//     {
//         PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
//     }

//     /*
//      * Set the page as drawing target for the PdfPainter.
//      * Before the painter can draw, a page has to be set first.
//      */
//     painter.SetPage( pPage );

//     /*
//      * Create a PdfFont object using the font "Arial".
//      * The font is found on the system using fontconfig and embedded into the
//      * PDF file. If Arial is not available, a default font will be used.
//      *
//      * The created PdfFont will be deleted by the PdfDocument.
//      */
//     pFont = document.CreateFont( "Arial" );
    
//     /*
//      * If the PdfFont object cannot be allocated return an error.
//      */
//     if( !pFont )
//     {
//         PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
//     }

//     /*
//      * Set the font size
//      */
//     pFont->SetFontSize( 18.0 );

//     /*
//      * Set the font as default font for drawing.
//      * A font has to be set before you can draw text on
//      * a PdfPainter.
//      */
//     painter.SetFont( pFont );

//     /*
//      * You could set a different color than black to draw
//      * the text.
//      *
//      * SAFE_OP( painter.SetColor( 1.0, 0.0, 0.0 ) );
//      */

//     /*
//      * Actually draw the line "Hello World!" on to the PdfPage at
//      * the position 2cm,2cm from the top left corner. 
//      * Please remember that PDF files have their origin at the 
//      * bottom left corner. Therefore we substract the y coordinate 
//      * from the page height.
//      * 
//      * The position specifies the start of the baseline of the text.
//      *
//      * All coordinates in PoDoFo are in PDF units.
//      * You can also use PdfPainterMM which takes coordinates in 1/1000th mm.
//      *
//      */
//     painter.DrawText( 56.69, pPage->GetPageSize().GetHeight() - 56.69, "Hello World!" );

//     /*
//      * Tell PoDoFo that the page has been drawn completely.
//      * This required to optimize drawing operations inside in PoDoFo
//      * and has to be done whenever you are done with drawing a page.
//      */
//     painter.FinishPage();

//     /*
//      * Set some additional information on the PDF file.
//      */
//     document.GetInfo()->SetCreator ( PdfString("examplahelloworld - A PoDoFo test application") );
//     document.GetInfo()->SetAuthor  ( PdfString("Dominik Seichter") );
//     document.GetInfo()->SetTitle   ( PdfString("Hello World") );
//     document.GetInfo()->SetSubject ( PdfString("Testing the PoDoFo PDF Library") );
//     document.GetInfo()->SetKeywords( PdfString("Test;PDF;Hello World;") );

//     /*
//      * The last step is to close the document.
//      */
//     document.Close();
// }

void MyPDF::genMap(string outMap) {
	cout << "Generating map" << endl;
	for (int pn = 0; pn < pc - 1; ++pn) {
		PDF.DeletePages(0, 1);
	}
	pc = PDF.GetPageCount();

	PdfObject* fontObject =  PDF.GetPage(0)->GetFromResources( PdfName("Font"), PdfName("R7") );
	PdfFont* telugu = PDF.GetFont( fontObject );
    telugu->SetFontSize( 20.0 );

    PdfFont* english = PDF.CreateFont( "Arial" );
    english->SetFontSize( 20.0 );

    PdfFont* teluguNoto = PDF.CreateFont( "Noto Sans Telugu", false, false, new PdfIdentityEncoding( 0, 0xffff, true ) );
    teluguNoto->SetFontSize( 20.0 );

	PDF.DeletePages(0, 1);
	PdfPage* page = PDF.CreatePage( PdfPage::CreateStandardPageSize( ePdfPageSize_A4 ) );
    if( !page ) {
		cout << "Error creating page" << endl;
        PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
    }

    PdfPainter painter;
	painter.SetPage( page );

	int pos = page->GetPageSize().GetHeight() - 60;
	for(map<unsigned short, string >::iterator c = AllChar.begin(); c != AllChar.end(); c++) {
		if (pos <= 20) {
			page = PDF.CreatePage( PdfPage::CreateStandardPageSize( ePdfPageSize_A4 ) );
			if( !page ) {
				cout << "Error creating page" << endl;
				PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
			}
			pos = page->GetPageSize().GetHeight() - 60;
			painter.SetPage( page );
		}

		PdfString pdfStr = PdfString(reinterpret_cast<const pdf_utf8*>(c->second.c_str()));
		painter.SetFont( telugu );
		painter.DrawText( 60, pos, pdfStr );

		painter.SetFont( english );
		painter.DrawText( 120, pos, PdfString(string(strmake() << " -> " << hex << c->first)) );

		// PoDoFo::PdfString disclaimer_inutf8(reinterpret_cast<const PoDoFo::pdf_utf8*>(teluguText.getChar(c->first).c_str()));
		// painter.DrawText( 240, pos, disclaimer_inutf8);

		// pdfStr = PdfString(telugu->GetEncoding()->ConvertToEncoding(string(" -> " + teluguText.getChar(c->first)), teluguNoto).GetBuffer());
		// painter.DrawText( 240, pos, PdfString( pdfStr ));

			// const char *str = teluguText.getChar(c->first).c_str();
			// std::mbstate_t state = std::mbstate_t();
			// std::size_t len = 1 + std::mbsrtowcs(NULL, &str, 0, &state);
			// std::vector<wchar_t> wstr(len);
			// std::mbsrtowcs(&wstr[0], &str, wstr.size(), &state);
		// std::wcout << "Wide string: " << &wstr[0] << '\n'
        //        << "The length, including '\\0': " << wstr.size() << '\n';


		// pdfStr = PdfString(teluguText.getChar(c->first).c_str());
		// pdfStr = PdfString("శి");
		// const pdf_utf8 utf8Text = "శి";
		// pdfStr = PdfString(reinterpret_cast<const pdf_utf8*>("「PoDoFo」శి"));
		// painter.DrawText( 240, pos, PdfString( &wstr[0], wstr.size()) );
		// pdfStr = PdfString(telugu->GetEncoding()->ConvertToEncoding(string(" -> " + teluguText.getChar(c->first)), teluguNoto).GetBuffer());

		pdfStr = PdfString(reinterpret_cast<const pdf_utf8*>("「PoDoFo」శి"));

		painter.SetFont( teluguNoto );
		painter.DrawText( 240, pos, pdfStr );

		pos -= painter.GetFont()->GetFontMetrics()->GetLineSpacing();
	}


    painter.FinishPage();

    // PdfStreamedDocument document( pszFilename );
    // PdfPage* pPage = document.CreatePage( PdfPage::CreateStandardPageSize( ePdfPageSize_A4 ) );

    // PdfFont* pFont = document.CreateFont( "Arial" );
    // pFont->SetFontSize( 18.0 );

    // PdfPainter painter;
    // painter.SetPage( pPage );
    // painter.SetFont( pFont );
    // painter.DrawText( 56.69, pPage->GetPageSize().GetHeight() - 56.69, "Hello World!" );
    // painter.FinishPage();

    // document.GetInfo()->SetCreator ( PdfString("examplahelloworld - A PoDoFo test application") );
    // document.GetInfo()->SetAuthor  ( PdfString("Dominik Seichter") );
    // document.GetInfo()->SetTitle   ( PdfString("Hello World") );
    // document.GetInfo()->SetSubject ( PdfString("Testing the PoDoFo PDF Library") );
    // document.GetInfo()->SetKeywords( PdfString("Test;PDF;Hello World;") );
    // document.Close();

	// PdfObject*     resources = page->GetResources();
	// PdfRect        mediabox = page->GetMediaBox();

	PDF.Write(outMap.c_str());
}

MyPDF::MyPDF(string input) {
	// modified.open("modified.txt");
	// actual.open("actual.txt");

	PDF.Load(input.c_str());
	pc = PDF.GetPageCount();

	PdfError::EnableDebug( false );
}

MyPDF::~MyPDF() {
	// actual.close();
	// modified.close();

	outdata.close();
	cout << endl;
}