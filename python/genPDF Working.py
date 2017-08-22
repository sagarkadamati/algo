from PyPDF2 import PdfFileReader, PdfFileWriter

pdfFileObj = open('02 The Cosmic Manifestation.pdf', 'rb')
outstream  = open("output.pdf", 'wb')

reader = PdfFileReader(pdfFileObj)
writer = PdfFileWriter()

page0 = reader.getPage(0)

print(reader.numPages)
for i in range(reader.numPages):
    page1 = reader.getPage(i)
    page2 = reader.getPage(i + 1)
    page3 = reader.getPage(i + 2)
    page4 = reader.getPage(i + 3)

    tx = page2.mediaBox.getWidth()
    ty = 0
    translation = [[1, 0, 0],
                   [0, 1, 0],
                   [tx, ty, 1]]

    frontSide = page0.createBlankPage(None, page0.mediaBox.getWidth() * 2, page0.mediaBox.getHeight())
    backSide = page0.createBlankPage(None, page0.mediaBox.getWidth() * 2, page0.mediaBox.getHeight())

    frontSide.mergePage(page4)
    backSide.mergePage(page2)

    frontSide.mergeTransformedPage(page1, [translation[0][0], translation[0][1],
                                          translation[1][0], translation[1][1],
                                          translation[2][0], translation[2][1]])
    backSide.mergeTransformedPage(page3, [translation[0][0], translation[0][1],
                                          translation[1][0], translation[1][1],
                                          translation[2][0], translation[2][1]])

    writer.addPage(frontSide)
    writer.addPage(backSide)

writer.write(outstream)

outstream.close()
pdfFileObj.close()