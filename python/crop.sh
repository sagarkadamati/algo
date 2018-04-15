#!/bin/bash

crop() {
	pdfcrop Bhagavatam/Skandamu$1.pdf croppedBhagavatam.pdf
	./CropCopy.py cropped/Skandamu$1.pdf
}

mkdir -p cropped
crop 01
crop 02
crop 03
crop 04
crop 05
crop 06
crop 07
crop 08
crop 09
crop 10A
crop 10B
crop 10C
crop 11A
crop 11B
crop 12
