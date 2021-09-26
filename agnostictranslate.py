# -*- coding: utf-8 -*-

import glob
from itertools import groupby

import dictionary

# Agnostic representation:
# shape separator position horizontal_separator shape separator position ...
# Calvo-Zaragoza, J.; Rizo, D.
# End-to-End Neural Optical Music Recognition of Monophonic Scores.
# Appl. Sci. 2018, 8, 606.


# -- AGNOSTIC REPRESENTATION GRAMMAR -- #

# Dictionary where each key is the duration (in terms of quarter notes) of the possible
# musical notes (whole, half, quarter, eighth and sixteenth) and its associated value is
# its corresponding agnostic shape label
durations = {
    "4": "whole",
    "2": "half",
    "1": "quarter",
    "0.5": "eighth",
    "0.25": "sixteenth"
}

# For coding symbols at the same horizontal level (i.e., the x axis of a staff section)
# We use the advance-position character code:
# The horizontal separator is a blank space when two consecutive symbols are on the same horizontal position,
# and a '+' when they are not
# Alfaro-Contreras, M., Calvo-Zaragoza, J., & Iñesta, J. M. (2019, July).
# Approaching end-to-end optical music recognition for homophonic scores.
# In Iberian Conference on Pattern Recognition and Image Analysis (pp. 147-158). Springer, Cham.
advance = ' + '
not_advance = ' '

# Agnostic coding for each of the 22 possibles absolute pitches
positions = ["S-3", "L-2", "S-2", "L-1", "S-1", "L0", "S0", "L1", "S1", "L2", "S2", "L3", "S3", "L4", "S4", "L5", "S5",
             "L6", "S6", "L7", "S7", "L8"]
# S2 (second staff-space) is the last position on which notes stems point up
# From than point on (L3, S3, ...), stems point down
stem_sep = positions.index("S2")

# Time signature is always represented in the same style:
# Ex.: 3/4 -> digit.3 separator L4 horizontal_separator digit.4 separator L2
m_c = ["digit", "L4", "L2"]

# Dictionary where each key is one of the possible Clefs and its associated value is a list of 4 elements where:
# - (1) agnostic shape label of the Clef
# - (2) agnostic position label of the Clef
# - (3) ordered list of agnostic position labels for the possible Sharp keys
# - (4) ordered list of agnostic position labels for the possible Flat keys
clefsdic = {
    "clefG2": ["clef.G", "L2", ["L5", "S3", "S5", "L4", "S2", "S4", "L3"], ["L3", "S4", "S2", "L4", "L2", "S3", "S1"]],
    "clefF4": ["clef.F", "L4", ["L4", "S2", "S4", "L3", "S1", "S3", "L2"], ["L2", "S3", "S1", "L3", "L1", "S2", "S0"]],
    "clefC3": ["clef.C", "L3", ["S4", "L3", "L5", "S3", "L2", "L4", "S2"], ["S2", "L4", "L2", "S3", "S1", "L3", "L1"]],
    "clefC1": ["clef.C", "L1", ["S2", "L1", "L3", "S1", "S3", "L2", "L4"], ["L4", "L2", "S3", "S1", "L3", "L1", "S2"]],
    "clefG1": ["clef.G", "L1", ["L4", "S2", "S4", "L3", "S1", "S3", "L2"], ["L2", "S3", "S1", "L3", "L1", "S2", "S0"]],
    "clefC2": ["clef.C", "L2", ["S3", "L2", "L4", "S2", "S4", "L3", "L5"], ["S1", "L3", "L1", "S2", "L4", "L2", "S3"]],
    "clefC4": ["clef.C", "L4", ["L2", "L4", "S2", "S4", "L3", "L5", "S3"], ["S3", "L5", "L3", "S4", "S2", "L4", "L2"]]
}
# Three possible accidentals: sharps, flats or naturals. This dictionary contains as keys those three accidentals
# and their corresponding values are a list with its agnostic shape label and the number element of the list of the
# previous dictionary (it points to the ordered list of agnostic position labels for the possible accidental keys)
# As expected, for the natural accidental the aforementioned number is None
accidentalsdic = {"#": ["accidental.sharp", 2],
                  "-": ["accidental.flat", 3],
                  "+": ["accidental.natural", None]}

