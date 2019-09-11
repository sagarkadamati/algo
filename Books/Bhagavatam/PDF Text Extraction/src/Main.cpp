// #include <iostream>
// #include <fstream>
#include <locale>
#include <clocale>

#include "MyPDF.h"

void convert(string input, string output, string removeFont, int start, int end) {
	MyPDF myPDF(input);

	// myPDF.removeFont(removeFont);
	// myPDF.deletePages(start, end);
	myPDF.extractTo("data.txt");
	// myPDF.genMap("map.pdf");
	// myPDF.saveAs(output);

	// myPDF.printMissing();
}

int main()
{
	std::setlocale(LC_ALL, "en_US.utf8"); // for C and C++ where synced with stdio
	std::locale::global(std::locale("en_US.utf8")); // for C++
	std::cout.imbue(std::locale());
	std::cout.imbue(std::locale(std::cout.getloc(), new std::numpunct<char>()));

	system("mkdir -p finial");

	// convert("org/Skandamu01.pdf" , "finial/Skandamu01.pdf" , "F1" , 11, 0);
	convert("org/Skandamu02.pdf" , "finial/Skandamu02.pdf" , "R10" , 1, 0);
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

	return 0;
}
