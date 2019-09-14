#!/usr/bin/env python

import sys
import fontforge

print(sys.argv[0])
F = fontforge.open(sys.argv[1])
# F = fontforge.open(CBCDOR+PallaviMedium-0008.cff)

for name in F:
    filename = str(hex(F[name].unicode)) + ".png"
    F[name].export(filename)
    # F[name].export(filename, 600)     # set height to 600 pixels
