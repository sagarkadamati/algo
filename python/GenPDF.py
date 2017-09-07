#!/usr/bin/env python3

''' This program is used to prepare pdf for printing '''

import os

from PyPDF2 import PdfFileReader, PdfFileWriter

from reportlab.pdfgen import canvas
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont

pdfmetrics.registerFont(TTFont('DejaVuSans', 'DejaVuSans.ttf'))

FILENAME = "Skandamu02"

PDFFILEOBJ = open("Bhagavatam/" + FILENAME + ".pdf", 'rb')
FRONTOUTSTREAM = open(FILENAME + "-front.pdf", 'wb')
BACKOUTSTREAM = open(FILENAME + "-back.pdf", 'wb')

READER = PdfFileReader(PDFFILEOBJ)
FRONTWRITER = PdfFileWriter()
BACKWRITER = PdfFileWriter()

POINT = 1
POINTSPI = 72
BORDER = 0.5 * POINTSPI

WIDTH = 8.27 * POINTSPI
HEIGHT = 11.69 * POINTSPI

HEADER = 0.12 * POINTSPI
FOOTER = 0

TOP = BORDER
LEFT = BORDER
RIGHT = BORDER
BOTTOM = BORDER

PAGEWIDTH = (HEIGHT / 2) - (LEFT + RIGHT)
PAGEHEIGHT = WIDTH - (TOP + BOTTOM + HEADER + FOOTER)

LEFTTITLE = "Bhagavatam"
RIGHTTITLE = "The Cosmic Manifestation"

PAGES = READER.numPages

