import os

import agnostictranslate as agnostic
import dictionary as internal
import image_processing as imgprocess
import kerntranslate as kern

OUT_FOLDER = 'OUT'
INTERNAL_FOLDER = 'INTERNAL'
AGNOSTIC_FOLDER = 'AGNOSTIC'
KERN_FOLDER = 'KERN'
SVG_FOLDER = 'SVG'
IMAGE_FOLDER = 'PNG'

extensionKern = '.krn'
extensionAgnosticInternal = '.txt'
extensionImage = '.png'


def create_folds():
    global out_path
    global internal_path
    global kern_path
    global agnostic_path
    global svg_path
    global image_path

    main_path = os.path.dirname(os.path.realpath(__file__))
    out_path = os.path.join(main_path, OUT_FOLDER)
    internal_path = os.path.join(out_path, INTERNAL_FOLDER)
    kern_path = os.path.join(out_path, KERN_FOLDER)
    agnostic_path = os.path.join(out_path, AGNOSTIC_FOLDER)
    svg_path = os.path.join(out_path, SVG_FOLDER)
    image_path = os.path.join(out_path, IMAGE_FOLDER)

    os.makedirs(out_path, exist_ok=True)
    os.makedirs(internal_path, exist_ok=True)
    os.makedirs(kern_path, exist_ok=True)
    os.makedirs(agnostic_path, exist_ok=True)
    os.makedirs(svg_path, exist_ok=True)
    os.makedirs(image_path, exist_ok=True)


def init(i: int, typeAgnostic: str):
    global fInternal
    global fKern
    global fAgnostic

    filenameAgnosticInternal = str(i) + extensionAgnosticInternal
    filenameKern = str(i) + extensionKern

    fInternal = open(os.path.join(internal_path, filenameAgnosticInternal), "w")

    fKern = open(os.path.join(kern_path, filenameKern), "w")
    fKern.write(kern.init + kern.advance)

    fAgnostic = open(os.path.join(agnostic_path, filenameAgnosticInternal), "w")
    agnostic.valueSeparator(typeAgnostic=typeAgnostic)


def piano_init(i: int, typeAgnostic: str):
    # Clefs are fixed to piano clefs
    # The order is conditioned to the appearance of a Humdrum **kern file
    # Staves are ordered from lowest to highest pitch
    # Therefore, 1 -> ClefF4; 2 -> ClefG2
    global fInternal
    global fKern
    global fAgnostic1_path
    global fAgnostic1
    global fAgnostic2

    filenameAgnosticInternal = str(i) + extensionAgnosticInternal
    filenameKern = str(i) + extensionKern

    fInternal = open(os.path.join(internal_path, filenameAgnosticInternal), "w")

    fKern = open(os.path.join(kern_path, filenameKern), "w")
    fKern.write(kern.init + kern.not_advance + kern.init + kern.advance)

    fAgnostic1_path = os.path.join(agnostic_path, '-' + filenameAgnosticInternal)
    fAgnostic1 = open(fAgnostic1_path, "w")
    fAgnostic2 = open(os.path.join(agnostic_path, filenameAgnosticInternal), "w")
    agnostic.valueSeparator(typeAgnostic=typeAgnostic)


def polyss_init(i: int, typeAgnostic: str):
    # Spines: left, lowest voice; right, highest voice
    global fInternal
    global fKern
    global fAgnostic1_path
    global fAgnostic1
    global fAgnostic2

    filenameAgnosticInternal = str(i) + extensionAgnosticInternal
    filenameKern = str(i) + extensionKern

    fInternal = open(os.path.join(internal_path, filenameAgnosticInternal), "w")

    fKern = open(os.path.join(kern_path, filenameKern), "w")
    fKern.write(kern.init + kern.advance)

    fAgnostic1_path = os.path.join(agnostic_path, '-' + filenameAgnosticInternal)
    fAgnostic1 = open(fAgnostic1_path, "w")
    fAgnostic2 = open(os.path.join(agnostic_path, filenameAgnosticInternal), "w")
    agnostic.valueSeparator(typeAgnostic=typeAgnostic)


def write_clef(c):
    global clef
    clef = c

    fInternal.write(clef + internal.advance)
    fKern.write(kern.clefs[clef] + kern.advance)
    fAgnostic.write(agnostic.clefs(clef) + agnostic.advance)


