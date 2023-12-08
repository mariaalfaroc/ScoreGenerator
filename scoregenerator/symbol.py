# -*- coding: utf-8 -*-

import random

import dictionary

sep = dictionary.separator


def valueMode(musicTexture: str):
    global mode
    mode = musicTexture


def generateSymbol(clef: str, key: str, duration: int, tie: int, prevpitch: int, lastbar: bool, bar_accidentals: dict,
                   id_start: int, id_stop: int):
    res = []

    durations = [list(dictionary.durations), []]
    pos_acc = list(dictionary.typeAcc)
    accidental = ''

    # FIRST, SYMBOL TYPE
    # Ties condition the generation of the next symbol
    # tie == 0 -> there is no tie,
    # tie == 1 -> we start a tie
    # tie == 2 -> there is an open tie,
    # tie == 3 -> we close an open tie
    if tie == 2:
        # If there is an open tie, the symbol to generate can ONLY BE a note
        weights = (100, 0)
    else:
        # If not, there is a 90 % chance of it being a note and a 10 %, being a rest
        weights = (90, 10)
    res.extend(random.choices(["n", "r"], weights=weights, k=1))

    # SECOND, SYMBOL DURATION
    # We distribute the weights of the possible symbol durations taking into account if they fit or not in the bar
    for id, dur in enumerate(durations[0]):
        if dur > duration:
            durations[1].append(0)
        else:
            left = len(durations[0]) - id
            j = id
            while j < len(durations[0]):
                durations[1].append(100 / left)
                j += 1
            break
    res.extend(random.choices(durations[0], weights=durations[1], k=1))

    # THIRD, SYMBOL PITCH
    # If the symbol is a rest, the "pitch" is the previous pitch of the last note that appeared to keep consistency
    pitch = randomWalk(prevpitch, id_start, id_stop) if res[0] == 'n' else prevpitch
    res.append(pitch)

    # FOURTH, SEE IF CHORD
    chord = 0
    if mode != 'poly-ss' and mode != 'mono' and mode != 'piano-mono':
        if res[0] == 'n':
            # 10 % of chance of this note being the first of a chord
            chord = random.choices([0, 1], weights=(90, 10), k=1)[0]

    # FIFTH, SYMBOL ACCIDENTALS
    _hasAcc = random.choices([0, 1], weights=(90, 10), k=1)[0]  # 0 -> No accidental, 1 -> Accidental
    if _hasAcc == 1 and res[0] == 'n':
        noteAbs = dictionary.pitches[clef][pitch]
        keyaccs = dictionary.accidentals[key]

        # If the note is already an accidental in the bar, we can only change the type
        if noteAbs in bar_accidentals:
            for acc in dictionary.typeAcc:
                if acc == bar_accidentals[noteAbs]:
                    pos_acc.remove(acc)
                    accidental = random.choice(pos_acc)
                    break
        # If the note is not an accidental
        else:
            # Check the Key Signature
            if noteAbs[0] in keyaccs[1]:
                pos_acc.remove(keyaccs[0])
            else:
                pos_acc.remove("+")
            accidental = random.choice(pos_acc)
        bar_accidentals[noteAbs] = accidental

    # SIXTH, SEE IF TIE
    # tie == 0 -> there is no tie,
    # tie == 1 -> we start a tie
    # tie == 2 -> there is an open tie,
    # tie == 3 -> we close an open tie
    if res[0] == 'n' and tie == 0 and lastbar is False:
        # The symbol is a note, there is NO OPEN TIE and the current BAR is NOT THE LAST ONE
        # 90 % of chance of having a tie, 10 % of not having it
        res.extend(random.choices([0, 1], weights=(90, 10), k=1))
    elif res[0] == 'n' and tie != 0 and lastbar is True and chord != 1:
        # If we are on the LAST BAR, and the note is NOT THE FIRST NOTE OF A CHORD and there is an OPEN TIE
        # We automatically close the open tie
        res.append(3)
    elif res[0] == 'n' and tie != 0 and chord != 1:
        # If the note is NOT THE FIRST NOTE OF A CHORD and there is an OPEN TIE
        # There is a 80 % of chance of closing the tie and a 20 % of keeping it open
        res.extend(random.choices([3, 2], weights=(80, 20), k=1))
    elif res[0] == 'n' and tie != 0 and chord == 1:
        # The symbol is a NOTE and is THE FIRST ONE OF A CHORD, but there is AN OPEN TIE
        # We automatically keep it open
        res.append(2)
    else:
        # For all the rest, there is no tie
        res.append(0)
    # We add the chord after the tie
    res.append(chord)

    # SEVENTH, SEE IF DOTTED
    dur_dotted = res[1] + res[1] / 2  # dotted_symbol = symbol_dur + symbol_dur / 2
    dot = 0
    if dur_dotted <= duration and res[1] > 0.25:
        # Sixteenth notes are not dotted because thirty-second notes are not considered
        dot = random.choices([0, 1], weights=(90, 10), k=1)[0]
    # If a chord is stating, we must explicitly know if it is dotted
    if chord == 1:
        res.append(dot)

    # EIGHTH, WE PREPARE THE OUTPUT
    # UNTIL NOW, we have
    # res = ["n/r", 4/2/1/0.5/0.25, int_pitch(0-21) if "n" else "-", tie(0-3), chord(0-1), dot(0-1) if chord=1]
    # and we want
    # res = [INTERNAL REPRESENTATION, DURATION, PITCH, TIE, CHORD, DOT IF CHORD]
    out = res[0] + sep + str(res[1])

    if res[0] == 'n':
        # If note, add the pitch
        out += sep + str(res[2]) + sep + accidental

    if dot == 1:
        out += sep + '.'
        if chord != 1:
            # If chord, we do not update the total duration as to later know the duration of each of the chord notes
            res[1] = dur_dotted

    if res[3] == 1:
        # Start tie
        out += sep + '('
        # We update the tie label to open tie
        res[3] = 2
    if res[3] == 3:
        # End tie
        out += sep + ')'
        # We update the tie label to no tie
        res[3] = 0

    res[0] = out

    return res


