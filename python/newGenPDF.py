from PyPDF2 import PdfFileReader, PdfFileWriter

pdfFileObj = open('test-crop.pdf', 'rb')
outstream  = open("output.pdf", 'wb')

reader = PdfFileReader(pdfFileObj)
writer = PdfFileWriter()

page0 = reader.getPage(0)

print(page0.cropBox.getLowerLeft())
print(page0.cropBox.getUpperLeft())
print(page0.cropBox.getLowerRight())
print(page0.cropBox.getUpperRight())

print(reader.numPages)
for i in range(9):
	page1 = reader.getPage(i)
	page2 = reader.getPage(i + 1)
	page3 = reader.getPage(i + 2)
	page4 = reader.getPage(i + 3)

	tx = page2.mediaBox.getWidth()
	ty = 0
	translation = [[1, 0, 0],
				   [0, 1, 0],
				   [tx, ty, 1]]

	newPage1 = page0.createBlankPage(None, 72 * 8.5 * 2, 72 * 11)
	newPage1.mergePage(page4)
	newPage1.mergeTransformedPage(page1, [translation[0][0], translation[0][1],
										  translation[1][0], translation[1][1],
										  translation[2][0], translation[2][1]])
	writer.addPage(newPage1)

	newPage2 = page0.createBlankPage(None, page0.mediaBox.getWidth() * 2, page0.mediaBox.getHeight())
	newPage2.mergePage(page2)
	newPage2.mergeTransformedPage(page3, [translation[0][0], translation[0][1],
										  translation[1][0], translation[1][1],
										  translation[2][0], translation[2][1]])
	writer.addPage(newPage2)

writer.write(outstream)

outstream.close()
pdfFileObj.close()