# Slurs have both start and end labels
# Start -> slur.start separator position_of_the_associated_note
# End -> slur.end separator position_of_the_associated_note
slurs = {"(": "slur.start",
         ")": "slur.end"}


# -- AGNOSTIC REPRESENTATION GRAMMAR -- #


def valueSeparator(typeAgnostic: str):
    global separator
    if typeAgnostic == 'standard':
        # Standard agnostic type -> shape:position
        separator = ':'
    elif typeAgnostic == 'split':
        # Split agnostic type -> shape position
        separator = ' '


def clefs(c: str):
    # Ex.: For CLEFG2 -> "clef.G separator L2"
    return clefsdic[c][0] + separator + clefsdic[c][1]


def timeSig(m: str):
    c_list = list(m)
    # Ex.: c = "M4/4" -> list(c) = ['M', '4', '/', '4']
    # digit.4 separator L4 not_advance digit.4 separator L2
    return m_c[0] + '.' + c_list[1] + separator + m_c[1] + not_advance + m_c[0] + '.' + c_list[3] + separator + m_c[2]


def barLine(n: int):
    if n == 1:
        # After the Time Signature there is an invisible bar line
        return ''
    else:
        return 'verticalLine' + separator + 'L1' + advance


def end_barLine():
    return 'verticalLine' + separator + 'L1' + advance + 'thickbarline' + separator + 'L1'


def accidentals(k: str, c: str):
    # k == Key Signature
    # c == Clef
    res = ''
    # Get the accidental Key Signature type, either "#" (sharp) or "-" (flat)
    acc_type = dictionary.accidentals[k][0]
    if k != "cM":
        # Get the agnostic shape label: "accidental.sharp" or "accidental.flat"
        shape = accidentalsdic[acc_type][0]
        # Get the number of accidentals of the key
        times = len(dictionary.accidentals[k][1])
        # Get the agnostic position label of the accidentals present in the key
        position = accidentalsdic[acc_type][1]
        for i in range(times):
            res += shape
            res += separator
            res += clefsdic[c][position][i]
            res += advance
    return res


def ag_symbol(line: str):
    res = ''
    x = line.split()

    # If symbol is either a note or a rest
    if x[0] == 'n' or x[0] == 'r':

        # Get agnostic shape label: first, type and second, duration
        res = 'note.' if x[0] == 'n' else 'rest.'
        res += durations[x[1]]

        # Get the agnostic position label for the note or the rest
        if x[0] == 'n':
            noteAbs = int(x[2])
            res += '_down' if noteAbs > stem_sep else '_up'
            pos = positions[noteAbs]
        else:
            # Rests are always on the third staff-line, except for the whole rest
            pos = 'L4' if durations[x[1]] == 'whole' else 'L3'
        res += separator + pos

        # If slur, add it
        for s in slurs.keys():
            if s in x:
                # They appear at the same horizontal position than the note -> horizontal_separator == not_advance
                slur = slurs[s] + separator + pos
                if int(x[2]) > stem_sep:
                    # If the stem of the note points down, the slur goes above the note
                    res = slur + not_advance + res
                else:
                    # If the stem of the note points up, the slur goes below the note
                    res += not_advance + slur
                break

        # If dotted, write it
        if '.' in x:
            # Dots ALWAYS go on a staff-space
            # If a dotted note is placed on a staff-line, the dot appears in the above space
            pos_dot = 'S' + pos[1:] if pos[0] == 'L' else pos
            res += advance + 'dot' + separator + pos_dot

        # If accidental, write it
        for acc in accidentalsdic.keys():
            if acc in x:
                # Accidentals appear BEFORE the associated note
                res = accidentalsdic[acc][0] + separator + pos + advance + res
                break
        return res

    return res