def write_pianoclef(c1, c2):
    global clef1
    global clef2
    clef1 = c1
    clef2 = c2

    fInternal.write(clef1 + internal.not_advance + clef2 + internal.advance)
    fKern.write(kern.clefs[clef1] + kern.not_advance + kern.clefs[clef2] + kern.advance)
    fAgnostic1.write(agnostic.clefs(clef1) + agnostic.advance)
    fAgnostic2.write(agnostic.clefs(clef2) + agnostic.advance)


def write_polyssclef(c):
    global clef1
    global clef2
    clef1 = clef2 = c

    fInternal.write(clef1 + internal.advance)
    fKern.write(kern.clefs[clef1] + kern.advance)
    fAgnostic1.write(agnostic.clefs(clef1) + agnostic.advance)
    fAgnostic2.write(agnostic.clefs(clef2) + agnostic.advance)


def write_key(k):
    global key
    key = k

    fInternal.write(key + internal.advance)
    fKern.write(kern.accidentals[key] + kern.advance)
    fAgnostic.write(agnostic.accidentals(key, clef))


def write_pianokey(k):
    global key
    key = k

    fInternal.write(key + internal.not_advance + key + internal.advance)
    fKern.write(kern.accidentals[key] + kern.not_advance + kern.accidentals[key] + kern.advance)
    fAgnostic1.write(agnostic.accidentals(key, clef1))
    fAgnostic2.write(agnostic.accidentals(key, clef2))


def write_polysskey(k):
    global key
    key = k

    fInternal.write(key + internal.advance)
    fKern.write(kern.accidentals[key] + kern.advance)
    fAgnostic1.write(agnostic.accidentals(key, clef1))
    fAgnostic2.write(agnostic.accidentals(key, clef2))


def write_timeSig(m):
    fInternal.write(m[0] + internal.advance)
    fKern.write(kern.bars[m[0]] + kern.advance)
    fAgnostic.write(agnostic.timeSig(m[0]) + agnostic.advance)


def write_pianotimeSig(m):
    fInternal.write(m[0] + internal.not_advance + m[0] + internal.advance)
    fKern.write(kern.bars[m[0]] + kern.not_advance + kern.bars[m[0]] + kern.advance)
    fAgnostic1.write(agnostic.timeSig(m[0]) + agnostic.advance)
    fAgnostic2.write(agnostic.timeSig(m[0]) + agnostic.advance)


def write_polysstimeSig(m):
    fInternal.write(m[0] + internal.advance)
    fKern.write(kern.bars[m[0]] + kern.advance)
    fAgnostic1.write(agnostic.timeSig(m[0]) + agnostic.advance)
    fAgnostic2.write(agnostic.timeSig(m[0]) + agnostic.advance)


def write_openspine():
    # When musicTexture=='poly-ss'
    fKern.write(kern.spine + kern.advance)


def write_barLine(n):
    fInternal.write('bar' + str(n) + internal.advance)
    fKern.write(kern.barLine(n) + kern.advance)
    fAgnostic.write(agnostic.barLine(n))  # agnostic.advance is handled in the barLine(n) function


def write_pianobarLine(n):
    fInternal.write('bar' + str(n) + internal.not_advance + 'bar' + str(n) + internal.advance)
    fKern.write(kern.barLine(n) + kern.not_advance + kern.barLine(n) + kern.advance)
    fAgnostic1.write(agnostic.barLine(n))
    fAgnostic2.write(agnostic.barLine(n))  # agnostic.advance is handled in the barLine(n) function


def write_symbol(s: list, bar_accidentals: dict):
    # s is the internal representation of the symbol
    # We only have chord as musical groupings
    size = len(s)
    for id, note in enumerate(s):
        fInternal.write(note)
        fKern.write(kern.kern_symbol(line=note, clef=clef, key=key, bar_accidentals=bar_accidentals))
        if id != size - 1:
            fInternal.write(internal.separator)
            fKern.write(kern.separator)
    fInternal.write(internal.advance)
    fKern.write(kern.advance)
    s_ag = agnostic.ag_chord(notes=s) if size > 1 else agnostic.ag_symbol(line=s[0])
    fAgnostic.write(s_ag)
    if size == 1:
        fAgnostic.write(agnostic.advance)


