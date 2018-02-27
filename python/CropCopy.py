#!/usr/bin/env python3

''' This program is used decrease pdf size produced by pdfcrop '''

import sys
from PyPDF2 import PdfFileReader, PdfFileWriter

PDFFILEOBJ = open("croppedBhagavatam.pdf", 'rb')
OUTSTREAM = open(str(sys.argv[1]), 'wb')

READER = PdfFileReader(PDFFILEOBJ)
WRITER = PdfFileWriter()

for i in range(READER.numPages):
    WRITER.addPage(READER.getPage(i))

WRITER.write(OUTSTREAM)
OUTSTREAM.close()
PDFFILEOBJ.close()
