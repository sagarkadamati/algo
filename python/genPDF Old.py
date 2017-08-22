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

print(page0.cropBox.getLowerLeft())
print(page0.cropBox.getUpperLeft())
print(page0.cropBox.getLowerRight())
print(page0.cropBox.getUpperRight())

print(reader.numPages)
# for i in range(reader.numPages):
for i in range(1):
    page1 = reader.getPage(i)
    page2 = reader.getPage(i + 1)

    # page1.scaleTo(width=5.5, height=8.5)
    # page2.scaleTo(width=5.5, height=8.5)

    print(page1.cropBox.getLowerLeft())
    print(page1.cropBox.getUpperLeft())
    print(page1.cropBox.getLowerRight())
    print(page1.cropBox.getUpperRight())

    print(page2.cropBox.getLowerLeft())
    print(page2.cropBox.getUpperLeft())
    print(page2.cropBox.getLowerRight())
    print(page2.cropBox.getUpperRight())

    newPage = page0.createBlankPage(None, page0.mediaBox.getWidth() * 2, page0.mediaBox.getHeight())

    newPage.mergePage(page1)
    # mergeRotateAroundPointPage(newPage, page2, 0,
    #             page2.mediaBox.getWidth()/2, page2.mediaBox.getWidth()/2)

    translation = [[1, 0, 0],
                [0, 1, 0],
                [-page2.mediaBox.getWidth()/2, -page2.mediaBox.getWidth()/2, 1]]

    newPage.mergeTransformedPage(page2, [ctm[0][0], ctm[0][1],
                                      ctm[1][0], ctm[1][1],
                                      ctm[2][0], ctm[2][1]])

    # page2.cropBox.setLowerLeft(page1.cropBox.getLowerRight())
    # page2.cropBox.setUpperLeft(page1.cropBox.getUpperRight())

    # tmp = page2.cropBox.getLowerRight()
    # data = tmp[0]
    # data *= 2
    # tmp = data, tmp[1]
    # page2.cropBox.setLowerRight(tmp)
    # tmp = page2.cropBox.getUpperRight()
    # data = tmp[0]
    # data *= 2
    # tmp = data, tmp[1]
    # page2.cropBox.setUpperRight(tmp)

    # print("New")
    # print(page2.cropBox.getLowerLeft())
    # print(page2.cropBox.getUpperLeft())
    # print(page2.cropBox.getLowerRight())
    # print(page2.cropBox.getUpperRight())

    # newPage.mergePage(page2)
    writer.addPage(newPage)

    # if (i == 1):
    #    page0.rotateCounterClockwise(90)
    #    page.mergePage(page0)

    # page.cropBox.setLowerLeft()
    # page.cropBox.setUpperLeft()
    # page.cropBox.setLowerRight()
    # page.cropBox.setUpperRight()

    # print(page.extractText())
    # writer.addPage(page.rotateCounterClockwise(90))

# parent = writer.addBookmark('Introduction', 0) # add parent bookmark
# writer.addBookmark('Hello, World', 0, parent) # add child bookmark
# writer.addBookmark('Hello, World', 0, parent=None) # add bookmark

writer.write(outstream)

outstream.close()
pdfFileObj.close()