def write_pianosymbol(s1: list, s2: list, bar_accidentals1: dict, bar_accidentals2: dict):
    # s is the internal representation of the symbol
    # We only have chord as musical groupings
    size1, size2 = len(s1), len(s2)
    for id1, note1 in enumerate(s1):
        fInternal.write(note1)
        fKern.write(kern.kern_symbol(line=note1, clef=clef1, key=key, bar_accidentals=bar_accidentals1))
        if id1 != size1 - 1:
            fInternal.write(internal.separator)
            fKern.write(kern.separator)
    fInternal.write(internal.not_advance)
    fKern.write(kern.not_advance)
    for id2, note2 in enumerate(s2):
        fInternal.write(note2)
        fKern.write(kern.kern_symbol(line=note2, clef=clef2, key=key, bar_accidentals=bar_accidentals2))
        if id2 != size2 - 1:
            fInternal.write(internal.separator)
            fKern.write(kern.separator)
    fInternal.write(internal.advance)
    fKern.write(kern.advance)
    s1_ag = agnostic.ag_chord(notes=s1) if size1 > 1 else agnostic.ag_symbol(line=s1[0])
    s2_ag = agnostic.ag_chord(notes=s2) if size2 > 1 else agnostic.ag_symbol(line=s2[0])
    if s1_ag != '':
        fAgnostic1.write(s1_ag)
        if size1 == 1:
            fAgnostic1.write(agnostic.advance)
    if s2_ag != '':
        fAgnostic2.write(s2_ag)
        if size2 == 1:
            fAgnostic2.write(agnostic.advance)


def write_end():
    fInternal.close()
    fKern.write(kern.end_barLine() + kern.advance + kern.end)
    fKern.close()
    fAgnostic.write(agnostic.end_barLine())
    fAgnostic.close()


def write_pianoend():
    fInternal.close()
    fKern.write(kern.end_barLine() + kern.not_advance + kern.end_barLine() +
                kern.advance +
                kern.end + kern.not_advance + kern.end)
    fKern.close()
    fAgnostic1.write(agnostic.end_barLine())
    fAgnostic1.close()
    fAgnostic2.write(agnostic.end_barLine())
    with open(fAgnostic1_path, 'r') as f1:
        fAgnostic2.write('\n' + f1.read())
    fAgnostic2.close()
    os.remove(fAgnostic1_path)


# ----------------------------------------------
# -- DATA PROCESSING FOR END-TO-END OMR -- #

def removefiles(files: list, extension: str):
    del_size = len(files)

    for file in files:
        # INTERNAL
        i_file = file.replace(SVG_FOLDER, INTERNAL_FOLDER)
        i_file = i_file.split(extension)[0] + extensionAgnosticInternal
        os.remove(i_file)
        # KERN
        k_file = file.replace(SVG_FOLDER, KERN_FOLDER)
        k_file = k_file.split(extension)[0] + extensionKern
        os.remove(k_file)
        # AGNOSTIC
        ag_file = file.replace(SVG_FOLDER, AGNOSTIC_FOLDER)
        ag_file = ag_file.split(extension)[0] + extensionAgnosticInternal
        os.remove(ag_file)
        # SVG
        os.remove(file)

    print("{} scores have been deleted".format(del_size))


def preprareforOMR(musicTexture: str, typeAgnostic: str, nstaves: int):
    # Convert HUMDRUM **KERN files to SVG
    imgprocess.kerntosvg(kern_path=kern_path, kern_folder=KERN_FOLDER, svg_folder=SVG_FOLDER, extensionKern=extensionKern)
    # Check for those that do not meet end-to-end conditions (single-staff section or pair-staff section, as appropriate)
    del_files = imgprocess.getMultiStaff(svg_path=svg_path, mode=musicTexture, numStaves=nstaves)
    # Remove those files
    removefiles(files=del_files, extension='.svg')
    # Convert to PNG to be able to crop images to standard size
    imgprocess.svgtopng(svg_path=svg_path, svg_folder=SVG_FOLDER, image_folder=IMAGE_FOLDER,
                        extensionImage=extensionImage)
    # Crop to centered the music information on the image
    crop_path = imgprocess.crop_and_filter(image_path=image_path, extensionImage=extensionImage)
    # Distort to simulate as if they were pictures taken with a camera
    imgprocess.distort(crop_path=crop_path, extensionImage=extensionImage)
    # ----
    # TODO
    # See if there are any measure rest and write its corresponding agnostic token
    # ----
    # Processing agnostic files to add specific music texture features if needed
    agnostic.encoding_reformat(agnostic_path=agnostic_path, mode=musicTexture, typeAgnostic=typeAgnostic)
