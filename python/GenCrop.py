#!/usr/bin/env python3

''' This program is used to prepare pdf for printing '''

import os

from PyPDF2 import PdfFileReader, PdfFileWriter

FILENAME = "Skandamu02"

PDFFILEOBJ = open("Bhagavatam/" + FILENAME + ".pdf", 'rb')
OUTSTREAM = open("crop.pdf", 'wb')

READER = PdfFileReader(PDFFILEOBJ)
WRITER = PdfFileWriter()

POINTSPI = 72
ADJUSTMENT = 12

PAGES = READER.numPages

i = 0
while i < PAGES:
    PAGE = READER.getPage(i)
    PAGE.mediaBox.setLowerLeft(
        (abs(PAGE.mediaBox.getLowerLeft_x() + ADJUSTMENT),
         abs(PAGE.mediaBox.getLowerLeft_y() + ADJUSTMENT))
        )
    PAGE.mediaBox.setLowerRight(
        (abs(PAGE.mediaBox.getLowerRight_x() - ADJUSTMENT),
         abs(PAGE.mediaBox.getLowerRight_y() + ADJUSTMENT))
        )
    PAGE.mediaBox.setUpperLeft(
        (abs(PAGE.mediaBox.getUpperLeft_x() + ADJUSTMENT),
         abs(PAGE.mediaBox.getUpperLeft_y() - ADJUSTMENT))
        )
    PAGE.mediaBox.setUpperRight(
        (abs(PAGE.mediaBox.getUpperRight_x() - ADJUSTMENT),
         abs(PAGE.mediaBox.getUpperRight_y() - ADJUSTMENT))
        )

    WRITER.addPage(PAGE)

    i += 1

WRITER.write(OUTSTREAM)

OUTSTREAM.close()
PDFFILEOBJ.close()
