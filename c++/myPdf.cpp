#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stack>

#include <podofo/podofo.h>

using namespace std;
using namespace PoDoFo;

void ReplaceStringInPlace(std::string& subject, const std::string& search,
                          const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
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
	PdfFont* pCurFont   = NULL;

	int count = 0;

	std::stack<PdfVariant> stack;
	std::ostringstream block;

	while( tokenizer.ReadNext( eType, pszToken, var ) )
	{
		if( eType == ePdfContentsType_Keyword )
		{
			if(record) {
				if( strcmp( pszToken, "cm" ) == 0 ) 
				{
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
				
					block << scale_x << " " 
					      << shear_x << " " 
					      << shear_y << " " 
					      << scale_y << " " 
					      << offset_x << " " 
					      << offset_y << " cm " << endl;
				}

				if( strcmp( pszToken, "re" ) == 0 ) 
				{
					offset_y = stack.top().GetReal();
					stack.pop();
					offset_x = stack.top().GetReal();
					stack.pop();
					scale_y  = stack.top().GetReal();
					stack.pop();
					shear_y  = stack.top().GetReal();
					stack.pop();
				
					block << shear_y << " " 
					      << scale_y << " " 
					      << offset_x << " " 
					      << offset_y << " " 
					      << pszToken << " " << endl;
				}

				if( strcmp( pszToken, "W" ) == 0 ||
				    strcmp( pszToken, "n" ) == 0 ||
				    strcmp( pszToken, "q" ) == 0 ||
				    strcmp( pszToken, "Q" ) == 0 )
				{
					block << pszToken << endl;
				}

				if( strcmp( pszToken, "w" ) == 0 ||
				    strcmp( pszToken, "Tz" ) == 0 ||
				    strcmp( pszToken, "g" ) == 0 ||
				    strcmp( pszToken, "G" ) == 0 )
				{
					g = stack.top().GetReal();
					stack.pop();
					block << g << " " << pszToken << endl;
				}

				if( strcmp( pszToken, "rg" ) == 0 ||
				    strcmp( pszToken, "RG" ) == 0 )
				{
					blue = stack.top().GetReal();
					stack.pop();
					green = stack.top().GetReal();
					stack.pop();
					red = stack.top().GetReal();
					stack.pop();

					// red = 0.0;
					// green = 0.0;
					// blue = 0.0;

					red = 0.396;
					green = 0.482;
					blue = 0.514;
				
					block << red << " " 
					      << green << " " 
					      << blue << " " 
					      << pszToken << endl;

					// cout << red << " " 
					//       << green << " " 
					//       << blue << " " 
					//       << pszToken << endl;
				}

				// support 'l' and 'm' tokens
				if( strcmp( pszToken, "l" ) == 0 || 
				    strcmp( pszToken, "m" ) == 0 )
				{
					x = stack.top().GetReal();
					stack.pop();
					y = stack.top().GetReal();
					stack.pop();
				}
				else if( strcmp( pszToken, "BT" ) == 0 ) 
				{
					bTextBlock   = true;     
					block << "BT" << endl;
				}
				else if( strcmp( pszToken, "ET" ) == 0 ) 
				{
					block << "ET" << endl;
				}
			}

			if( bTextBlock ) 
			{
				if( strcmp( pszToken, "Tf" ) == 0 ) 
				{
					size = stack.top().GetReal();
					stack.pop();

					str = stack.top().GetName().GetName();
					if(str.compare( removefont ) == 0)
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
						      << str
						      << " " << size << " " 
						      << "Tf" << endl;

					// cout << "/" 
					//       << str
					//       << " " << size << " " 
					//       << "Tf" << endl;
				}

				if(record) {
					if( strcmp( pszToken, "gs" ) == 0 ) 
					{
						block << "/" 
						      << stack.top().GetName().GetName() 
						      << " " << "gs" << endl;
					}

					if( strcmp( pszToken, "Tc" ) == 0 ||
					    strcmp( pszToken, "TL" ) == 0 ||
					    strcmp( pszToken, "Tw" ) == 0 )
					{
						td_y = stack.top().GetReal();
						stack.pop();
				
						block << td_y << " " << pszToken << endl;
					}

					if( strcmp( pszToken, "TD" ) == 0 ||
					    strcmp( pszToken, "Td" ) == 0)
					{
						td_y = stack.top().GetReal();
						stack.pop();
						td_x = stack.top().GetReal();
						stack.pop();
				
						block << td_x << " " 
						      << td_y << " " 
						      << pszToken << endl;
					}
					else if( strcmp( pszToken, "Tm" ) == 0 )
					{
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
				
						block << scale_x << " " 
						      << shear_x << " " 
						      << shear_y << " " 
						      << scale_y << " " 
						      << offset_x << " " 
						      << offset_y << " " 
						      << pszToken << endl;
					}
					else if( strcmp( pszToken, "Tj" ) == 0 ||
						 strcmp( pszToken, "'" ) == 0 ) 
					{
						str = stack.top().GetString().GetString();
						ReplaceStringInPlace(str, "\\", "\\\\");
						ReplaceStringInPlace(str, "(", "\\(");
						ReplaceStringInPlace(str, ")", "\\)");
		
						block << "(" << str 
						      << ")" << pszToken << endl;
						stack.pop();
					}
					else if( strcmp( pszToken, "TJ" ) == 0 ) 
					{
						PdfArray array = stack.top().GetArray();
						stack.pop();

						block << "[";
					
						for( int i=0; i<static_cast<int>(array.GetSize()); i++ ) 
						{
							string str;
							if( array[i].IsString() || array[i].IsHexString() ) {
								str = array[i].GetString().GetString();
								ReplaceStringInPlace(str, "\\", "\\\\");
								ReplaceStringInPlace(str, "(", "\\(");
								ReplaceStringInPlace(str, ")", "\\)");
							
								block << "("
								      << str
								      << ")";
							}
							else if( array[i].IsNumber())
								block << array[i].GetReal();
						}
						block << "]" << pszToken << endl;
					}
				}

			}
		}
		else if ( eType == ePdfContentsType_Variant )
		{
			stack.push( var );
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

	cout << "Skandam " << input << "Processing" << endl;

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
	for (pn = 0; pn < pc; ++pn) {
		PdfPage*        page = pdf.GetPage(pn);		

		get_glimpse(&pdf, page);

		// page->GetContents()->GetStream()->GetFilteredCopy(&pBuffer, &lLen);
		// actual << pBuffer;
		// free(pBuffer);

		str = extract(&pdf, page, removefont);
		// modified << str;

		page->GetContents()->GetStream()->Set(str.c_str());

		// actual.close();
		// modified.close();

		// system("diff -up actual.txt modified.txt | egrep '^\\+|^-' > diff.txt");
	}

	//page->GetContents()->GetStream()->Set(process_glimps(removefont).c_str());
	
	pdf.Write(output.c_str());
	// cout << "Total Glimps: " << size;
	// cout << endl;
}

int main()
{
	system("mkdir -p finial");
	convert("org/Skandamu01.pdf" , "finial/Skandamu01.pdf" , "F1" , 11, 0);
	convert("org/Skandamu02.pdf" , "finial/Skandamu02.pdf" , "R10", 1, 0);
 	convert("org/Skandamu03.pdf" , "finial/Skandamu03.pdf" , "R10", 1, 0);
	convert("org/Skandamu04.pdf" , "finial/Skandamu04.pdf" , "F3" , 1, 0);
	convert("org/Skandamu05.pdf" , "finial/Skandamu05.pdf" , "R10", 1, 0);

	convert("org/Skandamu06.pdf" , "finial/Skandamu06.pdf" , "R10", 1, 0);
	convert("org/Skandamu07.pdf" , "finial/Skandamu07.pdf" , "R10", 1, 0);
	convert("org/Skandamu08.pdf" , "finial/Skandamu08.pdf" , "R10", 1, 0);
	convert("org/Skandamu09.pdf" , "finial/Skandamu09.pdf" , "R10", 1, 0);
	convert("org/Skandamu10A.pdf", "finial/Skandamu10A.pdf", "F2" , 1, 0);

	convert("org/Skandamu10B.pdf", "finial/Skandamu10B.pdf", "F2" , 1, 0);
	convert("org/Skandamu10C.pdf", "finial/Skandamu10C.pdf", "F2" , 1, 0);
	convert("org/Skandamu11A.pdf", "finial/Skandamu11A.pdf", "F3" , 1, 0);
	convert("org/Skandamu11B.pdf", "finial/Skandamu11B.pdf", "F2" , 1, 0);
	convert("org/Skandamu12.pdf" , "finial/Skandamu12.pdf" , "F3" , 1, 0);
}
