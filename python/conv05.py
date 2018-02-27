#!/usr/bin/env python3

''' This program is used get the width and height of bhagavatam pdfs '''

import sys
from PyPDF2 import PdfFileReader

HEIGHT = 0
WIDTH = 0

def GetHeightAndWidth(fileName):
    PDFFILEOBJ = open(fileName, 'rb')
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

GetHeightAndWidth(str(sys.argv[1]))
print ("Width: " + str(WIDTH) + " Height: " + str(HEIGHT))
