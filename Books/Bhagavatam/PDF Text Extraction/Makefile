all:
	@g++ src/*.cpp -g -lpodofo -o myPdf
run: all
	@./myPdf
#	@ evince map.pdf
setup:
	@ sudo apt-get install libpodofo-dev
	@ sudo apt-get install libpodofo-utils
clean:
	@rm -rf myPdf *.pdf *~ output.pdf finial
