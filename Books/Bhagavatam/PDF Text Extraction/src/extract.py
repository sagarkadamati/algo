import fontforge

F = fontforge.open("../CDJMOL+PallaviMedium-0351.cff")
for name in F:
    # filename = name + ".png"
    # print name

    filename = str(hex(F[name].unicode)) + ".png"
    F[name].export(filename)
    # F[name].export(filename, 600)     # set height to 600 pixels