i = 0
while i < PAGES:
    CANVAS = canvas.Canvas("nos.pdf", pagesize=(HEIGHT, WIDTH))

    CANVAS.setStrokeColorRGB(0, 0, 0.5)
    CANVAS.setFillColorRGB(0, 0, 0.5)
    CANVAS.setFontSize(8)
    # CANVAS.setFont('DejaVuSans', 8 * POINT)

    PAGE1 = READER.getPage(i)
    PAGE1.scaleTo(PAGEWIDTH, PAGEHEIGHT)

    if (i + 3) < PAGES:
        PAGE4 = READER.getPage(i + 3)
        PAGE4.scaleTo(PAGEWIDTH, PAGEHEIGHT)

        CANVAS.drawString(LEFT + (BORDER * 0.7) + (7 * len(str(i + 4))),
                          BOTTOM + FOOTER + PAGEHEIGHT, LEFTTITLE)
        CANVAS.drawString(LEFT + (BORDER * 0.7),
                          BOTTOM + FOOTER + PAGEHEIGHT, str(i + 4))
    else:
        PAGE4 = PAGE1.createBlankPage(None, PAGEWIDTH, PAGEHEIGHT)

    CANVAS.drawString((2 * (LEFT + PAGEWIDTH)) + RIGHT - (BORDER * 0.7)
                      - (4 * len(RIGHTTITLE)),
                      BOTTOM + FOOTER + PAGEHEIGHT, RIGHTTITLE)
    CANVAS.drawString((2 * (LEFT + PAGEWIDTH)) + RIGHT - (BORDER * 0.7),
                      BOTTOM + FOOTER + PAGEHEIGHT, str(i + 1))
    # CANVAS.setFontSize(6)
    CANVAS.drawString(HEIGHT - (TOP * 0.75), WIDTH - (RIGHT * 0.5), str(int((i + 4) / 4)))
    CANVAS.showPage()

    CANVAS.setStrokeColorRGB(0, 0, 0.5)
    CANVAS.setFillColorRGB(0, 0, 0.5)
    CANVAS.setFontSize(8)
    # CANVAS.setFont('DejaVuSans', 8 * POINT)

    if (i + 1) < PAGES:
        PAGE2 = READER.getPage(i + 1)
        PAGE2.scaleTo(PAGEWIDTH, PAGEHEIGHT)
        CANVAS.drawString(LEFT + (BORDER * 0.7) + (7 * len(str(i + 2))),
                          BOTTOM + FOOTER + PAGEHEIGHT, LEFTTITLE)
        CANVAS.drawString(LEFT + (BORDER * 0.7),
                          BOTTOM + FOOTER + PAGEHEIGHT, str(i + 2))
    else:
        PAGE2 = PAGE1.createBlankPage(None, PAGEWIDTH, PAGEHEIGHT)

    if (i + 2) < PAGES:
        PAGE3 = READER.getPage(i + 2)
        PAGE3.scaleTo(PAGEWIDTH, PAGEHEIGHT)
        CANVAS.drawString((2 * (LEFT + PAGEWIDTH)) + RIGHT - (BORDER * 0.7)
                          - (4 * len(RIGHTTITLE)),
                          BOTTOM + FOOTER + PAGEHEIGHT, RIGHTTITLE)
        CANVAS.drawString((2 * (LEFT + PAGEWIDTH)) + RIGHT - (BORDER * 0.7),
                          BOTTOM + FOOTER + PAGEHEIGHT, str(i + 3))
    else:
        PAGE3 = PAGE1.createBlankPage(None, PAGEWIDTH, PAGEHEIGHT)

    CANVAS.showPage()
    CANVAS.save()

    FRONT = PAGE1.createBlankPage(None, HEIGHT, WIDTH)
    BACK = PAGE1.createBlankPage(None, HEIGHT, WIDTH)

    TX = LEFT
    TY = BOTTOM + FOOTER
    TRANSLATION = [[1, 0, 0],
                   [0, 1, 0],
                   [TX, TY, 1]]
    FRONT.mergeTransformedPage(PAGE4, [TRANSLATION[0][0], TRANSLATION[0][1],
                                       TRANSLATION[1][0], TRANSLATION[1][1],
                                       TRANSLATION[2][0], TRANSLATION[2][1]])

    TX = PAGEWIDTH + (2 * LEFT) + RIGHT
    TY = BOTTOM + FOOTER
    TRANSLATION = [[1, 0, 0],
                   [0, 1, 0],
                   [TX, TY, 1]]
    FRONT.mergeTransformedPage(PAGE1, [TRANSLATION[0][0], TRANSLATION[0][1],
                                       TRANSLATION[1][0], TRANSLATION[1][1],
                                       TRANSLATION[2][0], TRANSLATION[2][1]])

    TX = LEFT
    TY = BOTTOM + FOOTER
    TRANSLATION = [[1, 0, 0],
                   [0, 1, 0],
                   [TX, TY, 1]]

    BACK.mergeTransformedPage(PAGE2, [TRANSLATION[0][0], TRANSLATION[0][1],
                                      TRANSLATION[1][0], TRANSLATION[1][1],
                                      TRANSLATION[2][0], TRANSLATION[2][1]])

    TX = PAGEWIDTH + (2 * LEFT) + RIGHT
    TY = BOTTOM + FOOTER
    TRANSLATION = [[1, 0, 0],
                   [0, 1, 0],
                   [TX, TY, 1]]
    BACK.mergeTransformedPage(PAGE3, [TRANSLATION[0][0], TRANSLATION[0][1],
                                      TRANSLATION[1][0], TRANSLATION[1][1],
                                      TRANSLATION[2][0], TRANSLATION[2][1]])

    FRONTWRITER.addPage(FRONT)
    BACKWRITER.addPage(BACK)

    NOSFILEOBJ = open("nos.pdf", 'rb')
    NOSREADER = PdfFileReader(NOSFILEOBJ)
    FRONT.mergePage(NOSREADER.getPage(0))
    BACK.mergePage(NOSREADER.getPage(1))
    NOSFILEOBJ.close()

    i += 4

FRONTWRITER.write(FRONTOUTSTREAM)
BACKWRITER.write(BACKOUTSTREAM)

FRONTOUTSTREAM.close()
BACKOUTSTREAM.close()
PDFFILEOBJ.close()

os.remove("nos.pdf")
