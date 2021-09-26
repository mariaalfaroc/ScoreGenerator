# -*- coding: utf-8 -*-

import dictionary


# -- HUMDRUM **KERN REPRESENTATION GRAMMAR -- #
# Dictionaries for the internal to **kern translation
# https://www.humdrum.org/guide/

# Each note except for chords is represented on a different line
# We use separators for that
init = '**kern'
advance = '\n'
not_advance = '\t'
separator = ' '
spine = '*^'
end = '*-'

clefs = {
    "clefG2": "*clefG2",
    "clefF4": "*clefF4",
    "clefC3": "*clefC3",
    "clefC1": "*clefC1",
    "clefG1": "*clefG1",
    "clefC2": "*clefC2",
    "clefC4": "*clefC4"
}

accidentals = {
    "cM": "*k[]",
    "gM": "*k[f#]",
    "dM": "*k[f#c#]",
    "aM": "*k[f#c#g#]",
    "eM": "*k[f#c#g#d#]",
    "bM": "*k[f#c#g#d#a#]",
    "fsM": "*k[f#c#g#d#a#e#]",
    "csM": "*k[f#c#g#d#a#e#b#]",
    "fM": "*k[b-]",
    "bfM": "*k[b-e-]",
    "efM": "*k[b-e-a-]",
    "afM": "*k[b-e-a-d-]",
    "dfM": "*k[b-e-a-d-g-]",
    "gfM": "*k[b-e-a-d-g-c-]",
    "cfM": "*k[b-e-a-d-g-c-f-]"
}

bars = {
    "M4/4": "*M4/4",
    "M3/4": "*M3/4",
    "M2/2": "*M2/2",
    "M2/4": "*M2/4",
    "M6/8": "*M6/8",
    "M12/8": "*M12/8",
    "M9/8": "*M9/8",
    "M5/4": "*M5/4"
}

durations = {
    "4": "1",
    "2": "2",
    "1": "4",
    "0.5": "8",
    "0.25": "16"
}


# -- HUMDRUM **KERN REPRESENTATION GRAMMAR -- #


def barLine(n: int):
    if n == 1:
        return '=1-'
    else:
        return '=' + str(n)


def end_barLine():
    return '=='


def kern_symbol(line, clef: str, key: str, bar_accidentals: dict):
    res = '.'
    x = line.split()

    # If symbol is either a note or a rest
    if x[0] == 'n' or x[0] == 'r':

        # First, duration
        res = durations[x[1]]

        # If dotted, write it
        if '.' in x:
            res += '.'

        # Symbol is either a note,
        if x[0] == 'n':

            # Get the pitch
            noteAbs = dictionary.pitches[clef][int(x[2])]
            # In **kern, pitches are represented through a scheme of upper- and lower-case letters
            if int(noteAbs[1]) < 4:
                res += (4 - int(noteAbs[1])) * noteAbs[0]
            else:
                res += (int(noteAbs[1]) - 4 + 1) * noteAbs[0].lower()

            # If accidental, write it
            # In **kern, accidentals are ALWAYS codified even if they are not graphically present on the score
            if '#' in x:
                res += '#'
            elif '-' in x:
                res += '-'
            elif '+' in x:
                res += 'n'
            else:
                keyaccs = dictionary.accidentals[key]
                if noteAbs in bar_accidentals:
                    res += 'n' if bar_accidentals[noteAbs] == '+' else bar_accidentals[noteAbs]
                elif noteAbs[0] in keyaccs[1]:
                    # Naturals are not present in Key Signatures
                    res += keyaccs[0]

            # If slur, add it
            if '(' in x:
                res = '(' + res
                return res
            if ')' in x:
                res += ')'
                return res

        # or a rest
        else:
            res += 'r'
            return res

    return res