def generateChord(clef: str, key: str, duration: int, tie: int, prevpitch: int, lastbar: bool, bar_accidentals: dict,
                  dot: int, lastnote: bool):
    # CHORDS HAVE A MAXIMUM OF THREE NOTES due to development's limits
    res = []

    pos_acc = list(dictionary.typeAcc)
    accidental = ''

    # FIRST, SYMBOL TYPE
    # It is ALWAYS going to be a note
    res.append('n')

    # SECOND, SYMBOL DURATION
    # The duration is given by the arg duration
    # It is the same value for all the notes forming the chord
    # It is computed when the first note of the chord is created by the generateSymbol function.
    res.append(duration)

    # THIRD, SYMBOL PITCH
    pitch = pitchChord(prevpitch, lastnote)
    res.append(pitch)

    # FOURTH, SYMBOL ACCIDENTALS
    _hasAcc = random.choices([0, 1], weights=(90, 10), k=1)[0]  # 0 -> No accidental, 1 -> Accidental
    if _hasAcc == 1:
        noteAbs = dictionary.pitches[clef][pitch]
        keyaccs = dictionary.accidentals[key]

        # If the note is already an accidental in the bar, we can only change the type
        if noteAbs in bar_accidentals:
            for acc in dictionary.typeAcc:
                if acc == bar_accidentals[noteAbs]:
                    pos_acc.remove(acc)
                    accidental = random.choice(pos_acc)
                    break
        # If the note is not an accidental
        else:
            # Check the Key Signature
            if noteAbs[0] in keyaccs[1]:
                pos_acc.remove(keyaccs[0])
            else:
                pos_acc.remove("+")
            accidental = random.choice(pos_acc)
        bar_accidentals[noteAbs] = accidental

    # FIFTH, SEE IF TIE
    # tie == 0 -> there is no tie,
    # tie == 1 -> we start a tie
    # tie == 2 -> there is an open tie,
    # tie == 3 -> we close an open tie
    if tie != 0 and lastbar is True and lastnote is True:
        # If we are on the LAST BAR, and the note is THE LAST NOTE OF A CHORD and there is an OPEN TIE
        # We automatically close the open tie
        res.append(3)
    elif tie != 0 and lastbar is False and lastnote is True:
        # If we are NOT on the LAST BAR, the note is THE LAST NOTE OF A CHORD and there is an OPEN TIE
        # There is a 80 % of chance of closing the tie and a 20 % of keeping it open
        res.extend(random.choices([3, 2], weights=(80, 20), k=1))
    elif tie != 0 and lastnote is False:
        # The symbol is a ONE OF THE NOTES OF A CHORD BUT NOT THE LAST and there is AN OPEN TIE
        # We automatically keep it open
        res.append(2)
    else:
        # For all the rest, there is no tie
        res.append(0)

    # SIXTH, WE PREPARE THE OUTPUT
    # UNTIL NOW, we have
    # res = ["n", 4/2/1/0.5/0.25, int_pitch(0-21), tie(0-3)]
    # and we want
    # res = [INTERNAL REPRESENTATION, DURATION, PITCH, TIE]
    out = res[0] + sep + str(res[1]) + sep + str(res[2]) + sep + accidental

    if dot == 1:
        out += sep + '.'
        if lastnote:
            # We do update the total duration when the note is the LAST note of the chord
            res[1] = res[1] + res[1] / 2

    if res[3] == 1:
        # Start tie
        out += sep + '('
        # We update the tie label to open tie
        res[3] = 2
    if res[3] == 3:
        # End tie
        out += sep + ')'
        # We update the tie label to no tie
        res[3] = 0

    res[0] = out

    return res


# Random Walk Method
# Alfaro-Contreras, M., Calvo-Zaragoza, J., & Iñesta, J. M. (2019, July).
# Approaching end-to-end optical music recognition for homophonic scores.
# In Iberian Conference on Pattern Recognition and Image Analysis (pp. 147-158). Springer, Cham.
def randomWalk(prevpitch: int, id_start: int, id_stop: int):
    # id_start, id_stop -> ID for the first and last pitches of the range, respectively

    # 0 -> step back, 1 -> stay on site, 2 -> step forward
    step = random.choice([0, 1, 2])
    # 0 -> absorbing limit, 1 -> reflective limit
    typelimit = random.choice([0, 1])

    if step == 0:
        pitch = prevpitch - 1
        if pitch < id_start:
            pitch = id_start if typelimit == 0 else pitch + 2
    elif step == 1:
        pitch = prevpitch
    else:
        pitch = prevpitch + 1
        if pitch > id_stop:
            pitch = id_stop if typelimit == 0 else pitch - 2

    return pitch


def pitchChord(prevpitch: int, lastnote: bool):
    # The pitches of the one or two remaining notes are computed, by norm, by subtracting two pitches to the previous one
    # When that is not possible due to the limits on the pitch range, we set a series of solutions that are conditioned
    # by 'lastnote', a boolean that indicates if the pitch to generate is the one of the last note of the chord
    if lastnote:
        if prevpitch < 2:
            if prevpitch < 1:
                pitch = prevpitch + 1
            else:
                pitch = prevpitch - 1
        else:
            pitch = prevpitch - 2
    else:
        if prevpitch < 2:
            pitch = prevpitch + 3
        else:
            pitch = prevpitch - 2
    return pitch
