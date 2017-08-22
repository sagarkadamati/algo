from PyPDF2 import PdfFileReader, PdfFileWriter

def mergeRotateAroundPointPage(page, page2, rotation, tx, ty):
    translation = [[1, 0, 0],
                   [0, 1, 0],
                   [-tx,-ty,1]]
    rotation = math.radians(rotation)
    rotating = [[math.cos(rotation), math.sin(rotation),0],
                [-math.sin(rotation),math.cos(rotation), 0],
                [0,                  0,                  1]]
    rtranslation = [[1, 0, 0],
                   [0, 1, 0],
                   [tx,ty,1]]
    ctm = utils.matrixMultiply(translation, rotating)
    ctm = utils.matrixMultiply(ctm, rtranslation)

    return page.mergeTransformedPage(page2, [ctm[0][0], ctm[0][1],
                                             ctm[1][0], ctm[1][1],
                                             ctm[2][0], ctm[2][1]])

pdfFileObj = open('02 The Cosmic Manifestation.pdf', 'rb')
outstream  = open("output.pdf", 'wb')

reader = PdfFileReader(pdfFileObj)
writer = PdfFileWriter()

# pdf_info = reader.getDocumentInfo()
# print (pdf_info)

page0 = reader.getPage(0)

# print("\n")
# print(page0.cropBox.getLowerLeft())
# print(page0.cropBox.getUpperLeft())
# print(page0.cropBox.getLowerRight())
print(page0.cropBox.getUpperRight_y()/72)
print(page0.cropBox.getUpperRight_x()/72)

print(reader.numPages)
# for i in range(reader.numPages):
for i in range(1):
    page1 = reader.getPage(i)
    page2 = reader.getPage(i + 1)
    page3 = reader.getPage(i + 2)
    page4 = reader.getPage(i + 3)

    # page1.scaleTo(width=5.5, height=8.5)
    # page2.scaleTo(width=5.5, height=8.5)

    tx = page2.mediaBox.getWidth()
    ty = 0
    translation = [[1, 0, 0],
                   [0, 1, 0],
                   [tx, ty, 1]]

    newPage1 = page0.createBlankPage(None, page0.mediaBox.getWidth() * 2, page0.mediaBox.getHeight())
    newPage1.mergePage(page4)
    newPage1.mergeTransformedPage(page1, [translation[0][0], translation[0][1],
                                          translation[1][0], translation[1][1],
                                          translation[2][0], translation[2][1]])
    writer.addPage(newPage1)

    # newPage2 = page0.createBlankPage(None, page0.mediaBox.getWidth() * 2, page0.mediaBox.getHeight())
    # newPage2.mergePage(page2)
    # newPage2.mergeTransformedPage(page3, [translation[0][0], translation[0][1],
    #                                       translation[1][0], translation[1][1],
    #                                       translation[2][0], translation[2][1]])
    # writer.addPage(newPage2)

writer.write(outstream)

outstream.close()
pdfFileObj.close()