def ag_chord(notes: list):
    # notes is a list whose elements are the internal representation of the different notes of a chord
    # Ex.: notes = ['n 1 14 ', 'n 1 12 ', 'n 1 10 #']
    res = ''

    numDownStems = 0
    _hasStartSlur = False
    _hasEndSlur = False
    pitches = []
    accidentals = []
    dots = []

    # First, order the notes of the chord from highest to lowest pitch
    p = [int(note.split()[2]) for note in notes]
    ids_order = sorted(range(len(p)), key=p.__getitem__, reverse=True)
    notes_ordered = [notes[id] for id in ids_order]

    # Go through each note
    for index, note in enumerate(notes_ordered):
        x = note.split()
        # Since it is a chord, the symbol is always a note
        if x[0] == 'n':

            # Get agnostic shape label: first, type and second, duration
            res += 'note.'
            res += durations[x[1]]

            # Get the agnostic position label for the note
            noteAbs = int(x[2])
            pitches.append(noteAbs)
            # Determine the direction of the beam and save it to later substitute it for the final direction
            if noteAbs > stem_sep:
                # The chord's stem depends on the amount pointed-down-stems when the notes' chord are treated individually
                numDownStems += 1
                res += '_down'
            else:
                res += '_up'
            pos = positions[noteAbs]
            res += separator + pos

            # If dotted, save it -> Ex.: note note note advance dot dot dot
            if '.' in x:
                # Dots ALWAYS go on a staff-space
                # If a dotted note is placed on a staff-line, the dot appears in the above space
                pos_dot = 'S' + pos[1:] if pos[0] == 'L' else pos
                dots.append('dot' + separator + pos_dot)

            # Horizontal separator between notes' chord
            if index != len(notes) - 1:
                res += not_advance

            # If slur, save if start or end of it
            if '(' in x:
                _hasStartSlur = True
            if ')' in x:
                _hasEndSlur = True

            # If accidental, save type to later write it in the proper order
            accidentals.append('')
            for acc in accidentalsdic.keys():
                if acc in x:
                    accidentals.pop()
                    accidentals.append((accidentalsdic[acc][0] + separator + pos))
                    break

    # Determine final direction of the chord stem and the position of the slur if appropriate
    if numDownStems > 1:
        # The direction of the chord stem is down
        res = res.replace("_up", "_down")
        if _hasStartSlur or _hasEndSlur:
            # If the stem of the note points down, the slur goes above the note
            maxnoteAbs = max(pitches)
            pos = positions[maxnoteAbs]
            slur = 'slur.start' if _hasStartSlur else 'slur.end'
            res = slur + separator + pos + not_advance + res
    elif numDownStems <= 1:
        # The direction of the chord stem is up
        res = res.replace("_down", "_up")
        if _hasStartSlur or _hasEndSlur:
            # If the stem of the note points up, the slur goes below the note
            minnoteAbs = min(pitches)
            pos = positions[minnoteAbs]
            slur = 'slur.start' if _hasStartSlur else 'slur.end'
            res += not_advance + slur + separator + pos
    res += advance

    # If dotted, write it
    if len(dots) > 0:
        res += not_advance.join(dots)
        res += advance

    # If accidental, write it
    accidentals = list(filter(''.__ne__, accidentals))
    if len(accidentals) > 0:
        # First, order accidentals from lowest to highest pitch
        accidentals.reverse()
        if len(accidentals) > 2:
            # If three accidentals -> mid pitch, low pitch, high pitch
            accidentals[0], accidentals[1] = accidentals[1], accidentals[0]
        res = advance.join(accidentals) + advance + res

    return res


# -- AGNOSTIC FILTERING  -- #
# About music notation of rest:
# 1) If a rest (dotted or not) occupies the full bar, it is a measure rest, i.e., a whole rest
# 2) When there are several rests in a row (bearing in mind that the rest's duration equals measure's duration),
# the musical notation of putting one rest after another is broken in order to use a series of symbols,
# called measure rest
# When we have more than 4 rests in a row, they follow the same pattern
# Ex.: If we have 10 rest in a row:
# 'multirest:L3' + advance + 'digit.1:S5' + advance + 'digit.0:S5' + advance
def measure_rest():
    return {1: 'rest.whole' + separator + 'L4' + advance,
            2: 'digit.2' + separator + 'S5' + not_advance + 'rest.breve' + separator + 'L3' + advance,
            # TODO Ask about this
            # 3: 'rest.breve' + separator + 'L3' + advance +,
            4: 'digit.4' + separator + 'S5' + not_advance + 'rest.longa' + separator + 'L2' + advance,
            5: 'multirest' + separator + 'L3' + advance + 'digit.X' + separator + 'S5'
            }


