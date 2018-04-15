#!/usr/bin/env python3
'''This file is used to prepare pdf to printable format'''

from PyPDF2 import PdfFileReader, PdfFileWriter

PDFFILEOBJ = open('02 The Cosmic Manifestation.pdf', 'rb')
OUTSTREAM = open("output.pdf", 'wb')

READER = PdfFileReader(PDFFILEOBJ)
WRITER = PdfFileWriter()

i = 0
PAGES = READER.numPages

while i < PAGES:
	PAGE1 = READER.getPage(i)

	if (i + 1) < PAGES:
		PAGE2 = READER.getPage(i + 1)
	else:
		PAGE2 = PAGE1.createBlankPAGE(None, PAGE1.mediaBox.getWidth(), PAGE1.mediaBox.getHeight())

	if (i + 2) < PAGES:
		PAGE3 = READER.getPage(i + 2)
	else:
		PAGE3 = PAGE1.createBlankPAGE(None, PAGE1.mediaBox.getWidth(), PAGE1.mediaBox.getHeight())

	if (i + 3) < PAGES:
		PAGE4 = READER.getPage(i + 3)
	else:
		PAGE4 = PAGE1.createBlankPAGE(None, PAGE1.mediaBox.getWidth(), PAGE1.mediaBox.getHeight())

	TX = PAGE1.mediaBox.getWidth()
	TY = 0
	TRANSLATION = [[1, 0, 0],
				   [0, 1, 0],
				   [TX, TY, 1]]

	FRONT = PAGE1.createBlankPAGE(None, PAGE1.mediaBox.getWidth() * 2, PAGE1.mediaBox.getHeight())
	FRONT.mergePAGE(PAGE4)
	FRONT.mergeTransformedPAGE(PAGE1, [TRANSLATION[0][0], TRANSLATION[0][1],
									   TRANSLATION[1][0], TRANSLATION[1][1],
									   TRANSLATION[2][0], TRANSLATION[2][1]])

	BACK = PAGE1.createBlankPAGE(None, PAGE1.mediaBox.getWidth() * 2, PAGE1.mediaBox.getHeight())
	BACK.mergePAGE(PAGE2)
	BACK.mergeTransformedPAGE(PAGE3, [TRANSLATION[0][0], TRANSLATION[0][1],
									  TRANSLATION[1][0], TRANSLATION[1][1],
									  TRANSLATION[2][0], TRANSLATION[2][1]])

	WRITER.addPage(FRONT)
	WRITER.addPage(BACK)
	i += 4

WRITER.write(OUTSTREAM)

OUTSTREAM.close()
PDFFILEOBJ.close()
