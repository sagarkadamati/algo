#!/usr/bin/env python3

''' This program is used get the width and height of bhagavatam pdfs '''

import sys
from PyPDF2 import PdfFileReader, PdfFileWriter

HEIGHT = 0
WIDTH = 0

def getheightandwidth(filename):
	PDFFILEOBJ = open(filename, 'rb')
	READER = PdfFileReader(PDFFILEOBJ)

	global HEIGHT
	global WIDTH

	for i in range(READER.numPages):
		PAGE = READER.getPage(i)

		if HEIGHT < PAGE.mediaBox.getHeight():
			HEIGHT = PAGE.mediaBox.getHeight()

		if WIDTH < PAGE.mediaBox.getWidth():
			WIDTH = PAGE.mediaBox.getWidth()

	PDFFILEOBJ.close()
	return

getheightandwidth("BhagavatamCrop/Skandamu01.pdf")
getheightandwidth("BhagavatamCrop/Skandamu02.pdf")
getheightandwidth("BhagavatamCrop/Skandamu03.pdf")
getheightandwidth("BhagavatamCrop/Skandamu04.pdf")
getheightandwidth("BhagavatamCrop/Skandamu05.pdf")
getheightandwidth("BhagavatamCrop/Skandamu06.pdf")
getheightandwidth("BhagavatamCrop/Skandamu07.pdf")
getheightandwidth("BhagavatamCrop/Skandamu08.pdf")
getheightandwidth("BhagavatamCrop/Skandamu09.pdf")
getheightandwidth("BhagavatamCrop/Skandamu10A.pdf")
getheightandwidth("BhagavatamCrop/Skandamu10B.pdf")
getheightandwidth("BhagavatamCrop/Skandamu10C.pdf")
getheightandwidth("BhagavatamCrop/Skandamu11A.pdf")
getheightandwidth("BhagavatamCrop/Skandamu11B.pdf")
getheightandwidth("BhagavatamCrop/Skandamu12.pdf")

print ("Dimensions: Width - " + str(WIDTH) + ", Height - " + str(HEIGHT))

PDFFILEOBJ = open("BhagavatamCrop/Skandamu05.pdf", 'rb')
OUTSTREAM = open("new.pdf", 'wb')

READER = PdfFileReader(PDFFILEOBJ)
WRITER = PdfFileWriter()

for i in range(READER.numPages):
	PAGE = READER.getPage(i)
	NEWPAGE = PAGE.createBlankPage(None, WIDTH, HEIGHT)

	TX = 0
	TY = HEIGHT - PAGE.mediaBox.getHeight()
	TRANSLATION = [[1, 0, 0],
				   [0, 1, 0],
				   [TX, TY, 1]]
	NEWPAGE.mergeTransformedPage(PAGE, [TRANSLATION[0][0], TRANSLATION[0][1],
										TRANSLATION[1][0], TRANSLATION[1][1],
										TRANSLATION[2][0], TRANSLATION[2][1]])

	WRITER.addPage(NEWPAGE)

WRITER.write(OUTSTREAM)
OUTSTREAM.close()
PDFFILEOBJ.close()