# TODO
def rest_filter(agnostic_path: str, typeAgnostic: str):
    dic_measure_rest = measure_rest()
    advance_flatten = str(advance.split()[0])

    agfiles = glob.glob(agnostic_path + '/*')
    for agfile in agfiles:
        with open(agfile, 'r') as f:
            data = f.readlines()
        spines = [list(g) for _, g in groupby(data, key='\n'.__ne__)]
        for spine in spines:
            linedata_og = spine[0].split(not_advance)
            _hasbar = False
            seq_to_replace = []
            final_seqs_to_replace = []
            for id, token in enumerate(linedata_og):
                if 'verticalLine' in token and not _hasbar:
                    # We enter a measure
                    _hasbar1 = True
                    seq_to_replace += token
                    continue
                elif (('dot.' or advance_flatten in token) or (token in positions)) and _hasbar:
                    # Two situations fall under this condition:
                    # 1) The very next thing we find after the barline is the advance symbol or a position token, it depends on the agnostic separator
                    # 2) So far, the only thing we have in the measure are rests (they might be dotted)
                    seq_to_replace += token
                    continue
                elif 'rest.' in token and _hasbar:
                    # After, the advance we can find either symbols related to note notation or rest
                    # We find a rest, we continue
                    seq_to_replace += token
                    continue
                elif 'verticalLine' in token and _hasbar:
                    # We have arrived to the end of the current measure
                    # We have so far one measure rest
                    # Let's keep searching to see if we have measure rests in a row
                    seq_to_replace += token
                    final_seqs_to_replace.append(seq_to_replace)
                    continue
                else:
                    # After, the advance we can find either symbols related to note notation or rest
                    # We do not find a rest, we stop searching until the next measure
                    # That is, this measure is discarded
                    _hasbar = False
                    seq_to_replace.clear()
                    continue

            for seq in final_seqs_to_replace:
                new_seq = 'verticalLine' + separator + 'L1' + advance

                # Get the number of measure rests
                # One measure -> Two barlines
                c = seq.count('verticalLine')
                c = c - 1

                new_seq = dic_measure_rest[c] if c < 5 else dic_measure_rest[5]
                new_seq += 'verticalLine' + separator
                new_seq += 'L1' if typeAgnostic == 'standard' else ''
                if c >= 5:
                    new_seq.replace('digit.X', 'digit.' + str(c))

                # TODO
                # Overwrite new sequence

    return


# When we have music textures whose agnostic encoding is formed by more than one sequence
# we need to add specific staff or voice features to each symbol to identify each staff or/and voice
def encoding_reformat(agnostic_path: str, mode: str, typeAgnostic: str):
    token_sep = advance
    token_sep = token_sep.strip()  # Remove any whitespaces as they are removed when lines are splitted
    if mode == 'mono' or mode == 'homo':
        return
    elif mode == 'poly-ss' or mode == 'piano-mono' or mode == 'piano-homo':
        new_agfeature = ''
        if mode == 'poly-ss':
            new_agfeature = 'voice.'  # shape:position:voice
        elif mode == 'piano-mono' or mode == 'piano-homo':
            new_agfeature = 'hand.'  # shape:position:hand
        agfiles = glob.glob(agnostic_path + '/*')
        for agfile in agfiles:
            with open(agfile, 'r') as f:
                data = f.readlines()
                voice1 = data[0].split()
                voice2 = data[1].split()
            with open(agfile, 'w') as f:
                if typeAgnostic == 'standard':
                    new_voice1 = [token + separator + new_agfeature + '1' if token != token_sep else token for token in
                                  voice1]
                    new_voice2 = [token + separator + new_agfeature + '2' if token != token_sep else token for token in
                                  voice2]
                    voice1, voice2 = new_voice1, new_voice2
                elif typeAgnostic == 'split':
                    pos1 = [id for id, token in enumerate(voice1) if token in positions]
                    pos2 = [id for id, token in enumerate(voice2) if token in positions]
                    for i in range(len(pos1)):
                        voice1.insert(pos1[i] + i + 1, new_agfeature + '1')
                    for i in range(len(pos2)):
                        voice2.insert(pos2[i] + i + 1, new_agfeature + '2')
                f.write(' '.join(voice1) + '\n' + ' '.join(voice2))
    # elif mode == '..
    # If we were to have a poly-piano music texture:
    # shape:position:voice:hand
    return
